#pragma once
#include "Enemy.h"
#include "Bullet.h"

#define BULLETTIMER 200

class BulletTurret : public Enemy
{
private:
	Bullet* _bullet;
	int _fireTimer;
	bool _isFire = true; 
public:
	BulletTurret();
	~BulletTurret();

	virtual HRESULT Init() override;
	virtual void Render() override; 
	virtual void Update() override;
	virtual void BulletFire() override;
};

