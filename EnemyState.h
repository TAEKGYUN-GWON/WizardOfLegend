#pragma once
#include "Enemy.h"
//class Enemy;

//enum class EnemyAttackType;

class EnemyState : public enable_shared_from_this<EnemyState>
{
protected:

	Enemy* _enemy;
	string _name;
	float _timer;
	float _maxTimer;

public:
	EnemyState(){}
	EnemyState(Enemy* enemy) :_enemy(enemy) {}
	virtual void Enter() {};
	virtual void Stay() {};
	virtual void Exit() {};

	Enemy* GetEnemy() { return _enemy; }
	string GetStateToString() { return _name; }
	shared_ptr<EnemyState> GetState() { return shared_from_this(); }
};

class EnemyIdle : public EnemyState
{

private:

public:
	EnemyIdle(Enemy* enemy) : EnemyState(enemy){}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class EnemyMove : public EnemyState
{

private:
	float moveTimer;
public:
	EnemyMove(Enemy* enemy) : EnemyState(enemy) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};


class EnemyAttack : public EnemyState
{

private:
	EnemyAttackType _type;
public:
	EnemyAttack(Enemy* enemy) : EnemyState(enemy) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class EnemyHurt : public EnemyState
{

private:
public:
	EnemyHurt(Enemy* enemy) : EnemyState(enemy) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class EnemyDeath : public EnemyState
{

private:

public:
	EnemyDeath(Enemy* enemy) : EnemyState(enemy) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

