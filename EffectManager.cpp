#include "stdafx.h"
#include "EffectManager.h"

void EffectPool::InssertPool(int num)
{
	pool.push(ActivePool[num]);
	ActivePool.erase(ActivePool.begin() + num);
}

void EffectPool::InssertActiveObject()
{
	pool.top()->SetIsActive(true);
	ActivePool.push_back(pool.top());
	pool.pop();
}

void EffectPool::Init()
{
	ActivePool.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		Effect* effect = Object::CreateObject<Effect>();
		effect->Init();
		effect->SetIsActive(false);
		pool.push(effect);
	}
}

void EffectPool::Release()
{
	for (int i = 0; i < pool.size(); i++)	pool.pop();

	ActivePool.clear();
}

void EffectManager::Init()
{
	pool->Init();
}

void EffectManager::Update()
{
	for (int i = 0; i < pool->GetActivePoolSize(); i++)
	{
		if (!pool->GetActivePool()[i]->GetIsActive()) pool->InssertPool(i);
	}
}

void EffectManager::Release()
{
	pool->Release();
}

void EffectManager::SetEffect(string key, Vector2 pos, float angle,float FPS)
{
	pool->GetPoolObject()->SetEffect(key, pos, angle,FPS);
	pool->InssertActiveObject();
	
}
