#include "pch.h"
#include "Camera.h"
#include "Image.h"
#include "Animation.h"
#include "Skill_WindSlash.h"


Skill_WindSlash::Skill_WindSlash(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX =   x;
	mY =   y;
	mAngle = angle;
	mSkillArcana = SkillArcana::Basic;
	mSkillType = SkillType::Melee;
	mSkillTarget = SkillTarget::Player;
	mSkillElement = SkillElement::Wind;
	
}

void Skill_WindSlash::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"WindSlash", Resources(L"Skill/WindSlash.png"), 5, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"WindSlash");

	mSizeX = mImage->GetWidth() / 5 * 1.5 - 30;
	mSizeY = mImage->GetHeight() / 3 * 1.5;

	mSkillPower = 5.f;
	mSkillDamege = 11.f;

	mSlashAnimation = new Animation;
	mSlashAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mSlashAnimation->SetIsLoop(false);
	mSlashAnimation->SetFrameUpdateTime(0.02f);
	mSlashAnimation->Play();

	mSkillHitCount = 1;
}

void Skill_WindSlash::Release()
{
	SafeDelete(mSlashAnimation);
}

void Skill_WindSlash::Update()
{
	if (mSlashAnimation->GetNowFrameX() == 3) mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (mSlashAnimation->GetNowFrameX() == 4) mIsDestroy = true;
	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	//mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSlashAnimation->Update();
}

void Skill_WindSlash::Render()
{
	
	mImage->SetScale(2.f);
	mImage->SetAngle(mAngle * -(180/PI));
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSlashAnimation->GetNowFrameX(), mSlashAnimation->GetNowFrameY());
}
