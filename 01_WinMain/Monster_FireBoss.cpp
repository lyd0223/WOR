#include "pch.h"
#include "Monster_FireBoss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"
#include "Effect_FireWing.h"
#include "Skill_Flame.h"
#include "Skill_FireBall.h"
#include "TileMap.h"
#include "Tile.h"

Monster_FireBoss::Monster_FireBoss(const string& name, float x, float y)
	:MonsterObject(name)
{
	mX = x;
	mY = y;
}

void Monster_FireBoss::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireBoss", Resources(L"Enemy/FireBoss/FireBoss.png"), 12, 10);
	mImage = ImageManager::GetInstance()->FindImage(L"FireBoss");

	mSizeX = mImage->GetWidth() / 12;
	mSizeY = mImage->GetHeight() / 10 * 2;

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

	AnimationSet(&mLeftKickAnimation, false, false, 0, 3, 11, 3, 0.1f);
	AnimationSet(&mRightKickAnimation, false, false, 0, 2, 11, 2, 0.1f);

	AnimationSet(&mLeftAttackReadyAnimation, false, false, 0, 5, 1, 5, 0.1f);;
	AnimationSet(&mRightAttackReadyAnimation, false, false, 0, 4, 1, 4, 0.1f);

	AnimationSet(&mLeftThrowAnimation, false, false, 10, 5, 11, 5, 0.5f);
	AnimationSet(&mRightThrowAnimation, false, false, 10, 4, 11, 4, 0.5f);
	AnimationSet(&mUpThrowAnimation, false, false, 10, 7, 11, 7, 0.5f);
	AnimationSet(&mDownThrowAnimation, false, false, 10, 6, 11, 6, 0.5f);

	AnimationSet(&mLeftStunAnimation, false, true, 0, 7, 4, 7, 0.2f);
	AnimationSet(&mRightStunAnimation, false, true, 0, 6, 4, 6, 0.2f);

	AnimationSet(&mRefreshAnimation1, false, true, 0, 8, 6, 8, 0.1f);
	AnimationSet(&mRefreshAnimation2, false, true, 0, 9, 6, 9, 0.1f);

	AnimationSet(&mLeftStempAnimation, false, false, 10, 9, 11, 9, 0.7f);
	AnimationSet(&mRightStempAnimation, false, false, 10, 8, 11, 8, 0.7f);

	mMonsterType = MonsterType::Boss;
	mCurrentAnimation = mLeftIdleAnimation;
	mFireBossState = FireBossState::Idle;
	mCurrentAnimation->Play();

	mHitCount = 0;
	mHp = 500;
	mMapRect = RectMake(10 * TileSize, 8 * TileSize, 20 * TileSize, 16 * TileSize);

	mPlayer = (Player*) ObjectManager::GetInstance()->FindObject("Player");
	mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
}

void Monster_FireBoss::Release()
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

