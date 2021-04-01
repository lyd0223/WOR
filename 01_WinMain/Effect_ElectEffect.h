#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_ElectEffect : public GameObject
{
	Image* mImage;
	Animation* mAnimation;

public:
	Effect_ElectEffect(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

