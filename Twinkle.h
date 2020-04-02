#pragma once
#include "GameObject.h"

enum class Twinkle_Type
{
	RedBlack = 1,
	RedBlack_Twinkle,
	NavyBlue_Tile,
	NavyBlue,
	Red_Triangle,
	Line_Rectangle,
	SmallRed,
	SmallBlue,
	Blue
};

class Twinkle : public GameObject
{
public:
	Twinkle(Twinkle_Type type);
	virtual void Render() override;
};

