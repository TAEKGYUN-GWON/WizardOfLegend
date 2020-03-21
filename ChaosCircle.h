#pragma once
#include "SkillObject.h"
class ChaosCircle :	public SkillObject
{
private:

	bool _isStartAtk;
	bool _isEndAtk;
public:
	void Init(Object* onwer);
	virtual void Move();

};

