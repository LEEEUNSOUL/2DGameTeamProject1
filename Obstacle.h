#pragma once
#include "GameObject.h"
#include "Player.h"
#include <string>

enum OBSTYPE
{
	GROUND,
	WALL,
	PAN
};

class Obstacle : public GameObject
{
private:
	OBSTYPE _obsType;
	bool _isMoveUp;
	bool _isMoveDown;
	float _moveTimer;

public:
	Obstacle();
	~Obstacle();

	virtual HRESULT Init();
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	//세터 
	void setObsType(OBSTYPE type) { _obsType = type; }
	void SetIsMove(bool isMove) { _isMoveUp = isMove; }


	//게터 
	OBSTYPE getObsType() { return _obsType; }
	bool getIsMove() { return _isMoveUp; }

	void MoveUp();
};

