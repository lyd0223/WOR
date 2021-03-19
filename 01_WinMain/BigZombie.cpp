#include "pch.h"
#include "Image.h"
#include"Camera.h"
#include"Animation.h"
#include"Player.h"
#include"BigZombie.h"
#include "Tile.h"

BigZombie::BigZombie(const string& name, float x, float y)
	:MonsterObject(name)
{
	mName = name;
	mX = x; 
	mY = y;
}

void BigZombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"BigZombie", Resources(L"Monster/Bigzombie.png"), 7, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"BigZombie");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize + 75;
	mSizeY = TileSize + 75;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
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
	

	if (mPathList.size() != 0)
	{
		float nextX = mPathList[1]->GetX();
		float nextY = mPathList[1]->GetY();
		float angle = Math::GetAngle(mX, mY, nextX, nextY);

		mX += cosf(angle) * mSpeed;
		mY += -sinf(angle) * mSpeed;
	}
	

	mPlayer->Update();
	mCurrentAnimation->Update();
	mRect = RectMake(mX, mY, TileSize, TileSize);
}

void BigZombie::Render()
{
	mImage->SetScale(4.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	for (int i = 0; i < mPathList.size(); i++) 
	{
		D2D1_RECT_F rc = RectMakeCenter(mPathList[i]->GetX(), mPathList[i]->GetY(), TileSize, TileSize);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(rc);
	}
	
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