#pragma once
#include "gameObject.h"
#include "Character.h"
class BrokenWall : public GameObject
{
private:
	Character* character;

	float _timer;
	bool _isBroken = false;

public:
	BrokenWall();
	~BrokenWall();

	virtual HRESULT Init() override;
	virtual void Update() override;

	bool GetIsBroken() { return _isBroken; }

};

