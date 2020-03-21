#include "stdafx.h"
#include "SkillScript.h"
#include "SkillObject.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "EnemyState.h"

void SkillScript::CollisionBegin(void* obj)
{
	SkillObject* me = (SkillObject*)_object;
	Object* to = (Object*)obj;

	if (to->GetTag() == "Tile")
	{
		me->SetIsCollision(true);
		return;
	}

	switch (me->GetOwnerType())
	{
	case OnwerType::Player:
	{
		if (to->GetTag() != "Enemy")return;

		Player* player = (Player*)me->GetOnwer();
		Enemy* enemy = (Enemy*)obj;

		if (enemy->GetStateName() == "Death")return;

		me->SetIsCollision(true);
		enemy->GetAbility()->SetDamage(player->GetAbility()->GetAtk() + me->GetAtk());
		enemy->SetHurtAngle(Vector2::GetAngle(me->GetTrans()->GetPos(), enemy->GetTrans()->GetPos()));
		enemy->SetIsHurt(true);
		enemy->ChangeState(make_shared<EnemyHurt>(enemy));
	}
	break;
	case OnwerType::Enemy:
	{
		if (to->GetTag() != "Player")return;

		Enemy* enemy = (Enemy*)me->GetOnwer();
		Player* player = (Player*)obj;

		if (player->GetStateName() == "Death")return;

		me->SetIsCollision(true);
		player->GetAbility()->SetDamage(enemy->GetAbility()->GetAtk() + me->GetAtk());
		player->SetHurtAngle(Vector2::GetAngle(me->GetTrans()->GetPos(), player->GetTrans()->GetPos()));
		player->ChangeState(make_shared<PlayerHurt>(player));
	}
	break;
	}
}

void SkillScript::CollisionPreSolve(void* obj)
{
	/*SkillObject* me = (SkillObject*)_object;
	Object* to = (Object*)obj;

	if (to->GetTag() == "Tile")
	{
		me->SetIsCollision(true);
		return;
	}

	switch (me->GetOwnerType())
	{
	case OnwerType::Player:
	{
		if (to->GetTag() != "Enemy")return;

		Player* player = (Player*)me->GetOnwer();
		Enemy* enemy = (Enemy*)obj;

		if (enemy->GetStateName() == "Death")return;

		me->SetIsCollision(true);
		enemy->GetAbility()->SetDamage(player->GetAbility()->GetAtk() + me->GetAtk());
		enemy->SetHurtAngle(Vector2::GetAngle(me->GetTrans()->GetPos(), enemy->GetTrans()->GetPos()));
		enemy->SetIsHurt(true);
		enemy->ChangeState(make_shared<EnemyHurt>(enemy));
	}
	break;
	case OnwerType::Enemy:
	{
		if (to->GetTag() != "Player")return;
		
		Enemy* enemy = (Enemy*)me->GetOnwer();
		Player* player = (Player*)obj;

		if (player->GetStateName() == "Death")return;


		me->SetIsCollision(true);
		player->GetAbility()->SetDamage(enemy->GetAbility()->GetAtk() + me->GetAtk());
		player->SetHurtAngle(Vector2::GetAngle(me->GetTrans()->GetPos(), player->GetTrans()->GetPos()));
		player->ChangeState(make_shared<PlayerHurt>(player));
	}
	break;
	}*/
}

void SkillScript::CollisionEnd(void* obj)
{
	
}
