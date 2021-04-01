#pragma once
#include "SkillObject.h"

enum class CastingSkill : int {
	Meteor,
	Burn,

	End
};

class Image;
class Skill_Meteor;
class Skill_Flame;
class Effect_HitSpark;
class Animation;
class Effect_MagicCircle : public SkillObject
{
	Image* mImage;
	Animation* mCircleMakeAnimation;
	Skill_Meteor* mMeteor;
	Effect_HitSpark* mHitSpark;
	vector<Skill_Flame*> mFlameList;
	CastingSkill mCastingSkill;

	int mFrameIndexX;
	float mTimeCount1;
	float mTimeCount2;
	float mAngle;

	bool mIsOneCheck;
public:
	Effect_MagicCircle(const string& name, float x, float y, CastingSkill mCastingSkill);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	int GetFrameIndexX() { return mFrameIndexX; }

	void MakeFlameList();
};

