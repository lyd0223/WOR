#include "pch.h"
#include "HitSpark.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

HitSpark::HitSpark(const string & name, float x, float y, int indexY)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mIndexY = indexY;
}

void HitSpark::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"HitSpark", Resources(L"Effect/HitSpark.png"), 7, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"HitSpark");

	mHitSparkAnimation = new Animation();
	mHitSparkAnimation->InitFrameByStartEnd(0, mIndexY, 6, mIndexY, false);
	mHitSparkAnimation->SetFrameUpdateTime(0.5f);
	mHitSparkAnimation->Play();
}

void HitSpark::Release()
{
	SafeDelete(mHitSparkAnimation)
}

void HitSpark::Update()
{
	mHitSparkAnimation->Update();
	if (mHitSparkAnimation->GetNowFrameX() == 6) {
		mIsDestroy = true;
	}
}

void HitSpark::Render()
{
	//mImage->SetAngle(mAngle * (180 / PI));
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mHitSparkAnimation->GetNowFrameX(), mHitSparkAnimation->GetNowFrameY());
}
