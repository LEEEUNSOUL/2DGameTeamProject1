#pragma once
#include "State.h"
#include "Bullet.h"
#include "Character.h"

class AtkState : public State
{
private:
	int _count = 0;
	bool _isFire = false;
public:

	AtkState(Character* thisObj) : State(thisObj) {}

	virtual void EnterState() override;
	virtual void UpdateState() override;

};

