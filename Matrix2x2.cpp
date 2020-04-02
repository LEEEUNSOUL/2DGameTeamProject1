#include "stdafx.h"
#include "Matrix2x2.h"

const Matrix2x2 Matrix2x2::identity = Matrix2x2(1, 0, 0, 1);

Matrix2x2 Matrix2x2::operator*(Matrix2x2 right)
{
	Matrix2x2 result;
	result.m[0][0] = m[0][0] * right.m[0][0] + m[0][1] * right.m[1][0];
	result.m[0][1] = m[0][0] * right.m[0][1] + m[0][1] * right.m[1][1];
	result.m[1][0] = m[1][0] * right.m[0][0] + m[1][1] * right.m[1][0];
	result.m[1][1] = m[1][0] * right.m[0][1] + m[1][1] * right.m[1][1];

	return result;
}

float Matrix2x2::GetDeterminant()
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

Matrix2x2 Matrix2x2::GetTransposedMatrix()
{
	Matrix2x2 result = Matrix2x2(m[0][0],m[1][0],m[0][1],m[1][1]);
	return result;
}

Matrix2x2::Matrix2x2(float _11, float _12, float _21, float _22)
{
	m[0][0] = _11;
	m[0][1] = _12;
	m[1][0] = _21;
	m[1][1] = _22;
}