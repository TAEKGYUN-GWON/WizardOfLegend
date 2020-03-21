#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Room.h"
#include "Astar.h"
#include "Player.h"
#include "UiManager.h"
class Probe;
#define CREATE_ROOM_MAX 50
#define SELECT_ROOM 10

#define MAP_TILE_MAX_X ((MAP_MAX_WIDTH / TILE_WIDTH) + 1)
#define MAP_TILE_MAX_Y MAP_MAX_HEIGHT / TILE_HEIGHT

class ProceduralTest : public Scene
{
private: 
	Astar* _ast;
	vector<Tile*> tiles;
	vector<Room*> rooms;
	vector<Room*> selRooms;
	vector<Room*> mainRooms;
	vector<Room*> subRooms;
	Room* currentRoom;
	float maxY;
	float _alpha;
	bool alphaFlip;
	float timer;
	bool endPush; 
	bool endCreate;
	bool startDel;
	bool startExploration;
	int count;
	Player* _player;
	vector<Object*> _vFloors;
	UiManager* _uiMgr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();
	virtual void PhysicsUpdate(); 
	void PushRoom();
	void SelRoom();
	void DelRoom();
	void SetTile();
	void Exploration();
	void SetSubRoom();
	void SetTileProperty();
	void SetTileObjet();
	void SetWall();
	void SetTileImg();
	void DelTile();
	void SetPhysics();
	void SetPlayer();
	vector<Tile*>* GetTiles() { return &tiles; }
	void SendAPlayerBossRoom();
	void SetEnemy();

	void SetScene();
}; 

