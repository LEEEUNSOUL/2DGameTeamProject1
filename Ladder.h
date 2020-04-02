#pragma once
#include "GameObject.h"
#include "Character.h"
#include "Ground.h"
#include <list>

class Ladder : public GameObject
{
private:
	Character* character;
	list<Character*> _lCharacterAtLadder;
	Ground* ground;

	bool	_reachedLadderTop = false;
	bool	_canGoUp = true;

	bool  _onSensor = false;


public:
	Ladder() { _physics = new Physics(); };
	~Ladder() {};

	virtual HRESULT Init() override;
	virtual void Update() override;

	void ClimbingLadder();

	void SetCanGoUp(bool yesOrNo) { _canGoUp = yesOrNo; }
};