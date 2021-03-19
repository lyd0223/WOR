#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include "Animation.h"
#include "Skill_IceSword.h"

Skill_IceSword::Skill_IceSword(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x ;
	mY = y;
	mEndX = x;
	mEndY = y;
	mSpeed = 10.f;
	
}

void Skill_IceSword::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"IceSword", Resources(L"Skill/IceSword.png"), 1, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"IceSword");

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mImageAngle = 0.f;
	
}

void Skill_IceSword::Release()
{
	
}

void Skill_IceSword::Update()
{
	mImageAngle += 360.f * Time::GetInstance()->DeltaTime();

	//mX += cosf(mAngle) * mSpeed;
	//mY -= sinf(mAngle) * mSpeed;
	//mRect = RectMake(mX, mY, mSizeX, mSizeY);

}

void Skill_IceSword::Render()
{
	mImage->SetAngle(mImageAngle);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage,mX,mY,0,0);
}
