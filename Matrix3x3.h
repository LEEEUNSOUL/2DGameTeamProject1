#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include "Matrix2x2.h"

#pragma comment (lib,"d2d1.lib")

class Vector3;
class Matrix3x3
{
public:
	float m[3][3];

	Matrix3x3(float _11, float _12, float _13,
		float _21, float _22, float _23,
		float _31, float _32, float _33);

	Matrix3x3() {};

	Matrix3x3 operator*(Matrix3x3 right);

	static Vector3 Mul(Vector3 left, Matrix3x3 right);
	static const Matrix3x3 identity;

	float GetDeterminant();
	float GetCofactor(int i, int j);
	Matrix3x3 GetTransposedMatrix();
	Matrix3x3 GetInverseMatrix();
	Matrix2x2 GetSubMatrix(int i,int j);

	D2D1_MATRIX_3X2_F To_D2D1_Matrix_3x2_F();
};

