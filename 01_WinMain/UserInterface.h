#pragma once

#include "GameObject.h"
struct UIObject
{
	UIObject(float x, float y, float sizex, float sizey, Image* image) : X(x), Y(y), SizeX(sizex), SizeY(sizey), Image(image) {}
	float X;
	float Y;
	float SizeX;
	float SizeY;
	Image* Image;
};
class UserInterface : public GameObject
{
	UIObject* mHPBar;
	UIObject* mMPBar;
	UIObject* mStatus;
	UIObject* mSkillBox1;
	UIObject* mSkillBox2;
	UIObject* mSkillBox3;
	UIObject* mSpecialSkillBox;
	UIObject* mPlayerInfo;
	UIObject* mMouseLButton;
	UIObject* mMouseRButton;
	UIObject* mSpaceButton;
	UIObject* mQButton;
	UIObject* mEButton;
	
	Image* mHPBarImage;
	Image* mMPBarImage;
	

public :
	void Init()override;
	void Update()override;
	void Release()override;
	void Render()override;
};

