#include "pch.h"
#include "Effect_BurnMark.h"
#include "Image.h"
#include "Animation.h"

Effect_BurnMark::Effect_BurnMark(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_BurnMark::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"BurnMark", Resources(L"Effect/BurnMark.png"), 4, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"BurnMark");

	mRandomY = Random::GetInstance()->RandomInt(4);

	mBurnMarkAnimation = new Animation();
	mBurnMarkAnimation->InitFrameByStartEnd(0, mRandomY, 3, mRandomY, false);
	mBurnMarkAnimation->SetFrameUpdateTime(3.f);
	mBurnMarkAnimation->Play();
}

void Effect_BurnMark::Release()
{
	SafeDelete(mBurnMarkAnimation)
}

void Effect_BurnMark::Update()
{
	mBurnMarkAnimation->Update();
}

void Effect_BurnMark::Render()
{
	mImage->FrameRender(mX, mY, mBurnMarkAnimation->GetNowFrameX(), mBurnMarkAnimation->GetNowFrameY());
}
