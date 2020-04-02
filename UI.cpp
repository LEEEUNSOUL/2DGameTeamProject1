#include "stdafx.h"
#include "UI.h"
#include "CharacterManager.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Update()
{
	_count++;
	UIKeyControl();
}

HRESULT UI::Init()
{
	for (int i = 0; i < 3; i++)
	{
		info[i].selectPos = 0;
		info[i].UIpos = Vector2(117 + i * 179,71);
	}
	_uiImage = IMAGEMANAGER->FindImage("UI");
	_uiImage->SetSize(Vector2(WINSIZEX + 4, 170));

	_hpImage = IMAGEMANAGER->FindImage("hp");
	_hpImage->SetSize(Vector2(17, 17));

	_selectImage = IMAGEMANAGER->FindImage("select");
	_selectImage->SetSize(Vector2(40, 40));
	return S_OK;
}

void UI::Render()
{
	DrawFace();
	_uiImage->Render(0, WINSIZEY - 170, Pivot::LEFT_TOP, true);
	for (int i = 0; i < _cm->GetCharacters().size(); i++)
	{
		string name = _cm->GetCharacters()[i]->GetName();
		for (int j = 0; j < _cm->GetCharacters()[i]->GetHP(); j++)
			_hpImage->Render(GetInfoByName(name).UIpos.x + j * 23, WINSIZEY - 170 + 115, Pivot::LEFT_TOP, true);
	}
	
	//SELECT
	for (int i = 0; i < _cm->GetCharacters().size(); i++)
	{
		string name = _cm->GetCharacters()[i]->GetName();
		//active 
		if (i == _cm->getNowCharacterNum() && !_isClicked)
		{
			if (_count>40 || !this->GetAllowsUpdate())
			{
				_selectImage->Render(GetInfoByName(name).UIpos.x+85 + (GetInfoByName(name).selectPos%2)*38, WINSIZEY - 125 + (GetInfoByName(name).selectPos / 2) * 43, Pivot::LEFT_TOP, true);
				if(_count>60 || !this->GetAllowsUpdate()) _count = 0;
			}
			continue;
		}
		_selectImage->Render(GetInfoByName(name).UIpos.x + 85 + (GetInfoByName(name).selectPos % 2) * 38, WINSIZEY - 125 + (GetInfoByName(name).selectPos / 2) * 43, Pivot::LEFT_TOP, true);
	}
	DrawInventory(); 
}

CharacterInfo UI::GetInfoByName(string name)
{
	if (name == "Baleog")
	{
		return info[1];
	}
	else if (name == "Erik")
	{
		return info[0];
	}
	else if (name == "Olaf")
	{
		return info[2];
	}
}

