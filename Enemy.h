#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
private: 

public:
	Enemy() { _physics = new Physics(); };
	~Enemy() {};

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(); 
	virtual void EnemyMove(); 
	virtual void BulletFire(); 

};

