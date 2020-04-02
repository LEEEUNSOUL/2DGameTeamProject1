#pragma once
#include "Character.h"
#include <vector>

class Door;

class Olaf : public Character
{
private:
	vector<GameObject*> _vInvenOlaf;
	Door* _door;

public:

	Olaf();
	~Olaf();

	virtual HRESULT Init() override;

	vector<GameObject*> GetVInvenOlaf() { return _vInvenOlaf; }

	// 아이템 쓰는 함수
	void EatMeat()
	{
		if (GetHP() < 2)
		{
			SetHP(GetHP() + 2);
		}
		else if (GetHP() == 2)
		{
			SetHP(GetHP() + 1);
		}
	};
	void EatTomato() 
	{
		if (GetHP() < MAXHP)
		{
			SetHP(GetHP() + 1);
		}
	};
	void UseKeyAtKeyhole();
	void UseShoe() 
	{
		SetIfUsedShoe(true);
	};

	// 아이템 위치 찾아주는 함수
	int GetKeyLocation()
	{
		for (int i = 0; i < _vInvenOlaf.size(); i++)
		{
			if (_vInvenOlaf[i]->GetName() == "key")
			{
				return i;
			}
		}
	}
	int GetTomatoLocation()
	{
		for (int i = 0; i < _vInvenOlaf.size(); i++)
		{
			if (_vInvenOlaf[i]->GetName() == "tomato")
			{
				return i;
			}
		}
	}
	int GetMeatLocation()
	{
		for (int i = 0; i < _vInvenOlaf.size(); i++)
		{
			if (_vInvenOlaf[i]->GetName() == "meat")
			{
				return i;
			}
		}
	}
	int GetShoeLocation()
	{
		for (int i = 0; i < _vInvenOlaf.size(); i++)
		{
			if (_vInvenOlaf[i]->GetName() == "shoe")
			{
				return i;
			}
		}
	}
};