void UI::UIKeyControl()
{
	int nowCharacter = 0;
	if (_isClicked)
	{

		for (int i = 0; i < _cm->GetCharacters().size(); i++)
		{
			if (_cm->GetCharacters()[i]->GetName() != _owner)
				continue;
			nowCharacter = i;

			if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
			{
				_itemClicked->UseItem(_cm->GetCharacters()[i]->GetName());


				for (int k = 0; k < _cm->GetCharacters()[i]->GetInventory().size(); k++)
				{
					if (_cm->GetCharacters()[i]->GetInventory()[k] == _itemClicked)
					{
						_cm->GetCharacters()[i]->GetInventory().erase(_cm->GetCharacters()[i]->GetInventory().begin() + k);
						return;
					}
				}

			}
			if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
			{
				if (_inTrash)
				{
					nowCharacter = -1;
					_inTrash = false;
					break;
				}

				if (i == _cm->GetCharacters().size() - 1)
				{
					_inTrash = true;
					break;
				}
			}

			if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
			{
				if (_inTrash)
				{
					nowCharacter = _cm->GetCharacters().size()+1;
					_inTrash = false;
					break;
				}
				if (i == 0)
				{
					_inTrash = true;
					break;
				}
			}
		}


		if(_inTrash)
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
			{
				//pop back 
				for (int j = 0; j < _cm->GetCharacters().size(); j++)
				{
					if (_cm->GetCharacters()[j]->GetName() == _initialOwner)
					{
						for (int k = 0; k < _cm->GetCharacters()[j]->GetInventory().size(); k++)
						{
							if(_cm->GetCharacters()[j]->GetInventory()[k] == _itemClicked)
								_cm->GetCharacters()[j]->GetInventory().erase(_cm->GetCharacters()[j]->GetInventory().begin() + k);

						}
					}
				}
				_isClicked = false;
			}
		}
		else
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
			{
				_owner = _cm->GetCharacters()[(nowCharacter + 1) % _cm->GetCharacters().size()]->GetName();
				if (_owner != _initialOwner)
					_clickedNum = _cm->GetCharacters()[(nowCharacter + 1) % _cm->GetCharacters().size()]->GetInventory().size();
				else
					_clickedNum = GetInfoByName(_initialOwner).selectPos;
			}
			else if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
			{
				_owner = _cm->GetCharacters()[(nowCharacter - 1) % _cm->GetCharacters().size()]->GetName();
				if (_owner != _initialOwner)
					_clickedNum = _cm->GetCharacters()[(nowCharacter - 1) % _cm->GetCharacters().size()]->GetInventory().size();
				else
					_clickedNum = GetInfoByName(_initialOwner).selectPos;
			}

			if (!KEYMANAGER->IsOnceKeyDown(VK_RETURN))
				return;

			//pop back
			for (int j = 0; j < _cm->GetCharacters().size(); j++)
			{
				if (_cm->GetCharacters()[j]->GetName() == _initialOwner)
				{
					for (int k = 0; k < _cm->GetCharacters()[j]->GetInventory().size(); k++)
					{
						if (_cm->GetCharacters()[j]->GetInventory()[k] == _itemClicked)
							_cm->GetCharacters()[j]->GetInventory().erase(_cm->GetCharacters()[j]->GetInventory().begin() + k);
					}
				}
				if(_cm->GetCharacters()[j]->GetName() == _owner)
				{
					_cm->GetCharacters()[j]->GetInventory().push_back(_itemClicked);
				}
			}

			_isClicked = false;
		}	
	}
	else
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_CONTROL))
			_cm->SetNowCharacterNum((_cm->getNowCharacterNum() + 1) % _cm->GetCharacters().size());

		nowCharacter = _cm->getNowCharacterNum();
		string name = _cm->GetCharacters()[nowCharacter]->GetName();

		//그 자리에 아이템이 있다면 ISCLICKED
		if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			for (int j = 0; j < _cm->GetCharacters()[nowCharacter]->GetInventory().size(); j++)
			{
				if (info[nowCharacter].selectPos != _cm->GetCharacters()[nowCharacter]->GetInventory()[j]->GetItemNum())
					continue;

				_isClicked = true;
				_itemClicked = _cm->GetCharacters()[nowCharacter]->GetInventory()[j];
				_initialOwner = _owner = _cm->GetCharacters()[nowCharacter]->GetName();
			}
		}

		//그게 아니라면 SELECT 이동 
		if (KEYMANAGER->IsOnceKeyDown(VK_LEFT) && (GetInfoByName(name).selectPos) % 2 != 0)
			info[nowCharacter].selectPos -= 1;
		if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT) && (GetInfoByName(name).selectPos + 1) % 2 != 0)
			info[nowCharacter].selectPos += 1;
		if (KEYMANAGER->IsOnceKeyDown(VK_UP) && (GetInfoByName(name).selectPos > 1))
			info[nowCharacter].selectPos -= 2;
		if (KEYMANAGER->IsOnceKeyDown(VK_DOWN) && (GetInfoByName(name).selectPos < 2))
			info[nowCharacter].selectPos += 2;
	}

}

