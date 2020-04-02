#pragma once
#include "singletonBase.h"
#include <unordered_map>
#pragma comment(lib, "d2d1.lib")
#include <D2D1.h>
#include <d2d1helper.h>
#pragma comment(lib, "dwrite.lib")
#include <dwrite.h>
#pragma comment(lib, "WindowsCodecs.lib")
#include <wincodec.h>
#include "Image.h"

namespace DefaultBrush
{
	enum Enum
	{
		white, black, yello, red, blue, green, gray, end
	};
}
class ImageManager : public singletonBase<ImageManager>
{
private:
	typedef unordered_map<string, Image*> mapImageList;
	typedef unordered_map<string, Image*>::iterator mapImageIter;
	typedef unordered_map<wstring, IDWriteTextFormat*> mapTextList;
	typedef unordered_map<wstring, IDWriteTextFormat*>::iterator mapTextIter;

private:
	mapImageList		_imageList;

	//다이렉트2D (렌더링 엔진)
	ID2D1Factory*						_d2dFactory;
	ID2D1HwndRenderTarget*				_RenderTarget;

	//WIC (이미지 처리 컴포넌트)
	IWICImagingFactory*					_wicFactory;
	IWICFormatConverter*				_convertedSrcBmp;

	//다이렉트 Write (텍스트 엔진)
	IDWriteFactory*								_dwFactory;
	IDWriteTextLayout*							_dwLayout;
	ID2D1SolidColorBrush*						_dwDefaultBrush[DefaultBrush::end];
	mapTextList									_dwTextFormats;


private:
	HRESULT InitRT();
	ID2D1Bitmap* createD2DBitmapFromFile(wstring file);
	HRESULT DWInit();
	HRESULT addTextFormat(wstring fontname, float size);

public:
	ImageManager()
	{
		_d2dFactory = nullptr;
		_RenderTarget = nullptr;
		_wicFactory = nullptr;
		_convertedSrcBmp = nullptr;
	}
	~ImageManager() {}

	HRESULT Init();
	void Release();

	Image* AddImage(string key, wstring file, bool usePixelCollision = FALSE);
	Image* AddFrameImage(string key, wstring file, int maxFrameX, int maxFrameY, bool usePixelCollision = FALSE);
	void DeleteImage(string key);
	void DeleteAll();
	Image* FindImage(string key);


	ID2D1HwndRenderTarget*	GetRenderTarget() { return _RenderTarget; }

	void OnResize(UINT width, UINT height);

	void ReloadALL();

	//텍스트 출력 (기본 브러쉬 사용)
	void DrawText(int x, int y, wstring text, int size, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");
	//텍스트 출력 (원하는 색상과 알파값으로 브러쉬 생성해서 출력)
	void DrawText(int x, int y, wstring text, COLORREF rgb, float alpha, int size, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");
	//텍스트 필드 출력 (기본 브러쉬 사용)
	void DrawTextField(int x, int y, wstring text, int size, int width, int height, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");
	//텍스트 필드 출력 (원하는 색상과 알파값으로 브러쉬 생성해서 출력)
	void DrawTextField(int x, int y, wstring text, COLORREF rgb, int size, int width, int height, float alpha = 1.0f, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");


	//==============================================================
	// ## 도형 그리기 함수 ##

	void DrawLine(D2D1::ColorF::Enum color, float alpha, Vector2 start, Vector2 end, float strokeWidth = 1);
	void DrawLine(Vector2 start, Vector2 end, DefaultBrush::Enum defaultBrush = DefaultBrush::black,  float strokeWidth = 1);
	void DrawRectangle(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos = TRUE, float strokeWidth = 1);
	void DrawRectangle(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, bool isRelativePos = TRUE, float strokeWidth = 1);
	void DrawEllipse(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos = TRUE, float strokeWidth = 1);
	void DrawEllipse(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, bool isRelativePos = TRUE, float strokeWidth = 1);
	void FillRectangle(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos = TRUE);
	void FillRectangle(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, bool isRelativePos = TRUE);
	void FillEllipse(RECT rc, D2D1::ColorF::Enum color, float alpha, bool isRelativePos = TRUE);
	void FillEllipse(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, bool isRelativePos = TRUE);
	//==============================================================


};

