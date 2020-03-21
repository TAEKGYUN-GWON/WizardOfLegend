#include "stdafx.h"
#include "ChaosCircle.h"
#include "Player.h"
#include "Enemy.h"
void ChaosCircle::Init(Object* onwer)
{
	SkillObject::Init();
	_onwer = onwer;
	_type = OnwerType::Player;
	_skillType = SkillType::Continued;
	_atk = 0.3f;
	_trans->SetScale(100, 100);
	Player* player = (Player*)_onwer;
	_trans->SetPos(player->GetTrans()->GetPos() + Vector2(cosf(player->GetAtkAngle()), -sinf(player->GetAtkAngle())) * player->GetTrans()->GetScale());
	_name = "ChaosCircle";
	GRAPHICMANAGER->AddFrameImage("ChaosCircle", L"Resource/Wizard/Skill/ChaosCircle_0_12x1.png", 12, 1);
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("ChaosCircle");
	_sprite->SetFPS(2);
	_timer = 0;
	_maxTimer = 2.5f;
	_speed = 70.f;
	_isStartAtk = _isEndAtk = false;
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	_physics->SetBodyActive(false);
	_moveAngle = player->GetAtkAngle();
}

void ChaosCircle::Move()
{

	if (!_isStartAtk)
	{
		if (_sprite->GetCurrentFrameX() == 4)
		{
			_isStartAtk = true;
			_physics->SetBodyActive(true);
		}
	}
	else
		_timer += TIMEMANAGER->getElapsedTime();


	if (_timer <= _maxTimer)
	{
		if (_sprite->GetCurrentFrameX() == 7) _sprite->SetFrameX(4);
	}
	else
	{
		if (_sprite->GetCurrentFrameX() == _sprite->GetMaxFrameX())
		{
			SetIsRelese(); 
			SOUNDMANAGER->stop("WhipSwing");
		}
	}

	_trans->Move(Vector2(cosf(_moveAngle), -sinf(_moveAngle)) * _speed * TIMEMANAGER->getElapsedTime());
	_physics->SetBodyPosition();
	_trans->SetRotateToRadian(_physics->GetBodyAngle());
	_sprite->SetPosition(_trans->GetPos());
	
}
