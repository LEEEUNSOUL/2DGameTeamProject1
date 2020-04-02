#pragma once
#include "State.h"
#include "Character.h"

class StopState : public State
{
private:

	float _count; //월드카운트가 float이에요. 

public:
	StopState(Character* thisObj) : State(thisObj) { }
	virtual void EnterState() override;
	virtual void UpdateState() override;
};

