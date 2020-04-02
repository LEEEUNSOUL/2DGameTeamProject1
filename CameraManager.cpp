#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
	_transform = new Transform();
	SetPosition(Vector2(0,0));
	_transform->SetRotation(0);
	_transform->SetScale(1);
}

void CameraManager::SetPosition(Vector2 position)
{
	auto background = IMAGEMANAGER->FindImage("Background");
	Vector2 cameraRange = Vector2(background->GetWidth(), background->GetHeight());
	cameraRange = cameraRange * BACKGROUND_SCALE;
	cameraRange = cameraRange - Vector2(WINSIZEX, WINSIZEY);
	float x = Clamp(position.x, -cameraRange.x / 2, cameraRange.x / 2);
	_position = Vector2(x, position.y);
	_transform->SetPosition(_position*-1 + Vector2(WINSIZEX / 2, WINSIZEY / 2));
}

void CameraManager::SetRotation(float rotation)
{
	_rotation = rotation;
	_transform->SetRotation(rotation);
}

void CameraManager::SetScale(float scale)
{
	_scale = scale;
	_transform->SetScale(scale);
}

void CameraManager::Update()
{
	Vector2 nowPosition;

	if (!_isMoving)
		return;

	_lerpCount += 1.f / (TIMEMANAGER->GetFPS() * _moveTime);

	nowPosition = Vector2::Lerp(_startPosition, _endPosition, _lerpCount);
	SetPosition(nowPosition);

	if (_lerpCount >= 1)
	{
		_lerpCount = 0;
		_isMoving = false;
	}
}

void CameraManager::MoveCamera(Vector2 endPosition, float moveTime)
{
	_isMoving = true;
	_startPosition = GetPosition();
	_endPosition = endPosition;
	_moveTime = moveTime;
}