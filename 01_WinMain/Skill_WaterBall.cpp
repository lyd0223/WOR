#include "pch.h"

#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include"Player.h"
#include "Animation.h"
#include "Skill_WaterBall.h"


Skill_WaterBall::Skill_WaterBall(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mSkillElement = SkillElement::Water;
	mSkillTarget = SkillTarget::Player;
	mSkillType = SkillType::Throw;
	mSkillArcana = SkillArcana::Standard;
	mSkillCool = 5.f;
}

Skill_WaterBall::Skill_WaterBall(const string& name, float x, float y, float angle, float temp)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mSkillElement = SkillElement::Water;
	mSkillTarget = SkillTarget::Enemy;
	mSkillType = SkillType::Throw;
	mSkillArcana = SkillArcana::Standard;
	mSkillCool = 2.f;
}

void Skill_WaterBall::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"WaterBall", Resources(L"Skill/WaterBall.png"), 3, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"WaterBall");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mSizeX = mImage->GetWidth()/3;
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 60.f;
	mSkillDamege = 15.f;
	mWaterBallAnimation = new Animation;
	mWaterBallAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mWaterBallAnimation->SetIsLoop(false);
	mWaterBallAnimation->SetFrameUpdateTime(0.02f);
	mWaterBallAnimation->Play();

	mSkillPower = 3.f;

	SoundPlayer::GetInstance()->Play(L"WaterBall", 1.f);
}

void Skill_WaterBall::Release()
{
	SafeDelete(mWaterBallAnimation);
}

void Skill_WaterBall::Update()
{
	//if (mSlashAnimation->GetNowFrameX() == 6)mIsDestroy = true;

	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY += -sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mWaterBallAnimation->Update();
}

void Skill_WaterBall::Render()
{
	mImage->SetScale(1.5f);
	mImage->SetAlpha(0.9f);
	mImage->SetAngle((mAngle) * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mWaterBallAnimation->GetNowFrameX(), mWaterBallAnimation->GetNowFrameY());
}