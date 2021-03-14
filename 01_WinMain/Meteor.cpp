#include "pch.h"
#include "Meteor.h"
#include "Image.h"
#include "Animation.h"

Meteor::Meteor(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x - 150;
	mY = 0;
	mEndX = x;
	mEndY = y;
	mSpeed = 20.f;
	mAngle = Math::GetDistance(mX, mY, mEndX, mEndY);
}

void Meteor::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Meteor", Resources(L"Skill/Meteor.png"), 6, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"Meteor");
	
	mMeteorAnimation = new Animation();
	mMeteorAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mMeteorAnimation->SetIsLoop(true);
	mMeteorAnimation->SetFrameUpdateTime(0.1f);
	mMeteorAnimation->Play();
}

void Meteor::Release()
{
	SafeDelete(mMeteorAnimation);
}

void Meteor::Update()
{
	mMeteorAnimation->Update();

	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;

}

void Meteor::Render()
{
	mImage->FrameRender(mX, mY, mMeteorAnimation->GetNowFrameX(), mMeteorAnimation->GetNowFrameY());
}
