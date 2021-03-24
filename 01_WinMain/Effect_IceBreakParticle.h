#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_IceBreakParticle : public GameObject
{
	Image* mImage;
	Animation* mAnimation;

	float mAngle;
	float mSpeed;

	
	bool mIsMove;

public:
	Effect_IceBreakParticle(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;


	void SetSpeed(float speed) { mSpeed = speed; }
	void SetIsMove(bool isMove) { mIsMove = isMove; }
};
