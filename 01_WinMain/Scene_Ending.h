#pragma once
#include "Scene.h"

class Image;
class Scene_Ending : public Scene
{
	Image* mImage;
	
	float mFrameCount;
	float mAlpha;
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

