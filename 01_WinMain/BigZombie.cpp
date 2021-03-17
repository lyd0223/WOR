#include "pch.h"
#include "Image.h"
#include"Camera.h"
#include"Animation.h"
#include"BigZombie.h"


BigZombie::BigZombie(const string& name, float x, float y)
	
{
	mName = name;
	mX = x; 
	mY = y;
}

void BigZombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"BigZombie", Resources(L"Monster/Bigzombie.png"), 7, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"BigZombie");
	mMonsterState = MonsterState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize + 75;
	mSizeY = TileSize + 75;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 1, 0, 5, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 0, 1, 4, 1, AnimationTime);
	AnimationSet(&mLeftAttackAnimation, false, false, 0, 2, 4, 2, AnimationTime);
	AnimationSet(&mSpecialAttackAnimation, false, false, 0, 3, 5, 3, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 4, 5, 4, AnimationTime);

	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void BigZombie::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mSpecialAttackAnimation);
	SafeDelete(mDieAnimation);
}

void BigZombie::Update()
{
	if (Input::GetInstance()->GetKey('W'))
	{
		mY -= 5;
	}
	if (Input::GetInstance()->GetKey('S'))
	{
		mY += 5;
	}
	if (Input::GetInstance()->GetKey('A'))
	{
		mX -= 5;
	}
	if (Input::GetInstance()->GetKey('D'))
	{
		mX += 5;
	}
	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BigZombie::Render()
{
	mImage->SetScale(4.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	
}
void BigZombie::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void BigZombie::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void BigZombie::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}