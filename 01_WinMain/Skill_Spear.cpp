#include "pch.h"
#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include"Player.h"
#include "Animation.h"
#include "Skill_Spear.h"


Skill_Spear::Skill_Spear(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Skill_Spear::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Spear", Resources(L"Monster/Spear.png"), 1, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"Spear");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mSizeX = mImage->GetWidth()*2.5f;
	mSizeY = mImage->GetHeight()*2.5f;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSkillType = SkillType::Melee;

	mSpearAnimation = new Animation;
	mSpearAnimation->InitFrameByStartEnd(0, 0, 0, 0, false);
	mSpearAnimation->SetIsLoop(false);
	mSpearAnimation->SetFrameUpdateTime(0.1f);
	mSpearAnimation->Play();


}

void Skill_Spear::Release()
{
	SafeDelete(mSpearAnimation);
}

void Skill_Spear::Update()
{
	//if (mSlashAnimation->GetNowFrameX() == 6)mIsDestroy = true;

	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpearAnimation->Update();
}

void Skill_Spear::Render()
{
	mImage->SetScale(2.5f);
	mImage->SetAngle((mAngle) * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSpearAnimation->GetNowFrameX(), mSpearAnimation->GetNowFrameY());
}