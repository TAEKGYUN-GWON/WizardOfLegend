#include "stdafx.h"
#include "UiManager.h"

void UiManager::Init(Player* player)
{
	wstring dir = L"Resource/Wizard/UI/";
	GRAPHICMANAGER->AddImage("WindSkill", dir + L"WindSkill.png");
	GRAPHICMANAGER->AddImage("FireBallSkill", dir + L"FireBallSkill.png");
	GRAPHICMANAGER->AddImage("ChaosSkill", dir + L"ChaosSkill.png");
	GRAPHICMANAGER->AddImage("PlayerIcon", dir + L"PlayerIcon.png");

	GRAPHICMANAGER->AddImage("1", dir + L"1.png");
	GRAPHICMANAGER->AddImage("2", dir + L"2.png");
	GRAPHICMANAGER->AddImage("3", dir + L"3.png");
	_hpBar = new ProgressBar();
	_hpBar->Init("HPBarFill2", "HPBarBG2", dir, dir, Vector2(110, 53));



	wchar_t buffer[128];

	swprintf(buffer,128, L"%d/%d", (int)player->GetAbility()->GetCulHp(), (int)player->GetAbility()->GetMaxHp());
	

	text = Object::CreateObject<Object>();
	text->GetTrans()->SetPos(140, 30);
	text->SetCameraAffect(false);
	text->AddComponent<Sprite>();
	text->AddComponent<Text>();
	text->GetComponent<Text>()->CreateText(buffer, 20, 200, 50, ColorF::White, 1.0f, L"Silkscreen");
	//
	//text->GetComponent<Text>()->SetPos(Vector2(WINSIZE/2));

	Object* icon = Object::CreateObject<Object>();
	icon->SetName("WindBoomerang");
	icon->SetCameraAffect(false);
	auto s = icon->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("WindSkill");
	s->SetScale(Vector2(1.5, 1.5));


	icon->GetTrans()->SetScale(s->GetGraphic()->GetGraphicInfo()->size);
	
	_skillIcons.push_back(icon);

	icon = Object::CreateObject<Object>();
	icon->SetName("FireBall");
	icon->SetCameraAffect(false);
	s = icon->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("FireBallSkill");
	s->SetScale(Vector2(1.5, 1.5));
	icon->GetTrans()->SetScale(s->GetGraphic()->GetGraphicInfo()->size);
	_skillIcons.push_back(icon);

	icon = Object::CreateObject<Object>();
	icon->SetName("ChaosCircle");
	icon->SetCameraAffect(false);
	s = icon->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("ChaosSkill");
	s->SetScale(Vector2(1.5, 1.5));
	icon->GetTrans()->SetScale(s->GetGraphic()->GetGraphicInfo()->size);
	_skillIcons.push_back(icon);

	icon = Object::CreateObject<Object>();
	icon->SetName("PlayerIcon");
	icon->SetCameraAffect(false);
	s = icon->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("PlayerIcon");
	s->SetScale(Vector2(0.7, 0.7));
	icon->GetTrans()->SetPos(70, 60);
	s->SetPosition(icon->GetTrans()->GetPos());

	for (int i = 0; i < _skillIcons.size(); i++)
	{
		_skillIcons[i]->GetTrans()->SetPos(Vector2(80 + i * _skillIcons[i]->GetTrans()->GetScale().x*2, WINSIZEY - _skillIcons[i]->GetTrans()->GetScale().y - 20));
		_skillIcons[i]->GetComponent<Sprite>()->SetPosition(_skillIcons[i]->GetTrans()->GetPos());


		Object* childIcon = Object::CreateObject<Object>(_skillIcons[i]);
		char buffer[8];
		sprintf_s(buffer, "%d", i + 1);
		childIcon->SetName(buffer);
		childIcon->SetCameraAffect(false);
		auto s = childIcon->AddComponent<Sprite>();
		s->Init();
		s->SetImgName(buffer);
		s->SetScale(Vector2(1.5, 1.5));
		childIcon->GetTrans()->SetScale(s->GetGraphic()->GetGraphicInfo()->size * 1.5);
		childIcon->GetTrans()->SetPos(_skillIcons[i]->GetTrans()->GetPos() + Vector2::up * childIcon->GetTrans()->GetScale() * 2.3);
		s->SetPosition(childIcon->GetTrans()->GetPos());
	}
	this->player = player;
	_isActive = true;
}

void UiManager::Update()
{
	if (player)
	{
		wchar_t buffer[128];
		swprintf(buffer, 128, L"%d/%d", (int)player->GetAbility()->GetCulHp(), (int)player->GetAbility()->GetMaxHp());
		text->GetComponent<Text>()->ChangeText(buffer);

	}
	if (!_isActive|| _isRelease) return;
	_hpBar->SetGauge(player->GetAbility()->GetCulHp(), player->GetAbility()->GetMaxHp());
	for (Object* icon : _skillIcons)
	{
		if (player->GetCurrentSkill()->name == icon->GetName())	icon->GetComponent<Sprite>()->SetAlpha(1);
		else
		{
			if(icon->GetComponent<Sprite>()->GetAlpha()!=0.6f)	icon->GetComponent<Sprite>()->SetAlpha(0.6f);
		}
	}

}

void UiManager::Render()
{
	if (!_isActive|| _isRelease) return;
	for (Object* icon : _skillIcons)
	{
		for (int i = 0; i < player->GetSkills().size(); i++)
		{
			if (icon->GetName() == player->GetSkills()[i]->name)
			{
				if (player->GetSkills()[i]->curTime < player->GetSkills()[i]->cooldownTime)
				{
					float timer = player->GetSkills()[i]->curTime / player->GetSkills()[i]->cooldownTime;
					GRAPHICMANAGER->DrawFillRect(icon->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP), Vector2(icon->GetTrans()->GetScale().x, icon->GetTrans()->GetScale().y-icon->GetTrans()->GetScale().y * timer), 0, ColorF(ColorF::Black, 0.7), PIVOT::LEFT_TOP, false);
				}
			}
		}
	}
	_hpBar->Render();
}

void UiManager::Release()
{

	for (Object* icon : _skillIcons) icon->SetIsRelese();
	_skillIcons.clear();

	delete this;
}
