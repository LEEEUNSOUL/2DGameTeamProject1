#pragma once

#define Deg2Rad 3.1415f/180
#define Rad2Deg 180.f/3.1415f

class Vector3
{
private:
	float x;
	float y;
	float z;
public:
	Vector3() {};
	Vector3(float x, float y,float z) : x(x), y(y),z(z) {};

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }

	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }

	static Vector3 Lerp(Vector3 a, Vector3 b, float i);
	static void Swap(Vector3* a, Vector3* b);
	static float Dot(Vector3 a, Vector3 b);
	static Vector3 Cross(Vector3 a, Vector3 b);

	Vector3 Normalize();
	float Magnitude();
	float SqrMagnitude();
	Vector3 Rotate(float rotation,Vector3 axis);

	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forword;
	static const Vector3 back;
	static const Vector3 zero;

	Vector3 operator-(const Vector3& right);
	Vector3 operator+(const Vector3&  right);
	Vector3 operator*(float right);
	Vector3 operator/(int right);
	Vector3 operator*(const Vector3& right);
	Vector3 operator/(const Vector3& right);
	void operator+=(const Vector3&  right);
	void operator-=(const Vector3&  right);
	bool operator==(const Vector3& right);
};

