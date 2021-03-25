#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include "Animation.h"
#include "Skill_MonsterBigSlash.h"


Skill_MonsterBigSlash::Skill_MonsterBigSlash(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Skill_MonsterBigSlash::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MonsterBigSlash", Resources(L"Skill/MonsterSlash.png"), 5, 3);
	mImage = ImageManager::GetInstance()->FindImage(L"MonsterBigSlash");

	mSizeX = mImage->GetWidth() / 5 ;
	mSizeY = mImage->GetHeight() / 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);


	mSlashAnimation = new Animation;
	mSlashAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mSlashAnimation->SetIsLoop(false);
	mSlashAnimation->SetFrameUpdateTime(0.1f);
	mSlashAnimation->Play();

	mSkillTarget = SkillTarget::Enemy;
	mSkillType = SkillType::Melee;
}

void Skill_MonsterBigSlash::Release()
{
	SafeDelete(mSlashAnimation);
}

void Skill_MonsterBigSlash::Update()
{
	if (mSlashAnimation->GetNowFrameX() == 4)mIsDestroy = true;
	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSlashAnimation->Update();
}

void Skill_MonsterBigSlash::Render()
{
	mImage->SetScale(3.f);
	mImage->SetAngle(mAngle * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSlashAnimation->GetNowFrameX(), mSlashAnimation->GetNowFrameY());
}
