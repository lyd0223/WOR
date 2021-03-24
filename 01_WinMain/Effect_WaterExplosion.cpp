#include "pch.h"
#include "Effect_WaterExplosion.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_WaterExplosion::Effect_WaterExplosion(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_WaterExplosion::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"WaterExplosion", Resources(L"Effect_WaterExplosion.png"), 7, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"WaterExplosion");

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mAnimation->SetFrameUpdateTime(0.03f);
	mAnimation->Play();
}

void Effect_WaterExplosion::Release()
{
	SafeDelete(mAnimation)
}

void Effect_WaterExplosion::Update()
{
	mAnimation->Update();
	
	if (mAnimation->GetNowFrameX() == 6)
	{
		mIsDestroy = true;
	}
}

void Effect_WaterExplosion::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
