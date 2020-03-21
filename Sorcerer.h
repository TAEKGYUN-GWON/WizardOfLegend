#pragma once
#include "Enemy.h"
class Sorcerer : public Enemy
{
private:
	bool _isFire;
public:

	virtual void Init(Vector2 pos);
	virtual void Update();
	//virtual void Release();
	virtual void Attack();
	virtual void AttackExit();
	virtual void BasicUpdate();
	bool GetIsFire() { return _isFire; }
};

