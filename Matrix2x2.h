#pragma once


class Matrix2x2
{
public:
	float m[2][2];

	Matrix2x2(float _11, float _12, float _21, float _22);
	Matrix2x2() {};

	Matrix2x2 operator*(Matrix2x2 right);

	static const Matrix2x2 identity;

	float GetDeterminant();
	Matrix2x2 GetTransposedMatrix();
};

