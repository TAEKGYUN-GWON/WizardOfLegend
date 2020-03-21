#include "stdafx.h"
#include "IceBall.h"
#include "Enemy.h"
void IceBall::Init(Object* onwer)
{
	SkillObject::Init();
	_name = "IceBall";
	_onwer = onwer;
	_type = OnwerType::Enemy;
	_skillType = SkillType::One_time;
	_atk = 2;
	_trans->SetScale(15, 15);
	Enemy* enemy = (Enemy*)_onwer;
	_trans->SetPos(enemy->GetTrans()->GetPos() + Vector2(cosf(enemy->GetAngle()), -sinf(enemy->GetAngle())) * 2 * (enemy->GetTrans()->GetScale()));
	_trans->SetRotateToRadian(-enemy->GetAngle());
	GRAPHICMANAGER->AddFrameImage("IceBall", L"Resource/Wizard/Enemy/IceBall.png", 4, 1);
	_sprite = AddComponent<Sprite>();
	_sprite->SetScale(Vector2(1.3, 1.3));
	_sprite->Init(true, true);
	_sprite->SetImgName("IceBall");
	_sprite->SetFPS(3);
	_timer = 0;
	_maxTimer = 0.7f;
	_speed = 500;
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1, 1);
	//_physics->GetBody()->SetTransform(b2Vec2(_physics->GetBody()->GetPosition().x, _physics->GetBody()->GetPosition().y), _trans->GetRotateRadian());
	//_physics->SetBodyActive(false);
	_physics->GetBody()->SetTransform(_physics->GetBody()->GetPosition(), -enemy->GetAngle());
	_physics->GetBody()->SetFixedRotation(true);
	_moveAngle = enemy->GetAngle();
}

void IceBall::Move()
{
	
	
	if (_timer >= _maxTimer)
	{
		SetIsRelese();
		_timer = _maxTimer;
		return;
	}
	else _timer += TIMEMANAGER->getElapsedTime();
	_trans->Move(Vector2(cosf(_moveAngle), -sinf(_moveAngle)) * _speed * TIMEMANAGER->getElapsedTime());
	_physics->SetBodyPosition();
	_sprite->SetPosition(_trans->GetPos());
}
