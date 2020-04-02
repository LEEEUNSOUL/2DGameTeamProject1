#include "stdafx.h"
#include "RayCallBack.h"

float32 RayCallBack::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	if (!hitInfo.GetFixtures().size())
		hitInfo = RayHit(fixture, Vector2(point.x, point.y), Vector2(normal.x, normal.y));
	else
		hitInfo.AddFixture(fixture);
	return 1;
}
