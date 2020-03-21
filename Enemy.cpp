#include "stdafx.h"
#include "Enemy.h"
#include "EnemyState.h"
#include "EnemyScript.h"
void Enemy::Init()
{
	Object::Init();

	_tag = "Enemy";
	_state = make_shared<EnemyIdle>(this);
	_distance = _atkDistance = _speed = _angle = _isAtkFrame = _FPS = 0;
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_dirAngle = 0;
	_physics = AddComponent<PhysicsBody>();
	//_ability = make_shared<Ability>();
	_ability = new Ability();
	AddComponent<EnemyScript>();
}

void Enemy::Update()
{
	Object::Update();

	if (_state->GetStateToString() != "Hurt" && _isHurt)return;
	BasicUpdate();
	AngleDetection();
	_state->Stay();
	if (_state->GetStateToString() == "Move") Move();
	_timer += TIMEMANAGER->getElapsedTime();
}

void Enemy::Release()
{
	Object::Release();
}



void Enemy::BasicUpdate()
{

	_ability->Update();
	if (_state->GetStateToString() == "Attack")
		if (_sprite->GetCurrentFrameX() == _atkFrame)
			_isAtkFrame = true;
//	_timer += TIMEMANAGER->getElapsedTime();
	
}

void Enemy::AngleDetection()
{
	if ((_dirAngle > PI / 2 && _dirAngle <= PI) || (_dirAngle >= -PI && _dirAngle < -PI / 2)) _dir = E_Dir::LEFT;
	else _dir = E_Dir::RIGHT;

	if (_dir == E_Dir::LEFT) _sprite->SetFlipX(true);
	else _sprite->SetFlipX(false);
}

void Enemy::ChangeState(shared_ptr<EnemyState> state)
{

	_state->Exit();
	_state.swap(state);
	_state->Enter();
}

string Enemy::GetStateName()
{
	return _state->GetStateToString();
}

void Enemy::SetPath(list<Vector2> path)
{
	_path.clear();
	_path = path;
}

void Enemy::Move()
{
	if (_path.size())
	{
		Vector2 dir = *_path.begin() - _trans->GetPos();
		_dirAngle = Vector2::GetAngle(_trans->GetPos(), *_path.begin());
		_trans->Move(dir.Nomalized() * _speed * TIMEMANAGER->getElapsedTime());
		_physics->SetBodyPosition();

		if (Vector2::Distance(*_path.begin(), _trans->GetPos()) <= 5)
		{
			_path.erase(_path.begin());
		}
	}
}

void Enemy::SetImg(string stateName)
{
	
	_sprite->SetImgName(_name + stateName);

	BasicUpdate();
}
