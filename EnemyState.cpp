#include "stdafx.h"
#include "EnemyState.h"

//idle
void EnemyIdle::Enter()
{
	_name = "Idle";
	_timer = 0;
	_maxTimer = RND->getFromFloatTo(2, 4);
	_enemy->SetImg(_name);
	_enemy->GetPhysics()->SetBodyPosition();
	_enemy->GetPhysics()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
}

void EnemyIdle::Stay()
{
	if (_enemy->GetAbility()->GetIsDead())
	{
		_enemy->ChangeState(make_shared <EnemyDeath>(_enemy));
		return;
	}
	_timer += TIMEMANAGER->getElapsedTime();

	if (_enemy->GetDistance() <= _enemy->GetAtkDistance())
	{
		if (_enemy->GetAtkType() == E_AtkType::CLOSE)
			_enemy->ChangeState(make_shared <EnemyAttack>(_enemy));
		else
		{
			if (_enemy->GetTimer() >= _enemy->GetMaxTimer())
			{
				_enemy->SetTimer(0);
				_enemy->ChangeState(make_shared <EnemyAttack>(_enemy));
			}

		}
		return;
	}

	if (_timer >= _maxTimer)
	{
		_enemy->ChangeState(make_shared <EnemyMove>(_enemy));
		return;
	}
	_enemy->GetPhysics()->SetBodyPosition();
}

void EnemyIdle::Exit()
{
}


//move
void EnemyMove::Enter()
{
	_name = "Move";
	_timer = 0;
	_maxTimer = RND->getFromFloatTo(2, 4);
	_enemy->SetImg(_name);
	_enemy->SetIsMove(true);
	moveTimer = 0;
}

void EnemyMove::Stay()
{
	
	if (_enemy->GetAbility()->GetIsDead())
	{
		_enemy->ChangeState(make_shared <EnemyDeath>(_enemy));
		return;
	}

	_timer += TIMEMANAGER->getElapsedTime();

	if (_timer >= _maxTimer)
	{
		_enemy->ChangeState(make_shared <EnemyIdle>(_enemy));
		return;
	}

	if (_enemy->GetDistance() <= _enemy->GetAtkDistance())
	{
		if(_enemy->GetAtkType() == E_AtkType::CLOSE)
			_enemy->ChangeState(make_shared <EnemyAttack>(_enemy));
		else
		{
			if (_enemy->GetTimer() >= _enemy->GetMaxTimer())
			{
				_enemy->SetTimer(0);
				_enemy->ChangeState(make_shared <EnemyAttack>(_enemy));
			}
				
		}
		return;
	}

	_enemy->SetIsMove(false);

	moveTimer += TIMEMANAGER->getElapsedTime();

	if (moveTimer > 0.5f) {
		_enemy->SetIsMove(true);
		moveTimer = 0;
	}

}

void EnemyMove::Exit()
{
	
}


//attack
void EnemyAttack::Enter()
{
	_name = "Attack";
	_type = _enemy->GetAtkType();

	_enemy->SetImg(_name);
	SOUNDMANAGER->play(_enemy->GetName()+"Attack");
}

void EnemyAttack::Stay()
{
	 _enemy->SetDirAngle(_enemy->GetAngle());

	if (_enemy->GetAbility()->GetIsDead())
	{
		_enemy->ChangeState(make_shared <EnemyDeath>(_enemy));
		return;
	}

	if (_enemy->GetAtkFrame())
	{
		_enemy->Attack();

		if (_enemy->GetSprite()->GetCurrentFrameX() >= _enemy->GetSprite()->GetMaxFrameX())
		{
			_enemy->ChangeState(make_shared <EnemyIdle>(_enemy));
			return;
		}
	}
}

void EnemyAttack::Exit()
{
	_enemy->AttackExit();
}


//hurt
void EnemyHurt::Enter()
{
	SOUNDMANAGER->play("EnemyHurt");
	_timer = 0;
	_maxTimer = 0.5f;
	_name = "Hurt";
	_enemy->SetImg(_name);
	_enemy->SetIsHurt(true);
	_enemy->GetPhysics()->ApplyForce(b2Vec2(cosf(_enemy->GetHurtAngle()), -sinf(_enemy->GetHurtAngle())) );
}

void EnemyHurt::Stay()
{
	if (_enemy->GetAbility()->GetIsDead())
	{
		_enemy->ChangeState(make_shared <EnemyDeath>(_enemy));
		return;
	}

	_timer += TIMEMANAGER->getElapsedTime();
	
	if (_timer >= _maxTimer)
	{
		_enemy->ChangeState(make_shared <EnemyIdle>(_enemy));
		return;
	}

}

void EnemyHurt::Exit()
{
	_enemy->SetIsHurt(false);
	_enemy->GetPhysics()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
}



//death
void EnemyDeath::Enter()
{
	SOUNDMANAGER->play("EnemyDead");
	_timer = 0;
	_maxTimer = 1.5f;
	_name = "Death";
	_enemy->SetImg(_name);
	_enemy->GetPhysics()->SetBodyActive(false);
}

void EnemyDeath::Stay()
{
	if (_enemy->GetSprite()->GetCurrentFrameX() == _enemy->GetSprite()->GetMaxFrameX()) _enemy->GetSprite()->Pause();

	if (_enemy->GetComponent<Sprite>()->GetCurrentFrameX() == _enemy->GetComponent<Sprite>()->GetMaxFrameX())
		_timer += TIMEMANAGER->getElapsedTime();
	

	if(_timer>=_maxTimer)
		_enemy->SetIsActive(false);
}

void EnemyDeath::Exit()
{
}
