#include "stdafx.h"
#include "Rogue.h"
#include "EnemyState.h"
#include "EnemyAtkScript.h"
void Rogue::Init(Vector2 pos)
{
	Enemy::Init();
	_name = "Rogue";
	_atkDistance = 75;
	_distance = 1;
	_FPS = 1.3f;
	_speed = 80.f;
	_atkFrame = 0;
	_angle = PI;

	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"Rogue_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Hurt", dir + L"Rogue_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"RogueRunRight0_6x1.png", 6, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"RogueDead0_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"RogueAttack0_3x1.png", 3, 1);

	_sprite->SetPivot(PIVOT::BOTTOM);
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(40, 15));
	_sprite->SetScale(Vector2(1.3, 1.3));
	_sprite->SetPosition(_trans->GetPos());
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	_physics->GetBody()->SetFixedRotation(true);

	_leftAtk = Object::CreateObject<Object>(this);
	_leftAtk->Init();
	auto t = _leftAtk->GetTrans();
	t->SetScale(20, 30);
	t->SetPos(_trans->GetPos() + Vector2::left * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	auto p = _leftAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->SetSensor(true);
	p->GetBody()->SetFixedRotation(true);
	_leftAtk->AddComponent<EnemyAtkScript>();
	_leftAtk->SetIsActive(false);

	_rightAtk = Object::CreateObject<Object>(this);
	_rightAtk->Init();
	t = _rightAtk->GetTrans();
	t->SetScale(20, 30);
	t->SetPos(_trans->GetPos() + Vector2::right * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	p = _rightAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->SetSensor(true);
	p->GetBody()->SetFixedRotation(true);
	_rightAtk->AddComponent<EnemyAtkScript>();
	_rightAtk->SetIsActive(false);
	_state->Enter();

	_ability->Init(50, 10);
}
void Rogue::Update()
{
	Enemy::Update();
	if (_state->GetStateToString() == "Attack")
	{
		_FPS = 0.7f;
		_sprite->SetFPS(_FPS);
	}
	else
	{
		_FPS = 1.3;
		_sprite->SetFPS(_FPS);
	}

	if (_state->GetStateToString() == "Hurt" or _state->GetStateToString() == "Death")
	{
		_leftAtk->SetIsActive(false);
		_rightAtk->SetIsActive(false);
	}

	_leftAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::left * (5 + (_leftAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	_leftAtk->GetComponent<PhysicsBody>()->SetBodyPosition();

	_rightAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::right * (5 + (_rightAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	_rightAtk->GetComponent<PhysicsBody>()->SetBodyPosition();
}
void Rogue::Attack()
{
	switch (_dir)
	{
	case EnemyDirection::LEFT:
		_leftAtk->SetIsActive(true);
		break;
	case EnemyDirection::RIGHT:
		_rightAtk->SetIsActive(true);
		break;
	default:
		break;
	}
}

void Rogue::AttackExit()
{
	Enemy::AttackExit();
	if (_isHurt)return;
	_leftAtk->SetIsActive(false);
	_rightAtk->SetIsActive(false);
}

void Rogue::BasicUpdate()
{
	Enemy::BasicUpdate();
	//if (_state->GetStateToString() == "Idle")
	_sprite->SetPosition(_trans->GetPos() + Vector2::down * 13);


}
