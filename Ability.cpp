#include "stdafx.h"
#include "Ability.h"



void Ability::Init(float maxHp, float atk)
{
	this->maxHp = culHp = maxHp;

	this->atk = atk;

	isDead = false;
}

void Ability::Update()
{
	if (culHp <= 0)
	{
		culHp = 0;
		isDead = true;
	}
	else return;
}

void Ability::SetDamage(float atk)
{
	culHp -= atk;
	if (culHp <= 0)
	{
		culHp = 0;
		isDead = true;
	}
}

void Ability::SetHealing(float healPoint)
{
	culHp += healPoint;
	if (culHp > maxHp) culHp = maxHp;
}
