#pragma once
#include "GameObject.h"

class MovingObject;
class PlayerWideShadow : public GameObject
{
	Image* mImage;
	MovingObject* mPlayer;
	float mAngle;
public:
	PlayerWideShadow(const string& name, float x, float y);
	void Init()override;
	void Init(float x, float y);

	void Release()override;
	void Update()override;
	void Render()override;
};

