#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_MazitionBullet.h"
#include "Tile.h"

Monster_MazitionBullet::Monster_MazitionBullet(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_MazitionBullet::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MazitionBullet", Resources(L"Monster/MazitionBullet.png"), 5, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MazitionBullet");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize/2;
	mSizeY = TileSize / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mWalkAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mAttackAnimation, false, false, 4, 0, 4, 0, AnimationTime);
	AnimationSet(&mAttackReadyAnimation, false, false, 1, 0, 3, 0, AnimationTime);



	mCurrentAnimation = mAttackAnimation;
	mCurrentAnimation->Play();
}

void Monster_MazitionBullet::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mWalkAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mAttackReadyAnimation);
}

void Monster_MazitionBullet::Update()
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

void Monster_MazitionBullet::Render()
{
	mImage->SetScale(1.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_MazitionBullet::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_MazitionBullet::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_MazitionBullet::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}