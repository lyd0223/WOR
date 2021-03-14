#include "pch.h"
#include "FireBoss.h"
#include "Image.h"
#include "Animation.h"

FireBoss::FireBoss(const string& name, float x, float y)
	:Enemy(name)
{
	mX = x;
	mY = y;
}

void FireBoss::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireBoss", Resources(L"Enemy/FireBoss/FireBoss.png"), 12, 10);
	mImage = ImageManager::GetInstance()->FindImage(L"FireBoss");

	mSizeX = 100;
	mSizeY = 100;
	mImage->SetSize(Vector2(mSizeX, mSizeY));

	AnimationSet(&mLeftIdleAnimation, false, true, 0, 1, 0, 1, 0.2f);
	AnimationSet(&mRightIdleAnimation, false, true, 0, 0, 0, 0, 0.2f);
	AnimationSet(&mLeftDashAnimation, false, true, 1, 1, 2, 1, 0.1f);
	AnimationSet(&mRightDashAnimation, false, true, 1, 0, 2, 0, 0.1f);
	AnimationSet(&mUpDashAnimation, false, true, 4, 0, 4, 0, 0.1f);
	AnimationSet(&mDownDashAnimation, false, true, 4, 1, 4, 1, 0.1f);
	AnimationSet(&mLeftDashEndAnimation, false, true, 3, 1, 3, 1, 0.1f);
	AnimationSet(&mRightDashEndAnimation, false, true, 4, 0, 4, 0, 0.1f);
	AnimationSet(&mLeftSpecialAttackAnimation, false, false, 9, 1, 11, 1, 0.1f);
	AnimationSet(&mRightSpecialAttackAnimation,false, false ,9, 0, 11, 0, 0.1f);
	AnimationSet(&mLeftKickAnimation, false, false, 0, 3, 11, 3, 0.1f);
	AnimationSet(&mRightKickAnimation, false, false, 0, 2, 11, 2, 0.1f);
	AnimationSet(&mLeftAttackReadyAnimation, false, false, 0, 5, 3, 5, 0.1f);;
	AnimationSet(&mRightAttackReadyAnimation, false, false, 0, 4, 3, 4, 0.1f);
	AnimationSet(&mLeftThrowAnimation, false, false, 10, 5, 11, 5, 0.5f);
	AnimationSet(&mRightThrowAnimation, false, false, 10, 4, 11, 4, 0.5f);
	AnimationSet(&mUpDashAnimation, false, false, 10, 7, 11, 7, 0.5f);
	AnimationSet(&mDownThrowAnimation, false, false, 10, 6, 11, 6, 0.5f);
	AnimationSet(&mLeftStunAnimation, false, true, 0, 7, 4, 7, 0.3f);
	AnimationSet(&mRightStunAnimation, false, true, 0, 6, 4, 6, 0.3f);
	AnimationSet(&mRefreshAnimation1, false, true, 0, 8, 6, 8, 0.2f);
	AnimationSet(&mRefreshAnimation2, false, false, 0, 9, 6, 9, 0.2f);
	AnimationSet(&mLeftStempAnimation, false, false, 10, 9, 11, 9, 0.7f);
	AnimationSet(&mRightStempAnimation, false, false, 10, 8, 11, 8, 0.7f);

	mCurrentAnimation = mLeftIdleAnimation;
	mPattern = BossPattern::Idle;
	mCurrentAnimation->Play();
}

void FireBoss::Release()
{
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftDashAnimation);
	SafeDelete(mRightDashAnimation);
	SafeDelete(mUpDashAnimation);
	SafeDelete(mDownDashAnimation);
	SafeDelete(mLeftDashEndAnimation);
	SafeDelete(mRightDashEndAnimation);
	SafeDelete(mLeftSpecialAttackAnimation);
	SafeDelete(mRightSpecialAttackAnimation);
	SafeDelete(mLeftKickAnimation);
	SafeDelete(mRightKickAnimation);
	SafeDelete(mLeftAttackReadyAnimation);
	SafeDelete(mRightAttackReadyAnimation);
	SafeDelete(mLeftThrowAnimation);
	SafeDelete(mRightThrowAnimation);
	SafeDelete(mUpThrowAnimation);
	SafeDelete(mDownThrowAnimation);
	SafeDelete(mLeftStunAnimation);
	SafeDelete(mRightStunAnimation);
	SafeDelete(mRefreshAnimation1);
	SafeDelete(mRefreshAnimation2);
	SafeDelete(mLeftStempAnimation);
	SafeDelete(mRightStempAnimation);
}

void FireBoss::Update()
{
	mCurrentAnimation->Update();

	if(Input::GetInstance()->GetKey(VK_DOWN)) {
		mY += 10;
	}
	if (Input::GetInstance()->GetKey(VK_LEFT)) {
		mX -= 10;
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT)) {
		mX += 10;
	}
	if (Input::GetInstance()->GetKey(VK_UP)) {
		mY -= 10;
	}

}

void FireBoss::Render(HDC hdc)
{
	mImage->SetScale(1.5f);
	mImage->FrameRender(mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	wstring AnimationXstr = to_wstring(mCurrentAnimation->GetNowFrameX());
	wstring AnimationYstr = to_wstring(mCurrentAnimation->GetNowFrameY());
	TextOut(hdc, 5, 5, AnimationXstr.c_str(), AnimationXstr.length());
	TextOut(hdc, 5, 20, AnimationYstr.c_str(), AnimationYstr.length());
}

void FireBoss::AnimationSet(Animation ** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);
}

void FireBoss::AnimationChange(Animation * changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}
