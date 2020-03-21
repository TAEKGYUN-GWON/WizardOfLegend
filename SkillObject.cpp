#include "stdafx.h"
#include "SkillObject.h"
#include "SkillScript.h"
void SkillObject::Init()
{
	Object::Init();
	_tag = "Skill";
	_isCollision = false;
	_maxCoolDown = 0.5f;
	_curCoolDown = 0;
	AddComponent<SkillScript>();
}

void SkillObject::Update()
{
	Object::Update();


	Move();

	if (_isCollision)
	{
		if (_skillType == SkillType::One_time)
		{
			SetIsRelese();
			return;
		}
		else WindUpCollCoolDown();
		if (_physics->GetBodyActive()) _physics->SetBodyActive(false);

		if (_curCoolDown >= _maxCoolDown)
		{
			_curCoolDown = _maxCoolDown;
			_isCollision = false;
			_physics->SetBodyActive(true);
		}
	}
	else
	{
		if (!_physics->GetBodyActive() && _name != "ChaosCircle") _physics->SetBodyActive(true);
	}

}

void SkillObject::WindUpCollCoolDown()
{
	if (_curCoolDown < _maxCoolDown)
	{
		_curCoolDown += TIMEMANAGER->getElapsedTime();
	}
	else
	{
		_curCoolDown = _maxCoolDown;
		_isCollision = false;
	}
}
