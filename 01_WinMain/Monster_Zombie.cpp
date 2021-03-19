#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Zombie.h"
#include "Tile.h"

Monster_Zombie::Monster_Zombie(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Zombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Zombie", Resources(L"Monster/Zombie.png"), 10, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"Zombie");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize;
	mSizeY = TileSize;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);


	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 5, 0, 5, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, true, 1, 0, 2, 0, AnimationTime);
	AnimationReverseSet(&mLeftAttackAnimation, false, true, 4, 0, 3, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, true, 0, 1, 5, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, true, 5, 2, 0, 2, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 0, 3, 0, 3, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 6, 2, 6, 2, AnimationTime);
	AnimationSet(&mDieAnimation, false, true, 0, 3, 9, 3, AnimationTime);

	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Zombie::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mDieAnimation);

}

void Monster_Zombie::Update()
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

void Monster_Zombie::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_Zombie::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Zombie::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Zombie::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}