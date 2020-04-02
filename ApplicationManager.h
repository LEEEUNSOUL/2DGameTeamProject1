#pragma once
class Vector2;
class ApplicationManager
{
private:
	ApplicationManager();

	int frameRate = 60;

	Vector2 resolution;

	int displayFrequency = 60;
	int colorBit = 32;
	bool isFullScreen = false;

	void SetWindowSize();
public:
	static ApplicationManager* GetInstance();

	void SetResolution(int width, int height, bool _isFullScreen);
	void SetResolution(int width, int height);
	Vector2 GetResolution();

	void SetFrameRate(int _frameRate);
	int GetFrameRate();

	void SetDisplayFrequency(int _displayFrequency);
	void SetColorBit(int _colorBit);

	void SetIsFullScreen(bool _isFullScreen);
	bool GetIsFullScreen();

	void UpdateScreen();
	void EnterFullScreen();
	void ExitFullScreen();
};

