#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_MuscleMan.h"
#include "Tile.h"

Monster_MuscleMan::Monster_MuscleMan(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_MuscleMan::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MuscleMan", Resources(L"Monster/MuscleMan.png"), 6, 2);
	mImage = ImageManager::GetInstance()->FindImage(L"MuscleMan");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize + 50;
	mSizeY = TileSize + 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationSet(&mAttackAnimation, false, false, 4, 0, 4, 0, AnimationTime);
	AnimationSet(&mAttackReadyAnimation, false, false, 1, 0, 3, 0, AnimationTime);



	mCurrentAnimation = mIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_MuscleMan::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mDieAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mAttackReadyAnimation);

}

void Monster_MuscleMan::Update()
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

void Monster_MuscleMan::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

}
void Monster_MuscleMan::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_MuscleMan::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_MuscleMan::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}