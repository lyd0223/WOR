#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include "Animation.h"
#include "WindSlash.h"

WindSlash::WindSlash(const string& name, float x, float y, float angle)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	

}

void WindSlash::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"WindSlash", Resources(L"Skill/WindSlash.png"), 5, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"WindSlash");

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mAngle = 0.f;

	mSlashAnimation = new Animation;
	mSlashAnimation->InitFrameByBackStartEnd(0, 2, 4, 2, false);
	mSlashAnimation->SetIsLoop(false);
	mSlashAnimation->SetFrameUpdateTime(0.1f);
	mSlashAnimation->Play();


}

void WindSlash::Release()
{
	SafeDelete(mSlashAnimation);
}

void WindSlash::Update()
{
	
	mAngle = Math::GetAngle(mX, mY, _mousePosition.x, _mousePosition.y);
	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mSlashAnimation->Update();
}

void WindSlash::Render()
{
	
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSlashAnimation->GetNowFrameX(), mSlashAnimation->GetNowFrameY());
}
