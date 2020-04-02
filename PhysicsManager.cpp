#include "stdafx.h"
#include "PhysicsManager.h"
#include "DebugDraw.h"
PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{

}

HRESULT PhysicsManager::Init()
{
	////물리 세계 초기화

	return S_OK;
}

void PhysicsManager::SetWorld(b2World* world)
{
	_world = world;

	DebugDraw::GetInstance()->SetFlags(b2Draw::e_shapeBit);
	_world->SetDebugDraw(DebugDraw::GetInstance());
	_world->SetContactListener(PHYSICSMANAGER);
}

void PhysicsManager::Release()
{
	SAFE_DELETE(_world);
}

void PhysicsManager::Update()
{
	SetBodyPosition();
	_world->Step(TIMEMANAGER->getElapsedTime(), 8, 3);

	for (b2Body* body = _world->GetBodyList(); body; body = body->GetNext())
	{
		if (!body->GetUserData())
		{
			b2Body* deletedObject = body;
			body = body->GetNext();
			_world->DestroyBody(deletedObject);
			continue;
		}

		GameObject* obj = (GameObject*)body->GetUserData();
		Physics* physics = obj->GetPhysics();
		Transform* transform = obj->GetTransform();
		Vector2 physicsPos = m2p(Vector2(body->GetPosition().x, body->GetPosition().y));


		obj->GetTransform()->SetRotation(body->GetAngle());
		obj->GetTransform()->SetPosition(Vector2(physicsPos.x, physicsPos.y));
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_F1))
		isDebug = !isDebug;

	if (isDebug)
		DebugDraw::GetInstance()->Update();
}

void PhysicsManager::Render()
{
	if (isDebug)
	{
		_world->DrawDebugData();
		DebugDraw::GetInstance()->Render();
	}
}



b2Body* PhysicsManager::CreateBody(GameObject * obj)
{
	b2BodyDef bodyDef;
	Physics* physics = obj->GetPhysics();
	Transform* transform = obj->GetTransform();

	Vector2 physicsPos = p2m(Vector2(transform->GetPosition().x, transform->GetPosition().y));

	bodyDef.type = physics->GetBodyType();
	bodyDef.userData = obj;
	bodyDef.fixedRotation = true;
	bodyDef.linearVelocity = b2Vec2(physics->GetVelocity().x, physics->GetVelocity().y);
	bodyDef.angle = obj->GetTransform()->GetRotation() * Rad2Deg;
	bodyDef.position.Set(physicsPos.x, physicsPos.y);
	bodyDef.allowSleep = true;

	return _world->CreateBody(&bodyDef);
}


b2Shape * PhysicsManager::CreateShape(b2Body * body, float width, float height)
{
	GameObject* obj = (GameObject*)body->GetUserData();
	Physics* physics = obj->GetPhysics();
	Transform* transform = obj->GetTransform();


	Vector2 physicsPos = p2m(Vector2(physics->GetPosition().x, physics->GetPosition().y));
	Vector2 dimension = p2m(Vector2(width, height));

	SHAPETYPE type = physics->GetShapeType();

	b2Shape* shape;

	if (type == BOX)
	{
		shape = new b2PolygonShape;
		((b2PolygonShape *)shape)->SetAsBox(dimension.x / 2, dimension.y / 2);
		return shape;
	}
	else
	{
		shape = new b2CircleShape;
		((b2CircleShape *)shape)->m_radius = transform->GetSize().x *PIXELTOMETER;
		((b2CircleShape *)shape)->m_p.Set(physicsPos.x, physicsPos.y);

		return shape;
	}

}

b2Shape * PhysicsManager::CreateShape(b2Body * body, bool transformApplied)
{
	GameObject* obj = (GameObject*)body->GetUserData();
	Physics* physics = obj->GetPhysics();
	Transform* transform = obj->GetTransform();

	Vector2 physicsPos = p2m(Vector2(physics->GetPosition().x, physics->GetPosition().y));

	SHAPETYPE type = physics->GetShapeType();
	b2Shape* shape;

	Vector2 size = transform->GetSize() * transform->GetScale();

	if (type == BOX)
	{
		shape = new b2PolygonShape;
		if (!transformApplied)
			((b2PolygonShape *)shape)->SetAsBox(obj->GetSprite()->GetWidth() *PIXELTOMETER / 2, obj->GetSprite()->GetHeight() *PIXELTOMETER / 2);
		else
			((b2PolygonShape *)shape)->SetAsBox(size.x* PIXELTOMETER / 2, size.y *PIXELTOMETER / 2);
		return shape;
	}
	else
	{
		shape = new b2CircleShape;
		((b2CircleShape *)shape)->m_radius = transform->GetSize().x *PIXELTOMETER;
		((b2CircleShape *)shape)->m_p.Set(physicsPos.x, physicsPos.y);

		return shape;
	}
}

