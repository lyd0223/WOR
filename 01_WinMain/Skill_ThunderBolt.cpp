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
	mSkillType = SkillType::Melee;
	mSkillElement = SkillElement::Elect;
	mSkillArcana = SkillArcana::Signature;

	mIsActive = false;
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
	mThunderBoltAnimation->SetFrameUpdateTime(0.02f);
	mThunderBoltAnimation->Play();

	mSkillPower = 5.f;
	mSkillDamege = 10;
	mSkillCool = 5;
}

void Skill_ThunderBolt::Release()
{
	SafeDelete(mThunderBoltAnimation);
}

void Skill_ThunderBolt::Update()
{
	if (mIsActive)
	{
		if (mThunderBoltAnimation->GetNowFrameX() == 2)
		{
			SoundPlayer::GetInstance()->LoadFromFile(L"ThunderBoltSound", Resources(L"Sound/ThunderBolt.wav"), false);
			SoundPlayer::GetInstance()->Play(L"ThunderBoltSound", 1.f);
			ParticleManager::GetInstance()->MakeElectEffect(mX, mY);
		}
		if (mThunderBoltAnimation->GetNowFrameX() == 3)
		{
			
			mIsDestroy = true;
		}

		mRect = RectMakeCenter(mX , mY, mSizeX, mSizeY );
	
		mThunderBoltAnimation->Update();
	}
}

void Skill_ThunderBolt::Render()
{
	if (mIsActive)
	{
		mImage->SetScale(1.5f);
		//mImage->SetAngle((mAngle) * -(180 / PI));
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
		CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY, mThunderBoltAnimation->GetNowFrameX(), mThunderBoltAnimation->GetNowFrameY());
	}
}