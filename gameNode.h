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

	virtual HRESULT Init() override;			//�ʱ�ȭ ���� �Լ�
	HRESULT Init(bool managerInit);
	virtual void Release() override;			//�޸� ���� �Լ�
	virtual void Update() override;				//���� ���� �Լ�
	virtual void Render() override;				//�׸��� ���� �Լ�

	b2World* GetPhysicsWorld();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

