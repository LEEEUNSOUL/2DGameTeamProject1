#pragma once
#include "State.h"
#include "Character.h"

class InAirState : public State
{
public:
	InAirState(Character* thisObj) : State(thisObj) {}
	virtual void UpdateState() override;
	virtual void EnterState() override;
	virtual void ExitState() override;
};

