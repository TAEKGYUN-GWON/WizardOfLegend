#pragma once
class MousePointer 
{

private:
	MousePointer() {};
	Vector2 _pos;
public:
	static MousePointer* GetInstance()
	{
		static MousePointer* instance = new MousePointer();
		return instance;
	}
	Vector2 GetMouseWorldPositionForDesignResolution();
	Vector2 GetMouseWorldPosition();
	Vector2 GetMouseLocalPositionForDesignResolution();
	Vector2 GetMouseLocalPosition();
};

