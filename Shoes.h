#pragma once
#include "Item.h"

class Shoes : public Item
{
private:

public:
	Shoes() {};
	~Shoes() {};
	virtual HRESULT Init() override;
	virtual void Update() override;

	virtual void UseItem(string name) override;
};