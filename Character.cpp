#include "stdafx.h"
#include "Character.h"
#include "IdleState.h"
#include "State.h"
#include "Item.h"

HRESULT Character::Init()
{
	_state = new IdleState(this);
	_state->EnterState();
	
	return S_OK;
}

void Character::Release()
{
}

void Character::Update()
{
	GameObject::Update();
	_state->UpdateState();
}


void Character::ChangeState(State* state)
{
	_state->ExitState();
	_state = state;
	state->EnterState();
}

