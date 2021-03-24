#include "pch.h"
#include "Effect_WaterFormParticle.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_WaterFormParticle::Effect_WaterFormParticle(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_WaterFormParticle::Init()
{
	int randomY = Random::GetInstance()->RandomInt(4);

	ImageManager::GetInstance()->LoadFromFile(L"WaterFormParticle", Resources(L"Effect/WaterFormParticle.png"), 4, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"WaterFormParticle");

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, randomY, 3, randomY, false);
	mAnimation->SetFrameUpdateTime(0.03f);
	mAnimation->Play();
}

void Effect_WaterFormParticle::Release()
{
	SafeDelete(mAnimation)
}

void Effect_WaterFormParticle::Update()
{
	mAnimation->Update();

	if (mAnimation->GetNowFrameX() == 4)
	{
		mIsDestroy = true;
	}
}

void Effect_WaterFormParticle::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
