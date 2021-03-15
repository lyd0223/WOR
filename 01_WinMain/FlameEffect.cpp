#include "pch.h"
#include "FlameEffect.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

FlameEffect::FlameEffect(const string & name, float x, float y, float angle)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void FlameEffect::Init()
{
	//ImageManager::GetInstance()->LoadFromFile(L"FlameEffect", Resources(L"Effect/FlameEffect.png"), 6, 1);
	//mImage = ImageManager::GetInstance()->FindImage(L"FlameEffect");
	ImageManager::GetInstance()->LoadFromFile(L"ExplosionEffect", Resources(L"Effect/ExplosionEffect.png"), 4, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"ExplosionEffect");

	mFlameEffectAnimation = new Animation();
	mFlameEffectAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mFlameEffectAnimation->SetFrameUpdateTime(0.05f);
	mFlameEffectAnimation->Play();
}

void FlameEffect::Release()
{
	SafeDelete(mFlameEffectAnimation);
}

void FlameEffect::Update()
{
	mFlameEffectAnimation->Update();
	if (mFlameEffectAnimation != nullptr) {
		if (mFlameEffectAnimation->GetNowFrameX() == 3) {
			mIsDestroy = true;
		}
	}
}

void FlameEffect::Render()
{
	if (mFlameEffectAnimation != nullptr) {
		mImage->SetAngle(mAngle * -(180 / PI));
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mFlameEffectAnimation->GetNowFrameX(), mFlameEffectAnimation->GetNowFrameY());
	}
}
