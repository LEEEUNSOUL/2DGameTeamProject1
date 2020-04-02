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
	//�θ��� Init�� �ҷ����ֱ� ���ؼ�
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
