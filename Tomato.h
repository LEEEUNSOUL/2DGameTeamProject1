#pragma once
#include "Item.h"
#include "Character.h"

class Tomato : public Item
{
private:

public:
	Tomato() {};
	~Tomato() {};
	virtual HRESULT Init() override;

	virtual void UseItem(string name) override;
};