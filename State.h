#pragma once
class Character;
class State abstract //추상클래스
{
protected:
	Character* _thisObj;
public:
	State() {}
	State(Character* thisObj) : _thisObj(thisObj) {}

	virtual void EnterState() {}
	virtual void UpdateState() {}
	virtual void ExitState() {}
};

