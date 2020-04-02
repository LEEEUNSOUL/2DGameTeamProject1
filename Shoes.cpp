#include "stdafx.h"
#include "Shoes.h"
#include "Character.h"

HRESULT Shoes::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character")
		{
			Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();
			this->SetItemNum((character->GetInventory()).size());
			character->GetInventory().push_back(this);
			this->GetPhysics()->GetBody()->SetUserData(NULL);
			this->GetParent()->RemoveChild(this);
		}
	});

	return S_OK;
}

void Shoes::Update()
{
	Item::Update();
}

void Shoes::UseItem(string name)
{
	for (Object* ob : GetParent()->GetChildren())
	{
		if (ob->GetName() == name)
			((Character*)ob)->SetIfUsedShoe(true);
	}

	
}