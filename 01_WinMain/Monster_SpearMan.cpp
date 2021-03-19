#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_SpearMan.h"
#include "Tile.h"

Monster_SpearMan::Monster_SpearMan(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_SpearMan::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SpearMan", Resources(L"Monster/SpearMan.png"), 8, 6);
	mImage = ImageManager::GetInstance()->FindImage(L"SpearMan");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize;
	mSizeY = TileSize;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 1, 0, 1, 0, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 2, 0, 2, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, true, true, 0, 2, 4, 2, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, true, true, 5, 3, 1, 3, AnimationTime);
	AnimationSet(&mDownAttackAnimation, false, true, 0, 4, 1, 4, AnimationTime);
	AnimationSet(&mUpAttackAnimation, false, true, 2, 4, 3, 4, AnimationTime);
	AnimationSet(&mLeftAttackAnimation, false, true, 4, 4, 5, 4, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, true, 6, 4, 7, 4, AnimationTime);
	AnimationSet(&mDieAnimation, false, true, 0, 5, 6, 5, AnimationTime);


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_SpearMan::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mDownAttackAnimation);
	SafeDelete(mUpAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mDieAnimation);

}

void Monster_SpearMan::Update()
{
	
	if (mPathList.size() != 0)
	{
		float nextX = mPathList[1]->GetX();
		float nextY = mPathList[1]->GetY();
		float angle = Math::GetAngle(mX, mY, nextX, nextY);

		mX += cosf(angle) * mSpeed;
		mY += -sinf(angle) * mSpeed;
	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Monster_SpearMan::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_SpearMan::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_SpearMan::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_SpearMan::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}