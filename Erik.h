#pragma once
#include "Character.h"
#include <vector>

class Door;

class Erik : public Character
{
private:
	vector<GameObject*> _vInvenErik;
	Door* _door;

public:

	Erik();
	~Erik();

	virtual HRESULT Init() override;

	vector<GameObject*> GetVInvenErik() { return _vInvenErik; }

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
		for (int i = 0; i < _vInvenErik.size(); i++)
		{
			if (_vInvenErik[i]->GetName() == "key")
			{
				return i;
			}
		}
	}
	int GetTomatoLocation()
	{
		for (int i = 0; i < _vInvenErik.size(); i++)
		{
			if (_vInvenErik[i]->GetName() == "tomato")
			{
				return i;
			}
		}
	}
	int GetMeatLocation()
	{
		for (int i = 0; i < _vInvenErik.size(); i++)
		{
			if (_vInvenErik[i]->GetName() == "meat")
			{
				return i;
			}
		}
	}
	int GetShoeLocation()
	{
		for (int i = 0; i < _vInvenErik.size(); i++)
		{
			if (_vInvenErik[i]->GetName() == "shoe")
			{
				return i;
			}
		}
	}

};

