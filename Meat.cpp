#include "stdafx.h"
#include "Meat.h"
#include "Character.h"

HRESULT Meat::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character")
		{
			thisObj->GetSprite()->SetSize(Vector2(38, 38));
			Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();
			this->SetItemNum((character->GetInventory()).size());
			character->GetInventory().push_back(this);

			this->GetPhysics()->GetBody()->SetUserData(NULL);
			this->GetParent()->RemoveChild(this);
		}
	});

	return S_OK;
}

void Meat::Update()
{
	Item::Update();
}

void Meat::UseItem(string name)
{
	for (Object* ob : GetParent()->GetChildren())
	{
		if (ob->GetName() == name)
			((Character*)ob)->SetHP(min(((Character*)ob)->GetHP() + 2, 3));
	}


	
}