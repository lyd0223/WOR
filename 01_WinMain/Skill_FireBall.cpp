#include "pch.h"
#include "Skill_FireBall.h"
#include "Image.h"
#include "Player.h"
#include "Monster_FireBoss.h"
#include "Animation.h"
#include "FlameEffect.h"
#include "Camera.h"
#include "HitSpark.h"

Skill_FireBall::Skill_FireBall(const string & name, float x, float y, float angle)
	:GameObject(name)
{

	mX = x;
	mY = y;
	mAngle = angle;

	ImageManager::GetInstance()->LoadFromFile(L"FireBall", Resources(L"Skill/FireBall.png"), 9, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"FireBall");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mSpeed = 10.f;
	
}

Skill_FireBall::Skill_FireBall(const string & name, float x, float y, float angle, int delay)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mDelay = delay;
}

void Skill_FireBall::Init()
{

	AnimationSet(&mFireBallReadyAnimation, false, false, 0, 0, 4, 0, 0.1f);
	AnimationSet(&mFireBallFireAnimation, false, true, 4, 0, 8, 0, 0.1f);

	mState = FireBallState::Ready;
	mCurrentAnimation = mFireBallReadyAnimation;
	mCurrentAnimation->Play();
}

void Skill_FireBall::Release()
{
	SafeDelete(mFireBallReadyAnimation);
	SafeDelete(mFireBallFireAnimation);
}

void Skill_FireBall::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();

	if (mFrameCount < 1) {
		mDelay--;
		mFrameCount = 0;
	}

	mCurrentAnimation->Update();
	if (mState == FireBallState::Ready && mCurrentAnimation->GetNowFrameX() == 4) {
		if (mDelay < 0) {
			mState = FireBallState::Fire;
			AnimationChange(mFireBallFireAnimation);
			//mFlameEffect = new FlameEffect("FlameEffect", mX, mY, mAngle);
			//mFlameEffect->Init();
		}
	}

	if (mState == FireBallState::Fire) {
		//HitSpark* hitSpark = new HitSpark("HitSpark", mX, mY, mAngle);
		//hitSpark->Init();
		//ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, hitSpark);
		mX += cosf(mAngle) * mSpeed;
		mY += -sinf(mAngle) * mSpeed;
		mRect = RectMake(mX, mY, mSizeX, mSizeY);
	}

	if (mFlameEffect != nullptr) {
		mFlameEffect->Update();
		if (mFlameEffect->GetIsDestroy()) {
			mFlameEffect->Release();
			SafeDelete(mFlameEffect)
		}
	}
}

void Skill_FireBall::Render()
{
	mImage->SetAngle(mAngle * -(180 / PI));
	mImage->SetScale(2.f);
	if (mFlameEffect != nullptr) mFlameEffect->Render();
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}

void Skill_FireBall::AnimationSet(Animation ** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);
}

void Skill_FireBall::AnimationChange(Animation * changeAnimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeAnimation;
	mCurrentAnimation->Play();
}