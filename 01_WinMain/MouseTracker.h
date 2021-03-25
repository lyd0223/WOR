#pragma once
#include "GameObject.h"

class MovingObject;
class MouseTracker : public GameObject
{
	Image* mImage;
	MovingObject* mPlayer;
	float mAngle;
public:
	MouseTracker(const string& name, float x, float y, float angle);
	void Init()override ;
	void Init(float x, float y, float angle);
	
	void Release()override;
	void Update()override;
	void Render()override;
};

