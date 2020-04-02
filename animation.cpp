#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
{
}


Animation::~Animation()
{
}
void Animation::Update()
{

	_currentPosition.x = (int)(TIMEMANAGER->GetFPS() * _image->GetMaxFrameX() - (TIMEMANAGER->GetFPS() * _image->GetMaxFrameX() / _count)) % _image->GetMaxFrameX();
	_currentPosition.y = (TIMEMANAGER->GetFPS() * _image->GetMaxFrameX() / _count) / _image->GetMaxFrameX();
	_count = (_count + 1) % (int)(TIMEMANAGER->GetFPS() * _image->GetMaxFrameX());


}

void Animation::Render()
{
	_image->FrameRender(_transform->GetPosition().x, _transform->GetPosition().y, _currentPosition.x, Pivot::CENTER);
}
