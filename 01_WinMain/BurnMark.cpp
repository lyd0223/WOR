#include "pch.h"
#include "BurnMark.h"
#include "Image.h"
#include "Animation.h"

BurnMark::BurnMark(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void BurnMark::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"BurnMark", Resources(L"Effect/BurnMark.png"), 4, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"BurnMark");

	mRandomY = Random::GetInstance()->RandomInt(4);

	mBurnMarkAnimation = new Animation();
	mBurnMarkAnimation->InitFrameByStartEnd(0, mRandomY, 3, mRandomY, false);
	mBurnMarkAnimation->SetFrameUpdateTime(3.f);
	mBurnMarkAnimation->Play();
}

void BurnMark::Release()
{
	SafeDelete(mBurnMarkAnimation)
}

void BurnMark::Update()
{
	mBurnMarkAnimation->Update();
}

void BurnMark::Render()
{
	mImage->FrameRender(mX, mY, mBurnMarkAnimation->GetNowFrameX(), mBurnMarkAnimation->GetNowFrameY());
}
