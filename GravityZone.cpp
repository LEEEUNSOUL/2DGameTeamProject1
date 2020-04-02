#include "stdafx.h"
#include "GravityZone.h"
#include "Olaf.h"
#include "Erik.h"
#include "Baleog.h"

HRESULT GravityZone::Init()
{
	_physics->GetFixture()->SetSensor(true);

	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character") return;

		Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();

		if (character->GetIfUsedShoe() == false)
		{
			targetObj->GetPhysics()->GetBody()->SetGravityScale(-0.05f);
		}
	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character") return;

		Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();

		character->GetPhysics()->GetBody()->SetGravityScale(1);

	});

	return S_OK;
}

void GravityZone::Update()
{
	GameObject::Update();
}
