#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_WaterFormParticle : public GameObject
{
	Image* mImage;
	Animation* mAnimation;


public:
	Effect_WaterFormParticle(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

};

