#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	_transform = new Transform();
}

void GameObject::SetSprite(Image* sprite)
{
	_sprite = sprite;
	_currentPosition = Vector2(0, 1);
	_count = 0;
}

void GameObject::Release()
{
	if (_parent)
		_parent->RemoveChild(this);
	_physics->GetBody()->SetUserData(nullptr);
	delete _transform;
	delete _physics;
	delete this;
}

Image* GameObject::GetSprite()
{
	return _sprite;
}


void GameObject::SetCollisionEnterFunc(function<void(GameObject*, GameObject*)> enter)
{
	_callBack._enter = enter;
}

void GameObject::SetCollisionStayFunc(function<void(GameObject*, GameObject*)> stay)
{
	_callBack._stay = stay;
}

void GameObject::SetCollisionExitFunc(function<void(GameObject*, GameObject*)> exit)
{
	_callBack._exit = exit;
}

void GameObject::Update()
{
	Object::Update();
	if (!_sprite || !_sprite->IsFrameImage())
		return;

	if(_sprite->GetUpdateAnimation())
		_count++;
	if ((int)(TIMEMANAGER->GetFPS()*_deltaTime / _count) == 1)
	{
		_currentPosition.x = (int)(_currentPosition.x + 1) % (_sprite->GetMaxFrameX());
		_count = 0;
	}
	_currentPosition.y = 0;
}

void GameObject::Render()
{
	if (!_sprite)
		return;

	Vector2 position = _transform->GetPosition();
	_sprite->SetAngle(_transform->GetRotation());
	_sprite->SetScale(_transform->GetScale());
	_sprite->SetAlpha(_transform->GetAlpha());
	_sprite->SetSize(_transform->GetSize());
	_sprite->SetFlip(_transform->GetFlip(), false);

	if (_sprite->IsFrameImage())
		_sprite->FrameRender(position.x, position.y, _currentPosition.x, _isUI, Pivot::CENTER);
	else
		_sprite->Render(position.x, position.y, Pivot::CENTER, _isUI);
}