#include "pch.h"
#include "Effect_HitSpark.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

Effect_HitSpark::Effect_HitSpark(const string & name, float x, float y, int indexY)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mIndexY = indexY;
}

void Effect_HitSpark::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"HitSpark", Resources(L"Effect/HitSpark.png"), 7, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"HitSpark");

	mHitSparkAnimation = new Animation();
	mHitSparkAnimation->InitFrameByStartEnd(0, mIndexY, 6, mIndexY, false);
	mHitSparkAnimation->SetFrameUpdateTime(0.03f);
	mHitSparkAnimation->Play();
}

void Effect_HitSpark::Release()
{
	SafeDelete(mHitSparkAnimation)
}

void Effect_HitSpark::Update()
{
	mHitSparkAnimation->Update();
	if (mHitSparkAnimation->GetNowFrameX() == 6) 
	{
		mIsDestroy = true;
	}
}

void Effect_HitSpark::Render()
{
	//mImage->SetAngle(mAngle * (180 / PI));
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mHitSparkAnimation->GetNowFrameX(), mHitSparkAnimation->GetNowFrameY());
}
