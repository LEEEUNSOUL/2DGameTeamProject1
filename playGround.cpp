#include "stdafx.h"
#include "playGround.h"
#include "Blue.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
HRESULT playGround::Init()
{
	gameNode::Init(true);


#pragma region AddImage

	//IMAGE - UI 
	IMAGEMANAGER->AddImage("UI", L"Image/UI/UI_background.png");
	IMAGEMANAGER->AddImage("hp", L"Image/UI/hp.png");
	IMAGEMANAGER->AddImage("select", L"Image/UI/select.png");
	IMAGEMANAGER->AddImage("BaleogActive", L"Image/UI/BaleogActive.png");
	IMAGEMANAGER->AddImage("BaleogDead", L"Image/UI/BaleogDead.png");
	IMAGEMANAGER->AddImage("BaleogDefault", L"Image/UI/BaleogDefault.png");
	IMAGEMANAGER->AddImage("ErikActive", L"Image/UI/ErikActive.png");
	IMAGEMANAGER->AddImage("ErikDead", L"Image/UI/ErikDead.png");
	IMAGEMANAGER->AddImage("ErikDefault", L"Image/UI/ErikDefault.png");
	IMAGEMANAGER->AddImage("OlafActive", L"Image/UI/OlafActive.png");
	IMAGEMANAGER->AddImage("OlafDead", L"Image/UI/OlafDead.png");
	IMAGEMANAGER->AddImage("OlafDefault", L"Image/UI/OlafDefault.png");


	//IMAGE - MAP 
	IMAGEMANAGER->AddImage("Background", L"Image/background.png");
	IMAGEMANAGER->AddImage("DoorTop", L"Image/Obstacle/DoorTop.png");
	IMAGEMANAGER->AddImage("DoorBottom", L"Image/Obstacle/DoorBottom.png");
	IMAGEMANAGER->AddImage("DoorHideTop", L"Image/Obstacle/DoorHideTop.png");
	IMAGEMANAGER->AddImage("DoorHideBottom", L"Image/Obstacle/DoorHideBottom.png");
	IMAGEMANAGER->AddImage("KeyHole", L"Image/Obstacle/Keyhole.png");
	IMAGEMANAGER->AddImage("Lift", L"Image/Obstacle/Lift.png");
	IMAGEMANAGER->AddImage("Switch_Pressed", L"Image/Obstacle/Switch_pushed.png");
	IMAGEMANAGER->AddImage("Switch", L"Image/Obstacle/Switch.png");


	IMAGEMANAGER->AddFrameImage("ElectricBox", L"Image/Obstacle/ElectricBox_1.png", 7, 1);
	IMAGEMANAGER->AddFrameImage("ElectricRod", L"Image/Obstacle/ElectricRod.png", 3, 1);
	IMAGEMANAGER->AddFrameImage("Grinder", L"Image/Obstacle/Grinder.png", 3, 1);
	IMAGEMANAGER->AddFrameImage("BrokenWall_Frame", L"Image/Obstacle/wallBroken.png", 13, 1);
	IMAGEMANAGER->AddFrameImage("GravityZone", L"Image/Obstacle/GravityZone2.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Exit", L"Image/Obstacle/exit.png", 6, 1);
	IMAGEMANAGER->AddImage("BrokenWallStart", L"Image/Obstacle/wallBroken_1.png");
	IMAGEMANAGER->AddImage("BrokenWallEnd", L"Image/Obstacle/wallBroken_2.png");
	IMAGEMANAGER->AddImage("Wall_z1", L"Image/wall_z1.png");
	IMAGEMANAGER->AddImage("Wall_z2", L"Image/wall_z2.png");
	IMAGEMANAGER->AddImage("Wall_z3", L"Image/wall_z3.png");
	IMAGEMANAGER->AddImage("SecretWall", L"Image/secretwall.png");


	//IMAGE - CHARACTER
	IMAGEMANAGER->AddFrameImage("Erik_Electric", L"Image/Erik_Electric.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Grinder", L"Image/Erik_Grinder2.png", 9, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Idle", L"Image/Erik_Sprite/Erik_idle_02.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Run", L"Image/Erik_Sprite/Erik_Run.png", 8, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Jump", L"Image/Erik_Sprite/Erik_jump.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Hit", L"Image/Erik_Sprite/Erik_hit.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("Erik_ClimbUp", L"Image/Erik_Sprite/Erik_ClimbUp.png", 4, 1);
	IMAGEMANAGER->AddImage("Erik_ClimbAfter1", L"Image/Erik_Sprite/Erik_ClimbAfter1.png");
	IMAGEMANAGER->AddImage("Erik_ClimbAfter2", L"Image/Erik_Sprite/Erik_ClimbAfter2.png");
	IMAGEMANAGER->AddFrameImage("Erik_Push_Wall", L"Image/Erik_Sprite/Erik_Push_wall.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Paint", L"Image/Erik_Sprite/Erik_paint.png", 11, 1);
	IMAGEMANAGER->AddFrameImage("Erik_InAir", L"Image/Erik_Sprite/Erik_InAir.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Erik_AirDrop", L"Image/Erik_Sprite/Erik_DropAfter.png", 5, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Teleport", L"Image/Erik_Sprite/Erik_teleport.png", 7, 1);
	IMAGEMANAGER->AddFrameImage("Erik_Attack", L"Image/Erik_Sprite/Erik_Head_butt.png", 8, 1);


	IMAGEMANAGER->AddFrameImage("Olaf_Hit", L"Image/Olaf_sprite/Olaf_Hit.png", 1, 1, false);
	IMAGEMANAGER->AddFrameImage("Olaf_Shield_Up", L"Image/Olaf_sprite/Olaf_Top_Idle.png", 1, 1, false);
	IMAGEMANAGER->AddFrameImage("Olaf_Shield_Run", L"Image/Olaf_sprite/Olaf_Top_Run.png", 8, 1, false);
	IMAGEMANAGER->AddFrameImage("Olaf_Push_Wall", L"Image/Olaf_sprite/Olaf_Push.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_InAir", L"Image/Olaf_sprite/Olaf_InAir.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_AirDrop", L"Image/Olaf_sprite/Olaf_Drop_After.png", 5, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_AirDropNoMove", L"Image/Olaf_sprite/Olaf_InAir_NoMoving.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_AirDropMove", L"Image/Olaf_sprite/Olaf_InAir_Moveing.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_Teleport", L"Image/Olaf_sprite/Olaf_Teleport.png", 7, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_Electric", L"Image/Olaf_sprite/Olaf_Electric.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_Idle", L"Image/Olaf_sprite/Olaf_Idle1.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_Run", L"Image/Olaf_sprite/Oalf_Run.png", 8, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_Hit", L"Image/Olaf_sprite/Olaf_Hit.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_Grinder", L"Image/Olaf_sprite/Olaf_Grinder.png", 9, 1);
	IMAGEMANAGER->AddFrameImage("Olaf_ClimbUp", L"Image/Olaf_sprite/Olaf_ClimbUp.png", 4, 1);
	IMAGEMANAGER->AddImage("Olaf_ClimbAfter1", L"Image/Olaf_sprite/Olaf_ClimbAfter1.png");
	IMAGEMANAGER->AddImage("Olaf_ClimbAfter2", L"Image/Olaf_sprite/Olaf_ClimbAfter2.png");
	IMAGEMANAGER->AddImage("Olaf_ClimbAfter2_2", L"Image/Olaf_sprite/Olaf_ClimbAfter2_2.png");
	IMAGEMANAGER->AddFrameImage("Olaf_ClimbAfter", L"Image/Olaf_sprite/Olaf_ClimbAfter.png",2,1);



	IMAGEMANAGER->AddFrameImage("Baleog_Idle", L"Image/Baleog_sprite/Baleog_Idle.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Run", L"Image/Baleog_sprite/Baleog_Walk.png", 8, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Hit", L"Image/Baleog_sprite/Baleog_Hit.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Grinder", L"Image/Baleog_sprite/Baleog_Grinder.png", 9, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Electric", L"Image/Baleog_sprite/Baleog_Electric_shock_main.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_ClimbUp", L"Image/Baleog_sprite/Baleog_ClimbUp.png", 4, 1);
	IMAGEMANAGER->AddImage("Baleog_ClimbAfter1", L"Image/Baleog_sprite/Baleog_ClimbAfter1.png");
	IMAGEMANAGER->AddImage("Baleog_ClimbAfter2", L"Image/Baleog_sprite/Baleog_ClimbAfter2.png");
	IMAGEMANAGER->AddFrameImage("Baleog_Falldown", L"Image/Baleog_sprite/Baleog_Falldown.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Teleport", L"Image/Baleog_sprite/Baleog_Teleport.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Knife_down", L"Image/Baleog_sprite/Baleog_Knife_down.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Knife_up", L"Image/Baleog_sprite/Baleog_Knife_up.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("baleog_broken_arrow_right", L"Image/Baleog_sprite/baleog_broken_arrow_right.png", 3, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Shoot_arrow", L"Image/Baleog_sprite/Baleog_Shoot_arrow.png", 8, 1);
	IMAGEMANAGER->AddImage("Baleog_arrow", L"Image/Baleog_sprite/Baleog_arrow.png");
	IMAGEMANAGER->AddFrameImage("Baleog_Push_Wall", L"Image/Baleog_sprite/Baleog_Push_Wall.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_InAir", L"Image/Baleog_sprite/Baleog_Falldown.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Knife_down", L"Image/Baleog_sprite/Baleog_Knife_down.png", 4, 1, false);
	IMAGEMANAGER->AddFrameImage("Baleog_Knife_up", L"Image/Baleog_sprite/Baleog_Knife_up.png", 4, 1, false);
	IMAGEMANAGER->AddImage("Baleog_arrow", L"Image/Baleog_sprite/Baleog_arrow.png", false);
	IMAGEMANAGER->AddFrameImage("Baleog_Electric_shock_main", L"Image/Baleog_sprite/Baleog_Electric_shock_main.png", 2, 1, false);
	IMAGEMANAGER->AddFrameImage("Baleog_AirDrop", L"Image/Baleog_sprite/Baleog_AirDrop.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("Baleog_Teleport", L"Image/Baleog_sprite/Baleog_Teleport.png", 6, 1);

	//IMAGE - ITEM
	IMAGEMANAGER->AddImage("Meat", L"Image/Item/meat.png");
	IMAGEMANAGER->AddImage("Tomato", L"Image/Item/tomato.png");
	IMAGEMANAGER->AddImage("Key", L"Image/Item/key.png");
	IMAGEMANAGER->AddImage("Shoes", L"Image/Item/gravityShoes.png");

	//TWINKLE
	IMAGEMANAGER->AddFrameImage("Twinkle_1", L"Image/Twinkle/1.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_2", L"Image/Twinkle/2.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_3", L"Image/Twinkle/3.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_4", L"Image/Twinkle/4.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_5", L"Image/Twinkle/5.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_6", L"Image/Twinkle/6.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_7", L"Image/Twinkle/7.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_8", L"Image/Twinkle/8.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("Twinkle_9", L"Image/Twinkle/9.png", 6, 1);

	//ENEMY
	IMAGEMANAGER->AddImage("LaserBullet", L"Image/Enemy_Sprite/LaserBullet.png");
	IMAGEMANAGER->AddImage("turret_After_fire", L"Image/Enemy_Sprite/turret_After_fire.png");
	IMAGEMANAGER->AddImage("turret_before_fire", L"Image/Enemy_Sprite/turret_before_fire.png");
	IMAGEMANAGER->AddFrameImage("Enemy_01_fire", L"Image/Enemy_Sprite/Enemy_01_fire.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("Enemy_01_move", L"Image/Enemy_Sprite/Enemy_01_move.png", 3, 1);
	IMAGEMANAGER->AddFrameImage("Blue_Enemy", L"Image/Enemy_Sprite/Blue_Enemy.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("Blue_Enemy_Fire", L"Image/Enemy_Sprite/Blue_Enemy_Fire.png", 3, 1);

	

	IMAGEMANAGER->AddFrameImage("ElectricTop_Long", L"Image/Obstacle/ElectricTop_Long.png", 7, 1);
	IMAGEMANAGER->AddFrameImage("ElectricTop_Short", L"Image/Obstacle/ElectricTop_Short.png", 7, 1);


	//IMAGE - CHARACTER
	

	


	


#pragma endregion 
	


	//map init 
	map = new Map();
	map->Init();

#pragma region Twinkle_Init
	struct TwinkleInfo
	{
		int x;
		int y;
		Twinkle_Type type;
	};

	auto changePosition = [&](Vector2 origin, GameObject* object)
	{
		Vector2 objectSize = object->GetTransform()->GetSize() * object->GetTransform()->GetScale();
		return Hyolim_LeftTop(origin, objectSize.x, objectSize.y);
	};

	vector<TwinkleInfo> twinkleInfos;

	twinkleInfos.push_back({ 630,318,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 3554,242,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 3954,318,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 1337,1025,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 1941,1048,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 2444,1226,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 2998,1048,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 2798,1502,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 3704,1628,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 1436,1730,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 1940,1730,Twinkle_Type::Blue });
	twinkleInfos.push_back({ 2596,1730,Twinkle_Type::SmallRed });
	twinkleInfos.push_back({ 3654,292,Twinkle_Type::SmallRed });
	twinkleInfos.push_back({ 3554,1250,Twinkle_Type::SmallRed });
	twinkleInfos.push_back({ 2647,1049,Twinkle_Type::SmallRed });
	twinkleInfos.push_back({ 26,520,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 1048,630,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 1348,602,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 1736,608,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 2124,604,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 2508,614,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 2898,620,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 3176,520,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 3868,630,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 256,708,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 646,718,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 3176,520,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 478,1024,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 1638,1074,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 1840,1402,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 1184,1628,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 176,1300,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 580,1528,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 580,1300,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 3176,1528,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 3176,922,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 3352,822,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 580,1930,Twinkle_Type::RedBlack });
	twinkleInfos.push_back({ 756,1100,Twinkle_Type::RedBlack_Twinkle });
	twinkleInfos.push_back({ 656,1502,Twinkle_Type::RedBlack_Twinkle });
	twinkleInfos.push_back({ 0,1552,Twinkle_Type::RedBlack_Twinkle });
	twinkleInfos.push_back({ 3150,696,Twinkle_Type::RedBlack_Twinkle });
	twinkleInfos.push_back({ 3150,1100,Twinkle_Type::RedBlack_Twinkle });
	twinkleInfos.push_back({ 3150,596,Twinkle_Type::Line_Rectangle });
	twinkleInfos.push_back({ 3150,998,Twinkle_Type::Line_Rectangle });
	twinkleInfos.push_back({ 3150,1352,Twinkle_Type::Line_Rectangle });
	twinkleInfos.push_back({ 202,1906,Twinkle_Type::Line_Rectangle });
	twinkleInfos.push_back({ 554,1804,Twinkle_Type::Line_Rectangle });
	twinkleInfos.push_back({ 856,1804,Twinkle_Type::Line_Rectangle });
	twinkleInfos.push_back({ 3982,1203,Twinkle_Type::SmallBlue });
	twinkleInfos.push_back({ 2823,1455,Twinkle_Type::SmallBlue });
	twinkleInfos.push_back({ 1209,1580,Twinkle_Type::SmallBlue });
	twinkleInfos.push_back({ 2875,494,Twinkle_Type::Red_Triangle });
	twinkleInfos.push_back({ -65,784,Twinkle_Type::Red_Triangle });
	twinkleInfos.push_back({ 758,1706,Twinkle_Type::Red_Triangle });
	twinkleInfos.push_back({ 757,494,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 102,545,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 1413,495,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 231,784,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 621,795,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 1025,707,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 1324,680,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 1712,685,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 2100,681,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 2485,691,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 2484,692,Twinkle_Type::NavyBlue_Tile });
	twinkleInfos.push_back({ 2874,697,Twinkle_Type::NavyBlue_Tile });

	for (auto t : twinkleInfos)
	{
		auto _twinkle = new Twinkle(t.type);
		_twinkle->GetTransform()->SetPosition(changePosition(Vector2(t.x, t.y), _twinkle));
		//_twinkle->SetZOrder(10);
		AddChild(_twinkle);
	}
#pragma endregion

	//item init
	item = new Item();
	item->Init();


	//character test init 
	 _erik = new Erik();
	_erik->SetTag("Character");
	_erik->SetName("Erik");
	_erik->Init();
	_erik->GetTransform()->SetSize(Vector2(26, 33));
	_erik->GetTransform()->SetScale(2.5f);
	_erik->GetTransform()->SetPosition(Hyolim_LeftTop(	Vector2(1385, 1782),
														_erik->GetTransform()->GetSize().x,
														_erik->GetTransform()->GetSize().y));
	_erik->SetDeltaTime(0.7);


	_erik->GetPhysics()->SetBodyType(b2_dynamicBody);
	_erik->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_erik));
	_erik->GetPhysics()->SetVelocity(Vector2(0.f, 0.f));
	_erik->GetPhysics()->SetShapeType(BOX);
	b2Shape* erikShape = PHYSICSMANAGER->CreateShape(	_erik->GetPhysics()->GetBody(),true);
	_erik->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_erik->GetPhysics()->GetBody(), erikShape));
	_erik->GetPhysics()->SetCategoryBit(0x0002);
	_erik->SetZOrder(3);
	AddChild(_erik);


	 _olaf = new Olaf();
	_olaf->SetTag("Character");
	_olaf->SetName("Olaf");
	_olaf->Init();
	_olaf->GetTransform()->SetSize(Vector2(26, 33));
	_olaf->GetTransform()->SetScale(2.5f);
	_olaf->GetTransform()->SetPosition(Hyolim_LeftTop(	Vector2(1833, 1066),
														_olaf->GetTransform()->GetSize().x*BACKGROUND_SCALE,
														_olaf->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_olaf->GetPhysics()->SetBodyType(b2_dynamicBody);
	_olaf->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_olaf));
	_olaf->GetPhysics()->SetVelocity(Vector2(0.f, 0.f));
	_olaf->GetPhysics()->SetShapeType(BOX);

	b2Shape* olafShape = PHYSICSMANAGER->CreateShape(_olaf->GetPhysics()->GetBody(),true);

	_olaf->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_olaf->GetPhysics()->GetBody(), olafShape));
	_olaf->GetPhysics()->SetCategoryBit(0x0004);
	_olaf->SetZOrder(3);

	AddChild(_olaf);


	 _baleog =  new Baleog();
	_baleog->SetTag("Character");
	_baleog->SetName("Baleog");
	_baleog->Init();
	_baleog->GetTransform()->SetSize(Vector2(26, 33));
	_baleog->GetTransform()->SetScale(2.5);
	_baleog->GetTransform()->SetPosition(Hyolim_LeftTop(	Vector2(2535, 1731),
															_baleog->GetTransform()->GetSize().x*BACKGROUND_SCALE,
															_baleog->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_baleog->GetPhysics()->SetBodyType(b2_dynamicBody);
	_baleog->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_baleog));
	_baleog->GetPhysics()->SetVelocity(Vector2(0.f, 0.f));
	_baleog->GetPhysics()->SetShapeType(BOX);
	b2Shape* baleogShape = PHYSICSMANAGER->CreateShape(	_baleog->GetPhysics()->GetBody(),true);
	_baleog->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_baleog->GetPhysics()->GetBody(), baleogShape));
	_baleog->GetPhysics()->SetCategoryBit(0x0006);
	_baleog->SetZOrder(3);

	AddChild(_baleog);

	//character init 
	cm = new CharacterManager();
	cm->AddCharacter(_erik);
	cm->AddCharacter(_baleog);
	cm->AddCharacter(_olaf);
	AddChild(cm);

	//UI 세팅 
	ui = new UI();
	ui->Init();
	ui->SetTag("UI");
	AddChild(ui);
	ui->SetZOrder(10);
	ui->SetIsUI(true);
	ui->SetLink(cm);
	ui->SetAllowsUpdate(false);

	item->SetLink(cm);

	
	//COLLISION
	PHYSICSMANAGER->IgnoreCollision(_olaf,   _erik);
	PHYSICSMANAGER->IgnoreCollision(_olaf,   _baleog);
	PHYSICSMANAGER->IgnoreCollision(_baleog, _erik);
	
	//ENEMY
		//Enemy - BulletTurret
	auto _bulletTurret = new BulletTurret();
	_bulletTurret->SetTag("Enemy");
	_bulletTurret->SetName("BulletTurret");
	_bulletTurret->SetSprite(IMAGEMANAGER->FindImage("turret_before_fire"));
	_bulletTurret->Init();
	_bulletTurret->GetTransform()->SetSize(Vector2(90, 75));
	_bulletTurret->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(3900 - 20, 1700 + 70),
		_bulletTurret->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_bulletTurret->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_bulletTurret->GetPhysics()->SetBodyType(b2_staticBody);
	_bulletTurret->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_bulletTurret));
	_bulletTurret->GetPhysics()->SetShapeType(BOX);

	b2Shape* bulletTurretShape = PHYSICSMANAGER->CreateShape(_bulletTurret->GetPhysics()->GetBody(), true);
	_bulletTurret->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_bulletTurret->GetPhysics()->GetBody(), bulletTurretShape));
	_bulletTurret->GetPhysics()->SetCategoryBit(0x0012);
	AddChild(_bulletTurret);


	//Enemy GreenAlien 
	GreenAlien* _greenAlien1;
	GreenAlien* _greenAlien2;
	GreenAlien* _greenAlien3;


	_greenAlien1 = MakeGreenAlien(Vector2(1721, 1552), "GreenAlien1", 0x0012);
	_greenAlien2 = MakeGreenAlien(Vector2(2398, 1552), "GreenAlien2", 0x0014);
	_greenAlien3 = MakeGreenAlien(Vector2(3604, 1404), "GreenAlien3", 0x0015);

	PHYSICSMANAGER->IgnoreCollision(_greenAlien1, _greenAlien2);

	//Enemy - BlueEnemy
	Blue* _blue1;
	Blue* _blue2;
	Blue* _blue3;

	_blue1 = MakeBlueEnemy(Vector2(369, 1442), "Blue1", 0x0016);
	_blue2 = MakeBlueEnemy(Vector2(1541, 385), "Blue2", 0x0017);
	_blue3 = MakeBlueEnemy(Vector2(2222, 385), "Blue3", 0x0018);

	//PHYSICSMANAGER->IgnoreCollision(_blue2, _blue3);

	//PHYSICSMANAGER->IgnoreCollision(_erik, _blue2);
	//PHYSICSMANAGER->IgnoreCollision(_olaf, _blue2);
	//PHYSICSMANAGER->IgnoreCollision(_baleog, _blue2);

	//PHYSICSMANAGER->IgnoreCollision(_erik, _blue3);
	//PHYSICSMANAGER->IgnoreCollision(_olaf, _blue3);
	//PHYSICSMANAGER->IgnoreCollision(_baleog, _blue3);

	return S_OK;
}

