#include "stdafx.h"
#include "DeadState.h"


void DeadState::EnterState()
{
	_thisObj->GetPhysics()->GetBody()->SetLinearVelocity({ 0,_thisObj->GetPhysics()->GetBody()->GetLinearVelocity().y });
	_thisObj->GetPhysics()->SetGravityScale(0);
	_thisObj->GetPhysics()->SetIsSensor(true);
	_thisObj->GetSprite()->SetUpdateAnimation(false);
	_count = TIMEMANAGER->getWorldTime();
}

void DeadState::UpdateState()
{
	if (TIMEMANAGER->getWorldTime() - _count > 2)
	{
		_thisObj->AddAnimationCount();
		_count = TIMEMANAGER->getWorldTime();
	}
	if(_thisObj->GetSprite()->GetMaxFrameX() -1 == _thisObj->GetCurrentPosition().x)
	{
		_thisObj->SetIsDead(true);
	}
	
}

void DeadState::ExitState()
{
}

