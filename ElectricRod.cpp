#include "stdafx.h"
#include "ElectricRod.h"
#include "DeadState.h"

ElectricRod::ElectricRod()
{
	_physics = new Physics();
}


ElectricRod::~ElectricRod()
{
}

HRESULT ElectricRod::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character" && _isActive)
		{
			character = (Character *)targetObj->GetPhysics()->GetBody()->GetUserData();
			character->GetPhysics()->SetGravityScale(0);
			character->GetPhysics()->SetIsSensor(true);
			_timer = TIMEMANAGER->getWorldTime();
			
			//character->SetHP(0);
			character->SetSprite(IMAGEMANAGER->FindImage(character->GetName() + "_Electric"));
		}
	});
	return S_OK;
}

void ElectricRod::Update()
{
	GameObject::Update();

	//스위치롤 통해 꺼진 상태라면 통과 할 수 있게 sensor 처리 
	if(!_isActive)
	{
		this->GetPhysics()->SetIsSensor(true);
	}

	//2초 있다가 릴리즈 
	if (_timer > 0)
	{
		if (TIMEMANAGER->getWorldTime() - _timer > 1.5)
		{
			character->GetParent()->RemoveChild(character);
			_timer = 0;
			character->SetHP(0);
			character->ChangeState(new DeadState(character));

		}
	}
}
