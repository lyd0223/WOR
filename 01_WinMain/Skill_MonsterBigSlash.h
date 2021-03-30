#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_MonsterBigSlash : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;
	
	float mSpeed;
	Animation* mSlashAnimation;
public:
	Skill_MonsterBigSlash(const string& name) : SkillObject(name) {};
	Skill_MonsterBigSlash(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

