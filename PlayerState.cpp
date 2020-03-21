#include "stdafx.h"
#include "PlayerState.h"
#include "Player.h"
#include "FireBall.h"
#include "ChaosCircle.h"
#include "WindBoomerang.h"
//Idle
void PlayerIdle::Enter()
{
	_name = "Idle";
	_player->SetPlayerImg(_name);
	_player->GetPhysics()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
}

void PlayerIdle::Stay()
{
	if (_player->GetAbility()->GetIsDead())
	{
		_player->ChangeState(make_shared<PlayerDeath>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player->SetDirection(P_DIR::UP);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player->SetDirection(P_DIR::LEFT);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_player->SetDirection(P_DIR::DOWN);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player->SetDirection(P_DIR::RIGHT);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_player->ChangeState(make_shared<PlayerDash>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_player->GetCurrentSkill()->curTime >= _player->GetCurrentSkill()->cooldownTime)
			_player->ChangeState(make_shared<PlayerAttack>(_player));
		return;
	}

}

void PlayerIdle::Exit()
{
}

//Move
void PlayerMove::Enter()
{
	_name = "Move";
	_player->SetFPS(2.f);
	_player->SetPlayerImg(_name);
	SOUNDMANAGER->play("PlayerFootstep");
}

void PlayerMove::Stay()
{
	if (_player->GetAbility()->GetIsDead())
	{
		_player->ChangeState(make_shared<PlayerDeath>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_player->GetDirection() != P_DIR::RIGHT)
		{
			_player->SetDirection(P_DIR::RIGHT);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('W')) _player->SetMoveAngle(PI / 4);

		else if (KEYMANAGER->isStayKeyDown('S')) _player->SetMoveAngle(-PI / 4);

		else _player->SetMoveAngle(0);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_player->GetDirection() != P_DIR::LEFT)
		{
			_player->SetDirection(P_DIR::LEFT);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('W'))  _player->SetMoveAngle((PI * 3) / 4);

		else if (KEYMANAGER->isStayKeyDown('S')) _player->SetMoveAngle(-(PI * 3) / 4);

		else _player->SetMoveAngle(PI);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else if (KEYMANAGER->isStayKeyDown('W'))
	{

		if (_player->GetDirection() != P_DIR::UP)
		{
			_player->SetDirection(P_DIR::UP);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('A')) _player->SetMoveAngle((PI * 3) / 4);

		else if (KEYMANAGER->isStayKeyDown('D')) _player->SetMoveAngle(PI / 4);

		else _player->SetMoveAngle(PI / 2);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_player->GetDirection() != P_DIR::DOWN)
		{
			_player->SetDirection(P_DIR::DOWN);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('A')) _player->SetMoveAngle(-(PI * 3) / 4);

		else if (KEYMANAGER->isStayKeyDown('D')) _player->SetMoveAngle(-PI / 4);

		else _player->SetMoveAngle(-PI / 2);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}
	else
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_player->ChangeState(make_shared<PlayerDash>(_player));
		return;
	}

	_player->GetTrans()->Move(Vector2(cosf(_player->GetMoveAngle()), -sinf(_player->GetMoveAngle())) * _player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	_player->GetPhysics()->SetBodyPosition();
	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if(_player->GetCurrentSkill()->curTime >= _player->GetCurrentSkill()->cooldownTime)
			_player->ChangeState(make_shared<PlayerAttack>(_player));
		return;
	}

}

void PlayerMove::Exit()
{
	SOUNDMANAGER->stop("PlayerFootstep");
}

//Attack;
void PlayerAttack::Enter()
{
	_name = "Attack";
	_player->SetFPS(2.f);

	float angle = _player->GetAtkAngle();

	if (angle >= 45 * DegToRad && angle < 135 * DegToRad) _player->SetDirection(P_DIR::UP);

	else if (angle <= -45 * DegToRad && angle > -135 * DegToRad) _player->SetDirection(P_DIR::DOWN);

	else if (angle >= 135 * DegToRad && angle < 180 * DegToRad) _player->SetDirection(P_DIR::LEFT);
	else if (angle <= -135 * DegToRad && angle > -180 * DegToRad) _player->SetDirection(P_DIR::LEFT);


	else if (angle <= 0 * DegToRad && angle > -45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);
	else if (angle >= 0 * DegToRad && angle < 45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);
	isAttack = false;
	_player->SetPlayerImg(_name);
}

