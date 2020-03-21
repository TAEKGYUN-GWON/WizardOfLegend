#pragma once
#include "SkillObject.h"
class WindBoomerang : public SkillObject
{
private:
	float _angle;

public:
	void Init(Object* onwer);
	virtual void Move();
};