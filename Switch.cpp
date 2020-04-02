#include "stdafx.h"
#include "Switch.h"
#include "Door.h"


Switch::Switch()
{
	_physics = new Physics();
}


Switch::~Switch()
{

}

HRESULT Switch::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		_inArea = true;
	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		_inArea = false;
	});

	return S_OK;
}

void Switch::Update()
{
	GameObject::Update();

	//스위치 1
	if (_inArea && KEYMANAGER->IsOnceKeyDown('S') && _name == "Switch1")
	{
		ElectricRod* rod =(ElectricRod*) GetParent()->GetChildByName("ElectricRod");
		rod->SetSprite(IMAGEMANAGER->FindImage("ElectricRodEnd"));
		rod->SetActive(false);
		_isPressed1 = true;
	}

	//스위치 2
	if (_inArea && KEYMANAGER->IsOnceKeyDown('S') && _name == "Switch2")
	{
		_doorBottom2->SetIsDoor2Opening(true);
		_doorTop2->SetIsDoor2Opening(true);
		_isPressed2 = true;
	}

	//눌림 이펙트 
	if (_isPressed1 && _name == "Switch1" && _timer <40)
	{
		_timer++;
		this->SetSprite(IMAGEMANAGER->FindImage("Switch_Pressed"));
	}
	else if (_isPressed2 &&  _name == "Switch2" && _timer <40)
	{
		_timer++;
		this->SetSprite(IMAGEMANAGER->FindImage("Switch_Pressed"));
	}
	else if (_timer >= 40)
	{
		if (_isPressed1) _isPressed1 = false;
		if (_isPressed2) _isPressed2 = false;
		_timer = 0;
		this->SetSprite(IMAGEMANAGER->FindImage("Switch"));
	}

}