void playGround::Update()
{
	gameNode::Update();

	if (KEYMANAGER->IsOnceKeyDown(VK_TAB))
	{
		_updateUI = !_updateUI;

		if (_updateUI)
		{
			ui->SetAllowsUpdate(true);
			for (auto c : _children)
			{
				if (c->GetTag() != "UI")
					c->SetAllowsUpdate(false);
			}
		}
		else
		{
			ui->SetAllowsUpdate(false);
			cm->ChangeCharacter(cm->getNowCharacterNum());
			for (auto c : _children)
			{
				if (c->GetTag() != "UI")
					c->SetAllowsUpdate(true);
			}
		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_F11))
	{
		static bool isFullScreen = true;
		ApplicationManager::GetInstance()->SetResolution(WINSIZEX, WINSIZEY, isFullScreen);
		isFullScreen = !isFullScreen;
	}

}

GreenAlien * playGround::MakeGreenAlien(Vector2 pos, string name, uint16 num)
{
	//Enemy - GreenAlien
	auto _greenAlien = new GreenAlien();

	_greenAlien->SetTag("Enemy");
	_greenAlien->SetName(name);
	_greenAlien->Init();
	_greenAlien->GetTransform()->SetScale(2.5);
	_greenAlien->GetTransform()->SetSize(Vector2(31, 31));
	_greenAlien->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(pos - Vector2(0, 70)),
		_greenAlien->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_greenAlien->GetTransform()->GetSize().y*BACKGROUND_SCALE));
	_greenAlien->GetPhysics()->SetBodyType(b2_dynamicBody);
	_greenAlien->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_greenAlien));
	_greenAlien->GetPhysics()->SetShapeType(BOX);
	b2Shape* greenAlienShape = PHYSICSMANAGER->CreateShape(_greenAlien->GetPhysics()->GetBody(), true);
	_greenAlien->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_greenAlien->GetPhysics()->GetBody(), greenAlienShape));
	_greenAlien->GetPhysics()->SetCategoryBit(num);
	_greenAlien->GetPhysics()->SetGravityScale(0);
	_greenAlien->GetPhysics()->SetIsSensor(true);
	_greenAlien->SetLink(cm);

	AddChild(_greenAlien);


	//Enemy <-> Character IgnoreCollision
	//PHYSICSMANAGER->IgnoreCollision(_erik, _greenAlien);
	//PHYSICSMANAGER->IgnoreCollision(_olaf, _greenAlien);
	//PHYSICSMANAGER->IgnoreCollision(_baleog, _greenAlien);

	return _greenAlien;
}


