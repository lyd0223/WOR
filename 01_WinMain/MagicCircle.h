#pragma once
#include "GameObject.h"

enum class CastingSkill : int {
	Meteor,
	Burn,

	End
};

class Image;
class Meteor;
class Skill_Flame;
class HitSpark;
class Animation;
class MagicCircle : public GameObject
{
	Image* mImage;
	Animation* mCircleMakeAnimation;
	Meteor* mMeteor;
	vector<Skill_Flame*> mFlameList;
	HitSpark* mHitSpark;
	CastingSkill mCastingSkill;

	int mFrameIndexX;
	float mTimeCount1;
	float mTimeCount2;
	float mAngle;
public:
	MagicCircle(const string& name, float x, float y, CastingSkill mCastingSkill);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	int GetFrameIndexX() { return mFrameIndexX; }

	void MakeFlameList();
};

