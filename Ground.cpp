#include "stdafx.h"
#include "Ground.h"
#include "Character.h"
#include "ClimbState.h"
#include "BrokenWall.h"

Ground::Ground()
{
	_physics = new Physics();
}

Ground::~Ground()
{
}

HRESULT Ground::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character") return;

		if (thisObj->GetTag() == "LadderSensor")
		{
			ground = (Ground*)GetParent()->GetChildByName("Ground" + thisObj->GetName());
			character = (Character*)targetObj;
			_inArea = true;

			//아래에서 위로 
			if (character->GetIsClimbing())
				character->SetIsClimbUp(true);
		
		}
		if (thisObj->GetName() == "SecretWall")
		{
			BrokenWall* wall = (BrokenWall*)GetParent()->GetChildByName("BrokenWall");

			_inArea = false;
			if (wall->GetIsBroken())
			{
				thisObj->GetPhysics()->SetIsSensor(true);
				thisObj->SetZOrder(10);
			}


		}

	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character") return;
		_inArea = false;

		//targetObj->SetZOrder(3);
	});

	return S_OK;
}

void Ground::Update()
{
	if (_inArea)
	{
		//ENTER CLIMB STATE -- 위에서 아래로 
		if (!character->GetIsClimbDown() && KEYMANAGER->IsOnceKeyDown(VK_DOWN))
		{
			character->GetPhysics()->SetIsSensor(true);
			character->SetIsClimbDown(true);
			character->ChangeState(new ClimbState(character));
		}

		//좌표 보정 
		if (character->GetIsClimbDown())
		{
			if (this->GetTransform()->GetPosition().x  - character->GetTransform()->GetPosition().x > 5)
			{
				character->GetTransform()->Translate(Vector2(5,0));
			}
			else if (character->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x > 5)
			{
				character->GetTransform()->Translate(Vector2(-5,0));
			}
		}

	}

}
