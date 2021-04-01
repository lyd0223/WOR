#include "pch.h"
#include "Effect_Number.h"
#include "Image.h"
#include "Camera.h"

Effect_Number::Effect_Number(const string & name, float x, float y, int index)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mIndex = index;
	mAlpha = 1.f;
}

void Effect_Number::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"NumberBlack", Resources(L"UI/NumberBlack.png"), 10, 1);
	ImageManager::GetInstance()->LoadFromFile(L"NumberWhite", Resources(L"UI/NumberWhite.png"), 10, 1);
	ImageManager::GetInstance()->LoadFromFile(L"NumberGray", Resources(L"UI/NumberGray.png"), 10, 1);
	ImageManager::GetInstance()->LoadFromFile(L"NumberRed", Resources(L"UI/NumberRed.png"), 10, 1);

	mNumberBlack = ImageManager::GetInstance()->FindImage(L"NumberBlack");
	mNumberWhite = ImageManager::GetInstance()->FindImage(L"NumberWhite");
	mNumberGray = ImageManager::GetInstance()->FindImage(L"NumberGray");
	mNumberRed = ImageManager::GetInstance()->FindImage(L"NumberRed");

	if (mIndex > 10)
	{
		mTen = mIndex / 10;
		mOne = mIndex % 10;
	}
}

void Effect_Number::Release()
{
}

void Effect_Number::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();
	
	mY -= Time::GetInstance()->DeltaTime() * 50;
	mAlpha -= 0.05f;

	if (mFrameCount > 1)
	{
		mIsDestroy = true;
	}
}

void Effect_Number::Render()
{
	mNumberRed->SetScale(3.f);
	mNumberRed->SetAlpha(mAlpha);
	if (mIndex > 9)
	{
		mNumberRed->SetScale(3.f);
		mNumberRed->SetAlpha(mAlpha);
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mNumberRed, mX - 8, mY, mTen, 0);
		mNumberRed->SetScale(3.f);
		mNumberRed->SetAlpha(mAlpha);
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mNumberRed, mX + 8, mY, mOne, 0);
	}
	else
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mNumberRed, mX, mY, mIndex, 0);
}
