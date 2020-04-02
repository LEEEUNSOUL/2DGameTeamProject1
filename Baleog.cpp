#include "stdafx.h"
#include "Baleog.h"
#include "Door.h"

Baleog::Baleog()
{
	_sprite = IMAGEMANAGER->FindImage("Baleog_Idle");
}


Baleog::~Baleog()
{

}

HRESULT Baleog::Init()
{
	Character::Init();

	return S_OK;
}

void Baleog::UseKeyAtKeyhole()
{
	for (int i = 0; i < _vInvenBaleog.size(); i++)
	{
		if (_vInvenBaleog[i]->GetName() == "Key")
		{
			_door->SetIsDoor1Opening(true);
		}
	}
};
