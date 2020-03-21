#pragma once
#include "Ability.h"
class PlayerState;

typedef struct tagPlayerSkill
{
	string name;
	float cooldownTime;
	float curTime;
	tagPlayerSkill(string name, float coolTime) : name(name), cooldownTime(coolTime) { curTime = coolTime; }

}P_Skill;

typedef enum class Player_Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
} P_DIR;

class Player : public Object
{
private:
	shared_ptr<Ability> _ability;
	shared_ptr<PlayerState> _state;
	Sprite* _sprite;
	PhysicsBody* _physics;
	P_DIR _dir;
	vector<P_Skill*> _skills;
	P_Skill* _curSkill;
	float _speed;
	float _atkAngle;
	float _hurtAngle;
	float _moveAngle;
	float _FPS;
	int _atkFrame;
	bool _isAtkFrame;
	bool _isCollisionToWall;
	bool _isDead;
	bool _isBattle;
	Object* _maker;

public:

	virtual void Init(Vector2 pos);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void SetIsBattle(bool active) { _isBattle = active; }
	bool GetIsBattle() { return _isBattle; }

	void OffAtkFrame() { _isAtkFrame = false; }
	bool GetIsAtkFrame() { return _isAtkFrame; }
	int GetAtkFrame() { return _atkFrame; }
	void AttackExit() { OffAtkFrame(); }

	Sprite* GetSprite() { return _sprite; }
	PhysicsBody* GetPhysics() { return _physics; }

	void ChangeState(shared_ptr<PlayerState> state);

	shared_ptr<PlayerState> GetState() { return _state; }
	string GetStateName();

	shared_ptr<Ability> GetAbility() { return _ability; }
	P_DIR GetDirection() { return _dir; }
	void SetDirection(P_DIR dir) { _dir = dir; }
	string GetDirectionToString();

	void SetHurtAngle(float angle) { _hurtAngle = angle; }
	float GetHurtAngle() { return _hurtAngle; }

	float GetAtkAngle() { return _atkAngle; }
	float GetSpeed() { return _speed; }

	void SetMoveAngle(float angle) { _moveAngle = angle; }
	float GetMoveAngle() { return _moveAngle; }
	void Move();

	void SetIsCollToWall(bool active) { _isCollisionToWall = active; }
	bool GetIsCollToWall() { return _isCollisionToWall; }
	void SetIsDead(bool active) { _isDead = active; }
	void BasicUpdate();
	void WindUpCoolDown();
	void FlipDetection();
	void AtkAngleDetection();
	void SetPlayerImg(string stateName);
	void SetFPS(float FPS) { _FPS = FPS; }
	P_Skill* FindSkill(string name);
	P_Skill* GetCurrentSkill() { return _curSkill; };
	vector<P_Skill*> GetSkills() { return _skills; }
	void ChangeCurrentSkill();

};

