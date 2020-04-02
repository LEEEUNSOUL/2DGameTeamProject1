#pragma once
#include <vector>
#include "GameObject.h"
#include "Character.h"

using namespace std;


class CharacterManager : public GameObject
{
private:

	vector<Character*> _characters;
	int _nowCharacterNumber = 0;

public:
	void AddCharacter(Character* character);
	void ChangeCharacter(bool changeState = true);
	void ChangeCharacter(int index);
	void RemoveCharacter();

	virtual void Update() override;


	//���� 
	vector<Character*> GetCharacters() { return _characters; }
	int getNowCharacterNum() { return _nowCharacterNumber; }

	//����
	void SetNowCharacterNum(int num) { _nowCharacterNumber = num; }
};

