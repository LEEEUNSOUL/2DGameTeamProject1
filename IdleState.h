#pragma once
#include "State.h"
#include "Character.h"

class IdleState : public State
{
public:
	IdleState(Character* thisObj) : State(thisObj) {}
	virtual void UpdateState() override;
	virtual void EnterState() override;
	virtual void ExitState() override;
};

