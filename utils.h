#pragma once
#define PI 3.141592654f
#define PI2 PI * 2

namespace SEVENTEEN_UTIL
{
	//�Ÿ�(����) �˾ƿ��� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//�� ���� ���̰��� �˾ƿ��� �Լ�
	float getAngle(float x1, float y1, float x2, float y2);
}