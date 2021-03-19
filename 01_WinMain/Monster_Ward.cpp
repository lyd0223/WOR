#include "pch.h"
#include "Monster_Slime.h"
#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Ward.h"
#include "Tile.h"

Monster_Ward::Monster_Ward(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Ward::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Ward", Resources(L"Monster/Ward.png"), 4, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"Ward");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize / 2;
	mSizeY = TileSize / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, true, 0, 0, 3, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, true, 0, 0, 3, 0, AnimationTime);



	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Ward::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightAttackAnimation);

}

void Monster_Ward::Update()
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

void Monster_Ward::Render()
{
	mImage->SetScale(1.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_Ward::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Ward::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Ward::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}