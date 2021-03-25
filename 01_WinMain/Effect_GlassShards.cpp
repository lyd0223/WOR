#include "pch.h"
#include "Effect_GlassShards.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_GlassShards::Effect_GlassShards(const string & name, float x, float y, float angle, float scale, float speed)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mScale = scale;
	mSpeed = speed;
}

void Effect_GlassShards::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"GlassShards", Resources(L"Effect/GlassShardsLarge.png"), 4, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"GlassShards");

	int randomY = Random::GetInstance()->RandomInt(4);

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, randomY, 3, randomY, false);
	mAnimation->SetFrameUpdateTime(0.3f);
	mAnimation->Play();
}

void Effect_GlassShards::Release()
{
	SafeDelete(mAnimation)
}

void Effect_GlassShards::Update()
{
	mAnimation->Update();

	if (mAnimation->GetNowFrameX() == 3)
	{
		mIsDestroy = true;
	}

	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
}

void Effect_GlassShards::Render()
{
	mImage->SetAngle(mAngle * (180 / PI));
	mImage->SetScale(mScale);
	mImage->SetAlpha(0.3f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
