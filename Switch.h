#pragma once
#include "GameObject.h"
#include "ElectricRod.h"
#include "Door.h"

class Switch: public GameObject
{
private:
	bool _inArea = false;
	bool _isPressed1 = false;
	bool _isPressed2 = false;

	int _timer = 0;

	ElectricRod* rod;
	Door* _doorTop2;
	Door* _doorBottom2;
public:
	Switch();
	~Switch();

	virtual HRESULT Init() override;
	virtual void Update() override;


	void SetDoorTop2Link(Door* door) { _doorTop2 = door; }
	void SetDoorBottom2Link(Door* door) { _doorBottom2 = door; }
};

