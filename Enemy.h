#pragma once
#include "Object.h"
#include "Ability.h"
class EnemyState;

typedef enum class EnemyAttackType
{
	CLOSE,
	DISTANT

} E_AtkType;

typedef enum class EnemyDirection
{
	LEFT,
	RIGHT

}E_Dir;

class Enemy :	public Object
{
protected:

	Ability* _ability;
	shared_ptr<EnemyState> _state;
	E_AtkType _atkType;
	E_Dir _dir;
	float _FPS;
	float _distance;
	float _atkDistance;
	float _speed;
	float _angle;
	float _dirAngle;
	float _hurtAngle;
	int _atkFrame;
	bool _isAtkFrame;
	bool _isHurt;
	bool _isMove;
	float _timer;
	float _maxTimer;
	list<Vector2> _path;

	Sprite* _sprite;
	PhysicsBody* _physics;

public:

	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Attack() {};
	virtual void AttackExit() { OffAtkFrame(); }
	virtual void BasicUpdate();
	void Move();
	void AngleDetection();
	void ChangeState(shared_ptr<EnemyState> state);
	void OffAtkFrame() { _isAtkFrame = false; }


	//Getter
	float GetAngle() { return _angle; }
	float GetHurtAngle() { return _hurtAngle; }
	float GetDirAngle() { return _dirAngle; }
	float GetTimer() { return _timer; }
	float GetMaxTimer() { return _maxTimer; }
	float GetDistance() { return _distance; }
	float GetAtkDistance() { return _atkDistance; }
	float GetSpeed() { return _speed; }

	bool GetIsMove() { return _isMove; }
	bool GetIsHurt() { return _isHurt; }
	bool GetAtkFrame() { return _isAtkFrame; }

	shared_ptr<EnemyState> GetState() { return _state; }
	string GetStateName();
	Ability* GetAbility() { return _ability; }
	E_AtkType GetAtkType() { return _atkType; }
	Sprite* GetSprite() { return _sprite; }
	PhysicsBody* GetPhysics() { return _physics; }
	E_Dir GetDir() { return _dir; }
	list<Vector2> GetPath() { return _path; }


	//Setter
	void SetImg(string stateName);
	void SetPath(list<Vector2> path);
	void SetIsHurt(bool active) { _isHurt = active; }
	void SetIsMove(bool active) { _isMove = active; }
	void SetTimer(float time) { _timer = time; }
	void SetDistance(float distance) { _distance = distance; }
	void SetAngle(float angle) { _angle = angle; }
	void SetHurtAngle(float angle) { _hurtAngle = angle; }
	void SetDirAngle(float angle) { _dirAngle = angle; }
	void SetAtkType(E_AtkType atkType) { _atkType = atkType; }
};
