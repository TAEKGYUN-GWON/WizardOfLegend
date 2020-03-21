#pragma once
#include "ProgressBar.h"
#include "Player.h"
#include "Ability.h"
class UiManager
{
private:

	ProgressBar* _hpBar;
	vector<Object*> _skillIcons;
	Player* player;
	Object* text;
	bool _isActive;
	bool _isRelease;
public:

	void Init(Player* player);
	void Update();
	void Render();
	void Release();
};

