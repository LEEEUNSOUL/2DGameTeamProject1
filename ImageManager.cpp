#include "stdafx.h"
#include "ImageManager.h"
#include "Matrix3x3.h"
#include "Transform.h"
HRESULT ImageManager::Init()
{
	//D2D 팩토리 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);

	//WIC 팩토리 생성
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	InitRT();

	//텍스트 
	DWInit();
	addTextFormat(L"맑은고딕", 20);

	return S_OK;
}

void ImageManager::Release()
{

	DeleteAll();
	SafeRelease(_RenderTarget);
	SafeRelease(_d2dFactory);
	SafeRelease(_wicFactory);

	for (int i = 0; i < DefaultBrush::end; ++i)
		_dwDefaultBrush[i]->Release();

}

Image * ImageManager::AddImage(string key, wstring file, bool usePixelCollision)
{
	Image* img = FindImage(key);

	if (img)
		return img;

	ID2D1Bitmap* bitmap = createD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::tagLoadedImageInfo loadInfo = { key, file };
		img = new Image;
		img->Init(bitmap, loadInfo);
		_imageList.insert(make_pair(key, img));
		return img;
	}


	return nullptr;
}

Image * ImageManager::AddFrameImage(string key, wstring file, int maxFrameX, int maxFrameY, bool usePixelCollision)
{
	Image* img = FindImage(key);

	if (img)  return img;

	ID2D1Bitmap* bitmap = createD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::tagLoadedImageInfo loadInfo = { key, file };
		img = new Image;
		img->Init(bitmap, loadInfo, maxFrameX, maxFrameY);
		_imageList.insert(make_pair(key, img));
		return img;

	}


	return nullptr;
}

void ImageManager::DeleteImage(string key)
{
	mapImageIter iter = _imageList.find(key);
	if (iter != _imageList.end())
	{
		Image* img = iter->second;
		img->Release();
		delete img;
		img = NULL;
	}
}

void ImageManager::DeleteAll()
{
	for (mapImageIter iter = _imageList.begin(); iter != _imageList.end(); ++iter)
	{
		iter->second->Release();
		delete iter->second;
		iter->second = NULL;
	}
	_imageList.clear();

}

Image* ImageManager::FindImage(string key)
{
	mapImageIter iter = _imageList.find(key);
	if (iter != _imageList.end())
	{
		return iter->second;
	}
	return NULL;
}

void ImageManager::OnResize(UINT width, UINT height)
{
	if (_RenderTarget != NULL)
	{
		HRESULT hr = _RenderTarget->Resize(D2D1::SizeU(width, height));
		if (hr != S_OK)
		{
			ReloadALL();
		}
	}
}

void ImageManager::ReloadALL()
{
	//디바이스 로스트 상황 발생 시 리소스 모두 해제 후 다시 로드해야 함.
	//1. 현재 로드된 리소스들의 로드 정보를 수집한다.
	vector<Image::tagLoadedImageInfo> _loadInfoList;
	auto iter = _imageList.begin();
	for (; iter != _imageList.end(); ++iter)
	{
		_loadInfoList.emplace_back(iter->second->GetLoadInfo());
	}

	//2. 리소스 모두 해제
	DeleteAll();
	SafeRelease(_RenderTarget);

	//3. 모든 리소스 다시 로드
	InitRT();
	for (UINT i = 0; i < _loadInfoList.size(); ++i)
	{
		this->AddImage(_loadInfoList[i].key, _loadInfoList[i].directory);
	}

}

HRESULT ImageManager::InitRT()
{
	RECT rc;
	GetClientRect(_hWnd, &rc);

	D2D1_RENDER_TARGET_PROPERTIES dxRTProperties = D2D1::RenderTargetProperties();
	D2D1_SIZE_U dxSize = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	//렌더타겟 생성
	_d2dFactory->CreateHwndRenderTarget(dxRTProperties,
		D2D1::HwndRenderTargetProperties(_hWnd, dxSize),
		&_RenderTarget);

	//이미지 클래스에 RT 연결
	Image::setRT(_RenderTarget);

	return S_OK;
}

