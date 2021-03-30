#pragma once
#include "GameObject.h"
class Effect_Teleport : public GameObject
{
	
	Image* mImage;
	class Animation* mAnimation;
	bool mIsSceneChange;
	wstring mNowSceneName;
	wstring mChangeSceneName;
public:
	Effect_Teleport(float x, float y, bool isSceneChange, wstring nowSceneName =L"È÷È÷ ¾È¹Ù²Ü²«´ó" ,wstring changeSceneName = L"È÷È÷ ¾ÀÀüÈ¯¾ÈÇÒ²¨Áö·Õ");

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

};

