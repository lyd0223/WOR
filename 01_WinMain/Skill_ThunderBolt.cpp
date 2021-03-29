#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include"Player.h"
#include "Animation.h"
#include "Skill_ThunderBolt.h"


Skill_ThunderBolt::Skill_ThunderBolt(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mSkillTarget = SkillTarget::Player;
	mSkillType = SkillType::Throw;
	mSkillElement = SkillElement::Elect;
	mSkillArcana = SkillArcana::Standard;
}

void Skill_ThunderBolt::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"ThunderBolt", Resources(L"Skill/ThunderBolt.png"), 4, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"ThunderBolt");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mSizeX = mImage->GetWidth()/4;
	mSizeY = mImage->GetHeight()/1 - 200;
	mRect = RectMakeCenter(mX , mY , mSizeX, mSizeY );
	mSpeed = 0;


	mThunderBoltAnimation = new Animation;
	mThunderBoltAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mThunderBoltAnimation->SetIsLoop(false);
	mThunderBoltAnimation->SetFrameUpdateTime(0.1f);
	mThunderBoltAnimation->Play();

	mSkillPower = 5.f;
}

void Skill_ThunderBolt::Release()
{
	SafeDelete(mThunderBoltAnimation);
}

void Skill_ThunderBolt::Update()
{
	if (mThunderBoltAnimation->GetNowFrameX() == 3)mIsDestroy = true;

	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);

	
	mX += cosf(mAngle)  * 0;
	mY += -sinf(mAngle) * 0;
	mRect = RectMakeCenter(mX , mY, mSizeX, mSizeY );
	

	mThunderBoltAnimation->Update();
}

void Skill_ThunderBolt::Render()
{
	mImage->SetScale(1.f);
	//mImage->SetAngle((mAngle) * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY + 100, mThunderBoltAnimation->GetNowFrameX(), mThunderBoltAnimation->GetNowFrameY());
}