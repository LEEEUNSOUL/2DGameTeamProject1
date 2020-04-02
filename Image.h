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
	float				_alpha;			//�̹��� ����

	Vector2				_size;			//�̹��� ũ��
	Vector2				_scale;			//x,y ũ�� Ȯ��,��� ����
	float				_angle;

	tagLoadedImageInfo	_loadInfo;		//�̹��� �ε� ����
	Vector2 center;
	//�ȼ� �浹�� DC
	HDC	_pixelCollisionDC;

	//������ ���� ó���� ���� RECT���� ����
	vector<WICRect>		_frameInfo;
	int					_maxFrameX;
	int					_maxFrameY;

	//����
	bool _flipX;
	bool _flipY;

	//ī�޶�
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

	//�ʱ�ȭ
	HRESULT Init(ID2D1Bitmap* bitmap, tagLoadedImageInfo loadinfo);
	HRESULT Init(ID2D1Bitmap* bitmap, tagLoadedImageInfo loadinfo, int maxframeX, int maxframeY);

	void Release();

	//����
	void Render(int x, int y, Pivot::Enum pivot = Pivot::LEFT_TOP, bool isUI = TRUE);
	void FrameRender(int x, int y, int frameX, bool isUI = TRUE, Pivot::Enum pivot = Pivot::LEFT_TOP);


	//�ɼ�
	void SetSize(Vector2 size) { _size = size; }
	void SetAlpha(float alpha) { _alpha = alpha; };
	void SetScale(float scale) { _scale = Vector2(scale, scale); };
	void SetAngle(float rad) { _angle = rad * RAD_TO_DEG; };			// ���� -> ��׸��� ��ȯ 
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


	//���� 
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


	//�ȼ��浹��
	void SetPixelDC(HDC pixelDC) { _pixelCollisionDC = pixelDC; }
	//COLORREF GetPixel(int imageLeft, int imageTop, int x, int y);
	//COLORREF GetPixel(int x, int y);
	HDC GetPixelDC() { return _pixelCollisionDC; }

	//���� 
	void SetUpdateAnimation(bool updateAnimation ) { _updateAnimation = updateAnimation; }


public:
	static void setRT(ID2D1HwndRenderTarget* rt) { _RT = rt; };


private:

	D2D1::Matrix3x2F SetupRender(int x, int y);
	Vector2 GetPivotPosition(int x, int y, Pivot::Enum pivot);

};

