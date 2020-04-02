#pragma once
#include "GameObject.h"
#include "State.h"

#define MAXHP 3

class State;
class Item;

enum ATKType
{
	KNIFE_ATTACK,
	ARROW,
	HEAD_BUTT,
	SHIELD_UP
};

enum STOPTYPE
{
	NONE,
	WALL,
	ENEMY,
	GROUND,
	TELEPORT
};

class Character : public GameObject
{
private:
	State* _state;
	ATKType _atkType;
	STOPTYPE _stopType;

	int _hp = 2;
	bool _usedShoe = false;
	bool _isShield = false;
	bool _isClimbing = false;
	bool _isClimbDown = false;
	bool _isClimbUp = false;
	bool _isDead = false;
	Vector2 _ladderPos;

	vector<Item*> _Inventory;

public:
	Character() { _physics = new Physics(); }

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;

	void ChangeState(State* state);

	//getter 
	ATKType GetATKType() { return _atkType; }
	STOPTYPE GetStopType() { return _stopType; }
	vector<Item*> &GetInventory() { return _Inventory; }
	int GetHP() { return _hp; }
	bool GetIfUsedShoe() { return _usedShoe; }
	bool GetShield() { return _isShield; }
	bool GetIsClimbing() { return _isClimbing; }
	bool GetIsClimbDown() { return _isClimbDown; }
	bool GetIsClimbUp() { return _isClimbUp; }
	bool GetIsDead() { return _isDead; }
	Vector2 GetLadderPos() { return _ladderPos; }
	State* GetState() { return _state; }


	//setter
	void SetATKType(ATKType type) { _atkType = type; }
	void SetStopType(STOPTYPE stoptype) { _stopType = stoptype; }
	void SetHP(int hp)
	{
		_hp = hp;
		if (_hp <= 0)
			_isDead = true;
	}
	void SetIfUsedShoe(bool trueOrFalse) { _usedShoe = trueOrFalse; }
	void SetShield(bool shield) { _isShield = shield; }
	void SetIsClimbing(bool climbing) { _isClimbing = climbing; }
	void SetIsClimbDown(bool climbDown) { _isClimbDown = climbDown; }
	void SetIsClimbUp(bool climbUp) { _isClimbUp = climbUp; }
	void SetLadderPos(Vector2 pos) { _ladderPos = pos; }
	void SetIsDead(bool isDead) { _isDead = isDead; }

};

