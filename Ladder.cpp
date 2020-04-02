#include "stdafx.h"
#include "Ladder.h"
#include "ClimbState.h"
#include "Ground.h"

HRESULT Ladder::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character") return;

		Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();
		_lCharacterAtLadder.push_back(character);

		Ground* ground = (Ground *)GetParent()->GetChildByName("Ground" + thisObj->GetName());
		character->SetLadderPos(ground->GetTransform()->GetPosition());

	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() != "Character") 
			return;

		Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();
		_lCharacterAtLadder.remove(character);
	});

	return S_OK;
}

void Ladder::Update()
{
	ClimbingLadder();
}

void Ladder::ClimbingLadder()
{
	for (Character* character : _lCharacterAtLadder)
	{
		if (!character->GetAllowsUpdate())
			return;

		//아래에서 위 
		if (!character->GetIsClimbing() && KEYMANAGER->IsOnceKeyDown(VK_UP))
		{
			character->ChangeState(new ClimbState(character));
			character->SetIsClimbing(true);
			//character->GetTransform()->SetPosition(Vector2(this->GetTransform()->GetPosition().x, character->GetTransform()->GetPosition().y));
		}
		
		//좌표 보정 
		if (character->GetIsClimbing())
		{
			if (this->GetTransform()->GetPosition().x - character->GetTransform()->GetPosition().x > 5)
			{
				character->GetTransform()->Translate(Vector2(5, 0));
			}
			else if (character->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x > 5)
			{
				character->GetTransform()->Translate(Vector2(-5, 0));
			}
		}
	}
}