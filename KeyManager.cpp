#include "stdafx.h"
#include "KeyManager.h"



bool KeyManager::IsStayKeyDown(int key)
{
	bool keyState = GetAsyncKeyState(key) & 0x8000;
	return keyState;
}

bool KeyManager::IsOnceKeyDown(int key)
{
	bool keyState = GetAsyncKeyState(key) & 0x8000;
	bool result = (keyState && keyStates[key] != KeyState::Down && keyStates[key] != KeyState::Stay) ? true : false;

	if (result)
		keyStates[key] = KeyState::Down;

	if (keyStates[key] == KeyState::Down)
		return true;
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	bool keyState = GetAsyncKeyState(key) & 0x8000;
	bool result = (!keyState && (keyStates[key] == KeyState::Down || keyStates[key] == KeyState::Stay)) ? true : false;
	if (result)
		keyStates[key] = KeyState::Up;

	if (keyStates[key] == KeyState::Up)
		return true;
	return result;
}

void KeyManager::Update()
{
	for (auto k : keyStates)
	{
		bool keyState = GetAsyncKeyState(k.first) & 0x8000;
		switch (k.second)
		{
		case KeyState::Down:
			if (keyState)
				keyStates[k.first] = KeyState::Stay;
			else
				keyStates[k.first] = KeyState::Up;
			break;
		case KeyState::Stay:
			if (!keyState)
				keyStates[k.first] = KeyState::Up;
			break;
		case KeyState::Up:
			if (keyState)
				keyStates[k.first] = KeyState::Down;
			else
				keyStates[k.first] = KeyState::None;
			break;
		}
	}
}

Vector2 KeyManager::GetMousePosition()
{
	return mousePosition;
}

void KeyManager::SetMousePosition(Vector2 mousePosition)
{
	this->mousePosition = mousePosition;
}
