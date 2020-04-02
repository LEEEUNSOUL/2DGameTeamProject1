#include "stdafx.h"
#include "Olaf.h"
#include "Door.h"

Olaf::Olaf()
{
	_sprite = IMAGEMANAGER->FindImage("Olaf_Idle");
}


Olaf::~Olaf()
{
}

HRESULT Olaf::Init()
{
	Character::Init();

	return S_OK;
}

void Olaf::UseKeyAtKeyhole()
{
	for (int i = 0; i < _vInvenOlaf.size(); i++)
	{
		if (_vInvenOlaf[i]->GetName() == "Key")
		{
			_door->SetIsDoor1Opening(true);
		}
	}
};
