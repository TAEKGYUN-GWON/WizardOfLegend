#pragma once
#include "SkillObject.h"
class IceBall :	public SkillObject
{
private:

public:
	void Init(Object* onwer);
	virtual void Move();
};
