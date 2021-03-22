#include "pch.h"
#include "Skill_IceSpear.h"
#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include "Animation.h"
#include "Skill_SummonIceSpear.h"


Skill_SummonIceSpear::Skill_SummonIceSpear(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Skill_SummonIceSpear::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SummonIceSpear", Resources(L"Skill/IceSpear.png"), 1, 7);
	mImage = ImageManager::GetInstance()->FindImage(L"SummonIceSpear");

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mAngle = 0.f;

	mSummonIceSpearAnimation = new Animation;
	mSummonIceSpearAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mSummonIceSpearAnimation->SetIsLoop(false);
	mSummonIceSpearAnimation->SetFrameUpdateTime(0.1f);
	mSummonIceSpearAnimation->Play();
	mSkillType = SkillType::Throw;


}

void Skill_SummonIceSpear::Release()
{
	SafeDelete(mSummonIceSpearAnimation);
}

void Skill_SummonIceSpear::Update()
{
	if (Input::GetInstance()->GetKeyUp(VK_RBUTTON))mIsDestroy = true;

	D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mSummonIceSpearAnimation->Update();
}

void Skill_SummonIceSpear::Render()
{
	mImage->SetScale(2.5f);
	mImage->SetAngle((mAngle) * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSummonIceSpearAnimation->GetNowFrameX(), mSummonIceSpearAnimation->GetNowFrameY());
}