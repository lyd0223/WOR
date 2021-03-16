#include "pch.h"
#include "FireBoss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"
#include "FireWing.h"
#include "Flame.h"

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

	mSizeX = mImage->GetWidth() / 12;
	mSizeY = mImage->GetHeight() / 10;

	AnimationSet(&mLeftIdleAnimation, false, true, 0, 1, 0, 1, 0.2f);
	AnimationSet(&mRightIdleAnimation, false, true, 0, 0, 0, 0, 0.2f);

	AnimationSet(&mLeftDashStartAnimation, false, true, 1, 1, 1, 1, 0.1f);
	AnimationSet(&mRightDashStartAnimation, false, true, 0, 1, 0, 1, 0.1f);

	AnimationSet(&mLeftDashAnimation, false, true, 2, 1, 2, 1, 0.1f);
	AnimationSet(&mRightDashAnimation, false, true, 2, 0, 2, 0, 0.1f);
	AnimationSet(&mUpDashAnimation, false, true, 4, 0, 4, 0, 0.1f);
	AnimationSet(&mDownDashAnimation, false, true, 4, 1, 4, 1, 0.1f);

	AnimationSet(&mLeftDashEndAnimation, false, true, 3, 1, 3, 1, 0.1f);
	AnimationSet(&mRightDashEndAnimation, false, true, 4, 0, 4, 0, 0.1f);

	AnimationSet(&mLeftSpecialAttackAnimation, false, false, 9, 1, 11, 1, 0.1f);
	AnimationSet(&mRightSpecialAttackAnimation,false, false ,9, 0, 11, 0, 0.1f);

	AnimationSet(&mLeftKickAnimation, false, false, 0, 3, 11, 3, 0.05f);
	AnimationSet(&mRightKickAnimation, false, false, 0, 2, 11, 2, 0.05f);

	AnimationSet(&mLeftAttackReadyAnimation, false, false, 0, 5, 1, 5, 0.1f);;
	AnimationSet(&mRightAttackReadyAnimation, false, false, 0, 4, 1, 4, 0.1f);

	AnimationSet(&mLeftThrowAnimation, false, false, 10, 5, 11, 5, 0.5f);
	AnimationSet(&mRightThrowAnimation, false, false, 10, 4, 11, 4, 0.5f);
	AnimationSet(&mUpThrowAnimation, false, false, 10, 7, 11, 7, 0.5f);
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


	mPlayer = (Player*) ObjectManager::GetInstance()->FindObject("Player");
	mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());

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
	function<void(void)> func;
	mCurrentAnimation->Update();

	mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());

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

	if (Input::GetInstance()->GetKeyDown(VK_SPACE)) {
		//FireBallThrowPattern();
		//StempPattern();
		//KickPattern();
		Move();
	}

	if (mPattern == BossPattern::Throw && mCurrentAnimation->GetNowFrameX() == 10) {

	}

	if (mPattern == BossPattern::Kick) {

		if (mCurrentAnimation->GetNowFrameX() == 2 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 7) {
			MakeFlame();
		}

		if (mCurrentAnimation->GetNowFrameX() < 9) {
			mX += cosf(mKickAngle) * 5.f;
			mY += -sinf(mKickAngle) * 5.f;
		}
		else {
			mX += cosf(mKickAngle) * 20.f;
			mY += -sinf(mKickAngle) * 20.f;
		}

		if (mCurrentAnimation->GetNowFrameX() == 11)	mPattern = BossPattern::Idle;
	}

	if (mPattern == BossPattern::Dash) {
		mMoveDistance++;
		mX += cosf(mAngle) * 10.f;
		mY += -sinf(mAngle) * 10.f;

		float width = mX - mPlayer->GetX();
		float height = mY - mPlayer->GetY();
		float distance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY());

		if (width > height) {
			if (mX > mPlayer->GetX()) {
				AnimationChange(mLeftDashAnimation);
			}
			else {
				AnimationChange(mRightDashAnimation);
			}
		}
		else {
			if (mY > mPlayer->GetY()) {
				AnimationChange(mUpDashAnimation);
			}
			else {
				AnimationChange(mDownDashAnimation);
			}
		}

		if (distance < 100) {
			if (mX < mPlayer->GetX()) AnimationChange(mRightDashEndAnimation);
			else AnimationChange(mLeftDashEndAnimation);
			KickPattern();
		}

		if (mMoveDistance > 5) {
			mMoveDistance = 0;
			Flame* flame = new Flame("Flame", mX, mY, 0.f);
			flame->SetEndPositionX(0);
			flame->SetEndPositionY(0);
			flame->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, flame);
		}
	}
}

