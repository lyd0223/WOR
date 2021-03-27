#include "pch.h"
#include "Effect_Smoke.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_Smoke::Effect_Smoke(const string & name, float x, float y, float angle, float scale, float speed)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mScale = scale;
	mSpeed = speed;
}

void Effect_Smoke::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"GlassShards", Resources(L"Effect/Smoke.png"), 8, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"GlassShards");

	int randomY = Random::GetInstance()->RandomInt(3);

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, randomY, 7, randomY, false);
	mAnimation->SetFrameUpdateTime(0.1f);
	mAnimation->Play();

	mAlpha = 0.2f;
}

void Effect_Smoke::Release()
{
	SafeDelete(mAnimation)
}

void Effect_Smoke::Update()
{
	mAnimation->Update();

	if (mAnimation->GetNowFrameX() == 7)
	{
		mIsDestroy = true;
	}

	mAlpha -= 0.005f;
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
}

void Effect_Smoke::Render()
{
	mImage->SetAngle(mAngle * (180 / PI));
	mImage->SetScale(mScale);
	mImage->SetAlpha(mAlpha);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
