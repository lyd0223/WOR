#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_EnemyCreate : public GameObject
{
	Image* mImage;
	Animation* mAnimation;

	float mScale;

public:
	Effect_EnemyCreate(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
}