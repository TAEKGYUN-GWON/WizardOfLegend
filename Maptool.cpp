#include "stdafx.h"
#include "Maptool.h"
#include "Tile.h"
#include "Player.h"
void Maptool::Init()
{
	Scene::Init();
	mapMax_x = 100;
	mapMax_y = 100;
	SetUp();
	_sample = Object::CreateObject<Object>();
	_sample->SetCameraAffect(false);
	auto t = _sample->GetTrans();
	t->SetScale(WINSIZEX,200);
	t->SetPos(WINSIZEX / 2, WINSIZEY - t->GetScale().y / 2);
	auto s = _sample->AddComponent<Sprite>();
	s->SetRectColor(ColorF(ColorF::DarkRed, 0.7));
	s->SetFillRect(true);
	s->SetShowRect(true);
	s->SetDepth(3);
	Player* player = Object::CreateObject<Player>();
	player->Init(Vector2(WINSIZE/2));
	GRAPHICMANAGER->AddImage("bg", L"Resource/Wizard/Boss/bg.png");
}

void Maptool::Update()
{
	Scene::Update();
	CAMERA->Control();
}

void Maptool::Render()
{
	sort(_activeList.begin(), _activeList.end(), CompareToDepth);

	for (Object* child : _vTiles)
	{
		if (child->GetCameraAffect())
		{
			if (child->GetTrans()->GetPos().x + 100 < CAMERA->GetPosition().x || child->GetTrans()->GetPos().x - 100 > CAMERA->GetPosition().x + WINSIZE.x / CAMERA->GetScale().x ||
				child->GetTrans()->GetPos().y + 100 < CAMERA->GetPosition().y || child->GetTrans()->GetPos().y - 100 > CAMERA->GetPosition().y + WINSIZE.y / CAMERA->GetScale().x) child->SetAllowsRender(false);

			else child->SetAllowsRender(true);

		}

		child->Render();
	}
	_sample->Render();
	GRAPHICMANAGER->DrawImage("bg", WINSIZE / 2);
	for (Object* c : _children)
		if (c->GetTag() == "Player") c->Render();

}

void Maptool::Save()
{
}

void Maptool::Load()
{
}

void Maptool::SetUp()
{
	for (int i = 0; i < mapMax_y; i++)
	{
		for (int j = 0; j < mapMax_x; j++)
		{
			Tile* t = Object::CreateObject<Tile>();
			t->Init(j, i);
			t->GetSprite()->SetShowRect(true);
			t->SetAttribute(Attribute::NONE);
			t->GetSprite()->SetDepth(1);
			_vTiles.push_back(t);
		}
	}
}

void Maptool::SetMap()
{
}

void Maptool::ClickSetTile()
{
}

void Maptool::RemoveObject()
{
}
