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
	Effect_Teleport(float x, float y, bool isSceneChange, wstring nowSceneName =L"���� �ȹٲܲ���" ,wstring changeSceneName = L"���� ����ȯ���Ҳ�����");

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

};

