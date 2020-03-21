#pragma once
#include "Enemy.h"
class Rogue :	public Enemy
{
private:
	Object* _leftAtk;
	Object* _rightAtk;

public:
	virtual void Init(Vector2 pos);
	virtual void Update();
	//virtual void Release();
	virtual void Attack();
	virtual void AttackExit();
	virtual void BasicUpdate();
};

