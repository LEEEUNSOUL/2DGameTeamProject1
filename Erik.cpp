#include "stdafx.h"
#include "Erik.h"
#include "Door.h"

Erik::Erik()
{
	_sprite = IMAGEMANAGER->FindImage("Erik_Idle");
}


Erik::~Erik()
{
}

HRESULT Erik::Init()
{
	Character::Init();
	//부모의 Init을 불러와주기 위해서
	return S_OK;
}

void Erik::UseKeyAtKeyhole()
{
	for (int i = 0; i < _vInvenErik.size(); i++)
	{
		if (_vInvenErik[i]->GetName() == "Key")
		{
			_door->SetIsDoor1Opening(true);
		}
	}
};
