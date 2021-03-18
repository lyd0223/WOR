#include "pch.h"
#include "Flame.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

Flame::Flame(const string & name, float x, float y, float angle)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Flame::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Flame", Resources(L"Skill/Flame.png"), 32, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"Flame");

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

	mFlameAnimation = new Animation();
	mFlameAnimation->InitFrameByStartEnd(0, 0, 31, 0, false);
	mFlameAnimation->SetFrameUpdateTime(0.05f);
	mFlameAnimation->Play();
}

void Flame::Release()
{
	SafeDelete(mFlameAnimation)
}

void Flame::Update()
{
	mFlameAnimation->Update();
	if (mFlameAnimation->GetNowFrameX() == 31) {
		mIsDestroy = true;
	}

	if (mEndPositionX != 0) {
		mAngle = Math::GetAngle(mX, mY, mEndPositionX, mEndPositionY);
	}

	if (mIsMove) {
		mX += cosf(mAngle) * 1.f;
		mY += -sinf(mAngle) * 1.f;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	
}

void Flame::Render()
{
	
	float ang = 0;

	if (mIsSpin) {
		ang = Random::GetInstance()->RandomInt(180);
	}
	
	mImage->SetScale(0.5f);
	mImage->SetAngle(mAngle * (180 / PI)- ang);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mFlameAnimation->GetNowFrameX(), mFlameAnimation->GetNowFrameY());
}

void Flame::MakeCircleFlame()
{

}
