#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include "Animation.h"
#include "Skill_MonsterMiddleSlash.h"


Skill_MonsterMiddleSlash::Skill_MonsterMiddleSlash(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Skill_MonsterMiddleSlash::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MonsterSmallSlash", Resources(L"Skill/MonsterSlash.png"), 5, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"MonsterSmallSlash");

	mSizeX = mImage->GetWidth() / 5;
	mSizeY = mImage->GetHeight() / 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSkillType = SkillType::Melee;

	mSlashAnimation = new Animation;
	mSlashAnimation->InitFrameByStartEnd(0, 1, 4, 1, false);
	mSlashAnimation->SetIsLoop(false);
	mSlashAnimation->SetFrameUpdateTime(0.1f);
	mSlashAnimation->Play();


}

void Skill_MonsterMiddleSlash::Release()
{
	SafeDelete(mSlashAnimation);
}

void Skill_MonsterMiddleSlash::Update()
{
	if (mSlashAnimation->GetNowFrameX() == 4)mIsDestroy = true;
	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSlashAnimation->Update();
}

void Skill_MonsterMiddleSlash::Render()
{
	mImage->SetScale(2.f);
	mImage->SetAngle(mAngle * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSlashAnimation->GetNowFrameX(), mSlashAnimation->GetNowFrameY());
}