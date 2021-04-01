#include "pch.h"
#include "Skill_LightRing.h"
#include "Image.h"
#include "Camera.h"

Skill_LightRing::Skill_LightRing(const string & name, float x, float y, float angle)
	: SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;

	mSkillType = SkillType::Throw;
	mSkillArcana = SkillArcana::Basic;
	mSkillTarget = SkillTarget::Player;
	mSkillElement = SkillElement::Elect;
	mSkillDamege = 5.f;
	mSkillPower = 2.f;

	mStartX = mX;
	mStartY = mY;

}

void Skill_LightRing::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"LightRing", Resources(L"Skill/LightRing.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"LightRing");

	mRect = RectMakeCenter(mX, mY, mImage->GetWidth() * 2, mImage->GetHeight() * 2);

	mSpeed = 20.f;
}

void Skill_LightRing::Release()
{
}

void Skill_LightRing::Update()
{
	float distance = Math::GetDistance(mStartX, mStartY, mX, mY);

	if (distance > 250) mIsDestroy = true;

	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;

	mRect = RectMakeCenter(mX, mY, mImage->GetWidth() * 2.5, mImage->GetHeight() * 2.5);
}

void Skill_LightRing::Render()
{
	mImage->SetScale(2.5f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, 0, 0);
}
