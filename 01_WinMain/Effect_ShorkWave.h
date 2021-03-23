#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_ShorkWave : public GameObject
{
	Image* mImage;
	Animation* mAnimation;
	
	float mScale;
public:
	Effect_ShorkWave(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetScale(float scale) { mScale = scale; }
};

