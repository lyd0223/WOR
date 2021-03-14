#include "pch.h"
#include "Meteor.h"
#include "Image.h"
#include "Animation.h"

Meteor::Meteor(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x - 200;
	mY = 0;
	mEndX = x;
	mEndY = y;
	mSpeed = 10.f;
	mAngle = Math::GetAngle(mX, mY, mEndX, mEndY);
}

void Meteor::Init()
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

void Meteor::Release()
{
	SafeDelete(mMeteorAnimation)
}

void Meteor::Update()
{
	mMeteorAnimation->Update();

	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

}

void Meteor::Render()
{
	mImage->FrameRender(mX, mY, mMeteorAnimation->GetNowFrameX(), mMeteorAnimation->GetNowFrameY());
}
