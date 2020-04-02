#pragma once
#include "GameObject.h"
#include "Item.h"

using namespace std;

class CharacterManager;


struct CharacterInfo
{
	Vector2 UIpos;
	int selectPos;
};

class UI: public GameObject
{
private:

	CharacterManager* _cm;
	CharacterInfo info[3];

	bool _isClicked = false;
	Item* _itemClicked;
	int _clickedNum;
	string _owner; 
	string _initialOwner;
	bool _inTrash = false;

	Image* _uiImage;
	Image* _hpImage;
	Image* _selectImage;

	int _count = 0;

public:
	UI();
	~UI();

	virtual HRESULT Init() override;
	virtual void Render() override;
	virtual void Update() override;

	void SetLink(CharacterManager* cm)
	{
		_cm = cm;
	}

	//ĳ���ͺ� ������ ���� 
	CharacterInfo GetInfoByName(string name);

	//UI Ű ��Ʈ�� 
	void UIKeyControl();

	//��ο� �Լ� 
	void DrawFace();
	void DrawInventory();

};


