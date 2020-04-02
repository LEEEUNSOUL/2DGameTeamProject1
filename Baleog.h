#pragma once
#include "Character.h"
#include <vector>

class Door;

class Baleog : public Character
{
private:
	vector<GameObject*> _vInvenBaleog;
	Door* _door;

public:

	Baleog();
	~Baleog();

	virtual HRESULT Init() override;

	vector<GameObject*> GetVInvenBaleog() { return _vInvenBaleog; }

	// ������ ���� �Լ�
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


	// ������ ��ġ ã���ִ� �Լ�
	int GetKeyLocation()
	{
		for (int i = 0; i < _vInvenBaleog.size(); i++)
		{
			if (_vInvenBaleog[i]->GetName() == "key")
			{
				return i;
			}
		}
	}
	int GetTomatoLocation()
	{
		for (int i = 0; i < _vInvenBaleog.size(); i++)
		{
			if (_vInvenBaleog[i]->GetName() == "tomato")
			{
				return i;
			}
		}
	}
	int GetMeatLocation()
	{
		for (int i = 0; i < _vInvenBaleog.size(); i++)
		{
			if (_vInvenBaleog[i]->GetName() == "meat")
			{
				return i;
			}
		}
	}
	int GetShoeLocation()
	{
		for (int i = 0; i < _vInvenBaleog.size(); i++)
		{
			if (_vInvenBaleog[i]->GetName() == "shoe")
			{
				return i;
			}
		}
	}

};