ID2D1Bitmap * ImageManager::createD2DBitmapFromFile(wstring file)
{
	//1. 디코더를 생성한다.
	IWICBitmapDecoder* ipDecoderPtr = nullptr;
	_wicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &ipDecoderPtr);

	//2. 디코더에서 프레임을 얻는다.
	IWICBitmapFrameDecode*	ipFramePtr = nullptr;
	ipDecoderPtr->GetFrame(0, &ipFramePtr);

	//3. 프레임을 기반으로 포맷 컨버터를 만든다.
	SafeRelease(_convertedSrcBmp);
	_wicFactory->CreateFormatConverter(&_convertedSrcBmp);

	_convertedSrcBmp->Initialize(ipFramePtr,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);

	//4. 컨버트된 데이터를 기반으로 실제 Direct2D용 비트맵을 만든다.
	ID2D1Bitmap* ipResult = nullptr;
	_RenderTarget->CreateBitmapFromWicBitmap(_convertedSrcBmp,
		nullptr,
		&ipResult);


	SafeRelease(ipDecoderPtr);
	SafeRelease(ipFramePtr);

	return ipResult;
}

HRESULT ImageManager::DWInit()
{
	HRESULT hr;

	_dwFactory = NULL;

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*&_dwFactory),
		(IUnknown**)&_dwFactory
	);
	if (FAILED(hr))
		return hr;

	//기본 브러시 생성
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &_dwDefaultBrush[DefaultBrush::black]);
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &_dwDefaultBrush[DefaultBrush::white]);
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &_dwDefaultBrush[DefaultBrush::yello]);
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &_dwDefaultBrush[DefaultBrush::red]);
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &_dwDefaultBrush[DefaultBrush::blue]);
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &_dwDefaultBrush[DefaultBrush::green]);
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &_dwDefaultBrush[DefaultBrush::gray]);

	return hr;
}

HRESULT ImageManager::addTextFormat(wstring fontname, float size)
{
	HRESULT hr;
	IDWriteTextFormat* format = NULL;

	hr = _dwFactory->CreateTextFormat(
		fontname.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"ko",
		&format
	);

	this->_dwTextFormats.insert(make_pair(fontname, format));

	if (FAILED(hr))
		return hr;

	return hr;
}
void ImageManager::DrawText(int x, int y, wstring text, int size, DefaultBrush::Enum defaultBrush, DWRITE_TEXT_ALIGNMENT align, wstring font)
{
	//텍스트 레이아웃 생성
	_dwFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_dwTextFormats[font],
		text.length()*size,
		size,
		&_dwLayout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	_dwLayout->SetFontSize(size, range);

	_dwLayout->SetTextAlignment(align);

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_RenderTarget->DrawTextLayout(D2D1::Point2F(x, y), _dwLayout, _dwDefaultBrush[defaultBrush]);

	_dwLayout->Release();
}

void ImageManager::DrawText(int x, int y, wstring text, COLORREF rgb, float alpha, int size, DWRITE_TEXT_ALIGNMENT align, wstring font)
{
	//텍스트 레이아웃 생성
	_dwFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_dwTextFormats[font],
		text.length()*size,
		size,
		&_dwLayout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	_dwLayout->SetFontSize(size, range);
	_dwLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	_dwLayout->SetTextAlignment(align);

	//브러쉬 생성
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(rgb, alpha), &brush);

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_RenderTarget->DrawTextLayout(D2D1::Point2F(x, y), _dwLayout, brush);

	brush->Release();
	_dwLayout->Release();
}

void ImageManager::DrawTextField(int x, int y, wstring text, int size, int width, int height, DefaultBrush::Enum defaultBrush, DWRITE_TEXT_ALIGNMENT align, wstring font)
{
	_dwFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_dwTextFormats[font],
		width,
		height,
		&_dwLayout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	_dwLayout->SetFontSize(size, range);

	_dwLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	_dwLayout->SetTextAlignment(align);

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_RenderTarget->DrawTextLayout(D2D1::Point2F(x, y), _dwLayout, _dwDefaultBrush[defaultBrush]);

	_dwLayout->Release();
}

