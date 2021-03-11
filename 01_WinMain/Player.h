#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	class Image* mImage;
	float mSpeed;
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetSpeed() { return mSpeed; };
	void SetSpeed(int speed) { mSpeed = speed; };
};

