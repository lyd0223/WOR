#pragma once
#include "GameObject.h"

class Player;
class Enemy : public GameObject
{
protected:
	Image* mImage;
	Player* mPlayer;

	int mHp;
	float mAngle;
	float mSpeed;
	
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void SetPlayerPtr(Player* player) { mPlayer = player; }

	float GetAngle() { return mAngle; }
	void SetAngle(float angle) { mAngle = angle; }
	float GetSpeed() { return mSpeed; }
	void SetSpeed(float speed) { mSpeed = speed; }
};