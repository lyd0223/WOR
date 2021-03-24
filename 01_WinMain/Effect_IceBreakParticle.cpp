#include "pch.h"
#include "Effect_IceBreakParticle.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_IceBreakParticle::Effect_IceBreakParticle(const string & name, float x, float y, float angle)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Effect_IceBreakParticle::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"IceBreakParticle", Resources(L"Effect/IceBreakParticle.png"), 4, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"IceBreakParticle");

	int randomY;
	randomY = Random::GetInstance()->RandomInt(4);

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, randomY, 3, randomY, false);
	mAnimation->SetFrameUpdateTime(0.03f);
	mAnimation->Play();
}

void Effect_IceBreakParticle::Release()
{
	SafeDelete(mAnimation)
}

void Effect_IceBreakParticle::Update()
{
	mAnimation->Update();

	if (mAnimation->GetNowFrameX() == 3)
	{
		mIsDestroy = true;
	}

	if (mIsMove)
	{
		mX += cosf(mAngle) * mSpeed;
		mY += -sinf(mAngle) * mSpeed;
	}
}

void Effect_IceBreakParticle::Render()
{
	int randomInt = Random::GetInstance()->RandomInt(360);
	mImage->SetAngle(randomInt);
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
