#pragma once
#include "State.h"
#include "Character.h"

class StopState : public State
{
private:

	float _count; //����ī��Ʈ�� float�̿���. 

public:
	StopState(Character* thisObj) : State(thisObj) { }
	virtual void EnterState() override;
	virtual void UpdateState() override;
};

