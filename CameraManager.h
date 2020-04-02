#pragma once
#include "singletonBase.h"

class CameraManager : public singletonBase<CameraManager>
{
private:
	Transform* _transform;

	Vector2 _startPosition;
	Vector2 _endPosition;
	Vector2 _position;
	float _lerpCount = 0;
	float _moveTime = 0;
	float _scale;
	float _rotation;
	bool _isMoving = false;
public:
	CameraManager();

	Transform* GetTransfrom() { return _transform; }
	void Update();
	void MoveCamera(Vector2 endPosition, float moveTime);

	void SetPosition(Vector2 position);
	Vector2 GetPosition() { return _position; }

	void SetRotation(float rotation);
	float GetRotation() { return _rotation; }

	void SetScale(float scale);
	float GetScale() { return _scale; }

	bool GetIsMoving() { return _isMoving; }
};

