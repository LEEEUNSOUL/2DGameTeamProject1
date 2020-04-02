#include "stdafx.h"
#include "Item.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Tomato.h"
#include "Shoes.h"
#include "Key.h"
#include "Meat.h"

HRESULT Item::Init()
{
	//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á Meat
	auto _meat = (GameObject*) new Meat();
	_meat->SetTag("item");
	_meat->SetName("Meat");
	_meat->GetTransform()->SetScale(BACKGROUND_SCALE);
	_meat->GetTransform()->SetSize(Vector2(90, 90));
	_meat->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(555, 1213),
		_meat->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_meat->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_meat->SetSprite(IMAGEMANAGER->FindImage("Meat"));
	SceneManager::GetInstance()->GetNowScene()->AddChild(_meat);
	_meat->GetPhysics()->SetBodyType(b2_staticBody);
	_meat->GetPhysics()->SetBody(PHYSICSMANAGER->CreateDefaultBody(_meat,
		_meat->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_meat->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_meat->GetPhysics()->SetIsSensor(true);


	//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á Tomato
	auto _tomato = (GameObject*) new Tomato();
	_tomato->SetTag("item");
	_tomato->SetName("Tomato");
	_tomato->GetTransform()->SetScale(BACKGROUND_SCALE);
	_tomato->GetTransform()->SetSize(Vector2(40, 40));
	_tomato->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(1334, 1498),
		_tomato->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_tomato->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_tomato->SetSprite(IMAGEMANAGER->FindImage("Tomato"));
	SceneManager::GetInstance()->GetNowScene()->AddChild(_tomato);
	_tomato->GetPhysics()->SetBodyType(b2_staticBody);
	_tomato->GetPhysics()->SetBody(PHYSICSMANAGER->CreateDefaultBody(_tomato,
		_tomato->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_tomato->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_tomato->GetPhysics()->SetIsSensor(true);
	_tomato->Init();
	


	//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á Key
	auto _key = (GameObject*) new Key();
	_key->SetTag("item");
	_key->SetName("Key");
	_key->GetTransform()->SetScale(BACKGROUND_SCALE);
	_key->GetTransform()->SetSize(Vector2(40, 53));
	_key->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(3820, 1732),
		_key->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_key->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_key->SetSprite(IMAGEMANAGER->FindImage("Key"));
	SceneManager::GetInstance()->GetNowScene()->AddChild(_key);
	_key->GetPhysics()->SetBodyType(b2_staticBody);
	_key->GetPhysics()->SetBody(PHYSICSMANAGER->CreateDefaultBody(_key,
		_key->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_key->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_key->GetPhysics()->SetIsSensor(true);

	//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á GravityShoes
	auto _shoes = (GameObject*) new Shoes();
	_shoes->SetTag("item");
	_shoes->SetName("Shoes");
	_shoes->GetTransform()->SetScale(BACKGROUND_SCALE);
	_shoes->GetTransform()->SetSize(Vector2(40, 40));
	_shoes->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(1284, 138),
		_shoes->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_shoes->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_shoes->SetSprite(IMAGEMANAGER->FindImage("Shoes"));
	SceneManager::GetInstance()->GetNowScene()->AddChild(_shoes);
	_shoes->GetPhysics()->SetBodyType(b2_staticBody);
	_shoes->GetPhysics()->SetBody(PHYSICSMANAGER->CreateDefaultBody(_shoes,
		_shoes->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_shoes->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_shoes->GetPhysics()->SetIsSensor(true);
	

	return S_OK;
}

void Item::Update()
{
	GameObject::Update();
}
