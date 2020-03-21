#pragma once
#include "Scene.h"
#include "ProgressBar.h"
#include "UiManager.h"
class StartScene : public Scene
{
private:
	Object* _obj;
	Object* _logo;
	Object* _button;
	float alpha = 0;
	bool _IsButtonCollison;
	bool start;
	ProgressBar* _bar;
	UiManager* _uiMgr;
	float current, max;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void ButtonCollision();

};

