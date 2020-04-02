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

	//Enemy �Ѿ� �߻� & ������ ���� �Լ� 
	void Enemy_BulletFire(Vector2 pos, float speed, bool num);

	//Baleog �Ѿ� �߻� & ������ ���� �Լ� 
	void Baleog_BulletFire(Vector2 pos, float speed, bool num);

	void removeBullet(int arrIndex);

};

