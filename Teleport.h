#pragma once
#include "GameObject.h"
#include "Character.h"
#include <list>

class Teleport : public GameObject
{
private:
	list<Character*> _lCharacterAtTeleport1A;
	list<Character*> _lCharacterAtTeleport1B;
	list<Character*> _lCharacterAtTeleport2A;
	list<Character*> _lCharacterAtTeleport2B;

	bool _test;
	bool _test2;

public:
	Teleport() { _physics = new Physics(); };
	~Teleport() {};

	virtual HRESULT Init() override;
	virtual void Update() override;

	void Teleport1ATo1B();
	void Teleport1BTo1A();
	void Teleport2ATo2B();
	void Teleport2BTo2A();
};