#include "stdafx.h"
#include "EnemyAtkScript.h"
#include "Enemy.h"
#include "Player.h"
#include "PlayerState.h"

void EnemyAtkScript::CollisionBegin(void* obj)
{
	Enemy* onwer = (Enemy*)_object->GetParent();
	Object* to = (Object*)obj;

	if (to->GetTag() != "Player") return;

	Player* player = (Player*)to;

	player->GetAbility()->SetDamage(onwer->GetAbility()->GetAtk());
	player->SetHurtAngle(Vector2::GetAngle( _object->GetTrans()->GetPos(), player->GetTrans()->GetPos()));
	player->ChangeState(make_shared<PlayerHurt>(player));
}

void EnemyAtkScript::CollisionPreSolve(void* obj)
{
}

void EnemyAtkScript::CollisionEnd(void* obj)
{
}
