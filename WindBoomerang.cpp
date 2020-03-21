#include "stdafx.h"
#include "WindBoomerang.h"
#include "Player.h"
#include "Enemy.h"
/*
	_angle += 0.05f;
	_position.x = _playerPosition.x+cosf(_angle)*100;
	_position.y = _playerPosition.y -sinf(_angle)*100;

*/

void WindBoomerang::Init(Object* onwer)
{

	SkillObject::Init();
	_name = "WindBoomerang";
	_onwer = onwer;
	_type = OnwerType::Player;
	_skillType = SkillType::Continued;
	_atk = 1.5;
	_trans->SetScale(50, 50);
	Player* player = (Player*)_onwer;
	_trans->SetPos(player->GetTrans()->GetPos() + Vector2(cosf(player->GetAtkAngle()), -sinf(player->GetAtkAngle())) * 60);
	_trans->SetRotateToRadian(-player->GetAtkAngle());
	GRAPHICMANAGER->AddFrameImage("WindBoomerang", L"Resource/Wizard/Skill/WindBoomerang.png", 4, 1);
	_sprite = AddComponent<Sprite>();
	//_sprite->SetScale(Vector2(1.3, 1.3));
	_sprite->Init(true, true);
	_sprite->SetFPS(2);
	_sprite->SetImgName("WindBoomerang");
	_timer = 0;
	_angle = player->GetAtkAngle();
	_maxTimer = 1.5f;
	_speed = 100;
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	//_physics->GetBody()->SetTransform(b2Vec2(_physics->GetBody()->GetPosition().x, _physics->GetBody()->GetPosition().y), _trans->GetRotateRadian());
	//_physics->SetBodyActive(false);
	_physics->GetBody()->SetTransform(_physics->GetBody()->GetPosition(), -player->GetAtkAngle());
	//_physics->GetBody()->SetFixedRotation(true);
	_moveAngle = player->GetAtkAngle();

}

void WindBoomerang::Move()
{
	_timer += TIMEMANAGER->getElapsedTime();

	if (_timer >= _maxTimer)
	{
		SOUNDMANAGER->stop("Spin");
		SetIsRelese();
	}

	_angle += 0.05f * _speed * TIMEMANAGER->getElapsedTime();
	_trans->SetPos(_onwer->GetTrans()->GetPos() + Vector2(cosf(_angle), -sinf(_angle)) * 60);
	_physics->GetBody()->SetAngularVelocity(0.05f * _speed * TIMEMANAGER->getElapsedTime());
	_physics->SetBodyPosition();
	_sprite->SetPosition(_trans->GetPos());

}
