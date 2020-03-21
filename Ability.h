#pragma once
class Ability
{
private:
	float maxHp;
	float culHp;
	float atk;
	bool isDead;

public:
	Ability() {};
	void Init(float maxHp, float atk);
	void Update();
	
	float GetMaxHp() { return maxHp; }
	float GetCulHp() { return culHp; }
	float GetAtk() { return atk; }
	void SetAtk(float atk) { this->atk = atk; }
	void SetDamage(float atk);
	void SetHealing(float healPoint);
	bool GetIsDead() { return isDead; }

};

