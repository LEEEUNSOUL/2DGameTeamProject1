#pragma once
#include "GameObject.h"
#include "Character.h"

class ElectricBox : public GameObject
{
private:
	float _timer=0;
	Character* character;

public:
	ElectricBox();
	~ElectricBox();

	virtual HRESULT Init() override;
	virtual void Update() override;

};

