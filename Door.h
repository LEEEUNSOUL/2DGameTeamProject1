#pragma once
#include "GameObject.h"
#include "Character.h"

class Door : public GameObject
{
private:
	Character* character;

	bool _isDoor1Opening;
	bool _isDoor2Opening;

public:
	Door() { _physics = new Physics(); };
	~Door() {};

	virtual HRESULT Init() override;
	virtual void Update() override;

	void Door1Opening();
	void Door2Opening();

	bool GetIsDoor1Opening() { return _isDoor1Opening; }
	void SetIsDoor1Opening(bool isOpening) { _isDoor1Opening = isOpening; }

	bool GetIsDoor2Opening() { return _isDoor2Opening; }
	void SetIsDoor2Opening(bool isOpening) { _isDoor2Opening = isOpening; }
};