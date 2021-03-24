#include "pch.h"
#include "Skill_DragonArc.h"
#include "Image.h"
#include "Camera.h"

Skill_DragonArc::Skill_DragonArc(const string & name, float x, float y, float angle, bool isUp)
	: SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mIsUp = isUp;
}

void Skill_DragonArc::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"DragonArc", Resources(L"Skill_DragonArc"), 1, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"DragonArc");

	mSpeed = 2.f;
	mFrameCount = 0;
}

void Skill_DragonArc::Release()
{
}

void Skill_DragonArc::Update()
{
	mFrameCount = Time::GetInstance()->DeltaTime();

	if (mFrameCount > 0.5f)
	{
		mFrameCount = 0;
		ParticleManager::GetInstance()->MakeFireParticle(mX, mY, mAngle);
	}

	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
}

void Skill_DragonArc::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->Render(mImage, mX, mY);
}
