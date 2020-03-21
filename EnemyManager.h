#pragma once
#include "Enemy.h"
#include "Astar.h"

class Room;
class EnemyManager
{
private:
	list<Enemy*> _Enemys;
	Room* _owner;
	Astar* _ast;
	bool _isActive;
public:
	void Init(Room* owner);
	void Update();
	void Release();
	void SetIsActive(bool active) { _isActive = active; }
	bool GetIsActive() { return _isActive; }
	void SetEnemys();
	int GetEnemySize() { return _Enemys.size(); }
};

