#include "stdafx.h"
#include "GreenAlien.h"
#include "CharacterManager.h"

#include "Bullet.h"
#include <string.h>


GreenAlien::GreenAlien()
{
	SetSprite(IMAGEMANAGER->FindImage("Enemy_01_move"));
}

HRESULT GreenAlien::Init()
{
	_isMoving = true;
	return S_OK;
}

void GreenAlien::Render()
{
	GameObject::Render(); 
}

void GreenAlien::Update()
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
		if (!character) 
			continue;
		_isMoving = false;
		BulletFire();
		return;
	}
	if (!_isMoving)
	{
		SetSprite(IMAGEMANAGER->FindImage("Enemy_01_move"));
	}
	_isMoving = true;


}

void GreenAlien::EnemyMove()
{
	if (_isMoving)
	{
		if (_name == "GreenAlien1")
		{
			if (_transform->GetPosition().x < Hyolim_LeftTop(Vector2(1415, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = true;
			}
			else if (_transform->GetPosition().x > Hyolim_LeftTop(Vector2(1850, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = false;
			}
		}

		if (_name == "GreenAlien2")
		{
			if (_transform->GetPosition().x < Hyolim_LeftTop(Vector2(1800, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = true;
			}
			else if (_transform->GetPosition().x > Hyolim_LeftTop(Vector2(2203, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = false;
			}
		}

		if (_name == "GreenAlien3")
		{
			if (_transform->GetPosition().x < Hyolim_LeftTop(Vector2(3374, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = true;
			}
			else if (_transform->GetPosition().x > Hyolim_LeftTop(Vector2(3634, 0), _transform->GetSize().x, _transform->GetSize().y).x)
			{
				_isMoveRight = false;
			}
		}

		if (_isMoveRight)
		{
			_transform->SetFlip(false);;
			_transform->SetPosition(Vector2(_transform->GetPosition().x + 1, _transform->GetPosition().y));
		}

		else
		{
			_transform->SetFlip(true);
			_transform->SetPosition(Vector2(_transform->GetPosition().x - 1, _transform->GetPosition().y));
		}
	}
}

void GreenAlien::BulletFire()
{
	if (_fireTimer != 0 && _fireTimer % BULLETTIMER == 0)
	{
		if (_name != "GreenAlien1" && _name != "GreenAlien2" && _name != "GreenAlien3")  return;

		Bullet* _bullet = new Bullet;

		if (GetTransform()->GetFlip() == false)
		{
			SetSprite(IMAGEMANAGER->FindImage("Enemy_01_fire"));
			_transform->SetFlip(false);
			_bullet->Enemy_BulletFire(_transform->GetPosition(), 2, false);
		}

		else if (GetTransform()->GetFlip() == true)
		{
			SetSprite(IMAGEMANAGER->FindImage("Enemy_01_fire"));
			_transform->SetFlip(true);
			_bullet->Enemy_BulletFire(_transform->GetPosition(), -2, false);
		}
		_fireTimer = 0;
	} 
}
