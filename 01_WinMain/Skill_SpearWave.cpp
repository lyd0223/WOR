#include "pch.h"
#include "pch.h"
#include"Camera.h"
#include "Image.h"
#include"Player.h"
#include "Animation.h"
#include "Skill_SpearWave.h"


Skill_SpearWave::Skill_SpearWave(const string& name, float x, float y, float angle)
	:SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
}

void Skill_SpearWave::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SpearEffect", Resources(L"Skill/SpearEffect.png"), 1, 6);
	mImage = ImageManager::GetInstance()->FindImage(L"SpearEffect");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mSkillType = SkillType::Throw;
	mSkillElement = SkillElement::Water;

	mSpearWaveAnimation = new Animation;
	mSpearWaveAnimation->InitFrameByStartEnd(0, 0, 0, 5, false);
	mSpearWaveAnimation->SetIsLoop(false);
	mSpearWaveAnimation->SetFrameUpdateTime(0.1f);
	mSpearWaveAnimation->Play();


}

void Skill_SpearWave::Release()
{
	SafeDelete(mSpearWaveAnimation);
}

void Skill_SpearWave::Update()
{
	//if (mSlashAnimation->GetNowFrameX() == 6)mIsDestroy = true;

	//D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	//mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mSpearWaveAnimation->Update();
}

void Skill_SpearWave::Render()
{
	mImage->SetScale(2.5f);
	mImage->SetAngle((mAngle) * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mSpearWaveAnimation->GetNowFrameX(), mSpearWaveAnimation->GetNowFrameY());
}