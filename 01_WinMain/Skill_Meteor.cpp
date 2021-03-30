#include "pch.h"
#include "Skill_Meteor.h"
#include "Image.h"
#include "Animation.h"

Skill_Meteor::Skill_Meteor(const string & name, float x, float y)
	:SkillObject(name)
{
	mX = x - 200;
	mY = y - 720;
	mEndX = x;
	mEndY = y;
	mSpeed = 10.f;
	mAngle = Math::GetAngle(mX, mY, mEndX, mEndY);
	mSkillElement = SkillElement::Fire;
	mSkillArcana = SkillArcana::Signature;

}

void Skill_Meteor::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Meteor", Resources(L"Skill/Meteor.png"), 6, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"Meteor");

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	
	mMeteorAnimation = new Animation();
	mMeteorAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mMeteorAnimation->SetIsLoop(true);
	mMeteorAnimation->SetFrameUpdateTime(0.1f);
	mMeteorAnimation->Play();
}

void Skill_Meteor::Release()
{
	SafeDelete(mMeteorAnimation)
}

void Skill_Meteor::Update()
{
	mMeteorAnimation->Update();

	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

}

void Skill_Meteor::Render()
{
	mImage->FrameRender(mX, mY, mMeteorAnimation->GetNowFrameX(), mMeteorAnimation->GetNowFrameY());
}
