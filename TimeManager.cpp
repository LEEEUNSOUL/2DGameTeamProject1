#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
	: _timer(NULL)
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init()
{
	_timer = new timer;
	_timer->Init();

	return S_OK;
}

void TimeManager::Release()
{
	if (_timer != NULL) SAFE_DELETE(_timer);
}

void TimeManager::Update()
{
	if (_timer != NULL)
	{
		_timer->tick(lockFPS);
	}
}

void TimeManager::Render(HDC hdc)
{
	char str[256];
	string frameRate;

	//FPS / WorldTime / ElapsedTime
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG
	{
		sprintf_s(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	{
		sprintf_s(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif


}
