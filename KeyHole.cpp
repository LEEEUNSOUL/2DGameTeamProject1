#include "stdafx.h"
#include "KeyHole.h"
#include "Door.h"
#include "Character.h"
#include "Item.h"

KeyHole::KeyHole()
{
	_physics = new Physics();
}

KeyHole::~KeyHole()
{
}

HRESULT KeyHole::Init()
{

	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character")
		{
			_characters.push_back((Character*)targetObj);
		}
	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "Character")
		{
			_characters.remove((Character*)targetObj);
		}
	});


	return S_OK;
}

void KeyHole::Update()
{
	GameObject::Update();

	for (auto c : _characters)
	{
		auto nowInventory = c->GetInventory();
		int keyCount = -1;
		for (int i = 0; i < nowInventory.size(); i++)
		{
			if (nowInventory[i]->GetName() == "Key")
				keyCount = i;
		}
		if (keyCount != -1 && KEYMANAGER->IsOnceKeyDown('E'))
		{

			//여기서 문을 열어야하죵 
			//GameObject* doorTop1 = (GameObject *)GetParent()->GetChildByName("doorTop1");
			//GameObject* doorTop2 = (GameObject *)GetParent()->GetChildByName("doorTop2");
			//GameObject* doorBottom1 = (GameObject *)GetParent()->GetChildByName("doorBottom1");
			//GameObject* doorBottom2 = (GameObject *)GetParent()->GetChildByName("doorBottom2");
			//obj->GetPhysics()->SetIsSensor(false);

			_doorBottom1->SetIsDoor1Opening(true);
			_doorTop1->SetIsDoor1Opening(true);
			c->GetInventory().erase(c->GetInventory().begin() + keyCount);
		}
	}
}
