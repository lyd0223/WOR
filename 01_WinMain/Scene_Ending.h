#pragma once
#include "Scene.h"

class Image;
class Scene_Ending : public Scene
{
	Image* mImage;
	
	vector<D2D1_RECT_F> mRectList;
	wstring mTime;
	wstring mMonsterCount;

	float mFrameCount;
	float mAlpha;
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

