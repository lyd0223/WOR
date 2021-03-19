#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Mazition.h"
#include "Tile.h"

Monster_Mazition::Monster_Mazition(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Mazition::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Mazition", Resources(L"Monster/Mazition.png"), 6, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"Mazition");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize + 50;
	mSizeY = TileSize + 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 4, 2, 4, 2, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 1, 0, 3, 0, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 3, 2, 1, 2, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 0, 1, 4, 1, AnimationTime);
	AnimationReverseSet(&mLeftAttackAnimation, false, false, 4, 3, 0, 3, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 5, 0, 5, 0, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 5, 1, 5, 1, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 4, 5, 4, AnimationTime);


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Mazition::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mDieAnimation);
}

void Monster_Mazition::Update()
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

void Monster_Mazition::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_Mazition::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Mazition::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Mazition::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}