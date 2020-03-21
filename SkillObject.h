#pragma once
#include "Object.h"

enum class SkillType
{
	Continued,
	One_time
};

enum class OnwerType
{
	Player,
	Enemy
};

class SkillObject :	public Object
{
protected:

	PhysicsBody* _physics;
	Object* _onwer;
	Sprite* _sprite;
	OnwerType _type;
	SkillType _skillType;
	float _atk;
	float _speed;
	float _timer;
	float _maxTimer;
	float _moveAngle;
	float _maxCoolDown;
	float _curCoolDown;
	bool _isCollision;
public:
	virtual void Init();
	virtual void Update();
	virtual void Move() {};
	void WindUpCollCoolDown();
	void SetIsCollision(bool active) { _isCollision = active; }
	bool GetIsCollison() { return _isCollision; }
	float GetAtk() { return _atk; }
	OnwerType GetOwnerType() { return _type; }
	SkillType GetSkillType() { return _skillType; }
	Object* GetOnwer() { return _onwer; }
};

