#include "stdafx.h"
#include "Grinder.h"
#include "DeadState.h"

Grinder::Grinder()
{
	_physics = new Physics;
}


Grinder::~Grinder()
{
}

HRESULT Grinder::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character")
		{
			character = (Character *)targetObj->GetPhysics()->GetBody()->GetUserData();
			character->SetHP(0);
			character->ChangeState(new DeadState(character));
			character->SetSprite(IMAGEMANAGER->FindImage(character->GetName()+"_Grinder"));	
			character->SetDeltaTime(0.3);

			//PHYSICSMANAGER->IgnoreCollision(thisObj, targetObj);
			//_timer = TIMEMANAGER->getWorldTime();

		}
	});


	return S_OK;
}

void Grinder::Update()
{
	GameObject::Update();

	//��ȣ�� ���Դٸ� 
	//if (_timer > 0)
	//{
	//	//��� ��ٷȴٰ� ������ �������� 
	//	if (TIMEMANAGER->getWorldTime() - _timer > 1)
	//	{
	//		character->GetPhysics()->SetGravityScale(0.01f);
	//	}
	//	else
	//	{
	//		character->GetPhysics()->SetGravityScale(0.f);
	//		character->SetDeltaTime(0.15);
	//		if (!_isDown)
	//		{
	//			character->GetTransform()->SetPosition(character->GetTransform()->GetPosition() + Vector2(0, 30));
	//			_isDown = true;
	//		}
	//			
	//	}

	//	//������ MAX���� �����ֱ� 
	//	if (character->GetCurrentPosition().x == character->GetSprite()->GetMaxFrameX() -1 )
	//	{
	//		character->GetParent()->RemoveChild(character);
	//		character->SetIsDead(true);
	//		_isDown = false;
	//	}
	//}
}



