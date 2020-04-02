#pragma once
#include "GameObject.h"

enum BULLETTYPE
{
	BALEOG_ARROW,
	ENEMY_BULLET
};

class Bullet : public GameObject
{
public:
	Bullet(bool isPlayer = false);

	virtual void release();

	//Enemy 총알 발사 & 움직임 관련 함수 
	void Enemy_BulletFire(Vector2 pos, float speed, bool num);

	//Baleog 총알 발사 & 움직임 관련 함수 
	void Baleog_BulletFire(Vector2 pos, float speed, bool num);

	void removeBullet(int arrIndex);

};

