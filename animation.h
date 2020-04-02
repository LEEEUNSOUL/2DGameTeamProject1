#pragma once
#include "Image.h"
#include "GameObject.h"

class Animation : public GameObject
{
private:

	Image* _image;
	Vector2 _currentPosition = Vector2(0,1);
	float _deltaTime;
	bool _loop;
	int _count;


public:
	Animation();
	~Animation();

	void SetImage(Image* image) { _image = image; }
	void Update();
	void Render();
};

