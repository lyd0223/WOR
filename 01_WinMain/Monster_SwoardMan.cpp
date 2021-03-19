#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_SwoardMan.h"
#include "Tile.h"

Monster_SwoardMan::Monster_SwoardMan(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_SwoardMan::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SwoardMan", Resources(L"Monster/SwoardMan.png"), 8, 7);
	mImage = ImageManager::GetInstance()->FindImage(L"SwoardMan");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize;
	mSizeY = TileSize;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);


	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, true, true, 0, 1, 4, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, true, true, 6, 2, 2, 2, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 4, 4, 4, 4, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 5, 4, 5, 4, AnimationTime);
	AnimationSet(&mUpAttackAnimation, false, true, 0, 3, 1, 3, AnimationTime);
	AnimationSet(&mLeftAttackAnimation, false, true, 2, 3, 3, 3, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, true, 4, 3, 5, 3, AnimationTime);
	AnimationSet(&mDownAttackAnimation, false, true, 0, 3, 1, 3, AnimationTime);
	AnimationSet(&mDieAnimation, false, true, 0, 6, 7, 6, AnimationTime);

	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_SwoardMan::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mUpAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mDownAttackAnimation);
	SafeDelete(mDieAnimation);

}

void Monster_SwoardMan::Update()
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

void Monster_SwoardMan::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_SwoardMan::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_SwoardMan::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_SwoardMan::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}