#include "pch.h"
#include "Effect_DashEffect.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_DashEffect::Effect_DashEffect(const string & name, float x, float y, float angle)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Effect_DashEffect::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"DashEffect", Resources(L"Effect/DashEffect.png"), 5, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"DashEffect");

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mAnimation->SetFrameUpdateTime(0.03f);
	mAnimation->Play();
}

void Effect_DashEffect::Release()
{
	SafeDelete(mAnimation)
}

void Effect_DashEffect::Update()
{
	mAnimation->Update();
	
	if (mAnimation->GetNowFrameX() == 4)
	{
		mIsDestroy = true;
	}
}

void Effect_DashEffect::Render()
{
	mImage->SetScale(2.f);
	mImage->SetAlpha(0.5f);
	mImage->SetAngle(mAngle * (180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
