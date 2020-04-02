#include "stdafx.h"
#include "AtkState.h"
#include "IdleState.h"
#include "Character.h"
#include "MoveState.h"
#include "StopState.h"

void AtkState::EnterState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();
	//Baleog 공격 타입 KNIFE_UP
	if (_thisObj->GetName() == "Baleog")
	{
		if (_thisObj->GetATKType() == KNIFE_ATTACK)
		{
			int rnd = RND->getFromIntTo(0, 1);
			if (rnd == 0)
			{
				//오른쪽 방향
				if (_thisObj->GetSprite()->GetFlipX() == false)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_down"));
					_thisObj->GetTransform()->SetFlip(false);
				}

				//왼쪽 방향
				if (_thisObj->GetSprite()->GetFlipX() == true)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_down"));
					_thisObj->GetTransform()->SetFlip(true);
				}
			}
			else
			{
				//오른쪽 방향
				if (_thisObj->GetSprite()->GetFlipX() == false)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Knife_up"));
					_thisObj->GetTransform()->SetFlip(false);
				}

				//왼쪽 방향
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
		//오른쪽 
		if (_thisObj->GetSprite()->GetFlipX() == false)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Shoot_arrow"));
			_thisObj->GetTransform()->SetFlip(false);
			//_bullet->Baleog_BulletFire(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y + 3), 3, false);
		}
		//왼쪽
		else if (_thisObj->GetSprite()->GetFlipX() == true)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Shoot_arrow"));
			_thisObj->GetTransform()->SetFlip(true);
			//_bullet->Baleog_BulletFire(_thisObj->GetTransform()->GetPosition(), -3, true);
		}
	}

	//Baleog 공격 속도(프레임 돌리는 초) 0.2로 빠르게 설정 --> Idle에서도 바꿔줘야 합니다. 
	if (_thisObj->GetName() == "Baleog")
	{
		_thisObj->SetDeltaTime(0.15);
	}

	_count = TIMEMANAGER->getWorldTime();

	//Erik 공격 설정 
	if (_thisObj->GetATKType() == HEAD_BUTT && _thisObj->GetName() == "Erik")
		//박치기 모션 
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
	//Current State 가 MaxFrame과 같다면 changeState를 해라 
	//_thisObj->ChangeState(new IdleState(_thisObj));
		//Baleog 공격 타입 ARROW
	//if (_thisObj->GetATKType() == ARROW)
	//{
	// 불렛 함수 연결
	//}
}

void AtkState::UpdateState()
{
	if (_thisObj->GetATKType() == ARROW /*&& TIMEMANAGER->getWorldTime() - _count > 2*/ && _isFire == false)
	{
		//화살 프레임이 7일 때 --> 화살을 발사해라
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
		//오늘 바뀐 사항===========================
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
		//MaxFrame에 도달하면 State전환.
		else if (_thisObj->GetCurrentPosition().x == _thisObj->GetSprite()->GetMaxFrameX() - 1)
			_thisObj->ChangeState(new MoveState(_thisObj));
	}
}

