#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

HRESULT Obstacle::Init()
{
	_physics = new Physics;
	_isMoveUp = _isMoveDown = false;
	_moveTimer = 0;


	if (_name == "ground")
	{
		_obsType = GROUND;
	}
	else if (_name == "wall")
	{
		_obsType = WALL;
	}
	else if (_name == "pan")
	{
		_obsType = PAN;
	}

	SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
	{
		if (targetObj->GetTag() == "player")
		{
			Player* player = (Player *)targetObj->GetPhysics()->GetBody()->GetUserData();
			player->SetState(IDLE);

			//발판이라면 
			if (thisObj->GetName() == "pan")
			{
				Obstacle* obs = (Obstacle *)thisObj->GetParent()->GetChildByName("wall");
				obs->SetIsMove(true);

			}
		}
	});

	return S_OK;
}

void Obstacle::Release()
{
}

void Obstacle::Update()
{
	

	if(_obsType == WALL) MoveUp();
}

void Obstacle::Render()
{
	RECT rc = RectMakeCenter(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetSize().x, _transform->GetSize().y);
	IMAGEMANAGER->FillRectangle(rc, DefaultBrush::gray);

	if(_obsType == WALL && _moveTimer !=0)
	IMAGEMANAGER->DrawTextA(50, 50, L"Wall Move Timer: " + to_wstring(TIMEMANAGER->getWorldTime() - _moveTimer), 20, DefaultBrush::white, DWRITE_TEXT_ALIGNMENT_LEADING);
}

void Obstacle::MoveUp()
{

	if (_isMoveDown)
	{
		if (_transform->GetPosition().y < WINSIZEY / 2 - 100)
		{
			_transform->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y + 1));
		}
		else
		{
			_isMoveDown = false;
		}
	}else if (_isMoveUp)
	{
		if (_transform->GetPosition().y > WINSIZEY / 2 - 200)
		{
			_transform->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y - 1));
			_moveTimer = TIMEMANAGER->getWorldTime();

		}
		else
		{
			//5초 지나면 
			if (TIMEMANAGER->getWorldTime() - _moveTimer > 5)
			{
				_isMoveUp = false;
				_isMoveDown = true;
				_moveTimer = 0;
			}
		}

	}


}
