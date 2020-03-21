#include "stdafx.h"
#include "EnemyManager.h"
#include "Knight.h"
#include "Sorcerer.h"
#include "Rogue.h"
#include "ProceduralTest.h"
#include "Room.h"
#include "EnemyState.h"
void EnemyManager::Init(Room* owner)
{
	_owner = owner;
	SetEnemys();
	
	if (!_ast)
	{
		_ast = new Astar;
		ProceduralTest* scene = (ProceduralTest*) SCENEMANAGER->GetNowScene();
		_ast->Init(scene->GetTiles(), MAP_TILE_MAX_X, MAP_TILE_MAX_Y);
	}

}

void EnemyManager::Update()
{
	for (Enemy* e : _Enemys)
	{
		//if (!e->GetIsActive())
		//{
		//	e->SetIsRelese();
		//	_Enemys.remove(e);
		//	break;
		//}
		if (e->GetIsMove())
		{
			if (Vector2::Distance(SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos(), e->GetTrans()->GetPos()) > 20 &&
				Vector2::Distance(SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos(), e->GetTrans()->GetPos()) < 300)
			{
				e->SetPath(_ast->PathFinder(e->GetTrans()->GetPos(), SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos()));
			}
		}
		
		if(e->GetName()=="Knight")	e->SetAngle(Vector2::GetAngle( SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos(), e->GetTrans()->GetPos()));
		else e->SetAngle(Vector2::GetAngle(e->GetTrans()->GetPos(), SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos()));

		e->SetDistance(Vector2::Distance(e->GetTrans()->GetPos(), SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos()));
	}
}

void EnemyManager::Release()
{
	for (Enemy* e : _Enemys)
		e->SetIsRelese();

	_Enemys.clear();

	_ast->Release();

	_ast = nullptr;

	_isActive = false;
}

void EnemyManager::SetEnemys()
{
	int some = RND->getFromIntTo(3, 7);
	for (int i = 0; i < some; i++)
	{
		int type = RND->getInt(3);
		//int type = 0;

		switch (type)
		{
		case 0:
		{
			Knight* enemy = Object::CreateObject<Knight>();
			Vector2 pos = Vector2::RandPosition(_owner->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2(TILE_WIDTH * 2, TILE_HEIGHT),
				_owner->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) - Vector2(TILE_WIDTH, TILE_HEIGHT));
			
			enemy->Init(pos);
			_Enemys.push_back(enemy);
		}
		break;

		case 1:
		{
			//Sorcerer
			Sorcerer* enemy = Object::CreateObject<Sorcerer>();
			Vector2 pos = Vector2::RandPosition(_owner->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2(TILE_WIDTH * 2, TILE_HEIGHT),
				_owner->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) - Vector2(TILE_WIDTH, TILE_HEIGHT));

			enemy->Init(pos);
			_Enemys.push_back(enemy);
		}
		break;


		case 2:
		{
			//Rogue
			Rogue* enemy = Object::CreateObject<Rogue>();
			Vector2 pos = Vector2::RandPosition(_owner->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2(TILE_WIDTH * 2, TILE_HEIGHT),
				_owner->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) - Vector2(TILE_WIDTH, TILE_HEIGHT));

			enemy->Init(pos);
			_Enemys.push_back(enemy);
		}
		break;

		}
	}

}
