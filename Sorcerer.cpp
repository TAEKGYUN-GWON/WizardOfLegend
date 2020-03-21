#include "stdafx.h"
#include "Sorcerer.h"
#include "EnemyState.h"
#include "IceBall.h"
void Sorcerer::Init(Vector2 pos)
{
	Enemy::Init();

	_ability->Init(80, 10);
	_name = "Sorcerer";
	_atkDistance =100.f;
	_distance = 111;
	_FPS = 1.3f;
	_speed = 30.f;
	_atkFrame = 4;
	_angle = _timer = 0;
	_maxTimer = 2.f;
	_isFire = false;
	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"SummonerIdleDown.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Hurt", dir + L"SummonerHurt.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"SummonerRunRight0_3x1.png", 3, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"SummonerDead0_6x1.png", 6, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"SummonerCast0_6x1.png", 6, 1);
	_atkType = E_AtkType::DISTANT;
	_sprite->SetPivot(PIVOT::BOTTOM);
	_sprite->SetScale(Vector2(1.3, 1.3));
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(40, 15));
	_sprite->SetPosition(_trans->GetPos());
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	_physics->GetBody()->SetFixedRotation(true);
	_state->Enter();
}

void Sorcerer::Update()
{
	Enemy::Update();
	if (KEYMANAGER->isOnceKeyDown('1'))
		_distance = 5;
	if (KEYMANAGER->isOnceKeyDown('2'))
		_distance = 100;
}


void Sorcerer::Attack()
{
	if (_atkFrame == _sprite->GetCurrentFrameX() && !_isFire)
	{
		IceBall* ice = Object::CreateObject<IceBall>(this);
		ice->Init(this);
		_isFire = true;
	}
}

void Sorcerer::AttackExit()
{
	Enemy::AttackExit();
	_isFire = false;
}

void Sorcerer::BasicUpdate()
{
	Enemy::BasicUpdate();
	_sprite->SetPosition(_trans->GetPos() + Vector2::down * 10);
}
