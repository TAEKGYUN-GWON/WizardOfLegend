#include "stdafx.h"
#include "Room.h"
#include "RoomScript.h"
#include "EnemyManager.h"
void Room::Init()
{
	Object::Init();
	_tag = "Room";
	_trans->SetPos(RND->getFromIntTo(MAP_MAX_WIDTH / 2 - 700, MAP_MAX_WIDTH/2 + 700) , RND->getFromIntTo(MAP_MAX_HEIGHT / 2-100, MAP_MAX_HEIGHT / 2 + 100));
	
	_trans->SetScale(RND->getFromFloatTo(200.f, 500.f), RND->getFromFloatTo(200.f, 500));

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.f, 1.f, 0.f, false, true);
	_physics->GetBody()->SetFixedRotation(true);
	AddComponent<RoomScript>();
	_eMgr = new EnemyManager;
	//	_physics->SetBodyActive(false);
}

void Room::Update()
{
	if(_eMgr->GetIsActive()) _eMgr->Update();
	if(!_eMgr->GetEnemySize())_isActiveEnemy = false;
	return;
}

void Room::SetObject()
{

	//"Carpet"
	//"Grate"
	//"SmallProps"
	//"PillarIce"
	//"ArchwayBodyIce"
	//"IceBanner"
	//"ChaosBanner"


	int kind = RND->getInt(13);

	switch (kind)
	{
	case 0:
	{
		_roomObjects.insert(make_pair("Carpet", RoomObjectInfo(Vector2(_trans->GetPos()))));
	}
	break;
	case 1:
	{
		_roomObjects.insert(make_pair("Grate", RoomObjectInfo(Vector2(_trans->GetPos()))));
	}
	break;
	case 2:
	{
		_roomObjects.insert(make_pair("SmallProps", RoomObjectInfo(Vector2::RandPosition(_trans->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2::down * (TILE_HEIGHT * 2),
			_trans->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) + Vector2::up * (TILE_HEIGHT)))));
	}
	break;
	case 3:
	{
		Vector2 ObjectPos = _trans->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2::down * (TILE_HEIGHT * 3) + Vector2::right * (TILE_WIDTH * 3);
		_roomObjects.insert(make_pair("PillarIce", RoomObjectInfo(ObjectPos)));

		ObjectPos = _trans->GetPosToPivot(TF_PIVOT::RIGHT_TOP) + Vector2::down * (TILE_HEIGHT * 3) + Vector2::left * (TILE_WIDTH * 3);
		_roomObjects.insert(make_pair("PillarIce", RoomObjectInfo(ObjectPos)));

		ObjectPos = _trans->GetPosToPivot(TF_PIVOT::LEFT_BOTTOM) + Vector2::up * (TILE_HEIGHT * 3) + Vector2::right * (TILE_WIDTH * 3);
		_roomObjects.insert(make_pair("PillarIce", RoomObjectInfo(ObjectPos)));

		ObjectPos = _trans->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) + Vector2::up * (TILE_HEIGHT * 3) + Vector2::left * (TILE_WIDTH * 3);
		_roomObjects.insert(make_pair("PillarIce", RoomObjectInfo(ObjectPos)));
	}
	break;
	}


}

void Room::SetRoomEnemy()
{
	if (_eMgr->GetIsActive()) return;
	_eMgr->SetIsActive(true);
	_eMgr->Init(this);
	_isActiveEnemy = true;
}

void Room::DeActivePhysics()
{
	_physics->SetBodyActive(false);
}
