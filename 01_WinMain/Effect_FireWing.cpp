#include "pch.h"
#include "Effect_FireWing.h"
#include "Camera.h"
#include "Image.h"
#include "Animation.h"

Effect_FireWing::Effect_FireWing(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_FireWing::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireWing", Resources(L"Enemy/FireBoss/Wing.png"), 8, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"FireWing");

	mFireWingAnimation = new Animation();
	mFireWingAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mFireWingAnimation->SetFrameUpdateTime(0.05f);
	mFireWingAnimation->Play();
}

void Effect_FireWing::Release()
{
	SafeDelete(mFireWingAnimation)
}

void Effect_FireWing::Update()
{
	mFireWingAnimation->Update();
	mFrameIndexX = mFireWingAnimation->GetNowFrameX();

	if (mFireWingAnimation->GetNowFrameX() == 7) mIsDestroy = true;
}

void Effect_FireWing::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mFireWingAnimation->GetNowFrameX(), mFireWingAnimation->GetNowFrameY());
}
