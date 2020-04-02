#include "stdafx.h"
#include "MoveState.h"
#include "Character.h"
#include "IdleState.h"
#include "JumpState.h"
#include "StopState.h"
#include "AtkState.h"
#include "InAirState.h"

void MoveState::UpdateState()
{
	b2Body* body = _thisObj->GetPhysics()->GetBody();

	auto d = _thisObj->GetTransform()->GetSize() / 2 * _thisObj->GetTransform()->GetScale();
	auto rightRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition() + Vector2(d.x, d.y - 2), Vector2(0, 1), 3);
	auto leftRay = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition() + Vector2(-d.x, d.y - 2), Vector2(0, 1), 3);

	if (KEYMANAGER->IsOnceKeyDown('F'))
	{
		if (_thisObj->GetName() == "Erik")
		{
			_thisObj->ChangeState(new JumpState(_thisObj));
			return;
		}
	}

	if (KEYMANAGER->IsOnceKeyDown('D'))
	{
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
		if (_thisObj->GetName() == "Erik")
			//일정속도가 되면 Erik의 박치기 공격을 할수있다.
		{
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x > 5 ||
				_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x < -5)
			{
				_thisObj->SetATKType(HEAD_BUTT);
				_thisObj->ChangeState(new AtkState(_thisObj));
			}
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
		//오른쪽으로 움직임
	{
		auto wallpushray = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition(), Vector2(1, 0), 35);
		if (_thisObj->GetName() == "Olaf" || _thisObj->GetName() == "Baleog")
		{
			//바로전 Sprite의 FlipX와 반대방향으로 힘을 주는경우에 받고있던힘을 초기화해주는 작업입니다.
			//이거 없으면 방향전환 할 때 스케이트처럼 미끄러집니다.
			if (_thisObj->GetTransform()->GetFlip() == true)
				body->SetLinearVelocity(b2Vec2{ 0, 0 });
			_thisObj->GetTransform()->SetFlip(false);
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x > 6)
				return;
			b2Vec2 force = { 17,0 };
			_thisObj->GetPhysics()->ApplyForce(force);
			//Olaf가 Shield상태일때는 ShieldUp Image얻어옵니다.
			if (_thisObj->GetShield() && _thisObj->GetSprite() != IMAGEMANAGER->FindImage("Olaf_Shield_Run"))
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Shield_Run"));
			//======================================================= PushWall
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x == 0 && _thisObj->GetName() == "Olaf" &&
				_thisObj->GetStopType() != ENEMY && _thisObj->GetStopType() != WALL && _thisObj->GetStopType() != GROUND)
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Olaf_Push_Wall"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Push_Wall"));
			}
			else if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x != 0 && _thisObj->GetName() == "Olaf"
				&& !_thisObj->GetShield())
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Olaf_Run"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Run"));
			}
			if (!_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x  && _thisObj->GetName() == "Baleog" &&
				_thisObj->GetStopType() != ENEMY && _thisObj->GetStopType() != WALL && _thisObj->GetStopType() != GROUND)
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Baleog_Push_Wall"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Push_Wall"));
			}
			else if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x != 0 && _thisObj->GetName() == "Baleog")
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Baleog_Run"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Run"));
			}
			//=======================================================
		}
		//Erik의 이동속도는 다른캐릭터보다 빠르다.
		if (_thisObj->GetName() == "Erik")
		{
			//Erik은 방향 바뀔때 미끄러지는 느낌이있어서 Velocity초기화 안해주었습니다.
			if (_thisObj->GetTransform()->GetFlip() == true && !dynamic_cast<IdleState*>(_thisObj->GetState()))
			{
				b2Vec2 correctionforce = _thisObj->GetPhysics()->GetBody()->GetLinearVelocity();
				correctionforce.x /= 2.3f;
				_thisObj->GetPhysics()->GetBody()->SetLinearVelocity(correctionforce);
			}
			_thisObj->GetTransform()->SetFlip(false);
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x > 7)	
				return;
			b2Vec2 force = { 28,0 };
			_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force, true);
		}
		if (wallpushray.GetFixture() != nullptr)
		{
			GameObject* obj = (GameObject*)wallpushray.GetFixture()->GetBody()->GetUserData();
			if (obj->GetTag() == "Ground")
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Push_Wall"))
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Push_Wall"));
					_thisObj->SetDeltaTime(0.3f);
				}
			}
			return;
		}
		else
		{
			if (_thisObj->GetSprite() == IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Push_Wall"))
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Run"));
				_thisObj->SetDeltaTime(0.3f);
			}
		}
	}
	else if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
		//왼쪽으로 움직임.
	{
		auto wallpushray = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition(), Vector2(-1, 0), 35);

		if (_thisObj->GetName() == "Olaf" || _thisObj->GetName() == "Baleog")
		{
			if (_thisObj->GetTransform()->GetFlip() == false) body->SetLinearVelocity(b2Vec2{ 0,0 });
			_thisObj->GetTransform()->SetFlip(true);
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x < -6) return; //역방향
			b2Vec2 force = { -17,0 };
			_thisObj->GetPhysics()->ApplyForce(force);
			if (_thisObj->GetShield() && _thisObj->GetSprite() != IMAGEMANAGER->FindImage("Olaf_Shield_Run"))
				_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Shield_Run"));

			//======================================================= PushWall
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x == 0 && _thisObj->GetName() == "Olaf" &&
				_thisObj->GetStopType() != ENEMY && _thisObj->GetStopType() != WALL && _thisObj->GetStopType() != GROUND)
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Olaf_Push_Wall"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Push_Wall"));
			}
			else if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x != 0 && _thisObj->GetName() == "Olaf"
				&& _thisObj->GetShield() == false)
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Olaf_Run"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Run"));
			}
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x == 0 && _thisObj->GetName() == "Baleog" &&
				_thisObj->GetStopType() != ENEMY && _thisObj->GetStopType() != WALL && _thisObj->GetStopType() != GROUND)
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Baleog_Push_Wall"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Push_Wall"));
			}
			else if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x != 0 && _thisObj->GetName() == "Baleog")
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage("Baleog_Run"))
					_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Run"));
			}
			//=======================================================
		}
		if (_thisObj->GetName() == "Erik")
		{
			if (_thisObj->GetSprite()->GetFlipX() == false && !dynamic_cast<IdleState*>(_thisObj->GetState()))
			{
				b2Vec2 correctionforce = _thisObj->GetPhysics()->GetBody()->GetLinearVelocity();
				correctionforce.x /= 2.3f;
				_thisObj->GetPhysics()->GetBody()->SetLinearVelocity(correctionforce);
			}
			_thisObj->GetTransform()->SetFlip(true);
			/*auto wallpushray = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition(), Vector2(1, 0), 35);*/
			if (_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().x < -6) return;
			b2Vec2 force = { -28,0 };
			_thisObj->GetPhysics()->GetBody()->ApplyForceToCenter(force, true);
		}
		if (wallpushray.GetFixture() != nullptr)
		{
			GameObject* obj = (GameObject*)wallpushray.GetFixture()->GetBody()->GetUserData();
			if (obj->GetTag() == "Ground")
			{
				if (_thisObj->GetSprite() != IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Push_Wall"))
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Push_Wall"));
					_thisObj->SetDeltaTime(0.3f);
				}
			}
			return;
		}
		else
		{
			if (_thisObj->GetSprite() == IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Push_Wall"))
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_Run"));
				_thisObj->SetDeltaTime(0.3f);
			}
		}
	}
	else
	{
		//움직임이 없을때에는 ChangeState로 Idle상태로 바꿔주도록 했습니다.
		_thisObj->ChangeState(new IdleState(_thisObj));
	}
	if (rightRay.GetFixture() == nullptr && leftRay.GetFixture() == nullptr)
	{
		_thisObj->ChangeState(new InAirState(_thisObj));
	}
}

void MoveState::EnterState()
{
	if (_thisObj->GetName() == "Erik")
	{
		_thisObj->SetSprite(IMAGEMANAGER->FindImage("Erik_Run"));
		_thisObj->SetDeltaTime(0.3);
	}
	if (_thisObj->GetName() == "Baleog")
	{
		_thisObj->SetSprite(IMAGEMANAGER->FindImage("Baleog_Run"));
		_thisObj->GetTransform()->SetSize(Vector2(36,33));
		_thisObj->SetDeltaTime(0.3);
	}
	if (_thisObj->GetName() == "Olaf" && _thisObj->GetShield() == false)
	{
		_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Run"));
		_thisObj->SetDeltaTime(0.3);
	}
	else if (_thisObj->GetName() == "Olaf" && _thisObj->GetShield() == true)
	{
		_thisObj->SetSprite(IMAGEMANAGER->FindImage("Olaf_Shield_Run"));
		_thisObj->SetDeltaTime(0.3);
	}
	_count = TIMEMANAGER->getWorldTime();
}

void MoveState::ExitState()
{
	if (_thisObj->GetName() == "Baleog")
		_thisObj->GetTransform()->SetSize(Vector2(26, 33));
}

