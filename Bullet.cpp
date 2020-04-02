#include "stdafx.h"
#include "Bullet.h"
#include "Character.h"
#include "StopState.h"
#include "DeadState.h"

Bullet::Bullet(bool isPlayer)
{
	_physics = new Physics;

	//Character & bullet 충돌처리 
	if (isPlayer)
	{
		SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
		{
			if (targetObj->GetTag() != "Enemy")
				return;
			SceneManager::GetInstance()->GetNowScene()->RemoveChild(targetObj);
			thisObj->Release();
		});
	}
	else
	{
		SetCollisionEnterFunc([&](GameObject* thisObj, GameObject* targetObj)
		{
			//타깃이 플레이어라면 HP 다운 
			if (targetObj->GetTag() != "Character")
				return;

			//Character* character = (Character*)targetObj->GetPhysics()->GetBody()->GetUserData();
			((Character*)targetObj)->SetHP(((Character*)targetObj)->GetHP() - 1);
			if (((Character*)targetObj)->GetHP() > 0)
			{
				((Character*)targetObj)->SetStopType(STOPTYPE::ENEMY);
				((Character*)targetObj)->ChangeState(new StopState((Character*)targetObj));
			}
			else
			{
				targetObj->SetSprite(IMAGEMANAGER->FindImage(targetObj->GetName() + "_Hit"));
				((Character*)targetObj)->ChangeState(new DeadState((Character*)targetObj));
			}
			thisObj->Release();
		});
	}

}

void Bullet::release()
{
}

void Bullet::Enemy_BulletFire(Vector2 pos, float speed, bool num)
{
	//BULLETMAKE 
	Bullet* _EnemyBullet = new Bullet;
	_EnemyBullet->SetSprite(IMAGEMANAGER->FindImage("LaserBullet"));
	_EnemyBullet->SetName("EnemyBullet");
	_EnemyBullet->GetTransform()->SetSize(Vector2(44, 10));
	_EnemyBullet->GetTransform()->SetPosition(pos);


	_EnemyBullet->GetTransform()->SetFlip(num);

	//BULLET BODY 
	_EnemyBullet->GetPhysics()->SetBodyType(b2_dynamicBody);
	_EnemyBullet->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_EnemyBullet));
	_EnemyBullet->GetPhysics()->SetGravityScale(0);
	_EnemyBullet->GetPhysics()->SetVelocity(Vector2(speed, 0));
	_EnemyBullet->GetPhysics()->SetShapeType(BOX);

	//BULLET SHAPE & FIXTURE
	b2Shape* _EnemyBulletShape = PHYSICSMANAGER->CreateShape(_EnemyBullet->GetPhysics()->GetBody(),
		_EnemyBullet->GetTransform()->GetSize().x,
		_EnemyBullet->GetTransform()->GetSize().y);

	_EnemyBullet->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_EnemyBullet->GetPhysics()->GetBody(), _EnemyBulletShape));
	_EnemyBullet->GetPhysics()->SetIsSensor(true);
	SceneManager::GetInstance()->GetNowScene()->AddChild(_EnemyBullet);

}


void Bullet::Baleog_BulletFire(Vector2 pos, float speed, bool num)
{
	//BULLETMAKE 
	Bullet* _baleogArrow = new Bullet(true);
	_baleogArrow->SetSprite(IMAGEMANAGER->FindImage("Baleog_arrow"));
	_baleogArrow->SetName("Baleog_arrow");
	_baleogArrow->GetTransform()->SetSize(Vector2(33.6f, 12));
	_baleogArrow->GetTransform()->SetPosition(pos);
	_baleogArrow->GetTransform()->SetFlip(num);

	//BULLET BODY 
	_baleogArrow->GetPhysics()->SetBodyType(b2_dynamicBody);
	_baleogArrow->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_baleogArrow));
	_baleogArrow->GetPhysics()->SetGravityScale(0);
	_baleogArrow->GetPhysics()->SetVelocity(Vector2(speed, 0));
	_baleogArrow->GetPhysics()->SetShapeType(BOX);

	//BULLET SHAPE & FIXTURE
	b2Shape* _beleogArrrowShape = PHYSICSMANAGER->CreateShape(_baleogArrow->GetPhysics()->GetBody(),
		_baleogArrow->GetTransform()->GetSize().x,
		_baleogArrow->GetTransform()->GetSize().y);
	_baleogArrow->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_baleogArrow->GetPhysics()->GetBody(), _beleogArrrowShape));

	_baleogArrow->GetPhysics()->SetIsSensor(true);

	SceneManager::GetInstance()->GetNowScene()->AddChild(_baleogArrow);
}

void Bullet::removeBullet(int arrNum)
{

}
