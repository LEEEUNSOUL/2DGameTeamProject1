#include "stdafx.h"
#include "RayHit.h"

RayHit::RayHit(b2Fixture * fixture, Vector2 collisionPoint, Vector2 normalVector)
{
	for (auto f = fixture; f != nullptr; f = f->GetNext())
		_fixtures.push_back(fixture);
	_collisionPoint = collisionPoint * PIXELTOMETER;
	_normalVector = normalVector * PIXELTOMETER;
}
