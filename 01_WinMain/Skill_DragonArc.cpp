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

	mSkillArcana = SkillArcana::Standard;
	mSkillElement = SkillElement::Fire;
	mSkillType = SkillType::Throw;

	mSkillCool = 3.f;
	
}

void Skill_DragonArc::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"DragonArc", Resources(L"Skill/DragonArc.png"), 1, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"DragonArc");

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 15.f;
	mFrameCount = 0;
	mSkillDamege = 5.f;
	mMoveAngle = mAngle;
	mUpAngle = mAngle + (PI / 3);
	mDownAngle = mAngle - (PI / 3);

	SoundPlayer::GetInstance()->Play(L"FireArcStart", 1.f);
}

void Skill_DragonArc::Release()
{
}

void Skill_DragonArc::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();

	if (mFrameCount > 0.1f)
	{
		mFrameCount = 0;
		ParticleManager::GetInstance()->MakeFireParticle(mX, mY, mAngle);
	}

	if (mIsUp)
	{
		mMoveAngle += 0.1f;
		if (mMoveAngle > mUpAngle)
		{
			mIsUp = false;
		}
	}
	else
	{
		mMoveAngle -= 0.1f;
		if (mMoveAngle < mDownAngle)
		{
			mIsUp = true;
		}
	}

	mLineX = mX + cosf(mAngle) * 500;
	mLineY = mY + -sinf(mAngle) * 500;
	

	mX += cosf(mMoveAngle) * mSpeed;
	mY += -sinf(mMoveAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Skill_DragonArc::Render()
{
	mImage->SetAngle(mMoveAngle * -(180 / PI));
	mImage->SetScale(2.f);
	
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->Render(mImage, mX, mY);
}
