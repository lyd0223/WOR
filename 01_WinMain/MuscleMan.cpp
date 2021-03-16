#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"MuscleMan.h"

MuscleMan::MuscleMan(const string& name, float x, float y)

{
	mName = name;
	mX = x;
	mY = y;
}

void MuscleMan::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MuscleMan", Resources(L"Monster/MuscleMan.png"), 6, 2);
	mImage = ImageManager::GetInstance()->FindImage(L"MuscleMan");
	mMonsterState = MonsterState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize + 50;
	mSizeY = TileSize + 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationSet(&mAttackAnimation, false, false, 4, 0, 4, 0, AnimationTime);
	AnimationSet(&mAttackReadyAnimation, false, false, 1, 0, 3, 0, AnimationTime);



	mCurrentAnimation = mIdleAnimation;
	mCurrentAnimation->Play();
}

void MuscleMan::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mDieAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mAttackReadyAnimation);

}

void MuscleMan::Update()
{

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void MuscleMan::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void MuscleMan::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void MuscleMan::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void MuscleMan::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}