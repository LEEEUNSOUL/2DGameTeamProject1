#pragma once
#include "GameObject.h"

class Door;
class Character;
class KeyHole : public GameObject
{
private:
	bool _inArea = false;
	Door* _doorTop1;
	Door* _doorBottom1;
	list<Character*> _characters;
public:
	KeyHole();
	~KeyHole();

	virtual HRESULT Init() override;
	virtual void Update() override;

	void SetDoorTop1Link(Door* door) { _doorTop1 = door; }
	void SetDoorBottom1Link(Door* door) { _doorBottom1 = door; }
};

