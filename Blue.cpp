#include "stdafx.h"
#include "Blue.h"
#include "Bullet.h"
#include "CharacterManager.h"


Blue::Blue()
{
	SetSprite(IMAGEMANAGER->FindImage("Blue_Enemy"));
}

HRESULT Blue::Init()
{
	_isMoving = true; 
	return S_OK;
}

void Blue::Render()
{
	GameObject::Render();
}

void Blue::Update()
{
	_fireTimer++; 
	GameObject::Update();
	EnemyMove();
	
	RayHit hit;
	if (_isMoveRight)
		hit = PHYSICSMANAGER->RayCast(_transform->GetPosition(), Vector2::right, 200);
	else
		hit = PHYSICSMANAGER->RayCast(_transform->GetPosition(), Vector2::left, 200);

	for (auto f : hit.GetFixtures()) //모든 충돌 검사 
	{
		Character* character = dynamic_cast<Character*>((GameObject*)f->GetBody()->GetUserData());
		if (!character) continue; 
		_isMoving = false; 
		BulletFire(); 
		return;
	}
	if (!_isMoving)
	{
		SetSprite(IMAGEMANAGER->FindImage("Blue_Enemy"));
	}
	_isMoving = true;
}

void Blue::EnemyMove()
{
	SetDeltaTime(0.4);
	if (_isMoving)
	{
		if (_name == "Blue1")
		{
			if (_transform->GetPosition().x < Hyolim_LeftTop(Vector2(84, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = true;
			}
			else if (_transform->GetPosition().x > Hyolim_LeftTop(Vector2(600, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = false;
			}

			if (_isMoveRight) //오른쪽으로 
			{
				_transform->SetFlip(false);;
				_transform->SetPosition(Vector2(_transform->GetPosition().x + 2, _transform->GetPosition().y));
			}
			else //왼쪽으로 
			{
				_transform->SetFlip(true);
				_transform->SetPosition(Vector2(_transform->GetPosition().x - 2, _transform->GetPosition().y));
			}
		}

		if (_name == "Blue2")
		{
			if (_isMoveRight) //오른쪽으로 
			{
				_transform->SetFlip(false);
				_transform->SetPosition(Vector2(_transform->GetPosition().x + 2, _transform->GetPosition().y));
			}
			else //왼쪽으로 
			{
				_transform->SetFlip(true);
				_transform->SetPosition(Vector2(_transform->GetPosition().x - 2, _transform->GetPosition().y));
			}

			if (_transform->GetPosition().x < Hyolim_LeftTop(Vector2(935, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = true;
			}
			else if (_transform->GetPosition().x > Hyolim_LeftTop(Vector2(2000, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = false;
			}
		}

		//getName = Blue3
		if (_name == "Blue3")
		{
			if (_transform->GetPosition().x < Hyolim_LeftTop(Vector2(2175, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = true;
			}
			else if (_transform->GetPosition().x > Hyolim_LeftTop(Vector2(3550, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = false;
			}

			if (_isMoveRight)
			{
				_transform->SetFlip(false);
				_transform->SetPosition(Vector2(_transform->GetPosition().x + 2, _transform->GetPosition().y));
			}
			else
			{
				_transform->SetFlip(true);
				_transform->SetPosition(Vector2(_transform->GetPosition().x - 2, _transform->GetPosition().y));
			}
		}
	}
}

void Blue::BulletFire()
{
	SetDeltaTime(0.8);
	if (_fireTimer != 0 && _fireTimer % BULLETTIMER == 0) 
	{
		if (_name != "Blue1" && _name != "Blue3" && _name != "Blue2")  return;

		Bullet* _bullet = new Bullet;

		if (GetSprite()->GetFlipX() == false)
		{
			SetSprite(IMAGEMANAGER->FindImage("Blue_Enemy_Fire"));
			_transform->SetFlip(false);

			_bullet->Enemy_BulletFire(_transform->GetPosition(), 4, false);
		}

		else if (GetSprite()->GetFlipX() == true)
		{
			SetSprite(IMAGEMANAGER->FindImage("Blue_Enemy_Fire"));
			_transform->SetFlip(true);

			_bullet->Enemy_BulletFire(_transform->GetPosition(), -4, false);
		}

		_fireTimer = 0;
	}
}