void UI::DrawFace()
{
	int count = 0;
	string charlist[3] = { "","","" };

	for (int i = 0; i < _cm->GetCharacters().size(); i++)
	{
		string name = _cm->GetCharacters()[i]->GetName();
		charlist[count] = name;
		//active 
		if (i == _cm->getNowCharacterNum())
		{
			IMAGEMANAGER->FindImage(name + "Active")->SetSize(Vector2(86, 71));
			IMAGEMANAGER->FindImage(name + "Active")->Render(GetInfoByName(name).UIpos.x, WINSIZEY - 170 + 45, Pivot::LEFT_TOP, true);
		}
		else
		{
			IMAGEMANAGER->FindImage(name + "Default")->SetSize(Vector2(86, 71));
			IMAGEMANAGER->FindImage(name + "Default")->Render(GetInfoByName(name).UIpos.x, WINSIZEY - 170 + 45, Pivot::LEFT_TOP, true);
		}
		count++;
	}

	//죽었을 때 (벡터사이즈때문에 HP말고 이런식으로 처리)
	if (charlist[0] != "Baleog" && charlist[1] != "Baleog" &&charlist[2] != "Baleog")
	{
		IMAGEMANAGER->FindImage("BaleogDead")->SetSize(Vector2(86, 71));
		IMAGEMANAGER->FindImage("BaleogDead")->Render(info[1].UIpos.x, WINSIZEY - 170 + 45, Pivot::LEFT_TOP, true);
	}
	if (charlist[0] != "Erik" && charlist[1] != "Erik" &&charlist[2] != "Erik")
	{
		IMAGEMANAGER->FindImage("ErikDead")->SetSize(Vector2(86, 71));
		IMAGEMANAGER->FindImage("ErikDead")->Render(info[0].UIpos.x, WINSIZEY - 170 + 45, Pivot::LEFT_TOP, true);
	}
	if (charlist[0] != "Olaf" && charlist[1] != "Olaf" &&charlist[2] != "Olaf")
	{
		IMAGEMANAGER->FindImage("OlafDead")->SetSize(Vector2(86, 71));
		IMAGEMANAGER->FindImage("OlafDead")->Render(info[2].UIpos.x, WINSIZEY - 170 + 45, Pivot::LEFT_TOP, true);
	}
}


void UI::DrawInventory()
{
	for (int i = 0; i < _cm->GetCharacters().size(); i++)
	{
		for (int j = 0; j < _cm->GetCharacters()[i]->GetInventory().size(); j++)
		{
			Item* currentItem = _cm->GetCharacters()[i]->GetInventory()[j];

			if (!_isClicked)
			{
				IMAGEMANAGER->FindImage(currentItem->GetName())->Render
				(GetInfoByName(_cm->GetCharacters()[i]->GetName()).UIpos.x + 88 + 
					(currentItem->GetItemNum() % 2) * 38, WINSIZEY - 123 + (currentItem->GetItemNum() / 2) * 43);
				continue;
			}

			if (currentItem != _itemClicked)
			{
				IMAGEMANAGER->FindImage(currentItem->GetName())->Render(GetInfoByName(_cm->GetCharacters()[i]->GetName()).UIpos.x + 88 + (currentItem->GetItemNum() % 2) * 38, WINSIZEY - 123 + (currentItem->GetItemNum() / 2) * 43);
				continue;
			}

			if (_count > 40 || !this->GetAllowsUpdate())
			{
				if (_inTrash)
				{
					IMAGEMANAGER->FindImage(currentItem->GetName())->Render(642, WINSIZEY - 170 + 48);
				}
				else
				{
					IMAGEMANAGER->FindImage(currentItem->GetName())->Render(GetInfoByName(_owner).UIpos.x + 88 + (_clickedNum % 2) * 38, WINSIZEY - 123 + (_clickedNum / 2) * 43);
				}
				if (_count > 60 || !this->GetAllowsUpdate())
					_count = 0;
			}
		}
	}
}

