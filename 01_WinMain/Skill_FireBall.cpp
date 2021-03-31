#include "pch.h"
#include "Skill_FireBall.h"
#include "Image.h"
#include "Player.h"
#include "Monster_FireBoss.h"
#include "Animation.h"
#include "Camera.h"
#include "Effect_HitSpark.h"

Skill_FireBall::Skill_FireBall(const string & name, float x, float y, float angle)
	:SkillObject(name)
{

	mX = x;
	mY = y;
	mAngle = angle;
	mSkillArcana = SkillArcana::Signature;
	mSkillTarget = SkillTarget::Player;
	mSkillElement = SkillElement::Fire;
	mSkillType = SkillType::Throw;
	mSkillDamege = 5;
	mSkillPower = 10.f;
	mSkillCool = 3.f;
}

Skill_FireBall::Skill_FireBall(const string & name, float x, float y, float angle, int delay)
	: SkillObject(name)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mDelay = delay;
	mSkillDamege = 5;
	mSkillTarget = SkillTarget::Enemy;
	mSkillElement = SkillElement::Fire;
	mSkillType = SkillType::Throw;
}

void Skill_FireBall::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireBall", Resources(L"Skill/FireBall.png"), 9, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"FireBall");
	mSizeX = mImage->GetWidth() / 9;
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 10.f;

	AnimationSet(&mFireBallReadyAnimation, false, false, 0, 0, 4, 0, 0.1f);
	AnimationSet(&mFireBallFireAnimation, false, true, 4, 0, 8, 0, 0.1f);

	mState = FireBallState::Ready;
	mCurrentAnimation = mFireBallReadyAnimation;
	mCurrentAnimation->Play();

	mStartX = mX;
	mStartY = mY;
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

	float distance = Math::GetDistance(mStartX, mStartY, mX, mY);

	if (distance > 700) mIsDestroy = true;

	mCurrentAnimation->Update();

	if (mState == FireBallState::Ready && mCurrentAnimation->GetNowFrameX() == 4) {
		if (mDelay < 0) {
			mState = FireBallState::Fire;
			AnimationChange(mFireBallFireAnimation);
			SoundPlayer::GetInstance()->Play(L"FireBallCast", 1.f);
			ParticleManager::GetInstance()->MakeFireCircleParticle(mX, mY);
			ParticleManager::GetInstance()->MakeHitSparkParticle(mX, mY);
			
		}
	}

	if (mState == FireBallState::Fire) {
		mX += cosf(mAngle) * mSpeed;
		mY += -sinf(mAngle) * mSpeed;
		mRect = RectMake(mX, mY, mSizeX, mSizeY);
	}
}

void Skill_FireBall::Render()
{
	mImage->SetAngle(mAngle * -(180 / PI));
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
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
