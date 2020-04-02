#pragma once
#include "Character.h"
#include "GameObject.h"

class Exit : public GameObject
{
private:

	bool _inArea_Erik = false;
	bool _inArea_Baleog = false;
	bool _inArea_Olaf = false;


public:
	Exit();
	~Exit();

	virtual HRESULT Init() override;
	virtual void Update() override;

};

