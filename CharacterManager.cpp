#include "stdafx.h"
#include "CharacterManager.h"
#include "IdleState.h"


void CharacterManager::AddCharacter(Character* character)
{
	if (_characters.size())
		character->SetAllowsUpdate(false);

	_characters.push_back(character);
}

void CharacterManager::ChangeCharacter(bool changeState)
{
	if (changeState)
		_characters[_nowCharacterNumber]->ChangeState(new IdleState(_characters[_nowCharacterNumber]));
	_characters[_nowCharacterNumber]->SetAllowsUpdate(false);
	_nowCharacterNumber = (_nowCharacterNumber + 1) % _characters.size();
	_characters[_nowCharacterNumber]->SetAllowsUpdate(true);
	CAMERAMANAGER->MoveCamera(_characters[_nowCharacterNumber]->GetTransform()->GetPosition(),1.f);
}

void CharacterManager::ChangeCharacter(int index)
{
	for (int i = 0; i < _characters.size(); i++)
	{
		_characters[i]->SetAllowsUpdate(false); 
	}
	_characters[index]->SetAllowsUpdate(true);
	CAMERAMANAGER->MoveCamera(_characters[index]->GetTransform()->GetPosition(), 0.1f);
}

void CharacterManager::RemoveCharacter()
{
	for (int i = 0; i < _characters.size(); i++)
	{
		if (_characters[i]->GetIsDead())
		{
			if(i ==_nowCharacterNumber)
				ChangeCharacter(false);
			_nowCharacterNumber = max(_nowCharacterNumber-1, 0);
			_characters.erase(_characters.begin()+i);
			_characters[_nowCharacterNumber]->SetAllowsUpdate(true);
		}
	}
}

void CharacterManager::Update()
{
	//나중에 스텝끝나고 릴리즈 
	RemoveCharacter();

	if(!CAMERAMANAGER->GetIsMoving() && _characters.size()>0)
		CAMERAMANAGER->SetPosition(_characters[_nowCharacterNumber]->GetTransform()->GetPosition());

	if (KEYMANAGER->IsOnceKeyDown(VK_CONTROL) && !CAMERAMANAGER->GetIsMoving())
		ChangeCharacter();
}