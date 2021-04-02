#pragma once
class Scene
{
protected:
	bool mIsAlreadyInit = 0;
	float mTime;
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	inline bool GetIsAlreadyInit()const { return mIsAlreadyInit; };
	float GetTime()const { return mTime; }
};

