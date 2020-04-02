#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Erik.h"
#include "Olaf.h"
#include "Baleog.h"

#include "BulletTurret.h"
#include "GreenAlien.h"

#include "CharacterManager.h"
#include "UI.h"
#include "Item.h"
#include "Twinkle.h"

using namespace std;

class Blue;
class playGround : public gameNode
{
private:
	Map* map;
	CharacterManager* cm;
	UI* ui;
	Item* item;

	Erik* _erik;
	Olaf* _olaf;
	Baleog* _baleog;

	bool _updateUI = false;

public:
	playGround();
	~playGround();


	virtual HRESULT Init() override;
	virtual void Update() override;

	GreenAlien* MakeGreenAlien(Vector2 pos, string name, uint16 num);
	Blue* MakeBlueEnemy(Vector2 pos, string name, uint16 num);

};

