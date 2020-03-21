#pragma once
class BoxWorldManager : public singletonBase<BoxWorldManager>
{
private:
	b2World* _world;
public:
	BoxWorldManager();
	~BoxWorldManager();
	virtual void Release();
	void CreateWorld(b2Vec2 gravity = b2Vec2_zero);
	void RemoveBody(b2Body* body);
	void SetWorld();
	void SetWorld(b2World* world);
	inline b2World* GetWorld() { return _world; }
};

