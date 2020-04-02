#pragma once
#include "GameObject.h"
#include "Character.h"

class GravityZone :	public GameObject
{
private:
	Character* character;

public:
	GravityZone() { _physics = new Physics(); };
	~GravityZone() {};

	virtual HRESULT Init() override;
	virtual void Update() override;
};