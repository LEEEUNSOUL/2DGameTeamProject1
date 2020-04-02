#include "stdafx.h"
#include "Twinkle.h"


Twinkle::Twinkle(Twinkle_Type type)
{
	string name = "Twinkle_" + to_string((int)type);
	SetSprite(IMAGEMANAGER->FindImage(name));
	switch (type)
	{
	case Twinkle_Type::RedBlack:
		SetZOrder(1);
		_transform->SetSize(Vector2(32, 32));
		break;
	case Twinkle_Type::RedBlack_Twinkle:
		_transform->SetSize(Vector2(64, 96));
		break;
	case Twinkle_Type::NavyBlue_Tile:
		_transform->SetSize(Vector2(64, 64));
		break;
	case Twinkle_Type::NavyBlue:
		_transform->SetSize(Vector2(48, 48));
		break;
	case Twinkle_Type::Red_Triangle:
		_transform->SetSize(Vector2(128, 64));
		break;
	case Twinkle_Type::Line_Rectangle:
		_transform->SetSize(Vector2(64, 64));
		break;
	case Twinkle_Type::SmallRed:
		SetZOrder(1);
		_transform->SetSize(Vector2(32, 32));
		break;
	case Twinkle_Type::SmallBlue:
		SetZOrder(1);
		_transform->SetSize(Vector2(16, 16));
		break;
	case Twinkle_Type::Blue:
		SetZOrder(1);
		_transform->SetSize(Vector2(32, 32));
		break;
	default:
		break;
	}
	SetDeltaTime(0.2f);
	_transform->SetScale(1.24f);
}

void Twinkle::Render()
{
	GameObject::Render();
}
