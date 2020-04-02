#include "stdafx.h"
#include "BrokenWall.h"
#include "Character.h"

BrokenWall::BrokenWall()
{
	_physics = new Physics();
}


BrokenWall::~BrokenWall()
{
}

HRESULT BrokenWall::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		Character* character = (Character *)targetObj;

		BrokenWall* wall = (BrokenWall*)GetParent()->GetChildByName("BrokenWall");
		if (targetObj->GetName() == "Erik" && character->GetATKType() == HEAD_BUTT)
		{
			character = (Character *)targetObj->GetPhysics()->GetBody()->GetUserData();

			if (!_isBroken)
			{
				thisObj->SetSprite(IMAGEMANAGER->FindImage("BrokenWall_Frame"));
				thisObj->SetDeltaTime(0.2);
				_timer = TIMEMANAGER->getWorldTime();
			}
			
		}

		if (thisObj->GetName() == "SecretWall" && wall->GetIsBroken())
		{
			thisObj->GetPhysics()->SetIsSensor(true);
		}
	});

	return S_OK;
}

void BrokenWall::Update()
{
	GameObject::Update();
	if (_timer > 0 && !_isBroken)
	{		                                                                                                                                         
		if (_currentPosition.x == _sprite->GetMaxFrameX()-1)
		{
			SetSprite(IMAGEMANAGER->FindImage("BrokenWallEnd"));
			_isBroken = true;
			this->GetPhysics()->SetIsSensor(true);

		}
	}
}
