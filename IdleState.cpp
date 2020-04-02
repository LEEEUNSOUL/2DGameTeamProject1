#include "stdafx.h"
#include "IdleState.h"
#include "Character.h"
#include "MoveState.h"
#include "JumpState.h"
#include "StopState.h"
#include "AtkState.h"
#include "InAirState.h"

void IdleState::UpdateState()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && _thisObj->GetTag() == "Character")
	{
		_thisObj->ChangeState(new MoveState(_thisObj));
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && _thisObj->GetTag() == "Character")
	{
		_thisObj->ChangeState(new MoveState(_thisObj));
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE) && _thisObj->GetName() == "Erik")
		//������ ������ �� ���ֽ��ϴ�.
	{
		_thisObj->ChangeState(new JumpState(_thisObj));
	}
	//if (KEYMANAGER->IsOnceKeyDown('Q') && _thisObj->GetTag() == "Character")
	//{
	//	_thisObj->SetStopType(TELEPORT);
	//	_thisObj->ChangeState(new StopState(_thisObj));
	//}
	//���� Ű ������ �� 
	if (KEYMANAGER->IsOnceKeyDown('D'))
	{
		if (_thisObj->GetName() == "Baleog")
		{
			_thisObj->SetATKType(KNIFE_ATTACK);
			_thisObj->ChangeState(new AtkState(_thisObj));
		}
		if (_thisObj->GetName() == "Olaf")
		{
			if (_thisObj->GetShield() == false)
			{
				_thisObj->SetShield(true);
				_thisObj->ChangeState(new IdleState(_thisObj));
			}
			else if (_thisObj->GetShield() == true)
			{
				_thisObj->SetShield(false);
				_thisObj->ChangeState(new IdleState(_thisObj));
			}
		}
	}

	if (KEYMANAGER->IsOnceKeyDown('F'))
	{
		if (_thisObj->GetName() == "Baleog")
		{
			_thisObj->SetATKType(ARROW);
			_thisObj->ChangeState(new AtkState(_thisObj));
		}
		if (_thisObj->GetName() == "Erik")
		{
			_thisObj->ChangeState(new JumpState(_thisObj));
		}
	}
}

void IdleState::EnterState()
{
	//�ٷ��� �������� flip�Ǿ��ִ°��� ���� Idle�̹����� ��������� ������� �����մϴ�.
	if (_thisObj->GetName() == "Erik")
	{
		_thisObj->SetDeltaTime(0.3);
		if (_thisObj->GetSprite()->GetFlipX() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Idle"));
			_thisObj->GetTransform()->SetFlip(true);
		}
		else if (_thisObj->GetSprite()->GetFlipX() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Idle"));
			_thisObj->GetSprite()->SetFlip(false, false);
		}
	}
	if (_thisObj->GetName() == "Olaf")
	{
		_thisObj->SetDeltaTime(0.3);
		if (_thisObj->GetShield() == false)
		{
			if (_thisObj->GetSprite()->GetFlipX() == true)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Idle"));
				_thisObj->GetTransform()->SetFlip(true);
			}
			else if (_thisObj->GetSprite()->GetFlipX() == false)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Idle"));
				_thisObj->GetTransform()->SetFlip(false);
			}
		}
		else if (_thisObj->GetShield() == true)
		{
			if (_thisObj->GetSprite()->GetFlipX() == true)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Shield_Up"));
				_thisObj->GetTransform()->SetFlip(true);
			}
			else if (_thisObj->GetSprite()->GetFlipX() == false)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Shield_Up"));
				_thisObj->GetTransform()->SetFlip(false);
			}
		}
	}
	if (_thisObj->GetName() == "Baleog")
	{
		_thisObj->SetDeltaTime(0.3);
		if (_thisObj->GetShield() == false)
		{
			if (_thisObj->GetSprite()->GetFlipX() == true)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Idle"));
				_thisObj->GetTransform()->SetFlip(true);
			}
			else if (_thisObj->GetSprite()->GetFlipX() == false)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Idle"));
				_thisObj->GetTransform()->SetFlip(false);
			}
		}

	}
	b2Body* body = _thisObj->GetPhysics()->GetBody();
	if (!body) return;
	//MoveState���� IdleState�� ���� �ӵ��� 0���� �ٲ㼭 �������� �����.
	_thisObj->GetPhysics()->SetVelocity({ 0,body->GetLinearVelocity().y });
}

void IdleState::ExitState()
{

}