void PlayerAttack::Stay()
{
	if (_player->GetAbility()->GetIsDead())
	{
		_player->ChangeState(make_shared<PlayerDeath>(_player));
		return;
	}

	if (_player->GetSprite()->GetCurrentFrameX() == _player->GetAtkFrame())
	{
		if (_player->GetCurrentSkill()->name == "WindBoomerang")
		{
			if (!isAttack)
			{
				SOUNDMANAGER->play("Spin");
				WindBoomerang* chaos = Object::CreateObject<WindBoomerang>(_player);
				_player->GetCurrentSkill()->curTime = 0;
				chaos->Init(_player);
				isAttack = true;
			}
		}
		if (_player->GetCurrentSkill()->name == "FireBall")
		{
			if (!isAttack)
			{
				SOUNDMANAGER->play("FireBlast");
				FireBall* chaos = Object::CreateObject<FireBall>(_player);
				_player->GetCurrentSkill()->curTime = 0;
				chaos->Init(_player);
				isAttack = true;
			}
		}
		if (_player->GetCurrentSkill()->name == "ChaosCircle")
		{
			if (!isAttack)
			{
				SOUNDMANAGER->play("WhipSwing");
				ChaosCircle* chaos = Object::CreateObject<ChaosCircle>(_player);
				_player->GetCurrentSkill()->curTime = 0;
				chaos->Init(_player);
				isAttack = true;
			}
		}
		

	}
	if (_player->GetSprite()->GetCurrentFrameX() == _player->GetSprite()->GetMaxFrameX()) _player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerAttack::Exit()
{
}

//Hurt
void PlayerHurt::Enter()
{
	_name = "Hurt";
	SOUNDMANAGER->play("FireBlast");
	float angle = _player->GetHurtAngle();

	if (angle >= 45 * DegToRad && angle < 135 * DegToRad) _player->SetDirection(P_DIR::UP);

	else if (angle <= -45 * DegToRad && angle > -135 * DegToRad) _player->SetDirection(P_DIR::DOWN);

	else if (angle >= 135 * DegToRad && angle < 180 * DegToRad) _player->SetDirection(P_DIR::LEFT);
	else if (angle <= -135 * DegToRad && angle > -180 * DegToRad) _player->SetDirection(P_DIR::LEFT);


	else if (angle <= 0 * DegToRad && angle > -45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);
	else if (angle >= 0 * DegToRad && angle < 45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);

	_player->GetPhysics()->ApplyForce(b2Vec2(cosf(angle), -sinf(angle)) * 1);

	_player->SetPlayerImg(_name);
	_timer = 0;
	_maxTimer = 0.5f;
	CAMERA->ShakingSetting(0.5, 3);
}

void PlayerHurt::Stay()
{
	if (_player->GetAbility()->GetIsDead())
	{
		_player->ChangeState(make_shared<PlayerDeath>(_player));
		return;
	}
	_timer += TIMEMANAGER->getElapsedTime();

	if (_timer >= _maxTimer)
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
	}
}

void PlayerHurt::Exit()
{
	_player->GetPhysics()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
}

//Death
void PlayerDeath::Enter()
{
	_name = "Death";
	_player->SetFPS(1.5f);
	_player->SetPlayerImg(_name);
	_player->GetPhysics()->SetBodyActive(false);
	SOUNDMANAGER->play("PlayerDead");
}

void PlayerDeath::Stay()
{
	if (_player->GetSprite()->GetCurrentFrameX() == _player->GetSprite()->GetMaxFrameX())
	{
		_player->GetSprite()->Pause();
		_player->SetIsDead(true);
	}
}

void PlayerDeath::Exit()
{

}

void PlayerDash::Enter()
{
	_name = "Dash";
	SOUNDMANAGER->play("AirJet");
	_player->SetFPS(1.5f);
	_player->SetPlayerImg(_name);
	switch (_player->GetDirection())
	{
	case P_DIR::UP:
	{
		EFFECTMANAGER->SetEffect("DashAirBurst", _player->GetTrans()->GetPosToPivot(TF_PIVOT::BOTTOM), -PI / 2, 2.3f);
		lastPos = _player->GetTrans()->GetPos() + Vector2::up * 140;
	}
		break;
	case P_DIR::DOWN:
	{
		EFFECTMANAGER->SetEffect("DashAirBurst", _player->GetTrans()->GetPosToPivot(TF_PIVOT::TOP), PI/2, 2.3f);
		lastPos = _player->GetTrans()->GetPos() + Vector2::down * 140;
	}
		break;
	case P_DIR::LEFT:
	{
		EFFECTMANAGER->SetEffect("DashAirBurst", _player->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT) + Vector2::right * 10, 0, 2.3f);
		lastPos = _player->GetTrans()->GetPos() + Vector2::left * 140;
	}
		break;
	case P_DIR::RIGHT:
	{
		EFFECTMANAGER->SetEffect("DashAirBurst", _player->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT) + Vector2::left *10, PI, 2.3f);
		lastPos = _player->GetTrans()->GetPos() + Vector2::right * 140;
	}
		break;
	}
	speed = 500;
}

void PlayerDash::Stay()
{

	switch (_player->GetDirection())
	{
	case P_DIR::UP:
	{
		_player->GetTrans()->Move(Vector2::up * speed * TIMEMANAGER->getElapsedTime());
		_player->GetPhysics()->SetBodyPosition();
	}
	break;
	case P_DIR::DOWN:
	{
		_player->GetTrans()->Move(Vector2::down * speed * TIMEMANAGER->getElapsedTime());
		_player->GetPhysics()->SetBodyPosition();
	}
	break;
	case P_DIR::LEFT:
	{
		_player->GetTrans()->Move(Vector2::left * speed * TIMEMANAGER->getElapsedTime());
		_player->GetPhysics()->SetBodyPosition();
	}
	break;
	case P_DIR::RIGHT:
	{
		_player->GetTrans()->Move(Vector2::right * speed * TIMEMANAGER->getElapsedTime());
		_player->GetPhysics()->SetBodyPosition();
	}
	break;
	}

	if (Vector2::Distance(_player->GetTrans()->GetPos(), lastPos) < 5)_player->ChangeState(make_shared<PlayerIdle>(_player));

}

void PlayerDash::Exit()
{
}
