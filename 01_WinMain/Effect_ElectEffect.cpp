#include "pch.h"
#include "Effect_ElectEffect.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_ElectEffect::Effect_ElectEffect(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_ElectEffect::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"ElectEffect", Resources(L"Effect/ElectEffect.png"), 4, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"ElectEffect");

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mAnimation->SetFrameUpdateTime(0.02f);
	mAnimation->Play();

	SoundPlayer::GetInstance()->Play(L"ThunderBounce", 1.f);
}

void Effect_ElectEffect::Release()
{
	SafeDelete(mAnimation)
}

void Effect_ElectEffect::Update()
{
	if (mAnimation->GetNowFrameX() == 3) mIsDestroy = true;

	mAnimation->Update();
}

void Effect_ElectEffect::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
