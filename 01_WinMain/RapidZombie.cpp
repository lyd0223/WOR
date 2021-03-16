#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"RapidZombie.h"


RapidZombie::RapidZombie(const string& name, float x, float y)

{
	mName = name;
	mX = x;
	mY = y;
}

void RapidZombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"RapidZombie", Resources(L"Monster/RapidZombie.png"), 6, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"RapidZombie");
	mMonsterState = MonsterState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize ;
	mSizeY = TileSize ;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 1, 0, 1, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 2, 0, 3, 0, AnimationTime);
	AnimationReverseSet(&mLeftAttackAnimation, false, false, 5, 0, 4, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 5, 2, 0, 2, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 3, 3, 4, AnimationTime);
	


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void RapidZombie::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mDieAnimation);
	
}

void RapidZombie::Update()
{

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void RapidZombie::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void RapidZombie::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void RapidZombie::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void RapidZombie::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}