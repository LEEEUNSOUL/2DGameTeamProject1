#include "stdafx.h"
#include "Tomato.h"
#include "Character.h"

HRESULT Tomato::Init()
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

void Tomato::UseItem(string name)
{


	//character->SetHP(min(character->GetHP() + 1, 3));

	for (Object* ob : GetParent()->GetChildren())
	{
		if (ob->GetName() == name)
			((Character*)ob)->SetHP(min(((Character*)ob)->GetHP() + 1, 3));
	}
}