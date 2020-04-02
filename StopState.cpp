
#include "stdafx.h"
#include "StopState.h"
#include "Character.h"
#include "IdleState.h"

void StopState::EnterState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();
	if (!body) return;

	body->SetLinearVelocity(b2Vec2{ 0, 0 });
	//�ǰݽ� �з��� ��.

	b2Vec2 force = { 150, 0 };
	b2Vec2 force2 = { -150, 0 };
	b2Vec2 force3 = { 150, -800 };
	b2Vec2 force4 = { -150, -800 };

	_count = TIMEMANAGER->getWorldTime();

	if (_thisObj->GetStopType() == ENEMY)
		//���� Bullet�� �ǰݵǾ�����.
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
		//Erik�� ��ġ��� ����������. (Erik)
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
		//���߿��� �������� ������� �Ծ�����.
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
	//�����ð��Ŀ� Idle State�� ���ư��� �����߽��ϴ�.
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
