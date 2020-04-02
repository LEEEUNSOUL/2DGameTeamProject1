#pragma once
#include "State.h"
#include "Character.h"
#include "Image.h"

enum CLIMBLEVEL
{
	LEVEL_ZERO,
	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_THREE
};

class ClimbState : public State
{
private:

	CLIMBLEVEL _level;
	Vector2 _initialPos;
	int _count = 0;

public:

	ClimbState(Character* thisObj) : State(thisObj) {}


	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


	//스무스한 좌표 보정 함수 
	void AdjustPosition();
	void AdjustPosition(CLIMBLEVEL level);

};