Blue* playGround::MakeBlueEnemy(Vector2 pos, string name, uint16 num)
{
	//Enemy - Blue
	auto _blue = new Blue();

	_blue->SetTag("Enemy");
	_blue->SetName(name);
	_blue->Init();
	_blue->GetTransform()->SetSize(Vector2(31, 31));
	_blue->GetTransform()->SetScale(2.5);
	_blue->GetTransform()->SetPosition(Hyolim_LeftTop(Vector2(pos - Vector2(0,70)),
		_blue->GetTransform()->GetSize().x*BACKGROUND_SCALE,
		_blue->GetTransform()->GetSize().y*BACKGROUND_SCALE));

	_blue->SetSprite(IMAGEMANAGER->FindImage("Blue_Enemy"));
	_blue->GetPhysics()->SetBodyType(b2_dynamicBody);
	_blue->GetPhysics()->SetBody(PHYSICSMANAGER->CreateBody(_blue));
	_blue->GetPhysics()->SetShapeType(BOX);
	_blue->GetPhysics()->SetGravityScale(0);
	b2Shape* blueShape = PHYSICSMANAGER->CreateShape(_blue->GetPhysics()->GetBody(), true);
	_blue->GetPhysics()->SetFixture(PHYSICSMANAGER->CreateFixture(_blue->GetPhysics()->GetBody(), blueShape));
	_blue->GetPhysics()->SetCategoryBit(num);
	_blue->SetZOrder(7);
	_blue->GetPhysics()->SetGravityScale(0);
	_blue->GetPhysics()->SetIsSensor(true);
	_blue->SetLink(cm);

	AddChild(_blue);
	//충돌 판별용 바디//////////////////////////////////////////////
	/*auto _rect = new GameObject(true);
	_rect->SetTag("EnemyRect");
	_rect->GetTransform()->SetSize(Vector2(100, 30));
	_rect->GetTransform()->SetPosition(Hyolim_LeftTop(_rect->GetTransform()->GetPosition(),
													  _rect->GetTransform()->GetSize().x*BACKGROUND_SCALE,
													  _rect->GetTransform()->GetSize().y*BACKGROUND_SCALE));

	SceneManager::GetInstance()->GetNowScene()->AddChild(_rect);
	_rect->GetPhysics()->SetBodyType(b2_staticBody);
	_rect->GetPhysics()->SetBody(PHYSICSMANAGER->CreateDefaultBody(_rect,
																   _rect->GetTransform()->GetSize().x*2*BACKGROUND_SCALE,
																   _rect->GetTransform()->GetSize().y*2*BACKGROUND_SCALE));*/
																   //////////////////////////////////////////////////////////////

																   //Enemy <-> Character IgnoreCollision

	return _blue;
}




