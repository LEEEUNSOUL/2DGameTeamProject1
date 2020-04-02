#include "stdafx.h"
#include "InAirState.h"
#include "MoveState.h"
#include "IdleState.h"


void InAirState::UpdateState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();

	auto d = _thisObj->GetTransform()->GetSize() / 2 * _thisObj->GetTransform()->GetScale();
	auto rightRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition() + Vector2(d.x, d.y - 2), Vector2(0, 1), 3);
	auto leftRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition() + Vector2(-d.x, d.y - 2), Vector2(0, 1), 3);

	if (rightRay.GetFixture() != nullptr)
	{
		GameObject* obj = (GameObject*)rightRay.GetFixture()->GetBody()->GetUserData();
		if (obj->GetTag() == "Ground")
			_thisObj->ChangeState(new IdleState(_thisObj));
		return;
	}
	if (leftRay.GetFixture() != nullptr)
	{
		GameObject* obj = (GameObject*)leftRay.GetFixture()->GetBody()->GetUserData();
		if (obj->GetTag() == "Ground")
			_thisObj->ChangeState(new IdleState(_thisObj));
		return;
	}


	if (_thisObj->GetName() == "Olaf" && _thisObj->GetShield())
	{
		_thisObj->GetPhysics()->SetGravityScale(0.5);
		_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_AirDropNoMove"));
		_thisObj->GetTransform()->SetFlip(_thisObj->GetTransform()->GetFlip());
		
	}
	if (KEYMANAGER->IsOnceKeyDown('D') && _thisObj->GetName() == "Olaf")
	{
		if (_thisObj->GetShield() == false)	_thisObj->SetShield(true);
		else if (_thisObj->GetShield() == true)	_thisObj->SetShield(false);
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		_thisObj->GetTransform()->SetFlip(true);
		if (body->GetLinearVelocity().x < -3) return;
		b2Vec2 force = { -6,0 };
		_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force, true);
		//Olaf가 Shield상태일때는 ShieldUp InAir Image를 얻어옵니다.
		if (_thisObj->GetShield() == true && _thisObj->GetName() == "Olaf")
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_AirDropMove"));
			_thisObj->GetTransform()->SetFlip(true);
		}
		//Olaf가 Shield상태가 아닐때에는 InAir Image를 얻어옵니다.
		else if (_thisObj->GetShield() == false && _thisObj->GetName() == "Olaf")
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_InAir"));
			_thisObj->GetTransform()->SetFlip(true);
		}
	}
	else if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_thisObj->GetTransform()->SetFlip(false);
		if (body->GetLinearVelocity().x > 3) return;
		b2Vec2 force = { 6,0 };
		_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force, true);
		if (_thisObj->GetShield() == true && _thisObj->GetName() == "Olaf")
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_AirDropMove"));
			_thisObj->GetTransform()->SetFlip(false);

		}
		else if (_thisObj->GetShield() == false && _thisObj->GetName() == "Olaf")
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_InAir"));
			_thisObj->GetTransform()->SetFlip(false);
		}
	}
}

void InAirState::EnterState()
{
	if (_thisObj->GetTag() == "Character")
	{
		_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_InAir"));
		if (_thisObj->GetTransform()->GetFlip() == true) _thisObj->GetTransform()->SetFlip(false);
		else if (_thisObj->GetTransform()->GetFlip() == false) _thisObj->GetTransform()->SetFlip(true);
		_thisObj->SetDeltaTime(0.3);
	}
}

void InAirState::ExitState()
{
	_thisObj->GetPhysics()->SetGravityScale(1);
}
