#pragma once
#include "Object.h"
class Effect :	public Object
{
private:
	Sprite* sprite;

public:
	virtual void Init();
	virtual void Update();
	Sprite* GetSprite() { return sprite; }
	int GetCurFrame();
	int GetMaxFrame();
	void SetEffect(string key, Vector2 pos, float angle, float FPS);
};

