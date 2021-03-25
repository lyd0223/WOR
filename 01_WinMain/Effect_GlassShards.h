#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_GlassShards : public GameObject
{
	Image* mImage;
	Animation* mAnimation;

	float mAngle;
	float mScale;
	float mSpeed;
public:
	Effect_GlassShards(const string& name, float x, float y, float angle, float scale, float speed);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

