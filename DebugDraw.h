#pragma once
#include "Box2D/Box2D.h"
#include <list>
#include "Vector2.h"

using namespace std;

struct LineInfo
{
	Vector2 _startPosition;
	Vector2 _endPosition;
};

class DebugDraw : public b2Draw
{
private:
	list<LineInfo> lineData;
public:
	static DebugDraw* GetInstance();
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	virtual void DrawTransform(const b2Transform& xf) override;
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
	void DrawLine(Vector2 point1, Vector2 point2);
	void Update();
	void Render();
};

