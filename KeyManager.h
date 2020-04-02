#pragma once
#include <map>
#include "Vector2.h"

using namespace std;

enum class KeyState
{
	None,
	Down,
	Stay,
	Up
};

class KeyManager : public singletonBase<KeyManager>
{
private:
	map<int, KeyState> keyStates;
	Vector2 mousePosition;
public:

	bool IsStayKeyDown(int key);		
	bool IsOnceKeyDown(int key);
	bool IsOnceKeyUp(int key);

	Vector2 GetMousePosition();
	void SetMousePosition(Vector2 mousePosition);
	void Update();
};

