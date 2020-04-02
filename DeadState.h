#pragma once
#include "State.h"
#include "Character.h"

class DeadState : public State
{
private:
	int _count = 0;
public:

	DeadState(Character* thisObj) : State(thisObj) {}

	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


};

