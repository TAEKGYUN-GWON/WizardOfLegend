#include "stdafx.h"
#include "StartScene.h"
#include "ProceduralTest.h"
#include "Maptool.h"
#include "TestScene.h"
#include "Knight.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Player.h"
#include "ChaosCircle.h"
void StartScene::Init()
{
	Scene::Init();

	//GRAPHICMANAGER->AddFrameImage("will", L"blueNumber.png", 4, 1);
	//GRAPHICMANAGER->AddImage("will", L"blueNumber.png");
	//GRAPHICMANAGER->AddFrameImage("eagle", L"BossUp.png",32,1);
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");
	wstring dir = L"Resource/Wizard/UI/";
	GRAPHICMANAGER->AddFrameImage("TitleScreen", dir+L"TitleScreen.png",1,1);
	GRAPHICMANAGER->AddFrameImage("Loading", dir+L"Loading.png",1,1);

	GRAPHICMANAGER->AddFrameImage("TitleLogo", dir+L"TitleLogo.png",1,1);
	_logo = Object::CreateObject<Object>();
	_logo->GetTrans()->SetPos(WINSIZE / 2 + Vector2::up * 150);
	_logo->SetCameraAffect(false);
	auto s = _logo->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("TitleLogo");
	s->SetAlpha(alpha);

	_button = Object::CreateObject<Object>();
	_button->GetTrans()->SetPos(WINSIZE / 2 + Vector2::down * 50);
	_button->SetCameraAffect(false);
	s = _button->AddComponent<Sprite>();
	auto text = _button->AddComponent<Text>();
	text->CreateText(L"Game Start", 30, 400, 50, ColorF(ColorF::White, 0),1, L"Silkscreen");
	text->SetPos(_button->GetTrans()->GetPos()+Vector2::left * 100 + Vector2::down * 35);
	_button->GetTrans()->SetScale(210, 25);
	_button->GetTrans()->Move(Vector2::down * 55 + Vector2::right * 5);
	_button->SetIsActive(false);

	dir = L"Resource/Wizard/Tile/";
	for (int i = 1; i <= 4; i++)
	{
		string str = "Tile";
		wstring item = to_wstring(i) + L".png";
		GRAPHICMANAGER->AddImage(str + to_string(i), dir + item);
	}

	//CAMERA->SetScale(Vector2(1, 1));
	//CAMERA->SetPos(Vector2(430, 204));
	SCENEMANAGER->addScene("t", new TestScene);
	SCENEMANAGER->addScene("MapTool", new Maptool);
	//SCENEMANAGER->addScene("tt", new Maptool);
	SCENEMANAGER->addScene("t1", new ProceduralTest);

	Object* wall = Object::CreateObject<Object>();
	wall->SetName("Wall");
	wall->Init();
	wall->GetTrans()->SetPos(WINSIZE/2 +Vector2(100,100));
	wall->GetTrans()->SetScale(50, 50);
	auto p = wall->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1);

	//Sorcerer* so = Object::CreateObject<Sorcerer>();
	//so->Init(WINSIZE / 3);
	//
	//Player* test = Object::CreateObject<Player>();
	//test->Init(WINSIZE / 2);

	//_obj = Object::CreateObject<Object>();
	//_obj->GetTrans()->SetPos(WINSIZEX / 2-100, WINSIZEY / 2);
	//_obj->GetTrans()->SetScale(100, 100);
	//_obj->SetName("1");
	//auto s = _obj->AddComponent<Sprite>();
	//s->Init();
	//s->SetImgName("eagle");
	//
	//
	//Object* obj = Object::CreateObject<Object>();
	//obj->Init();
	//obj->SetName("2");
	//obj->GetTrans()->SetPos(WINSIZE / 2);
	//s = obj->AddComponent<Sprite>();
	//s->Init();
	//s->SetImgName("eagle");
	string sDir = "Resource/Wizard/UI/";
	current = max = 100;
	//_uiMgr = new UiManager();
	//_uiMgr->Init(test);
	sDir = "Resource/Wizard/SoundEffect/";
	string wav = ".wav";
	SOUNDMANAGER->addSound("AirJet", sDir + "AirJet" + wav, false, false);
	SOUNDMANAGER->addSound("EnemyDead", sDir + "EnemyDead" + wav, false, false);
	SOUNDMANAGER->addSound("IceBossLaughAlt", sDir + "IceBossLaughAlt" + wav, false, false);

	SOUNDMANAGER->addSound("PlayerDead", sDir + "PlayerDead" + wav, false, false);
	SOUNDMANAGER->addSound("PlayerFootstep", sDir + "PlayerFootstep" + wav, false, true);
	SOUNDMANAGER->addSound("EnemyHurt", sDir + "EnemyHurt0" + wav, false, false);

	SOUNDMANAGER->addSound("FireballExplode", sDir + "FireballExplode" + wav, false, false);
	SOUNDMANAGER->addSound("FireBlast", sDir + "FireBlast" + wav, false, false);
	SOUNDMANAGER->addSound("IceBossHurt", sDir + "IceBossHurt1" + wav, false, false);

	SOUNDMANAGER->addSound("SorcererAttack", sDir + "EnemyCast" + wav, false, false);
	SOUNDMANAGER->addSound("KnightAttack", sDir + "KnightAttack" + wav, false, false);
	SOUNDMANAGER->addSound("RogueAttack", sDir + "RogueAttack" + wav, false, false);


	SOUNDMANAGER->addSound("Spin", sDir + "Spin" + wav, false, true);
	SOUNDMANAGER->addSound("WhipSwing", sDir + "WhipSwing" + wav, false, true);

	sDir = "Resource/Wizard/BGM/";

	SOUNDMANAGER->addSound("TitleScreen", sDir + "TitleScreen" + wav, true, true);
	SOUNDMANAGER->addSound("Ice", sDir + "Ice" + wav, true, true);
	SOUNDMANAGER->addSound("Ending", sDir + "Ending" + wav, true, true);
	SOUNDMANAGER->addSound("Boss", sDir + "Boss" + wav, true, true);
	SOUNDMANAGER->play("TitleScreen",0.5f);
	SOUNDMANAGER->isPlaySound("TitleScreen");
}

