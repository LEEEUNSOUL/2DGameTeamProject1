#include "stdafx.h"
#include "Key.h"
#include "Character.h"
#include "Door.h"

HRESULT Key::Init()
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

void Key::Update()
{
	Item::Update();
}

void Key::UseItem(string name)
{
	/*for (Object* ob : GetParent()->GetChildren())
	{
		if (ob->GetName() == name)
			((Character*)ob)->SetHP(min(((Character*)ob)->GetHP() + 2, 3));
	}*/
	/*for (Object* ob : _children)
	{
		if (ob->GetTag() != "Character") return;

		for (int i = 0; i < ((Character*)ob)->GetInventory().size(); i++)
		{
			if (((Character*)ob)->GetInventory()[i]->GetName() != "Key")
				return;
			((Door*)ob)->SetIsDoor1Opening(true);
		}
	}*/
}