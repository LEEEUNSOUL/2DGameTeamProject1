#pragma once
#include "Item.h"

class Key : public Item
{
private:

public:
	Key() {};
	~Key() {};
	virtual HRESULT Init() override;
	virtual void Update() override;

	virtual void UseItem(string name) override;
};