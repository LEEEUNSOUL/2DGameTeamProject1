#pragma once
#include "Vector2.h"
#include "Box2D/Box2D.h"

enum SHAPETYPE
{
	BOX,
	CIRCLE
};

class Physics
{

protected:

	float _friction = 0;
	float _gravityScale = 0;
	int _groupIndex = 0;
	bool _ignoreCollision = false;
	bool _isSensor = false;
	Vector2 _position;
	SHAPETYPE _shapeType = BOX;
	b2BodyType _bodyType;
	Vector2 _velocity;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	uint16 _categoryBit;

public:
	Physics();
	~Physics();

	//GETTER
	b2Body* GetBody() { return _body; }
	b2Fixture* GetFixture() { return _fixture; }
	float GetFriction() { return _friction; }

	int GetGroupIndex() { return _groupIndex; }
	Vector2 GetPosition() { return _position; }
	SHAPETYPE GetShapeType() { return _shapeType; }
	b2BodyType GetBodyType() { return _bodyType; }
	Vector2 GetVelocity() { return _velocity; }
	bool GetIgnoreCollision() { return _ignoreCollision; }
	float GetGravityScale() { return _gravityScale; }
	bool GetIsSensor() { return _isSensor; }
	uint16 GetCategoryBit() { return _categoryBit; }

	//SETTER
	void SetBody(b2Body* body) { _body = body; }
	void SetFixture(b2Fixture* fixture) { _fixture = fixture; }
	void SetFriction(float friction)
	{
		_friction = friction;
		_body->GetFixtureList()->SetFriction(_friction);
	}
	void SetGroupIndex(int index)
	{
		b2Filter filter;
		filter.groupIndex = index;
		GetFixture()->SetFilterData(filter);
		//_groupIndex = index;
	}
	void SetCategoryBit(uint16 categoryBit)
	{
		b2Filter filter = GetFixture()->GetFilterData();
		filter.categoryBits = categoryBit;
		GetFixture()->SetFilterData(filter);
	}

	void SetBodyType(b2BodyType type) { _bodyType = type; }
	void SetShapeType(SHAPETYPE type) { _shapeType = type; }
	void SetIsSensor(bool isSensor)
	{
		_isSensor = isSensor;
		_body->GetFixtureList()->SetSensor(isSensor);
	}
	void SetVelocity(Vector2 velocity)
	{
		_velocity = velocity;
		_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
	}
	void SetGravityScale(float gravityScale)
	{
		_gravityScale = gravityScale;
		_body->SetGravityScale(gravityScale);
	}
	void SetIgnoreCollison(bool isIgnore) { _ignoreCollision = isIgnore; }

	void ApplyForce(b2Vec2 force)
	{
		if (_velocity == Vector2::zero)
			_velocity = Vector2(force.x, force.y);
		else
			_velocity = Vector2(_body->GetLinearVelocity().x, _body->GetLinearVelocity().y);
		_body->ApplyForceToCenter(force, true);
	}
};

