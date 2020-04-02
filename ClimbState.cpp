#include "stdafx.h"
#include "ClimbState.h"
#include "InAirState.h"
#include "MoveState.h"
#include "IdleState.h"

void ClimbState::EnterState()
{
	_thisObj->GetPhysics()->SetGravityScale(0);
	_thisObj->GetPhysics()->SetVelocity(Vector2::zero);


	//내려갈때 
	if (_thisObj->GetIsClimbDown())
	{
		_level = LEVEL_ZERO;
		_initialPos = _thisObj->GetTransform()->GetPosition();
	}
	//올라갈때 
	else
	{
		_level = LEVEL_THREE;
		_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbUp"));
		_thisObj->GetSprite()->SetUpdateAnimation(false);
		_thisObj->GetPhysics()->SetIsSensor(true);
	}
	
}

void ClimbState::UpdateState()
{
	AdjustPosition();

	if (KEYMANAGER->IsOnceKeyDown(VK_LEFT) || KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	{
		_thisObj->ChangeState(new InAirState(_thisObj));
		return;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{
		_thisObj->SetIsClimbDown(true);
		if (_level == LEVEL_TWO)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbUp"));
			_thisObj->GetSprite()->SetUpdateAnimation(false);
			_thisObj->GetTransform()->SetPosition(Vector2(_thisObj->GetTransform()->GetPosition().x,_thisObj->GetTransform()->GetPosition().y+5));
			_level = LEVEL_THREE;

		}
		else if (_level == LEVEL_ONE)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter1"));
			_level = LEVEL_TWO;

		}
		else if (_level == LEVEL_ZERO)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter2"));
			_level = LEVEL_ONE;
		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		_thisObj->SetIsClimbDown(false);
		if (_level == LEVEL_ONE)
		{
			_thisObj->ChangeState(new IdleState(_thisObj));
		}
		else if (_level == LEVEL_TWO)
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter2"));
			_level = LEVEL_ONE;
		}
		else if (_level == LEVEL_THREE && _thisObj->GetIsClimbUp())
		{
			_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter1"));
			_level = LEVEL_TWO;
		}
	}
	
	//프레임 모션 
	if(_level == LEVEL_THREE)
	{
		if (KEYMANAGER->IsStayKeyDown(VK_UP))
		{
			if (_thisObj->GetIsClimbUp())
			{
				_count++;
				if (_count > 35)
				{
					_thisObj->ChangeState(new IdleState(_thisObj));
				}
				else if (_count > 20)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter2"));
					AdjustPosition(LEVEL_ONE);
				}
				else if (_count > 5)
				{
					_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter1"));
					AdjustPosition(LEVEL_TWO);
				}
			}
			else
			{
				_thisObj->SetDeltaTime(0.3);
				_thisObj->AddAnimationCount();
				_thisObj->GetTransform()->SetPosition(_thisObj->GetTransform()->GetPosition() + Vector2(0, -2));
			}
		
		}
		else if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
		{
			_thisObj->SetDeltaTime(0.3);
			_thisObj->AddAnimationCount();
			_thisObj->GetTransform()->SetPosition(_thisObj->GetTransform()->GetPosition() + Vector2(0, 2));

		}
	}
	if (_level != LEVEL_THREE)
	{
		if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
		{
			_thisObj->SetIsClimbDown(true);
			_count++;
			if (_count > 30)
			{
				_level = LEVEL_THREE;
				_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbUp"));
				_thisObj->GetSprite()->SetUpdateAnimation(false);
			}
			else if (_count > 15)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter1"));
				AdjustPosition(LEVEL_TWO);
				_level = LEVEL_TWO;
			}
			else if (_count > 10)
			{
				_thisObj->SetSprite(IMAGEMANAGER->FindImage(_thisObj->GetName() + "_ClimbAfter2"));
				AdjustPosition(LEVEL_ONE);
				_level = LEVEL_ONE;
			}
		}
	}


	//RAYCAST 
	auto size = _thisObj->GetTransform()->GetSize() * _thisObj->GetTransform()->GetScale();
	auto ray = PHYSICSMANAGER->RayCast(_thisObj->GetTransform()->GetPosition(),Vector2(0,1), size.y/2);

	if (ray.GetFixture())
	{
		auto obj = (GameObject*)ray.GetFixture()->GetBody()->GetUserData();
		if (obj->GetTag() == "Ground")
			_thisObj->ChangeState(new IdleState(_thisObj));
	}

}

void ClimbState::ExitState()
{
	_thisObj->GetPhysics()->SetIsSensor(false);
	_thisObj->SetIsClimbing(false);
	_thisObj->SetIsClimbUp(false);
	_thisObj->SetIsClimbDown(false);
	_thisObj->GetPhysics()->SetGravityScale(1);
}

void ClimbState::AdjustPosition()
{
	if (_level == LEVEL_ONE && !_thisObj->GetIsClimbDown())
	{
		//밑에서 위로 
		if (_thisObj->GetTransform()->GetPosition().y+4 - _thisObj->GetLadderPos().y > 0)
				_thisObj->GetTransform()->Translate(Vector2(0, -2));

		if (_initialPos.y + 25 - _thisObj->GetTransform()->GetPosition().y > 2 && _thisObj->GetIsClimbDown())
			_thisObj->GetTransform()->SetPosition(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y + 2));

	}
	else if (_level == LEVEL_TWO )
	{
		if (_thisObj->GetTransform()->GetPosition().y  - _thisObj->GetLadderPos().y > 15  && !_thisObj->GetIsClimbDown())
		{
			_thisObj->GetTransform()->SetPosition(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y  - 2 ));
		}
		//위에서 밑으로 
		if (_initialPos.y + 25 - _thisObj->GetTransform()->GetPosition().y > 2 && _thisObj->GetIsClimbDown())
			_thisObj->GetTransform()->SetPosition(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y + 2));
		
	}
}

void ClimbState::AdjustPosition(CLIMBLEVEL level)
{
	if (level == LEVEL_ONE)
	{
		//밑에서 위로 
		if (_thisObj->GetTransform()->GetPosition().y + 4 - _thisObj->GetLadderPos().y > 0)
			_thisObj->GetTransform()->Translate(Vector2(0, -2));
	}
	else if (level == LEVEL_TWO)
	{
		if (_thisObj->GetTransform()->GetPosition().y - _thisObj->GetLadderPos().y > 15 && !_thisObj->GetIsClimbDown())
		{
			_thisObj->GetTransform()->SetPosition(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y - 2));
		}
		//위에서 밑으로 
		if (_initialPos.y + 25 - _thisObj->GetTransform()->GetPosition().y > 2 && _thisObj->GetIsClimbDown())
			_thisObj->GetTransform()->SetPosition(Vector2(_thisObj->GetTransform()->GetPosition().x, _thisObj->GetTransform()->GetPosition().y + 2));
	}
}

