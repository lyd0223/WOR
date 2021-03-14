#include "pch.h"
#include "HitSpark.h"
#include "Image.h"
#include "Animation.h"

HitSpark::HitSpark(const string & name, float x, float y, int indexY)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mIndexY = indexY;
}

void HitSpark::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"HitSpark", Resources(L"Effect/HitSpark.png"), 7, 1);
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
	mImage->SetScale(2.f);
	mImage->FrameRender(mX, mY, mHitSparkAnimation->GetNowFrameX(), mHitSparkAnimation->GetNowFrameY());
}
