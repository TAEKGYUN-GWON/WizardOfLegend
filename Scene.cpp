#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}


void Scene::Init()
{
	EFFECTMANAGER->Init();
	//if (_allowRelease)_allowRelease = false;
	_b2World = new b2World(b2Vec2(0,0));
	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 3;
	PHYSICSMANAGER->SetWorld(_b2World);
	_b2World->SetContactListener(PHYSICSMANAGER);
	_b2World->SetAllowSleeping(true);
	_b2World->SetContinuousPhysics(true);
	wstring dir = L"Resource/Wizard/UI/";
	GRAPHICMANAGER->AddImage("mouse",dir+L"MouseCursor0.png");
	mouse = Object::CreateObject<Object>();
	mouse->Init();
	auto s = mouse->AddComponent<Sprite>();
	s->Init();
	s->SetScale(Vector2(2,2));
	s->SetImgName("mouse");
	s->SetDepth(2);
}


void Scene::Release()
{
	EFFECTMANAGER->Release();
	//if (SCENEMANAGER->GetNowScene() == this)
	//{
	//	_allowRelease = true;
	//	return;
	//}
	//Object::Release();
	
	//shared_ptr<int> a;

	for (b2Body* body = _b2World->GetBodyList(); body!=nullptr;)
	{
		if (body == nullptr)break;
		b2Body* deletedObject = body;
		body = body->GetNext();
		_b2World->DestroyBody(deletedObject);
	}

	if (!_children.size()) return;

	auto _children = this->_children;

	for (Object* c :_children)
	{
		c->Release();
	}
	_children.clear();
	_activeList.clear();
	_deActiveList.clear();

	for (Object* c : _removeList)
	{
		c->Release();
	}

	_removeList.clear();

	delete _b2World;
	Object::Release();
}

void Scene::Update()
{
	Object::Update();
	/*for (Object* c : _removeList)
	{
		if (c->GetComponent<PhysicsBody>())
		{
			c->GetComponent<PhysicsBody>()->GetBody()->GetWorld()->DestroyBody(GetComponent<PhysicsBody>()->GetBody());
		}
		c->Release();
	}
	_removeList.clear();

	for (Object* child : _ActiveList)
	{
		if (child->GetAllowInit()) child->Init();
		child->Update();
	}*/
	//mouse->SetCameraAffect(false);
	mouse->GetTrans()->SetPos(MOUSEPOINTER->GetMouseWorldPosition());
	mouse->GetComponent<Sprite>()->SetPosition(mouse->GetTrans()->GetPos());

	ShowCursor(false);
	EFFECTMANAGER->Update();
}

void Scene::PhysicsUpdate()
{

	_b2World->Step(timeStep, velocityIterations, positionIterations);
	for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext())
	{

		if (!body->GetUserData())
		{
			b2Body* deletedObject = body;
			body = body->GetNext();
			_b2World->DestroyBody(deletedObject);
			continue;
		}
		if (((Object*)body->GetUserData())->GetTrans() != nullptr)
		{
			Transform* now = ((Object*)body->GetUserData())->GetTrans();
			PhysicsBody* nowP = ((Object*)body->GetUserData())->GetComponent<PhysicsBody>();
			now->SetPos(nowP->GetBodyPosition());
		}
	}
}



bool Scene::CompareToBottomPos(Object* a, Object* b)
{
	Sprite* aS = a->GetComponent<Sprite>();
	Sprite* bS = b->GetComponent<Sprite>();

	if (!aS)
		return false;
	else if (!bS)
		return true;

	return aS->GetDepth() < bS->GetDepth();
}

bool Scene::CompareToDepth(Object* a, Object* b)
{
	Transform* aT = a->GetComponent<Transform>();
	Transform* bT = b->GetComponent<Transform>();

	if (!aT) return false;
	else if (!bT) return true;

	return aT->GetPosToPivot(TF_PIVOT::BOTTOM).y < bT->GetPosToPivot(TF_PIVOT::BOTTOM).y;
}


void Scene::Render()
{
	//if (_allowRelease) return;
	//sort(_children.begin(), _children.end(), CompareToBottomPos);

	sort(_activeList.begin(), _activeList.end(), CompareToBottomPos);

	for (Object* child : _activeList)
	{
		if (child->GetCameraAffect())
		{
			if (child->GetTrans()->GetPos().x+100 < CAMERA->GetPosition().x || child->GetTrans()->GetPos().x-100 > CAMERA->GetPosition().x + WINSIZE.x / CAMERA->GetScale().x ||
				child->GetTrans()->GetPos().y+100 < CAMERA->GetPosition().y || child->GetTrans()->GetPos().y-100 > CAMERA->GetPosition().y + WINSIZE.y / CAMERA->GetScale().x) child->SetAllowsRender(false);

			else child->SetAllowsRender(true);

		}

		child->Render();
	}
}

