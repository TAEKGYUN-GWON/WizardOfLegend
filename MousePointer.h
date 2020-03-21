#pragma once
#include "singletonBase.h"
class MousePointer :public singletonBase<MousePointer>
{
private:
	Vector2 _pos;
public:

	Vector2 GetMouseWorldPositionForDesignResolution();
	Vector2 GetMouseWorldPosition();
	Vector2 GetMouseLocalPositionForDesignResolution();
	Vector2 GetMouseLocalPosition();
};

