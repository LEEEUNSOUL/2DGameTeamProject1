#include "stdafx.h"
#include "Object.h"

bool Compare(Object* a, Object* b)
{
	return ((GameObject*)a)->GetZOrder() < ((GameObject*)b)->GetZOrder();
}


void Object::AddChild(Object* child)
{
	child->Init();
	_children.push_back(child);
	child->SetParent(this);
	//_children.sort(Compare);
}


void Object::RemoveChild(Object* child)
{
	for (auto c : _children)
	{
		if (c != child)
			continue;
		_children.remove(child);
		break;
	}
}


void Object::SetParent(Object* parent)
{
	if (_parent)
		_parent->RemoveChild(this);
	_parent = parent;
}

void Object::Update()
{
	_children.sort(Compare);
	for (auto c : _children)
	{
		if (!c->GetAllowsUpdate())
			continue;
		c->Update();
	}
}






