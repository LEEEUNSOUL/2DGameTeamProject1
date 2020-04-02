#pragma once
#include "State.h"
#include "Character.h"

class JumpState : public State
{
private:
	int _jumpCount;
public:
	JumpState(Character* thisObj) : State(thisObj) {}
	virtual void UpdateState() override;
	virtual void EnterState() override;
	virtual void ExitState() override;
};

