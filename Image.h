#pragma once
#define RAD_TO_DEG 180/PI

namespace Pivot
{
	enum Enum
	{
		LEFT_TOP, CENTER, BOTTOM, TOP
	};
}

class Image
{
public:
	struct tagLoadedImageInfo
	{
		string key;
		wstring directory;
	};
private:
	static ID2D1HwndRenderTarget* _RT;

	ID2D1Bitmap*		_bitmap;
	float				_alpha;			//이미지 투명도

	Vector2				_size;			//이미지 크기
	Vector2				_scale;			//x,y 크기 확대,축소 배율
	float				_angle;

	tagLoadedImageInfo	_loadInfo;		//이미지 로드 정보
	Vector2 center;
	//픽셀 충돌용 DC
	HDC	_pixelCollisionDC;

	//프레임 렌더 처리를 위한 RECT정보 저장
	vector<WICRect>		_frameInfo;
	int					_maxFrameX;
	int					_maxFrameY;

	//반전
	bool _flipX;
	bool _flipY;

	//카메라
	float _cameraX;
	float _cameraY;

	bool _updateAnimation = true;


public:
	Image()
	{
		_bitmap = nullptr;
		_pixelCollisionDC = nullptr;
		_flipX = false;
		_flipY = false;
	}
	virtual ~Image() {}

	//초기화
	HRESULT Init(ID2D1Bitmap* bitmap, tagLoadedImageInfo loadinfo);
	HRESULT Init(ID2D1Bitmap* bitmap, tagLoadedImageInfo loadinfo, int maxframeX, int maxframeY);

	void Release();

	//랜더
	void Render(int x, int y, Pivot::Enum pivot = Pivot::LEFT_TOP, bool isUI = TRUE);
	void FrameRender(int x, int y, int frameX, bool isUI = TRUE, Pivot::Enum pivot = Pivot::LEFT_TOP);


	//옵션
	void SetSize(Vector2 size) { _size = size; }
	void SetAlpha(float alpha) { _alpha = alpha; };
	void SetScale(float scale) { _scale = Vector2(scale, scale); };
	void SetAngle(float rad) { _angle = rad * RAD_TO_DEG; };			// 라디안 -> 디그리로 변환 
	void SetFlip(bool flipX, bool flipY)
	{
		_flipX = flipX;
		_flipY = flipY;
	}
	void SetCamera(float cameraX, float cameraY)
	{
		_cameraX = cameraX;
		_cameraY = cameraY;
	}


	void ResetRenderOption();


	//게터 
	int GetMaxFrameX() { return _maxFrameX; }
	int GetMaxFrameY() { return _maxFrameY; }
	UINT GetWidth() { return (_bitmap->GetPixelSize().width); }
	UINT GetHeight() { return _bitmap->GetPixelSize().height; }
	Vector2 GetFrameSize(int frame) { return Vector2(_frameInfo[frame].Width, _frameInfo[frame].Height); }
	float GetCameraX() { return _cameraX; }
	float GetCameraY() { return _cameraY; }
	bool GetFlipX() { return _flipX; }
	bool GetUpdateAnimation() { return _updateAnimation; }

	bool IsFrameImage()
	{
		if (_frameInfo.size() == 1)
			return false;
		else if (_frameInfo.size() > 1)
			return true;
	}

	tagLoadedImageInfo GetLoadInfo() { return _loadInfo; }


	//픽셀충돌용
	void SetPixelDC(HDC pixelDC) { _pixelCollisionDC = pixelDC; }
	//COLORREF GetPixel(int imageLeft, int imageTop, int x, int y);
	//COLORREF GetPixel(int x, int y);
	HDC GetPixelDC() { return _pixelCollisionDC; }

	//세터 
	void SetUpdateAnimation(bool updateAnimation ) { _updateAnimation = updateAnimation; }


public:
	static void setRT(ID2D1HwndRenderTarget* rt) { _RT = rt; };


private:

	D2D1::Matrix3x2F SetupRender(int x, int y);
	Vector2 GetPivotPosition(int x, int y, Pivot::Enum pivot);

};