void ImageManager::DrawTextField(int x, int y, wstring text, COLORREF rgb, int size, int width, int height, float alpha, DWRITE_TEXT_ALIGNMENT align, wstring font)
{
	_dwFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_dwTextFormats[font],
		width,
		height,
		&_dwLayout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	_dwLayout->SetFontSize(size, range);

	_dwLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	_dwLayout->SetTextAlignment(align);

	//브러쉬 생성
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(rgb, alpha), &brush);

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_RenderTarget->DrawTextLayout(D2D1::Point2F(x, y), _dwLayout, brush);

	brush->Release();
	_dwLayout->Release();
}

//============================================================================
// ## 선, 도형 렌더링 ##
//============================================================================

void ImageManager::DrawLine(D2D1::ColorF::Enum color, float alpha, Vector2 start, Vector2 end, float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());

	_RenderTarget->DrawLine(D2D1::Point2F(start.x, start.y), D2D1::Point2F(end.x, end.y), brush, strokeWidth);

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	brush->Release();
}
void ImageManager::DrawLine(Vector2 start, Vector2 end, DefaultBrush::Enum defaultBrush, float strokeWidth)
{
	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());

	_RenderTarget->DrawLine(D2D1::Point2F(start.x, start.y), D2D1::Point2F(end.x, end.y), _dwDefaultBrush[defaultBrush], strokeWidth);

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void ImageManager::DrawRectangle(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos, float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());

	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	_RenderTarget->DrawRectangle(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom), brush, strokeWidth);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	brush->Release();
}
void ImageManager::DrawRectangle(RECT rc, DefaultBrush::Enum defaultBrush, bool isRelativePos, float strokeWidth)
{
	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());

	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	_RenderTarget->DrawRectangle(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom), _dwDefaultBrush[defaultBrush], strokeWidth);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void ImageManager::DrawEllipse(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos, float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = rc.left + width * 0.5;
	ellipse.point.y = rc.top + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;


	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());
	_RenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	brush->Release();
}

void ImageManager::DrawEllipse(RECT rc, DefaultBrush::Enum defaultBrush, bool isRelativePos, float strokeWidth)
{
	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = rc.left + width * 0.5;
	ellipse.point.y = rc.top + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;


	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());

	_RenderTarget->DrawEllipse(&ellipse, _dwDefaultBrush[defaultBrush], strokeWidth);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void ImageManager::FillRectangle(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos)
{
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();



	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());

	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	_RenderTarget->FillRectangle(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom), brush);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	brush->Release();
}
void ImageManager::FillRectangle(RECT rc, DefaultBrush::Enum defaultBrush, bool isRelativePos)
{
	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());
	if (isRelativePos)
	{
		//rc = CAMERA->getRelativeRECT(rc);
	}

	_RenderTarget->FillRectangle(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom), _dwDefaultBrush[defaultBrush]);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void ImageManager::FillEllipse(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos)
{
	ID2D1SolidColorBrush* brush;
	_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = rc.left + width * 0.5;
	ellipse.point.y = rc.top + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;

	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()*result.To_D2D1_Matrix_3x2_F());
	_RenderTarget->FillEllipse(&ellipse, brush);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	brush->Release();
}
void ImageManager::FillEllipse(RECT rc, DefaultBrush::Enum defaultBrush, bool isRelativePos)
{
	//if (isRelativePos)
	//{
	//	rc = CAMERA->getRelativeRECT(rc);
	//}

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = rc.left + width * 0.5;
	ellipse.point.y = rc.top + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;

	Transform* cameraTransform = CameraManager::getSingleton()->GetTransfrom();
	Matrix3x3 scale =
		Matrix3x3
		(
			cameraTransform->GetScale(), 0, 0,
			0, cameraTransform->GetScale(), 0,
			0, 0, 1
		);

	Matrix3x3 rotate =
		Matrix3x3
		(
			cos(cameraTransform->GetRotation()), -sin(cameraTransform->GetRotation()), 0,
			sin(cameraTransform->GetRotation()), cos(cameraTransform->GetRotation()), 0,
			0, 0, 1
		);

	Matrix3x3 translate =
		Matrix3x3
		(
			1, 0, 0,
			0, 1, 0,
			cameraTransform->GetPosition().x, cameraTransform->GetPosition().y, 1
		);

	Matrix3x3 result = scale * rotate * translate;

	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity() * result.To_D2D1_Matrix_3x2_F());
	_RenderTarget->FillEllipse(&ellipse, _dwDefaultBrush[defaultBrush]);
	_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
