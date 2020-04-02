#pragma once

#include "Enemy.h"
#define BULLETTIMER 250

class CharacterManager;

class GreenAlien : public Enemy
{
private: 
	bool _isMoving; 
	bool _isMoveRight; 
	int _fireTimer;

	CharacterManager* _cm;

public:
	GreenAlien();
	~GreenAlien() {};

	virtual HRESULT Init() override;
	virtual void Render() override; 
	virtual void Update() override;
	virtual void EnemyMove() override;
	virtual void BulletFire() override;

	void SetLink(CharacterManager* cm) { _cm = cm; }
};

