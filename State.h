#pragma once
class Character;
class State abstract //�߻�Ŭ����
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

