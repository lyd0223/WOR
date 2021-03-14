#include "pch.h"
#include "FireBall.h"
#include "Image.h"
#include "Player.h"
#include "FireBoss.h"
#include "Animation.h"

FireBall::FireBall(const string & name, float x, float y, float angle)
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
	// ���⼭ �������൵ �ȵ��ư�
	
}

void FireBall::Init()
{
	//��������?
	
	// �̹����� ó�� ���� �ɶ� �ȵ��ư�
	// �״ϱ� ���� ���̾ ������Ǵ°���?
	// ��������

	AnimationSet(&mFireBallReadyAnimation, false, false, 0, 0, 3, 0, 0.1f);
	AnimationSet(&mFireBallFireAnimation, false, true, 4, 0, 8, 0, 0.1f);

	mState = FireBallState::Ready;
	mCurrentAnimation = mFireBallReadyAnimation;
	mCurrentAnimation->Play();
}

void FireBall::Release()
{
	SafeDelete(mFireBallReadyAnimation);
	SafeDelete(mFireBallFireAnimation);
}

void FireBall::Update()
{
	mCurrentAnimation->Update();
	if (mState == FireBallState::Ready && mCurrentAnimation->GetNowFrameX() == 3) {
		mState = FireBallState::Fire;
		AnimationChange(mFireBallFireAnimation);
	}

	if (mState == FireBallState::Fire) {
		mX += cosf(mAngle) * mSpeed;
		mY += -sinf(mAngle) * mSpeed;
		mRect = RectMake(mX, mY, mSizeX, mSizeY);
	}
}

void FireBall::Render(HDC hdc)
{
	mImage->SetAngle(mAngle * -(180 / PI));
	mImage->SetScale(1.f);
	mImage->FrameRender(mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}

void FireBall::AnimationSet(Animation ** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);
}

void FireBall::AnimationChange(Animation * changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}