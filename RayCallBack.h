#pragma once
#include "Vector2.h"
#include "RayHit.h"

class RayCallBack : public b2RayCastCallback
{
private:
	RayHit hitInfo;
public:
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,const b2Vec2& normal, float32 fraction);
	RayHit GetHitInfo() { return hitInfo; }
};

