#pragma once
#include "GameObject.h"
#include "Character.h"

class ElectricRod: public GameObject
{
private:
	Character* character;
	float _timer = 0;
	bool _isActive = true;

public:
	ElectricRod();
	~ElectricRod();

	virtual HRESULT Init() override;
	virtual void Update() override;

	void SetActive(bool active) { _isActive = active; }
};

