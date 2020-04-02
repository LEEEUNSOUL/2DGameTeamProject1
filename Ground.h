#pragma once
#include "GameObject.h"
#include "Character.h"

class Ground : public GameObject
{
private:
	Character* character;
	bool _inArea = false;
	Ground* ground;

public:
	Ground();
	~Ground();

	virtual HRESULT Init();
	virtual void Update() override;
};