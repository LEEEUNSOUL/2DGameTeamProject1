#pragma once
#include "Item.h"


class Character;

class Meat : public Item
{
private:
	Character* character;

public:
	Meat() {};
	~Meat() {};
	virtual HRESULT Init() override;
	virtual void Update() override;

	virtual void UseItem(string name) override;
};