#include "stdafx.h"
#include "Knight.h"
#include "EnemyState.h"
#include "EnemyAtkScript.h"
void Knight::Init(Vector2 pos)
{
	Enemy::Init();
	_name = "Knight";
	_atkDistance = 75;
	_distance = 1;
	_FPS = 1.3f;
	_speed = 60.f;
	_atkFrame = 3;
	_angle = 0;
	_dirAngle = 0;
	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"Knight_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Hurt", dir + L"Knight_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"Knight_Move_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"Knight_Death_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"Knight_Attack_5x1.png", 5, 1);

	_sprite->SetPivot(PIVOT::BOTTOM);
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(40, 15));
	_sprite->SetScale(Vector2(1.3, 1.3));
	_sprite->SetPosition(_trans->GetPos());
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	_physics->GetBody()->SetFixedRotation(true);

	_leftAtk = Object::CreateObject<Object>(this);
	_leftAtk->Init();
	_leftAtk->SetName("left");
	auto t = _leftAtk->GetTrans();
	t->SetScale(20, 30);
	t->SetPos(_trans->GetPos() + Vector2::left * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	auto p = _leftAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->GetBody()->SetFixedRotation(true);
	p->SetSensor(true);
	p->SetBodyActive(false);
	//_leftAtk->AddComponent<EnemyAtkScript>();
	//_leftAtk->SetIsActive(false);

	_rightAtk = Object::CreateObject<Object>(this);
	_rightAtk->Init();
	_rightAtk->SetName("right");
	t = _rightAtk->GetTrans();
	t->SetScale(20, 30);
	t->SetPos(_trans->GetPos() + Vector2::right * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	p = _rightAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->SetSensor(true);
	p->GetBody()->SetFixedRotation(true);
	p->SetBodyActive(false);
	//_rightAtk->AddComponent<EnemyAtkScript>();
	//_rightAtk->SetIsActive(false);

	_state->Enter();
	_ability->Init(120, 15);
}
//
void Knight::Update()
{
	
	Enemy::Update();

	if (_state->GetStateToString() == "Hurt" or _state->GetStateToString() == "Death")
	{
		_leftAtk->SetIsActive(false);
		_rightAtk->SetIsActive(false);
	}


	_leftAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::left * (5 + (_leftAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	if (_leftAtk->GetComponent<PhysicsBody>()->GetBodyActive()) _leftAtk->GetComponent<PhysicsBody>()->SetBodyPosition();

	_rightAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::right * (5 + (_rightAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	if (_rightAtk->GetComponent<PhysicsBody>()->GetBodyActive())	_rightAtk->GetComponent<PhysicsBody>()->SetBodyPosition();
}
//
//void Knight::Release()
//{
//	Enemy::Release();
//}

void Knight::Attack()
{
	
	switch (_dir)
	{
	case EnemyDirection::LEFT:
		_rightAtk->SetIsActive(true);
		break;
	case EnemyDirection::RIGHT:
		_leftAtk->SetIsActive(true);
		break;
	default:
		break;
	}
	
}

void Knight::AttackExit()
{
	Enemy::AttackExit();
	if (_isHurt)return;
	_leftAtk->SetIsActive(false);
	_rightAtk->SetIsActive(false);
}


void Knight::BasicUpdate()
{
	Enemy::BasicUpdate();
	if (_state->GetStateToString() == "Idle" or _state->GetStateToString() == "Hurt")
		_sprite->SetPosition(_trans->GetPos() + Vector2::down * 13);
	else if (_state->GetStateToString() == "Move")
	{
		if (_dir == E_Dir::RIGHT)
			_sprite->SetPosition(_trans->GetPos() + Vector2::right * 2 + Vector2::down * 8);
		else
			_sprite->SetPosition(_trans->GetPos() + Vector2::left * 2 + Vector2::down * 8);
	}
	else if (_state->GetStateToString() == "Attack")
	{
		if (_dir == E_Dir::RIGHT)
			_sprite->SetPosition(_trans->GetPos() + Vector2::up * 5 + Vector2::right * 5 + Vector2::down * 13);
		else
			_sprite->SetPosition(_trans->GetPos() + Vector2::up * 5 + Vector2::left * 5 + Vector2::down * 13);
	}


	

}