void Monster_FireBoss::Update()
{
	mCurrentAnimation->Update();

	mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());

	TileMap* tilemap = (TileMap*)ObjectManager::GetInstance()->FindObject("TileMap");
	vector<vector<Tile*>> tilelist = tilemap->GetTileList();

	D2D1_RECT_F temp;
	for (int y = mY / TileSize - 1; y < mY / TileSize + 1; y++)
	{
		for (int x = mX / TileSize - 1; x < mX / TileSize + 1; x++)
		{
			if (tilelist[y][x]->GetType() == Type::Wall)
			{
				D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
				D2D1_RECT_F tempRect;
				if (tilelist[y][x]->GetType() == Type::Wall)
				{
					if (IntersectRect(tempRect, &tileRect, &mRect))
					{
						if (y == (int)mY / TileSize && x == (int)mX / TileSize - 1)
							mX = tileRect.right + mSizeX / 2;
						else if (y == (int)mY / TileSize && x == (int)mX / TileSize + 1)
							mX = tileRect.left - mSizeX / 2;
						else if (y == (int)mY / TileSize - 1 && x == (int)mX / TileSize)
							mY = tileRect.bottom + mSizeY / 2;
						else if (y == (int)mY / TileSize + 1 && x == (int)mX / TileSize)
							mY = tileRect.top - mSizeY / 2;


					}
				}
			}
		}
	}

	//if (Input::GetInstance()->GetKeyDown('9')) {
	//	DragonArcWavePattern();
	//}

	if (mCurrentAnimation == mRightIdleAnimation || mCurrentAnimation == mLeftIdleAnimation)
	{
		mFrameCount += Time::GetInstance()->DeltaTime();
		
		if (mFrameCount > 1.5)
		{
			mFrameCount = 0;
			MakePatternList();
		}
	}

	if (!mPatternList.empty())
	{
		switch (mPatternList.front())
		{
		case FireBossState::AttackReady:
			AttackReady();
			break;
		case FireBossState::Dash:
			Move();
			break;
		case FireBossState::Kick:
			KickPattern();
			break;
		case FireBossState::Throw:
			FireBallThrowPattern();
			break;
		case FireBossState::Stemp:
			StempPattern();
			break;
		case FireBossState::Stun:
			Stun();
			break;
		case FireBossState::Refresh:
			Refresh();
			break;
		}
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Monster_FireBoss::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	wstring str = to_wstring(mHp);
	D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, 20, str, 20);
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMapRect, D2D1::ColorF::Aqua);
}

void Monster_FireBoss::AnimationSet(Animation ** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);
}

void Monster_FireBoss::AnimationChange(Animation * changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}

void Monster_FireBoss::Move()
{
	if (mCurrentAnimation == mRightDashEndAnimation ||
		mCurrentAnimation == mLeftDashEndAnimation)
	{
		mFrameCount += Time::GetInstance()->DeltaTime();
		if (mFrameCount > 0.2)
		{
			mFrameCount = 0;
			mPatternList.pop();
			mIsWing = false;
		}
		return;
	}

	mFireBossState = FireBossState::Dash;
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

	mMoveDistance++;
	if (mMoveDistance > 5) {
		mMoveDistance = 0;
		Skill_Flame* flame = new Skill_Flame("Flame", mX, mY, 0.f);
		flame->SetEndPositionX(0);
		flame->SetEndPositionY(0);
		flame->SetAlpha(0.7f);
		flame->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, flame);
	}

	if (distance < 100) {
		if (mIsWing == false)
		{
			MakeFireWing(mX, mY + 20);
			mIsWing = true;
		}
		if (mX < mPlayer->GetX()) AnimationChange(mRightDashEndAnimation);
		else AnimationChange(mLeftDashEndAnimation);
	}
}

void Monster_FireBoss::AttackReady()
{
	mFrameCount += Time::GetInstance()->DeltaTime();
	if (mX < mPlayer->GetX()) AnimationChange(mRightAttackReadyAnimation);
	else AnimationChange(mLeftAttackReadyAnimation);



	if (mIsWing == false)
	{
		Effect_FireWing* fireWing = new Effect_FireWing("FireWing", mX, mY - 80);
		fireWing->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, fireWing);
		ParticleManager::GetInstance()->MakeShorkWaveParticle(mX, mRect.bottom, 1.5f);
		mFireBossState = FireBossState::AttackReady;
		mIsWing = true;
	}

	if (mFrameCount > 0.5)
	{
		mFrameCount = 0;
		mPatternList.pop();
		mIsWing = false;
	}
}

