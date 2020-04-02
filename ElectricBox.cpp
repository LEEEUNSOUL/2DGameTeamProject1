#include "stdafx.h"
#include "ElectricBox.h"
#include "Character.h"
#include "DeadState.h"



ElectricBox::ElectricBox()
{
	_physics = new Physics();
}


ElectricBox::~ElectricBox()
{
}

HRESULT ElectricBox::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character")
		{
			character = (Character *)targetObj->GetPhysics()->GetBody()->GetUserData();
			character->SetDeltaTime(0.5);
			_timer = TIMEMANAGER->getWorldTime();
			character->SetSprite(IMAGEMANAGER->FindImage(character->GetName()+"_Electric"));

			
		}
	});
	return S_OK;
}

void ElectricBox::Update()
{
	GameObject::Update();

	if (_timer > 0)
	{
		//2초있다가 릴리즈 
		if (TIMEMANAGER->getWorldTime() - _timer > 2)
		{
			character->SetHP(0);
			character->GetParent()->RemoveChild(character);
			character->ChangeState(new DeadState(character));

		}
	}
}
