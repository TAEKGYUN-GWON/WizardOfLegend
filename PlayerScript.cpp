#include "stdafx.h"
#include "PlayerScript.h"
#include "Ability.h"
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"
#include "PlayerState.h"

void PlayerScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;

	if (me->GetStateName() == "Dash")
	{
		if (to->GetTag() == "Tile")
			me->ChangeState(make_shared<PlayerIdle>(me));
	}
}

void PlayerScript::CollisionPreSolve(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;
	if (me->GetStateName() == "Dash")
	{
		if (to->GetTag() == "Tile")
			me->ChangeState(make_shared<PlayerIdle>(me));
	}
}

void PlayerScript::CollisionEnd(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;
	if (me->GetStateName() == "Dash")
	{
		if (to->GetTag() == "Tile")
			me->ChangeState(make_shared<PlayerIdle>(me));
	}
}

