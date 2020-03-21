#include "stdafx.h"
#include "Effect.h"

void Effect::Init()
{
	Object::Init();
	_tag = "Effect";
	sprite = AddComponent<Sprite>();
	sprite->Init(true, true);
}

void Effect::Update()
{
	Object::Update();
	if (sprite->GetCurrentFrameX() == sprite->GetMaxFrameX()) SetIsActive(false);
	sprite->SetPosition(_trans->GetPos());
}

int Effect::GetCurFrame()
{
	return sprite->GetCurrentFrameX();
}
int Effect::GetMaxFrame()
{
	return sprite->GetMaxFrameX();
}

void Effect::SetEffect(string key, Vector2 pos, float angle, float FPS)
{
	_trans->SetPos(pos);
	_trans->SetRotateToRadian(angle);
	sprite->SetImgName(key);
	sprite->SetFPS(FPS);

}
