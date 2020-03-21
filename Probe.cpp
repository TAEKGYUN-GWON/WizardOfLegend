#include "stdafx.h"
#include "Probe.h"
#include "ProceduralTest.h"

void Probe::Init(Vector2 pos, list<Vector2> path)
{
	Object::Init();
	_tag = "Probe";
	_trans->SetPos(pos);
	_trans->SetScale(10, 10);
	SetPath(path);
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1, 1, 0, 0, 1);
	_physics->GetBody()->SetFixedRotation(true);
	speed = 400;
	_startMove = false;
}

void Probe::Update()
{
	Object::Update();

#ifdef _DEBUG
	Move();

	if (_startMove)
		SetTileAttribute();
#else

	while (path.size())
	{
		Move();

		if (_startMove)
			SetTileAttribute();
	}
#endif

}

void Probe::Release()
{
	//SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_physics->GetBody());
	Object::Release();
}

void Probe::SetPath(list<Vector2> path)
{
	this->path.clear();
	this->path = path;
	int a;
}

void Probe::Move()
{
	if (path.size())
	{
		_physics->SetBodyPosition();
		if (!_startMove) _startMove = true;
		Vector2 normalize = Vector2(*path.begin() - _trans->GetPos()).Nomalized();
		_trans->SetPos(_trans->GetPos() + normalize * speed * TIMEMANAGER->getElapsedTime());

		//float angle = Vector2::GetAngle(_trans->GetPos(), *path.begin());
		//_trans->SetPos(_trans->GetPos() + Vector2(cosf(angle),-sinf(angle))* speed * TIMEMANAGER->getElapsedTime());

		_physics->SetBodyPosition();
		
		
		int a;

		if ((int)Vector2::Distance(*path.begin(), _trans->GetPos()) < 30)
			path.pop_front();
	}

}

void Probe::SetTileAttribute()
{
	for (int i = 0; i < 9; i++)
	{
		Vector2 tileIdx((_trans->GetPos().x / TILE_WIDTH) + i % 3, (_trans->GetPos().y / TILE_HEIGHT) + i / 3);
		auto t = (*tiles)[(int)tileIdx.x + (MAP_TILE_MAX_X) * (int)tileIdx.y];
		t->SetAttribute(Attribute::NONE);
		t->SetName("Road");
		auto s = t->GetSprite();
		s->SetFillRect(true);
		s->SetRectColor(ColorF::Coral);
	}
}
