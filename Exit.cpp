#include "stdafx.h"
#include "Exit.h"


Exit::Exit()
{
	_physics = new Physics();
}


Exit::~Exit()
{
}

HRESULT Exit::Init()
{
	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetName() == "Olaf")
		{
			_inArea_Olaf = true;
		}
		if (targetObj->GetName() == "Baleog")
		{
			_inArea_Baleog = true;
		}
		if (targetObj->GetName() == "Erik")
		{
			_inArea_Erik = true;
		}
	});

	SetCollisionExitFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetName() == "Olaf")
		{
			_inArea_Olaf = false;
		}
		if (targetObj->GetName() == "Baleog")
		{
			_inArea_Baleog = false;
		}
		if (targetObj->GetName() == "Erik")
		{
			_inArea_Erik = false;
		}
	});


	return S_OK;
}

void Exit::Update()
{
	if (_inArea_Olaf && _inArea_Erik && _inArea_Baleog)
	{
		exit(0);
	}
}
