#pragma once
class Player;

class PlayerState : public enable_shared_from_this<PlayerState>
{
protected:

	Player* _player;
	string _name;
	float _timer;
	float _maxTimer;

public:
	PlayerState() {}
	PlayerState(Player* player) :_player(player) {}
	virtual void Enter() {};
	virtual void Stay() {};
	virtual void Exit() {};

	Player* GetPlayer() { return _player; }
	string GetStateToString() { return _name; }
	shared_ptr<PlayerState> GetState() { return shared_from_this(); }
};


class PlayerIdle : public PlayerState
{

private:

public:
	PlayerIdle(Player* player) : PlayerState(player) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class PlayerMove : public PlayerState
{

private:

public:
	PlayerMove(Player* player) : PlayerState(player) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class PlayerDash : public PlayerState
{

private:
	Vector2 lastPos;
	float speed;
public:
	PlayerDash(Player* player) : PlayerState(player) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};


class PlayerAttack : public PlayerState
{

private:
	bool isAttack;

public:
	PlayerAttack(Player* player) : PlayerState(player) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class PlayerHurt : public PlayerState
{

private:

public:
	PlayerHurt(Player* player) : PlayerState(player) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

class PlayerDeath : public PlayerState
{

private:

public:
	PlayerDeath(Player* player) : PlayerState(player) {}
	virtual void Enter();
	virtual void Stay();
	virtual void Exit();
};

