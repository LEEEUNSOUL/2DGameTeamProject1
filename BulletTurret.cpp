#include "stdafx.h"
#include "BulletTurret.h"
#include "Bullet.h"
#include "Character.h"

BulletTurret::BulletTurret()
{
}


BulletTurret::~BulletTurret()
{
}

HRESULT BulletTurret::Init()
{

	return S_OK;
}

void BulletTurret::Render()
{
	GameObject::Render(); 

	//IMAGEMANAGER->DrawTextA(30, 40, L"EnemyBullet" + to_wstring(_bullet->GetTransform()->GetPosition().x), 10, DefaultBrush::white);
}

void BulletTurret::Update()
{
	GameObject::Update();
	_fireTimer++;
	BulletFire(); 
}

void BulletTurret::BulletFire()
{
	if (_fireTimer != 0 && _fireTimer % BULLETTIMER == 0) /*&&*/ //_isFire)
	{
		auto _bullet = new Bullet;
		_bullet->Enemy_BulletFire(Vector2(_transform->GetPosition().x-40, _transform->GetPosition().y-15), -10, false);
		_fireTimer = 0;		
	}
}

