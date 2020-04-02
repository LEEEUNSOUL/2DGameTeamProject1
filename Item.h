#pragma once
#include "GameObject.h"
#include <list>

class Olaf;
class Erik;
class Baleog;

//class Key;
//class Meat;
//class Tomato;
//class Shoes;

class CharacterManager;

class Item : public GameObject
{
protected:
	CharacterManager* _cm;
	int _itemNum = 0;

public:
	Item()
	{
		_physics = new Physics();
	}
	~Item() {}

	virtual HRESULT Init() override;
	virtual void Update() override;

	virtual void UseItem(string name) {};

	void SetLink(CharacterManager* cm)
	{
		_cm = cm;
	}

	void SetItemNum(int itemNum) { _itemNum = itemNum; }
	int GetItemNum() { return _itemNum; }
};