#include "stdafx.h"
#include "AtkState.h"
#include "IdleState.h"
#include "Character.h"
#include "MoveState.h"
#include "StopState.h"

void AtkState::EnterState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();
	//Baleog ���� Ÿ�� KNIFE_UP
	if (_thisObj->GetName() == "Baleog")
	{
		if (_thisObj->GetATKType() == KNIFE_ATTACK)
		{
			int rnd = RND->getFromIntTo(0, 1);
			if (rnd == 0)
			{
				//������ ����
				if (_thisObj->GetSprite()->GetFlipX() == false)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_down"));
					_thisObj->GetTransform()->SetFlip(false);
				}

				//���� ����
				if (_thisObj->GetSprite()->GetFlipX() == true)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_down"));
					_thisObj->GetTransform()->SetFlip(true);
				}
			}
			else
			{
				//������ ����
				if (_thisObj->GetSprite()->GetFlipX() == false)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_up"));
					_thisObj->GetTransform()->SetFlip(false);
				}

				//���� ����
				if (_thisObj->GetSprite()->GetFlipX() == true)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_up"));
					_thisObj->GetTransform()->SetFlip(true);
				}
			}
		}
	}

	if (_thisObj->GetATKType() == ARROW)
	{
		//auto _bullet = new Bullet;
		//������ 
		if (_thisObj->GetSprite()->GetFlipX() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Shoot_arrow"));
			_thisObj->GetTransform()->SetFlip(false);
			//_bullet->Baleog_BulletFire(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y + 3), 3, false);
		}
		//����
		else if (_thisObj->GetSprite()->GetFlipX() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Shoot_arrow"));
			_thisObj->GetTransform()->SetFlip(true);
			//_bullet->Baleog_BulletFire(_thisObj->GetTransform()->GetPosition(), -3, true);
		}
	}

	//Baleog ���� �ӵ�(������ ������ ��) 0.2�� ������ ���� --> Idle������ �ٲ���� �մϴ�. 
	if (_thisObj->GetName() == "Baleog")
	{
		_thisObj->SetDeltaTime(0.15);
	}

	_count = TIMEMANAGER->getWorldTime();

	//Erik ���� ���� 
	if (_thisObj->GetATKType() == HEAD_BUTT && _thisObj->GetName() == "Erik")
		//��ġ�� ��� 
	{
		if (_thisObj->GetSprite()->GetFlipX() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Attack"));
			_thisObj->GetTransform()->SetFlip(false);
			_thisObj->SetDeltaTime(0.4);
		}
		else if (_thisObj->GetSprite()->GetFlipX() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Attack"));
			_thisObj->GetTransform()->SetFlip(true);
			_thisObj->SetDeltaTime(0.4);
		}

	}
	//Current State �� MaxFrame�� ���ٸ� changeState�� �ض� 
	//_thisObj->ChangeState(new IdleState(_thisObj));
		//Baleog ���� Ÿ�� ARROW
	//if (_thisObj->GetATKType() == ARROW)
	//{
	// �ҷ� �Լ� ����
	//}
}

void AtkState::UpdateState()
{
	if (_thisObj->GetATKType() == ARROW /*&& TIMEMANAGER->getWorldTime() - _count > 2*/ && _isFire == false)
	{
		//ȭ�� �������� 7�� �� --> ȭ���� �߻��ض�
		if (_thisObj->GetCurrentPosition().x == 6)
		{
			if (_thisObj->GetSprite()->GetFlipX() == false)
			{
				auto _bullet = new Bullet(true);
				_bullet->Baleog_BulletFire(Vector2(_thisObj->GetTransform()->GetPosition().x + 40, _thisObj->GetTransform()->GetPosition().y + 2), 6, false);
				_isFire = true;
			}

			if (_thisObj->GetSprite()->GetFlipX() == true)
			{
				auto _bullet = new Bullet(true);
				_bullet->Baleog_BulletFire(Vector2(_thisObj->GetTransform()->GetPosition().x - 40, _thisObj->GetTransform()->GetPosition().y + 2), -6, true);
				_isFire = true;
			}
		}
	}

	if (_thisObj->GetCurrentPosition().x == _thisObj->GetSprite()->GetMaxFrameX() - 1
		&& _thisObj->GetATKType() != HEAD_BUTT)
	{
		_thisObj->ChangeState(new IdleState(_thisObj));
	}
	if (_thisObj->GetATKType() == HEAD_BUTT)
	{
		//���� �ٲ� ����===========================
		auto d = _thisObj->GetTransform()->GetSize() / 2 * _thisObj->GetTransform()->GetScale();
		auto CheckRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition(), Vector2(-1, 0), 35);

		if (CheckRay.GetFixture() != nullptr)
		{
			GameObject* obj = (GameObject*)CheckRay.GetFixture()->GetBody()->GetUserData();
			if (obj->GetTag() == "BrokenWall")
			{
				_thisObj->SetStopType(WALL);
				_thisObj->ChangeState(new StopState(_thisObj));
			}
		}
		//========================================
		//MaxFrame�� �����ϸ� State��ȯ.
		else if (_thisObj->GetCurrentPosition().x == _thisObj->GetSprite()->GetMaxFrameX() - 1)
			_thisObj->ChangeState(new MoveState(_thisObj));
	}
}

