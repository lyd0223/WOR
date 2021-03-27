#include "pch.h"
#include "Effect_FlameEffect.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

Effect_FlameEffect::Effect_FlameEffect(const string & name, float x, float y, float angle, float scale)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mScale = scale;
}

void Effect_FlameEffect::Init()
{
	//ImageManager::GetInstance()->LoadFromFile(L"FlameEffect", Resources(L"Effect/FlameEffect.png"), 6, 1);
	//mImage = ImageManager::GetInstance()->FindImage(L"FlameEffect");
	ImageManager::GetInstance()->LoadFromFile(L"ExplosionEffect", Resources(L"Effect/BlastEffect.png"), 7, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"ExplosionEffect");

	mFlameEffectAnimation = new Animation();
	mFlameEffectAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mFlameEffectAnimation->SetFrameUpdateTime(0.02f);
	mFlameEffectAnimation->Play();
}

void Effect_FlameEffect::Release()
{
	SafeDelete(mFlameEffectAnimation);
}

void Effect_FlameEffect::Update()
{
	mFlameEffectAnimation->Update();
	if (mFlameEffectAnimation != nullptr) {
		if (mFlameEffectAnimation->GetNowFrameX() == 3) {
			mIsDestroy = true;
		}
	}
}

void Effect_FlameEffect::Render()
{
	if (mFlameEffectAnimation != nullptr) {
		mImage->SetScale(mScale);
		mImage->SetAngle(mAngle * (180 / PI));
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mFlameEffectAnimation->GetNowFrameX(), mFlameEffectAnimation->GetNowFrameY());
	}
}
