#pragma once
#include "singletonBase.h"
#include "timer.h"

class TimeManager : public singletonBase <TimeManager>
{
private:
	timer* _timer;
	float lockFPS = 60;
public:
	TimeManager();
	~TimeManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetFPS(float fps) { lockFPS = fps; }
	float GetFPS() { return lockFPS; }

	//Delta타임
	inline float getElapsedTime() const { return _timer->getElapsedTime(); }

	//World타임
	inline float getWorldTime() const { return _timer->getWorldTime(); }

};

