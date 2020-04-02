#include "stdafx.h"
#include "Matrix3x3.h"
#include "Vector3.h"

const Matrix3x3 Matrix3x3::identity = Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);

Matrix3x3 Matrix3x3::operator*(Matrix3x3 right)
{
	Matrix3x3 result;

	result.m[0][0] = m[0][0] * right.m[0][0] + m[0][1] * right.m[1][0] + m[0][2] * right.m[2][0];
	result.m[0][1] = m[0][0] * right.m[0][1] + m[0][1] * right.m[1][1] + m[0][2] * right.m[2][1];
	result.m[0][2] = m[0][0] * right.m[0][2] + m[0][1] * right.m[1][2] + m[0][2] * right.m[2][2];

	result.m[1][0] = m[1][0] * right.m[0][0] + m[1][1] * right.m[1][0] + m[1][2] * right.m[2][0];
	result.m[1][1] = m[1][0] * right.m[0][1] + m[1][1] * right.m[1][1] + m[1][2] * right.m[2][1];
	result.m[1][2] = m[1][0] * right.m[0][2] + m[1][1] * right.m[1][2] + m[1][2] * right.m[2][2];

	result.m[2][0] = m[2][0] * right.m[0][0] + m[2][1] * right.m[1][0] + m[2][2] * right.m[2][0];
	result.m[2][1] = m[2][0] * right.m[0][1] + m[2][1] * right.m[1][1] + m[2][2] * right.m[2][1];
	result.m[2][2] = m[2][0] * right.m[0][2] + m[2][1] * right.m[1][2] + m[2][2] * right.m[2][2];

	return result;
}

Vector3 Matrix3x3::Mul(Vector3 left, Matrix3x3 right)
{
	Vector3 result;
	result.SetX(left.GetX() * right.m[0][0] + left.GetY() * right.m[1][0] + left.GetZ() * right.m[2][0]);
	result.SetY(left.GetX() * right.m[0][1] + left.GetY() * right.m[1][1] + left.GetZ() * right.m[2][1]);
	result.SetZ(left.GetX() * right.m[0][2] + left.GetY() * right.m[1][2] + left.GetZ() * right.m[2][2]);

	return result;
}

D2D1_MATRIX_3X2_F Matrix3x3::To_D2D1_Matrix_3x2_F()
{
	return D2D1::Matrix3x2F(m[0][0], m[0][1], m[1][0], m[1][1], m[2][0], m[2][1]);
}

float Matrix3x3::GetDeterminant()
{
	float a = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1];
	float b = m[0][0] * m[1][2] * m[2][1] + m[0][1] * m[1][0] * m[2][2] + m[0][2] * m[1][1] * m[2][0];
	return a-b;
}

Matrix3x3 Matrix3x3::GetTransposedMatrix()
{
	Matrix3x3 transposed = Matrix3x3(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1],m[2][1],m[0][2],m[1][2],m[2][2]);
	return transposed;
}

Matrix2x2 Matrix3x3::GetSubMatrix(int i,int j)
{
	Matrix2x2 result;
	int nowRow = 0;
	int nowCol = 0;

	for (int row = 0; row < 3; row++)
	{
		if (row == i-1)
			continue;

		for (int col = 0; col < 3; col++)
		{
			if (col == j-1)
				continue;
			result.m[nowRow][nowCol] = m[row][col];
			nowCol++;
		}
		nowCol = 0;
		nowRow++;
	}

	return result;
}

Matrix3x3::Matrix3x3(float _11, float _12, float _13,
	float _21, float _22, float _23,
	float _31, float _32, float _33)
{
	m[0][0] = (_11);
	m[0][1] = (_12);
	m[0][2] = (_13);
	m[1][0] = (_21);
	m[1][1] = (_22);
	m[1][2] = (_23);
	m[2][0] = (_31);
	m[2][1] = (_32);
	m[2][2] = (_33);
}

float Matrix3x3::GetCofactor(int i, int j)
{
	return pow(-1, i + j)*GetSubMatrix(i, j).GetDeterminant();
}

Matrix3x3 Matrix3x3::GetInverseMatrix()
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.m[i][j] = GetCofactor(i+1, j+1);
		}
	}

	float d = 1.f / GetDeterminant();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.m[i][j] *= d;
		}
	}
	return result.GetTransposedMatrix();
}