
#include "stdafx.h"
#include "StopState.h"
#include "Character.h"
#include "IdleState.h"

void StopState::EnterState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();
	if (!body) return;

	body->SetLinearVelocity(b2Vec2{ 0, 0 });
	//피격시 밀려날 힘.

	b2Vec2 force = { 150, 0 };
	b2Vec2 force2 = { -150, 0 };
	b2Vec2 force3 = { 150, -800 };
	b2Vec2 force4 = { -150, -800 };

	_count = TIMEMANAGER->getWorldTime();

	if (_thisObj->GetStopType() == ENEMY)
		//적의 Bullet에 피격되었을때.
	{
		if (_thisObj->GetTransform()->GetFlip() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Hit"));
			_thisObj->GetTransform()->SetFlip(true);
			_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force, true);
		}
		if (_thisObj->GetTransform()->GetFlip() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Hit"));
			_thisObj->GetTransform()->SetFlip(false);
			_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force2, true);
		}
	}
	else if (_thisObj->GetStopType() == WALL)
		//Erik의 박치기로 기절했을때. (Erik)
	{
		if (_thisObj->GetTransform()->GetFlip() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Paint"));
			_thisObj->GetTransform()->SetFlip(true);
			_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force3, true);
		}
		if (_thisObj->GetTransform()->GetFlip() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Paint"));
			_thisObj->GetTransform()->SetFlip(false);
			_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force4, true);
		}
	}
	else if (_thisObj->GetStopType() == GROUND)
		//공중에서 떨어져서 대미지를 입었을때.
	{
		if (_thisObj->GetSprite()->GetFlipX() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_AirDrop"));
			_thisObj->GetTransform()->SetFlip(true);
			//_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force4, true);
		}
		if (_thisObj->GetTransform()->GetFlip() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_AirDrop"));
			_thisObj->GetTransform()->SetFlip(false);
			//_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force4, true);
		}
	}
	else if (_thisObj->GetStopType() == TELEPORT)
	{
		_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Teleport"));

		_thisObj->GetTransform()->SetFlip(true);
	}

}

void StopState::UpdateState()
{
	//_count = TIMEMANAGER->getWorldTime();
	//일정시간후에 Idle State로 돌아가게 세팅했습니다.
	if (_thisObj->GetStopType() == ENEMY && TIMEMANAGER->getWorldTime() - _count > 0.8)
	{
		_thisObj->ChangeState(new IdleState(_thisObj));
	}
	if (_thisObj->GetStopType() == WALL && TIMEMANAGER->getWorldTime() - _count > 1.5)
	{
		_thisObj->ChangeState(new IdleState(_thisObj));
	}
	if (_thisObj->GetStopType() == GROUND && TIMEMANAGER->getWorldTime() - _count > 1.2)
	{
		_thisObj->ChangeState(new IdleState(_thisObj));
	}
	if (_thisObj->GetStopType() == TELEPORT && _thisObj->GetCurrentPosition().x ==
		_thisObj->GetSprite()->GetMaxFrameX() - 1 /*&& TIMEMANAGER->getWorldTime() - _count > 1.2*/)
	{
		_thisObj->ChangeState(new IdleState(_thisObj));
	}

	if (_thisObj->GetStopType() == ENEMY)   _thisObj->SetDeltaTime(0.3);
	if (_thisObj->GetStopType() == WALL)   _thisObj->SetDeltaTime(0.3);
	if (_thisObj->GetStopType() == GROUND)   _thisObj->SetDeltaTime(0.3);
	if (_thisObj->GetStopType() == TELEPORT) _thisObj->SetDeltaTime(0.2);
}