void StartScene::Update()
{
	//_uiMgr->Update();
	if (alpha < 1) alpha += 0.5 * TIMEMANAGER->getElapsedTime();
	
	if (alpha >= 1 && !start)
	{
		alpha = 1;
		start = true;
		_button->SetIsActive(true);
	}

	_logo->GetComponent<Sprite>()->SetAlpha(alpha);

	Scene::Update();
	ButtonCollision();
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		SCENEMANAGER->changeScene("MapTool");
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if(_IsButtonCollison)	SCENEMANAGER->changeScene("t1");
		return;
	}

	if (KEYMANAGER->isOnceKeyDown('K')) CAMERA->ShakingSetting(1, 5);

	CAMERA->Control();

}

void StartScene::Render()
{
	GRAPHICMANAGER->DrawImage("eagle", Vector2(100,100), 1, PIVOT::CENTER, false);
	GRAPHICMANAGER->DrawImage("TitleScreen", WINSIZE / 2, 0.8, PIVOT::CENTER, false);

	sort(_activeList.begin(), _activeList.end(), CompareToDepth);

	for (Object* child : _activeList)
	{
		if (child->GetCameraAffect())
		{
			if (child->GetTrans()->GetPos().x + 100 < CAMERA->GetPosition().x || child->GetTrans()->GetPos().x - 100 > CAMERA->GetPosition().x + WINSIZE.x / CAMERA->GetScale().x ||
				child->GetTrans()->GetPos().y + 100 < CAMERA->GetPosition().y || child->GetTrans()->GetPos().y - 100 > CAMERA->GetPosition().y + WINSIZE.y / CAMERA->GetScale().x) child->SetAllowsRender(false);

			else child->SetAllowsRender(true);

		}

		child->Render();
	}
	//_uiMgr->Render();
	//GRAPHICMANAGER->Text(Vector2(100, 100), L"1) Dungeon Scene", 20, 300, 50, ColorF::AliceBlue);
	//GRAPHICMANAGER->Text(Vector2(100, 150), L"2) Town Scene", 20, 300, 50, ColorF::AntiqueWhite);
	//GRAPHICMANAGER->Text(Vector2(100, 200), L"3) Entrance Scene", 20, 300, 50, ColorF::Aqua);
	//GRAPHICMANAGER->Text(Vector2(100, 250), L"4) Shop Scene", 20, 300, 50, ColorF::Aquamarine);
	//GRAPHICMANAGER->Text(Vector2(100, 300), L"5) Maptool Scene", 20, 300, 50, ColorF::Azure);
	//
	//
	//wchar_t buffer[128];
	//swprintf(buffer, 128, L"Camera X : %f\nCamera Y : %f", CAMERA->GetPosition().x, CAMERA->GetPosition().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 100), buffer, 20, 300, 50, ColorF::Azure);
	//
	//
	//swprintf(buffer, 128, L"Maoue X : %f\Mouse Y : %f", MOUSEPOINTER->GetMouseWorldPosition().x, MOUSEPOINTER->GetMouseWorldPosition().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 50, ColorF::Azure);
	//
	//Vector2 pos = CAMERA->GetPosition() + _ptMouse;
	//
	//swprintf(buffer, 128, L"WorldMaoue X : %f\WorldMaoue Y : %f", pos.x, pos.y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 300), buffer, 20, 300, 50, ColorF::Azure);


	//swprintf(buffer, 128, L"%d %d", GRAPHICMANAGER->FindImage("will")->GetFrameWidth(), GRAPHICMANAGER->FindImage("will")->GetFrameHeight());
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 30, ColorF::AntiqueWhite);


	//GRAPHICMANAGER->DrawFrameImage("will", Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0, Vector2(0.7f, 0.5f));
	//GRAPHICMANAGER->DrawImage("eagle", Vector2(400, 500), Vector2(1, 1), 0.0f);
}

void StartScene::Release()
{
	
	SOUNDMANAGER->stop("TitleScreen");
	Scene::Release();
}

void StartScene::ButtonCollision()
{
	if (!start)return;
	if (mouse->GetTrans()->GetPos() > _button->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) &&
		mouse->GetTrans()->GetPos() < _button->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM))
	{

		_IsButtonCollison = true;
		_button->GetComponent<Text>()->SetColor(ColorF(ColorF::White, 1.0f), 0, strlen("Game Start"));
	}
	else
	{
		_IsButtonCollison = false;
		_button->GetComponent<Text>()->SetColor(ColorF(ColorF::White, 0.7f), 0, strlen("Game Start"));
	}
}
