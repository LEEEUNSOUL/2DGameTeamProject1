#pragma once
#include "GameObject.h"
#include "Character.h"
#include <string>
 

class Grinder: public GameObject
{
private:
	float _timer=0;
	Character* character;
	bool _isDown = false;


public:
	Grinder();
	~Grinder();

	virtual HRESULT Init() override;
	virtual void Update() override;

};