void Monster_FireBoss::StempPattern()
{
	if (mX < mPlayer->GetX()) AnimationChange(mRightStempAnimation);
	else AnimationChange(mLeftStempAnimation);

	mFireBossState = FireBossState::Stemp;
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

void Monster_FireBoss::ThreeRushPattern()
{

}

void Monster_FireBoss::FireBallThrowPattern()
{
	mFrameCount += Time::GetInstance()->DeltaTime();

	float width = mX - mPlayer->GetX();
	float height = mY - mPlayer->GetY();

	if (mFireBossState != FireBossState::Throw)
	{
		if (width > height) 
		{
			if (mX > mPlayer->GetX()) 
			{
				AnimationChange(mLeftThrowAnimation);
			}
			else 
			{
				AnimationChange(mRightThrowAnimation);
			}
		}
		else 
		{
			if (mY > mPlayer->GetY()) 
			{
				AnimationChange(mUpThrowAnimation);
			}
			else 
			{
				AnimationChange(mDownThrowAnimation);
			}
		}

		mFireBossState = FireBossState::Throw;
	}

	if (mIsFireBall == false)
	{
		for (int i = 0; i < 5; i++) 
		{
			float x = mX + (cosf(mAngle - PI / 2 + PI / 4 * i) * 100);
			float y = mY - (sinf(mAngle - PI / 2 + PI / 4 * i) * 100);

			Skill_FireBall* fireBall = new Skill_FireBall("FireBall", x, y, mAngle, i * 20);
			fireBall->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, fireBall);
		}
		mIsFireBall = true;

	}

	if (mFrameCount > 2)
	{
		mFrameCount = 0;
		mIsFireBall = false;
		mPatternList.pop();
	}
}

void Monster_FireBoss::MeteorPattern()
{
	float mapCenterX = mMapRect.left + (mMapRect.right - mMapRect.left) / 2;
	float mapCenterY = mMapRect.top + (mMapRect.bottom - mMapRect.right) / 2;
	float angle = Math::GetAngle(mX, mY, mapCenterX, mapCenterY);



	for (int i = 0; i < 25; i++) {
		float randomX = Random::GetInstance()->RandomInt(mMapRect.left, mMapRect.right);
		float randomY = Random::GetInstance()->RandomInt(mMapRect.top, mMapRect.bottom);
		SkillManager::GetInstance()->MeteorSkill("Meteor", randomX, randomY);
	}
}

void Monster_FireBoss::DragonArcWavePattern()
{
	int random = Random::GetInstance()->RandomInt(4);

	if (mIsOneCheck == false)
	{
		SoundPlayer::GetInstance()->Play(L"FireChargeup", 1.f);

		switch (random)
		{
		case 0:	// 辑率
			mX = mMapRect.left + 30;
			mY = Random::GetInstance()->RandomInt(mMapRect.top + 30, mMapRect.bottom - 30);
			break;
		case 1: // 合率
			mX = Random::GetInstance()->RandomInt(mMapRect.left + 30, mMapRect.right - 30);
			mY = mMapRect.top + 30;
			break;
		case 2:	// 悼率
			mX = mMapRect.right - 30;
			mY = Random::GetInstance()->RandomInt(mMapRect.top + 30, mMapRect.bottom - 30);
			break;
		case 3:	// 巢率
			mX = Random::GetInstance()->RandomInt(mMapRect.left + 30, mMapRect.right - 30);
			mY = mMapRect.bottom - 30;
			break;
		}

		//mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		//POINT temp;
		//switch (random)
		//{
		//case 0:
		//	temp.x;
		//	temp.y;
		//	break;
		//case 1:
		//	temp.x;
		//	temp.y;
		//	break;
		//case 2:
		//	temp.x;
		//	temp.y;
		//	break;
		//case 3:
		//	temp.x;
		//	temp.y;
		//	break;
		//}

		//float distance = Math::GetDistance(mX, mY, temp.x, temp.y);

		//for (int i = 0; i < distance / 5; i++)
		//{
		//	float x = mX + cosf(mAngle) * (i * 20);
		//	float y = mY + -sinf(mAngle) * (i * 20);
		//	Skill_Flame* flame = new Skill_Flame("Flame", x, y, 0);
		//	flame->Init();
		//	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, flame);
		//}
	}

	mX += cosf(mAngle);
}

void Monster_FireBoss::KickPattern()
{
	if (mCurrentAnimation->GetNowFrameX() == 11) {
		mFrameCount += Time::GetInstance()->DeltaTime();

		if (mFrameCount > 0.5f)
		{
			mFireBossState = FireBossState::Idle;
			mPatternList.pop();
		}
	}
	
	if (mFireBossState != FireBossState::Kick) {
		if (mX < mPlayer->GetX()) AnimationChange(mRightKickAnimation);
		else AnimationChange(mLeftKickAnimation);

		mFireBossState = FireBossState::Kick;
		mKickAngle = mAngle;
	}

	if (mCurrentAnimation->GetNowFrameX() == 2 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 7) {
		MakeFlame();
	}

	if (mCurrentAnimation->GetNowFrameX() < 9) {
		mX += cosf(mKickAngle) * 5.f;
		mY += -sinf(mKickAngle) * 5.f;
	}
	else {
		mX += cosf(mKickAngle) * 5.f;
		mY += -sinf(mKickAngle) * 5.f;
	}

}

