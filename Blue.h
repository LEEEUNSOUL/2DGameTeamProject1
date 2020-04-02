#pragma once
#include "Enemy.h"
#define BULLETTIMER 220

class CharacterManager;

class Blue : public Enemy
{
private: 
	bool _isMoving; 
	bool _isMoveRight;
	int _fireTimer;

	CharacterManager* _cm;

public:
	Blue();
	~Blue() {};
	virtual HRESULT Init() override;
	virtual void Render() override; 
	virtual void Update() override;
	virtual void EnemyMove() override;
	virtual void BulletFire() override;

	void SetLink(CharacterManager* cm) { _cm = cm; }
};

