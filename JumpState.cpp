#include "stdafx.h"
#include "Character.h"
#include "JumpState.h"
#include "MoveState.h"
#include "IdleState.h"

void JumpState::UpdateState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();

	auto d = _thisObj->GetTransform()->GetSize() / 2 * _thisObj->GetTransform()->GetScale();
	auto rightRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition() + Vector2(d.x, d.y - 2), Vector2(0, 1), 3);
	auto leftRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition() + Vector2(-d.x, d.y - 2), Vector2(0, 1), 3);
	if (rightRay.GetFixture() != nullptr && leftRay.GetFixture() != nullptr)
	{
		GameObject* obj = (GameObject*)rightRay.GetFixture()->GetBody()->GetUserData();
		if (obj->GetTag() == "Ground")
		{
			if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) || KEYMANAGER->IsStayKeyDown(VK_LEFT))
				_thisObj->ChangeState(new MoveState(_thisObj));
			else
				_thisObj->ChangeState(new IdleState(_thisObj));
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		_thisObj->GetTransform()->SetFlip(true);
		if (body->GetLinearVelocity().x < -6) return;
		b2Vec2 force = { -3,0 };
		_thisObj->GetPhysics()->ApplyForce(force);
	}
	else if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_thisObj->GetTransform()->SetFlip(false);
		if (body->GetLinearVelocity().x > 6) return;
		b2Vec2 force = { 3,0 };
		_thisObj->GetPhysics()->ApplyForce(force);
	}
}

void JumpState::EnterState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();

	if (KEYMANAGER->IsOnceKeyDown('F'))
	{
		if (_thisObj->GetTransform()->GetFlip() == true) IMAGEMANAGER->FindImage("Erik_Jump")->SetFlip(true,false);
		else if (_thisObj->GetTransform()->GetFlip() == false) IMAGEMANAGER->FindImage("Erik_Jump")->SetFlip(false,false);
		_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Jump"));
		_thisObj->SetDeltaTime(0.3);
		b2Vec2 force = { 0, -1000 };
		_thisObj->GetPhysics()->ApplyForce(force);
	}

}

void JumpState::ExitState()
{

}