b2Fixture* PhysicsManager::CreateFixture(b2Body * body, b2Shape * shape)
{
	GameObject* obj = (GameObject*)body->GetUserData();

	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = 1;
	fixtureDef.friction = obj->GetPhysics()->GetFriction();
	fixtureDef.filter.groupIndex = obj->GetPhysics()->GetGroupIndex();


	if (obj->GetName() == "bullet") fixtureDef.isSensor = true;
	else fixtureDef.isSensor = false;

	return body->CreateFixture(&fixtureDef);

}

void PhysicsManager::DestroyBody(b2Body * body)
{
	_world->DestroyBody(body);
}

RayHit PhysicsManager::RayCast(Vector2 startPoint, Vector2 direction, float distance)
{
	auto rayCallBack = new RayCallBack();
	Vector2 startPoint_World = startPoint * PIXELTOMETER;
	Vector2 endPoint_World = (startPoint + direction * distance) * PIXELTOMETER;
	b2Vec2 start = { startPoint_World.x,startPoint_World.y };
	b2Vec2 end = { endPoint_World.x,endPoint_World.y };
	_world->RayCast(rayCallBack, start, end);
	if (isDebug)
		DebugDraw::GetInstance()->DrawLine(startPoint, startPoint + direction * distance);
	return rayCallBack->GetHitInfo();
}

b2Body * PhysicsManager::CreateDefaultBody(GameObject * obj, float width, float height)
{
	//body 
	b2BodyDef bodyDef;
	Physics* physics = obj->GetPhysics();
	Transform* transform = obj->GetTransform();
	Vector2 physicsPos = p2m(Vector2(transform->GetPosition().x, transform->GetPosition().y));

	bodyDef.type = physics->GetBodyType();
	bodyDef.userData = obj;
	bodyDef.fixedRotation = true;
	bodyDef.linearVelocity = b2Vec2(physics->GetVelocity().x, physics->GetVelocity().y);
	bodyDef.angle = obj->GetTransform()->GetRotation() * Rad2Deg;
	bodyDef.position.Set(physicsPos.x, physicsPos.y);
	bodyDef.allowSleep = true;

	b2Body* newBody = _world->CreateBody(&bodyDef);

	//shape 
	b2PolygonShape newShape_box;
	Vector2 dimension = p2m(Vector2(width, height));
	newShape_box.SetAsBox(dimension.x / 2, dimension.y / 2);

	//fixture 
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &newShape_box;
	fixtureDef.density = 1;
	fixtureDef.friction = obj->GetPhysics()->GetFriction();
	fixtureDef.filter.groupIndex = obj->GetPhysics()->GetGroupIndex();

	if (obj->GetName() == "bullet") fixtureDef.isSensor = true;
	else fixtureDef.isSensor = false;

	//newBody->CreateFixture(&fixtureDef);

	obj->GetPhysics()->SetFixture(newBody->CreateFixture(&fixtureDef));

	return newBody;

}


//플레이어가 움직이면 physics 의 좌표도 움직이게 
void PhysicsManager::SetBodyPosition()
{
	for (b2Body* body = _world->GetBodyList(); body; body = body->GetNext())
	{
		GameObject* obj = (GameObject*)body->GetUserData();
		Vector2 pos = p2m(Vector2(obj->GetTransform()->GetPosition().x, obj->GetTransform()->GetPosition().y));

		body->SetAwake(true);
		body->SetTransform(b2Vec2(pos.x, pos.y), body->GetAngle());
	}
}

void PhysicsManager::IgnoreCollision(GameObject * obj1, GameObject * obj2)
{
	b2Filter filter1 = obj1->GetPhysics()->GetBody()->GetFixtureList()->GetFilterData();
	b2Filter filter2 = obj2->GetPhysics()->GetBody()->GetFixtureList()->GetFilterData();

	filter1.maskBits = ~filter2.categoryBits;
	filter2.maskBits = ~filter1.categoryBits;

	obj1->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(filter1);
	obj2->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(filter2);
}



void PhysicsManager::BeginContact(b2Contact * contact)
{
	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	//a나 b의 유저데이터가 있냐 없냐
	if (!a || !b)
		return;


	a->GetCollisionCallBack()._enter(a, b);
	b->GetCollisionCallBack()._enter(b, a);

}

void PhysicsManager::EndContact(b2Contact * contact)
{
	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (!a || !b)
		return;

	a->GetCollisionCallBack()._exit(a, b);
	b->GetCollisionCallBack()._exit(b, a);

}

void PhysicsManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (!a || !b)
		return;


	a->GetCollisionCallBack()._stay(a, b);
	b->GetCollisionCallBack()._stay(b, a);
}

