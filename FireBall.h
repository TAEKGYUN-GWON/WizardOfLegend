#pragma once
#include "SkillObject.h"
class FireBall : public SkillObject
{
private:

public:
	void Init(Object* onwer);
	virtual void Move();
};

