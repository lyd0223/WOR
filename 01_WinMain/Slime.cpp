#include "pch.h"
#include "Slime.h"
#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Slime.h"


Slime::Slime(const string& name, float x, float y)

{
	mName = name;
	mX = x;
	mY = y;
}

void Slime::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Slime", Resources(L"Monster/Slime.png"), 10, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"Slime");
	mMonsterState = MonsterState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize / 2;
	mSizeY = TileSize/2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 9, 3, 9, 3, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, true, 1, 0, 7, 0, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, true, 7, 3, 1, 3, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, true, 0, 1, 4, 1, AnimationTime);
	AnimationReverseSet(&mLeftHitAnimation, false, true, 7, 3, 3, 3, AnimationTime);
	AnimationSet(&mDieAnimation, false, true, 5, 1, 9, 1, AnimationTime);



	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Slime::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mDieAnimation);

}

void Slime::Update()
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

void Slime::Render()
{
	mImage->SetScale(1.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Slime::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Slime::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Slime::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}