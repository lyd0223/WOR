#include "pch.h"
#include "Effect_FireParticle.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

Effect_FireParticle::Effect_FireParticle(const string & name, float x, float y, float angle)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Effect_FireParticle::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireParticle", Resources(L"Effect/FireParticle.png"), 6, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"FireParticle");

	mSpeed = 3.f;

	int randomY;
	randomY = Random::GetInstance()->RandomInt(4);
	mRandomAngle = Random::GetInstance()->RandomInt(360);
	
	mFireParticleAnimation = new Animation();
	mFireParticleAnimation->InitFrameByStartEnd(0, randomY, 5, randomY, false);
	mFireParticleAnimation->SetFrameUpdateTime(0.05f);
	mFireParticleAnimation->Play();
}

void Effect_FireParticle::Release()
{
	SafeDelete(mFireParticleAnimation)
}

void Effect_FireParticle::Update()
{
	mFireParticleAnimation->Update();
	
	if (mFireParticleAnimation->GetNowFrameX() == 5)
	{
		mIsDestroy = true;
	}

	if (mIsMove)
	{
		mX += cosf(mAngle) * mSpeed;
		mY += -sinf(mAngle) * mSpeed;
	}
}

void Effect_FireParticle::Render()
{
	mImage->SetAngle(mRandomAngle);
	mImage->SetScale(5.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mFireParticleAnimation->GetNowFrameX(), mFireParticleAnimation->GetNowFrameY());
}
