#pragma once
#include "Scene.h"
#include <functional>
class Scene_Loading : public Scene
{
	vector<function<void(void)>> mLoadList;
	int mLoadIndex;
	float mCharacterX;
	float mTextY;
	string mStr;
	string mStr2;
public:
	void AddLoadFunc(const function<void(void)>& func);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
};