void Monster_FireBoss::MakeFlame()
{
	for (int i = 0; i < 12; i++) {
		float x = mX + (cosf(mKickAngle - PI / 2 + PI / 12 * i) * 150);
		float y = mY - (sinf(mKickAngle - PI / 2 + PI / 12 * i) * 150);
		float endY = mY - (sinf(mKickAngle - PI / 2 + PI / 12 * i) * 300);
		float endX = mX + (cosf(mKickAngle - PI / 2 + PI / 12 * i) * 300);
		SkillManager::GetInstance()->KickFlame("KickFlame" + i, x, y, mKickAngle, endX, endY);
	}
}

void Monster_FireBoss::MakeFireWing(float x, float y)
{
	mFireWing = new Effect_FireWing("FireWing", x, y);
	mFireWing->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, mFireWing);
}

void Monster_FireBoss::Refresh()
{
	mFrameCount += Time::GetInstance()->DeltaTime();

	if (mIsHitCountChange == false)
	{
		mHitCount = mHp;
		mIsHitCountChange = true;
	}

	if (mCurrentAnimation != mRefreshAnimation1 &&
		mCurrentAnimation != mRefreshAnimation2)
	{
		AnimationChange(mRefreshAnimation1);
		SoundPlayer::GetInstance()->Play(L"FireBossFlex0", 1.f);
	}

	if (mFrameCount > 1 && mIsRefreshChange == false)
	{
		mIsRefreshChange = true;
		mFrameCount = 0;
		AnimationChange(mRefreshAnimation2);
		SoundPlayer::GetInstance()->Play(L"FireBossFlex1", 1.f);
	}

	if (mCurrentAnimation == mRefreshAnimation2 && mFrameCount > 1)
	{
		if (mX < mPlayer->GetX()) AnimationChange(mRightIdleAnimation);
		else AnimationChange(mLeftIdleAnimation);

		mPatternList.pop();
		mIsRefreshChange = false;
		mFrameCount = 0;
	}

	if (mHitCount - mHp > 20)
	{
		mFrameCount = 0;
		mHitCount = 0;
		mPatternList.push(FireBossState::Stun);
		mPatternList.pop();
	}
}

void Monster_FireBoss::Stun()
{
	mFrameCount += Time::GetInstance()->DeltaTime();
	if (mCurrentAnimation != mRightStunAnimation && mCurrentAnimation != mLeftStunAnimation)
	{
		if (mX < mPlayer->GetX()) AnimationChange(mRightStunAnimation);
		else AnimationChange(mLeftStunAnimation);
	}

	if (mCurrentAnimation->GetNowFrameX() == mCurrentAnimation->GetMaxIndex())
	{
		if (mCurrentAnimation == mRightStunAnimation) AnimationChange(mLeftStunAnimation);
		else if (mCurrentAnimation == mLeftStunAnimation) AnimationChange(mRightStunAnimation);
	}

	if (mFrameCount > 5)
	{
		mFrameCount = 0;
		mIsHitCountChange = false;
		mPatternList.pop();

		if (mX < mPlayer->GetX()) AnimationChange(mRightIdleAnimation);
		else AnimationChange(mLeftIdleAnimation);
	}


}

void Monster_FireBoss::MakePatternList()
{
	while (!mPatternList.empty())
	{
		mPatternList.pop();
	}

	mPatternList.push(FireBossState::AttackReady);
	mPatternList.push(FireBossState::Dash);
	mPatternList.push(FireBossState::Kick);
	mPatternList.push(FireBossState::Throw);
	mPatternList.push(FireBossState::Refresh);
}