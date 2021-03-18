#include "pch.h"
#include "FireWing.h"
#include "Camera.h"
#include "Image.h"
#include "Animation.h"

FireWing::FireWing(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void FireWing::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireWing", Resources(L"Enemy/FireBoss/Wing.png"), 8, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"FireWing");

	mFireWingAnimation = new Animation();
	mFireWingAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mFireWingAnimation->SetFrameUpdateTime(0.05f);
	mFireWingAnimation->Play();
}

void FireWing::Release()
{
	SafeDelete(mFireWingAnimation)
}

void FireWing::Update()
{
	mFireWingAnimation->Update();
	mFrameIndexX = mFireWingAnimation->GetNowFrameX();

	if (mFireWingAnimation->GetNowFrameX() == 7) mIsDestroy = true;
}

void FireWing::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mFireWingAnimation->GetNowFrameX(), mFireWingAnimation->GetNowFrameY());
}
