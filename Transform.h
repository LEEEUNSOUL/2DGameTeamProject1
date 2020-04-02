#pragma once
#include "Vector2.h"

class Transform
{
private:

	Vector2 _position;
	Vector2 _size;

	int _frameX;
	int _frameY;

	float _rotation = 0;
	float _alpha = 1;
	float _scale = 1;

	bool _isFlip = false;
public:
	Transform();
	~Transform();

	//Getter
	Vector2 GetPosition() { return _position; }
	Vector2 GetSize() { return _size; }
	float GetRotation() { return _rotation; }
	float GetAlpha() { return _alpha; }
	float GetScale() { return _scale; }
	float GetFrameX() { return _frameX; }
	float GetFrameY() { return _frameY; }
	bool GetFlip() { return _isFlip; }

	//Setter 
	void SetPosition(Vector2 pos) { _position = pos; }
	void SetPosX(float posX) { _position.x = posX; }
	void SetPosY(float posY) { _position.y = posY; }
	void SetScale(float scale) { _scale = scale; }
	void SetRotation(float rotation) { _rotation = rotation; }
	void SetSize(Vector2 size) { _size = size; }
	void SetAlpha(float alpha) { _alpha = alpha; }
	void SetFlip(bool isFlip) { _isFlip = isFlip; }
	void Translate(Vector2 dir)
	{
		_position += dir;
	}
};

