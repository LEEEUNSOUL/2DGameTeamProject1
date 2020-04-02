#include "stdafx.h"
#include "DebugDraw.h"

bool operator==(LineInfo a, LineInfo b)
{
	return (a._startPosition == b._startPosition) && (a._endPosition == b._endPosition);
}

DebugDraw* DebugDraw::GetInstance()
{
	static DebugDraw* instance = new DebugDraw();
	return instance;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	for (int i = 0; i < vertexCount; i++)
	{
		Vector2 cameraPosition = Vector2::zero;
		Vector2 point1 = Vector2(vertices[i].x*METERTOPIXEL+ cameraPosition.x, vertices[i].y*METERTOPIXEL + cameraPosition.y);
		Vector2 point2;
		if (i + 1 == vertexCount)
			point2 = Vector2(vertices[0].x*METERTOPIXEL + cameraPosition.x, vertices[0].y*METERTOPIXEL + cameraPosition.y);
		else
			point2 = Vector2(vertices[i + 1].x*METERTOPIXEL + cameraPosition.x, vertices[i + 1].y*METERTOPIXEL + cameraPosition.y);
		IMAGEMANAGER->DrawLine(point1, point2, DefaultBrush::white,2);
	}
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	RECT rt;
	rt = 
	{
		LONG((center.x - radius) * METERTOPIXEL),
		LONG((center.y - radius) * METERTOPIXEL),
		LONG((center.x + radius) * METERTOPIXEL),
		LONG((center.y + radius) * METERTOPIXEL)
	};

	IMAGEMANAGER->DrawEllipse(rt,DefaultBrush::white,false,2);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{

}

void DebugDraw::DrawLine(Vector2 point1, Vector2 point2)
{
	LineInfo newLine;
	newLine._startPosition = point1;
	newLine._endPosition = point2;
	lineData.push_back(newLine);
}

void DebugDraw::Update()
{
	for (auto nowLine : lineData)
	{
		lineData.remove(nowLine);
		return;
	}
}

void DebugDraw::Render()
{
	for (auto nowLine : lineData)
		IMAGEMANAGER->DrawLine(nowLine._startPosition, nowLine._endPosition, DefaultBrush::white, 2);
}