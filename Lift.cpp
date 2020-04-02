#include "stdafx.h"
#include "Lift.h"
#include "playGround.h"

HRESULT Lift::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character")
			return;
		characters.push_back((Character *)targetObj->GetPhysics()->GetBody()->GetUserData());

		Lift* lift = (Lift*)thisObj->GetParent()->GetChildByName("lift");
		lift->SetIsOnLift(true);
	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character")
			return;

		characters.remove((Character *)targetObj->GetPhysics()->GetBody()->GetUserData());
		this->SetIsOnLift(false);
	});

	return S_OK;
}

void Lift::Update()
{
	GameObject::Update();

	LiftMove();
}

void Lift::LiftMove()
{
	bool prevState = _isLiftMovingUp;
	if ((KEYMANAGER->IsOnceKeyDown(VK_DOWN) || KEYMANAGER->IsOnceKeyDown(VK_UP)) && _isOnLift)
		_isLiftMovingUp = !_isLiftMovingUp;
	if (prevState != _isLiftMovingUp && _isOnLift)
	{
		for (auto c : characters)
		{
			auto body = c->GetPhysics()->GetBody();
			body->SetLinearVelocity({ body->GetLinearVelocity().x,100 });
		}
	}


	if (_isLiftMovingUp)
	{
		if (_transform->GetPosition().y > Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 1150),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_physics->GetBody()->SetLinearVelocity(b2Vec2(0, -1));
		}
		if (_transform->GetPosition().y <= Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 1150),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_physics->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		}
	}
	else
	{
		if (_transform->GetPosition().y < Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 1804),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_physics->GetBody()->SetLinearVelocity(b2Vec2(0, 1));
		}

		if (_transform->GetPosition().y >= Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 1804),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_physics->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		}
	}

}
