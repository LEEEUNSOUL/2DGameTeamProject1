#pragma once
#include "Object.h"
#include "Physics.h"
#include "Transform.h"
#include "gameNode.h"
#include <functional>
#include <list>

using namespace std;
class GameObject;

struct CollisionCallBack
{
	function<void(GameObject*, GameObject*)> _enter = [](GameObject*, GameObject*) {};
	function<void(GameObject*, GameObject*)> _stay = [](GameObject*, GameObject*) {};
	function<void(GameObject*, GameObject*)> _exit = [](GameObject*, GameObject*) {};
};

class b2Body;
class b2Fixture;

class GameObject : public Object
{
protected:


	Physics*			_physics;
	Transform*			_transform;
	Image*				_sprite = nullptr;
	CollisionCallBack	_callBack;

	Vector2 _currentPosition = Vector2(0, 1);
	float _deltaTime = 0.3f;
	bool _loop;
	int _count = 0;
	int _zOrder = 0;
	bool _isUI = false;

public:

	GameObject();




	virtual void Render() override;
	virtual void Update() override;
	virtual void Release() override;


	//CALLBACK 
	void SetCollisionEnterFunc(function<void(GameObject*, GameObject*)> enter);
	void SetCollisionStayFunc(function<void(GameObject*, GameObject*)> stay);
	void SetCollisionExitFunc(function<void(GameObject*, GameObject*)> exit);

	//GETTER
	CollisionCallBack GetCollisionCallBack() { return _callBack; }
	Image* GetSprite();
	Physics* GetPhysics() { return _physics; }
	Transform* GetTransform() { return _transform; }
	Vector2 GetCurrentPosition() { return _currentPosition; }
	int GetZOrder() { return _zOrder; }
	bool GetIsUI() { return _isUI; }

	//SETTER
	void SetSprite(Image* sprite);
	void SetDeltaTime(float deltaTime) { _deltaTime = deltaTime; }
	void SetCurrentPosition(Vector2 vec) { _currentPosition = vec; }
	void SetZOrder(int zOrder)
	{
		_zOrder = zOrder;
	}
	void SetIsUI(bool isUI) { _isUI = isUI; }

	void AddAnimationCount() { _count++; }

	template <typename T>
	static GameObject* CreateObject(T, GameObject* parent = nullptr)
	{
		GameObject* newObject = (GameObject *) new T();

		if (parent == nullptr)
		{
			SceneManager::GetInstance()->GetNowScene()->AddChild(newObject);
		}
		else
			newObject->SetParent(parent);

		return newObject;
	}
};

