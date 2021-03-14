#include "pch.h"
#include "MagicCircle.h"
#include "Image.h"
#include "Animation.h"
#include "Meteor.h"

MagicCircle::MagicCircle(const string & name, float x, float y, CastingSkill castingSkill)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mCastingSkill = castingSkill;
}

void MagicCircle::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MagicCircle", Resources(L"Skill/Circle.png"), 24, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MagicCircle");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

	mAngle = Random::GetInstance()->RandomInt(360);

	mCircleMakeAnimation = new Animation();
	mCircleMakeAnimation->InitFrameByStartEnd(0, 0, 24, 0, false);
	mCircleMakeAnimation->SetFrameUpdateTime(0.1f);

	mCircleMakeAnimation->Play();
}

void MagicCircle::Release()
{
	SafeDelete(mCircleMakeAnimation);
}

void MagicCircle::Update()
{
	mCircleMakeAnimation->Update();

	if (mCircleMakeAnimation->GetNowFrameX() == 3 && mCastingSkill == CastingSkill::Meteor) {
		mMeteor = new Meteor("Meteor", mX, mY);
		mCastingSkillList.push_back(mMeteor);
	}

	for(GameObject* )
}

void MagicCircle::Render(HDC hdc)
{
	mImage->FrameRender(mX, mY, mCircleMakeAnimation->GetNowFrameX(), mCircleMakeAnimation->GetNowFrameY());
}
