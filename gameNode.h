#pragma once
#include "Object.h"
#include "image.h"
#include <string>

class b2World;
class gameNode : public Object
{
protected:
	HDC _hdc;
	bool _managerInit;
	b2World* _physicsWorld;
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT Init() override;			//초기화 전용 함수
	HRESULT Init(bool managerInit);
	virtual void Release() override;			//메모리 해제 함수
	virtual void Update() override;				//연산 전용 함수
	virtual void Render() override;				//그리기 전용 함수

	b2World* GetPhysicsWorld();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

