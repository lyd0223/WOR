#include "pch.h"
#include "Effect_ShorkWave.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_ShorkWave::Effect_ShorkWave(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_ShorkWave::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MeteorShockWave", Resources(L"Effect/ShorkWave.png"), 5, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MeteorShockWave");

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mAnimation->SetFrameUpdateTime(0.03f);
	mAnimation->Play();
}

void Effect_ShorkWave::Release()
{
	SafeDelete(mAnimation)
}

void Effect_ShorkWave::Update()
{
	mAnimation->Update();

	if (mAnimation->GetNowFrameX() == 4)
	{
		mIsDestroy = true;
	}
}

void Effect_ShorkWave::Render()
{
	mImage->SetScale(mScale);
	mImage->SetAlpha(0.3f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
