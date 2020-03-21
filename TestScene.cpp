#include "stdafx.h"
#include "TestScene.h"
#include"StartScene.h"

void TestScene::Init()
{
	Scene::Init();
	//bullet = Object::CreateObject<Object>();
	//bullet->GetTrans()->SetPos(WINSIZEX * 4, WINSIZEY / 2);
	//bullet->GetTrans()->SetScale(50,30);

	//auto p = bullet->AddComponent<PhysicsBody>();
	//p->Init(DYNAMIC, 1, 10.f, 0, true);
	////p->GetBody()->GetFixtureList()->GetShape()->
	//p->GetBody()->SetFixedRotation(true);
	//GRAPHICMANAGER->AddFrameImage("fatkachu", L"resource/img/Object/maple.png", 4, 1);
	//GRAPHICMANAGER->AddImage("fatkachu", L"resource/img/Object/popcorn.png");
	//GRAPHICMANAGER->AddFrameImage("fatkachu", L"fatkachu.png",4,1);
	//GRAPHICMANAGER->FindImage("fatkachu")->SetFrameSize(Vector2(2, 2));
	
	//mgr = new ParticleManager;
	//mgr->Init(500,ParticleType::CIRCLE, Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(10, 10),"None",false,0.f,true);
	//Object* floor = Object::CreateObject<Object>();
	//floor->GetTrans()->SetScale(1280, 30);
	//floor->GetTrans()->SetPos(WINSIZEX / 2, WINSIZEY);
	//auto a = floor->AddComponent<PhysicsBody>();
	//a->Init(BodyType::STATIC, 1, 1);
	//GetWorld()->SetGravity(b2Vec2(0, 10));
	for (int i = 0; i < 9001; i++)
	{
		Object* obj = Object::CreateObject<Object>();
		obj->GetTrans()->SetPos(WINSIZE.x / 2, WINSIZE.y / 2);
		obj->GetTrans()->SetScale(100,100);
		//obj->AddComponent<PhysicsBody>()->Init(BodyType::STATIC, 1, 0, 0, 0, 1);
	}
	//GRAPHICMANAGER->AddFrameImage("r", L"Resource/Wizard/Enemy/Sprite/RogueAttack0_2x1.png", 2, 1);
	//GRAPHICMANAGER->AddFrameImage("s", L"Resource/Wizard/Enemy/Sprite/KnightAttack0_5x1.png", 5, 1);
	//test = Object::CreateObject<Object>();
	//test->GetTrans()->SetPos(WINSIZE / 2);
	//auto s = test->AddComponent<Sprite>();
	//s->Init(true, true);
	//s->SetImgName("r");
	//for (int i = 0; i < 1; i++)
	//{
	//	Object* obj = Object::CreateObject<Object>(test);
	//	//obj->GetTrans()->SetPos(WINSIZE.x / 2, WINSIZE.y / 2);
	//	//obj->GetTrans()->SetScale(100, 100);
	//	obj->GetTrans()->SetPos(WINSIZE / 2);
	//	//obj = Object::CreateObject<Object>();
	//	auto s = obj->AddComponent<Sprite>();
	//	s->Init(true, true);
	//	s->SetImgName("s");
	//}
	SCENEMANAGER->addScene("PG", new StartScene);
}


void TestScene::Update()
{
	Scene::Update();

	
	//cout << "DT : " << TIMEMANAGER->getElapsedTime() << endl;

	CAMERA->Control();
	if (KEYMANAGER->isStayKeyDown('1'))
		ActiveTest();

	if (KEYMANAGER->isStayKeyDown('2'))
		UnActiveTest();

	if (KEYMANAGER->isStayKeyDown('3'))
		RemoveTest();

	if (KEYMANAGER->isOnceKeyDown('4'))
		test->Release();
	if (KEYMANAGER->isOnceKeyDown('C'))
		SCENEMANAGER->changeScene("PG");
	//mgr->Update(); 
	//if (KEYMANAGER->isOnceKeyDown('4')) SCENEMANAGER->changeScene("Shop");
	//if (KEYMANAGER->isOnceKeyDown('S'))
	//{
	//	for (Object* obj : test)
	//		obj->GetComponent<PhysicsBody>()->SetSensor(false);
	//}
	//if (KEYMANAGER->isOnceKeyDown('F'))
	//{
	//	bullet->GetComponent<PhysicsBody>()->ApplyForce(Vector2::b2Left * 90000000);
	//}
	//	//bullet->GetComponent<PhysicsBody>()->GetBody()->SetAngularVelocity(999);

	//if (KEYMANAGER->isOnceKeyDown('D'))
	//{
	//	for (Object* obj : test)
	//		obj->GetComponent<PhysicsBody>()->SetBodyActive(true);
	//}
	//_timer += TIMEMANAGER->getElapsedTime();
	//if (_count < 200)
	//{
	//	//if (_timer > 0.1f)
	//	//{
	//		Object* obj = Object::CreateObject<Object>();

	//		float x = RND->getFromFloatTo(WINSIZEY / 2-100, WINSIZEX/2+200);
	//		float y = RND->getFromFloatTo(WINSIZEY / 2 - 100, WINSIZEY / 2 + 100);

	//		obj->GetTrans()->SetPos(Vector2(x, y));

	//		float w = RND->getFromFloatTo(100, 300);
	//		float h = RND->getFromFloatTo(100, 400);
	//		obj->GetTrans()->SetScale(Vector2(w, h));

	//		auto a = obj->AddComponent<PhysicsBody>();
	//		a->Init(BodyType::DYNAMIC, 0,0.1f);
	//		a->SetSensor(true);
	//		a->GetBody()->SetFixedRotation(true);
	//		_timer = 0;
	//		_count++;
	//		test.push_back(obj);
	//	//}
	//}

}

void TestScene::Render()
{
	Scene::Render();
	//mgr->Render();
	//for (Object* child : _children)
	//{
	//	child->Render();


	//}
	wchar_t buffer[128];

	swprintf(buffer, 128, L"Children : %d", _children.size());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 100), buffer, 20, 300, 50, ColorF::Azure);


	swprintf(buffer, 128, L"Children : %d", (int)SCENEMANAGER->GetNowScene()->GetWorld()->GetBodyCount());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2-500, 100), buffer, 20, 300, 50, ColorF::Azure);
	//_b2World->GetBodyList()

	swprintf(buffer, 128, L"ActiveList : %d", _activeList.size());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 50, ColorF::Azure);

	swprintf(buffer, 128, L"UnActive : %d", _deActiveList.size());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 300), buffer, 20, 300, 50, ColorF::Azure);

	swprintf(buffer, 128, L"RemoveList : %d", _removeList.size());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 400), buffer, 20, 300, 50, ColorF::Azure);


	swprintf(buffer, 128, L"FPS : %f", TIMEMANAGER->GetFps());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 500), buffer, 20, 300, 50, ColorF::Azure);

}


void TestScene::ActiveTest()
{
	for (int i = 0; i < 100; i++)
	{
		_activeList[i]->SetIsActive(false);
	}
}

void TestScene::UnActiveTest()
{
	for (int i = 0; i < 100; i++)
	{
		_deActiveList[i]->SetIsActive(true);
	}
}

void TestScene::RemoveTest()
{
	for (int i = 0; i < 100; i++)
	{
		//_children[i]->SetIsRelese();
	}
	//test->Release();
}
