#include "stdafx.h"
#include "Door.h"
#include "playGround.h"

HRESULT Door::Init()
{
	_isDoor1Opening = _isDoor2Opening = false;

	return S_OK;
}

void Door::Update()
{
	GameObject::Update();

	if (_tag == "door1")
	{
		if (_isDoor1Opening) { Door1Opening(); }
	}
	if (_tag == "door2")
	{
		if (_isDoor2Opening) { Door2Opening(); }
	}

}

void Door::Door1Opening()
{
	if (_name == "doorTop1")
	{
		if (_transform->GetPosition().y > Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 1250 - /*76*/ 45),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_transform->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y - 1.0f));
			_physics->SetIsSensor(true);
		}
		else
		{
			float time = TIMEMANAGER->getWorldTime();
			if (time > 2)
			{
				SetIsDoor1Opening(false);

				time = 0.0f;
			}
		}
	}
	else if (_name == "doorBottom1")
	{
		if (_transform->GetPosition().y < Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 1326 + /*76*/ 45),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_transform->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y + 1.0f));
			_physics->SetIsSensor(true);
		}
		else
		{
			float time = TIMEMANAGER->getWorldTime();
			if (time > 2)
			{
				SetIsDoor1Opening(false);

				time = 0.0f;
			}
		}
	}
}

void Door::Door2Opening()
{
	if (_name == "doorTop2")
	{
		if (_transform->GetPosition().y > Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 295 - /*76*/ 45),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_transform->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y - 1.0f));
			_physics->SetIsSensor(true);
		}
		//else
		//{
		//	float time = TIMEMANAGER->getWorldTime();
		//	if (time > 2)
		//	{
		//		SetIsDoor2Opening(false);
		//		SetIsDoor2Closing(true);

		//		time = 0.0f;
		//	}
		//}
	}
	else if (_name == "doorBottom2")
	{
		if (_transform->GetPosition().y < Hyolim_LeftTop(Vector2(_transform->GetPosition().x, 371 + /*76*/ 45),
			_transform->GetSize().x*BACKGROUND_SCALE, _transform->GetSize().y*BACKGROUND_SCALE).y)
		{
			_transform->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y + 1.0f));
			_physics->SetIsSensor(true);
		}
		//else
		//{
		//	float time = TIMEMANAGER->getWorldTime();
		//	if (time > 2)
		//	{
		//		SetIsDoor2Opening(false);
		//		SetIsDoor2Closing(true);

		//		time = 0.0f;
		//	}
		//}
	}
}