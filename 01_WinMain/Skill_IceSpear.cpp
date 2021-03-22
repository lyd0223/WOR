#include "pch.h"
#include "Skill_IceSpear.h"
#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include"Player.h"
#include "Animation.h"
#include "Skill_IceSpear.h"


Skill_IceSpear::Skill_IceSpear(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Skill_IceSpear::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"IceSpear", Resources(L"Skill/IceSpear.png"), 1, 7);
	mImage = ImageManager::GetInstance()->FindImage(L"IceSpear");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mSpeed = 20.f;
	mSkillType = SkillType::Throw;

	mIceSpearAnimation = new Animation;
	mIceSpearAnimation->InitFrameByStartEnd(6, 0, 6, 0, false);
	mIceSpearAnimation->SetIsLoop(false);
	mIceSpearAnimation->SetFrameUpdateTime(0.1f);
	mIceSpearAnimation->Play();


}

void Skill_IceSpear::Release()
{
	SafeDelete(mIceSpearAnimation);
}

void Skill_IceSpear::Update()
{
	//if (mSlashAnimation->GetNowFrameX() == 6)mIsDestroy = true;

	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mIceSpearAnimation->Update();
}

void Skill_IceSpear::Render()
{
	mImage->SetScale(2.5f);
	mImage->SetAngle((mAngle) * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mIceSpearAnimation->GetNowFrameX(), mIceSpearAnimation->GetNowFrameY());
}