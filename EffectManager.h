#pragma once
#include "Effect.h"

class EffectPool
{
	priority_queue<Effect*> pool;
	vector<Effect*> ActivePool;
public:
	EffectPool() {};
	~EffectPool() {};
	void InssertPool(int num);
	void InssertActiveObject();

	void Init();
	void Release();
	inline Effect* GetPoolObject() { return pool.top(); }
	inline Effect* GetActivePoolObject(int num) { return ActivePool[num]; }
	inline int GetPoolSize() { return pool.size(); }
	inline int GetActivePoolSize() { return ActivePool.size(); }
	inline priority_queue<Effect*> GetPool() { return pool; }
	inline vector<Effect*> GetActivePool() { return ActivePool; }

};


class EffectManager 
{
private:
	EffectPool* pool;
	EffectManager() { pool = new EffectPool; }
public:
	static EffectManager* GetInstance()
	{
		static EffectManager* instance = new EffectManager();
		return instance;
	}
	void Init();
	void Update();
	void Release();
	void SetEffect(string key, Vector2 pos,float angle, float FPS = 1.3f);
	EffectPool* GetPool() { return pool; }
};

