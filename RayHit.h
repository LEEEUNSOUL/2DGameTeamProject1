#pragma once
#include "Box2D/Box2D.h"
#include "Vector2.h"

class RayHit
{
private:
	list<b2Fixture*> _fixtures;
	Vector2 _collisionPoint = Vector2::zero;
	Vector2 _normalVector = Vector2::zero;
public:
	RayHit(b2Fixture* fixture, Vector2 collisionPoint, Vector2 normalVector);
	RayHit() {};

	void AddFixture(b2Fixture* fixture) { _fixtures.push_back(fixture); }
	b2Fixture* GetFixture() 
	{ 
		if (!_fixtures.size())
			return nullptr;
		return *_fixtures.begin(); 
	}
	Vector2 GetCollisionPoint() { return _collisionPoint; }
	Vector2 GetNormalVector() { return _normalVector; }
	list<b2Fixture*> GetFixtures() { return _fixtures; }
};

