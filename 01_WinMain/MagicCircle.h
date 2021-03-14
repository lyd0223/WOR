#pragma once
#include "GameObject.h"

enum class CastingSkill : int {
	Meteor,
	Burn,

	End
};

class Image;
class Meteor;
class Animation;
class MagicCircle : public GameObject
{
	Image* mImage;
	Animation* mCircleMakeAnimation;
	Meteor* mMeteor;
	CastingSkill mCastingSkill;
	vector<GameObject*> mCastingSkillList;

	float mAngle;
public:
	MagicCircle(const string& name, float x, float y, CastingSkill mCastingSkill);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