void FireBoss::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
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

void FireBoss::Move()
{
	mPattern = BossPattern::Dash;
}

void FireBoss::AttckReady()
{
	if (mX < mPlayer->GetX()) AnimationChange(mRightAttackReadyAnimation);
	else AnimationChange(mLeftAttackReadyAnimation);

	mPattern = BossPattern::AttackReady;

	FireWing* fireWing = new FireWing("FireWing", mX, mY);
	fireWing->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, fireWing);
}

void FireBoss::StempPattern()
{
	if (mX < mPlayer->GetX()) AnimationChange(mRightStempAnimation);
	else AnimationChange(mLeftStempAnimation);

	mPattern = BossPattern::Stemp;
	if (mCurrentAnimation->GetNowFrameX() == 10) {
		for (int i = 1; i < 5; i++) {
			float x = mPlayer->GetX() + cosf(PI / 4 * i * 2 + 45) * 150;
			float y = mPlayer->GetY() - sinf(PI / 4 * i * 2 + 45) * 150;
			int randomX = Random::GetInstance()->RandomInt(x - 50, x + 50);
			int randomY = Random::GetInstance()->RandomInt(y - 50, y + 50);
			SkillManager::GetInstance()->FlameSkill("Flame", randomX, randomY, mAngle);
		}
		SkillManager::GetInstance()->FlameSkill("Flame", mPlayer->GetX(), mPlayer->GetY(), mAngle);
	}
}

void FireBoss::ThreeRushPattern()
{

}

void FireBoss::FireBallThrowPattern()
{
	float width = mX - mPlayer->GetX();
	float height = mY - mPlayer->GetY();

	mPattern = BossPattern::Throw;
	if (width > height) {
		if (mX > mPlayer->GetX()) {
			AnimationChange(mLeftThrowAnimation);
		}
		else {
			AnimationChange(mRightThrowAnimation);
		}
	}
	else {
		if (mY > mPlayer->GetY()) {
			AnimationChange(mUpThrowAnimation);
		}
		else {
			AnimationChange(mDownThrowAnimation);
		}
	}
	
	for (int i = 0; i < 5; i++) {
		float x = mX + (cosf(mAngle - PI / 2 + PI / 4 * i) * 100);
		float y = mY - (sinf(mAngle - PI / 2 + PI / 4 * i) * 100);

		SkillManager::GetInstance()->FireBallSkill("FireBall", x, y, mAngle);
	}
}

void FireBoss::MeteorPattern()
{
	// 보스 맵이 있으면 보스맵 사이즈만큼 랜덤값 

	for (int i = 0; i < 25; i++) {
		float randomX = 0;
		float randomY = 0;
		SkillManager::GetInstance()->MeteorSkill("Meteor", randomX, randomY);
	}
}

void FireBoss::DragonArcWavePattern()
{

}

void FireBoss::KickPattern()
{
	if (mX < mPlayer->GetX()) AnimationChange(mRightKickAnimation);
	else AnimationChange(mLeftKickAnimation);

	mPattern = BossPattern::Kick;
	mKickAngle = mAngle;
}

void FireBoss::MakeFlame()
{
	for (int i = 0; i < 18; i++) {
		float x = mX + (cosf(mKickAngle - PI / 2 + PI / 18 * i) * 100);
		float y = mY - (sinf(mKickAngle - PI / 2 + PI / 18 * i) * 100);

		SkillManager::GetInstance()->KickFlame("KickFlame" + i, x, y, mKickAngle);
	}
}