#include "stdafx.h"
#include "Vector2.h"

const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::right = Vector2(1, 0);
const Vector2 Vector2::left = Vector2(-1, 0);
const Vector2 Vector2::down = Vector2(0, -1);
const Vector2 Vector2::zero = Vector2(0, 0);

bool Vector2::operator==(const Vector2& right)
{
	return (right.x == x) && (right.y == y);
}

bool Vector2::operator!=(const Vector2& right)
{
	return (right.x != x) || (right.y != y);
}

Vector2 Vector2::operator-(const Vector2& right)
{
	return Vector2(x - right.x, y - right.y);
}

Vector2 Vector2::operator+(const Vector2& right)
{
	return Vector2(x + right.x, y + right.y);
}

void Vector2::operator+=(const Vector2& right)
{
	this->x += right.x;
	this->y += right.y;
}


void Vector2::operator-=(const Vector2& right)
{
	this->x -= right.x;
	this->y -= right.y;
}

Vector2 Vector2::operator*(float right)
{
	return Vector2(x * right, y * right);
}

Vector2 Vector2::operator*(const Vector2& right)
{
	return Vector2(x * right.x, y * right.y);
}

Vector2 Vector2::operator/(const Vector2& right)
{
	return Vector2(x / right.x, y / right.y);
}

Vector2 Vector2::operator/(int right)
{
	return Vector2(x / right, y / right);
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float i)
{
	float x = (1 - i)*a.x + i * b.x;
	float y = (1 - i)*a.y + i * b.y;

	return Vector2(x, y);
}

void Vector2::Swap(Vector2* a, Vector2* b)
{
	Vector2 temp = *a;
	*a = *b;
	*b = temp;
}

float Vector2::SqrMagnitude()
{
	return pow(x, 2) + pow(y, 2);
}

float Vector2::Magnitude()
{
	return sqrt(SqrMagnitude());
}

Vector2 Vector2::Normalize()
{
	return Vector2(x, y) / Magnitude();
}

float Vector2::Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::Rotate(float rotation)
{
	float newX = x * cos(rotation*Deg2Rad) - y * sin(rotation*Deg2Rad);
	float newY = x * sin(rotation*Deg2Rad) + y * cos(rotation*Deg2Rad);
	return Vector2(newX, newY);
}