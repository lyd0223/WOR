﻿
#include"pch.h"
#include"Image.h"
#include"Animation.h"
#include "Player.h"
#include"Tile.h"
#include "Camera.h"
#include "SkillObject.h"
#include "MouseTracker.h"
#include "PlayerNormalShadow.h"
#include "PlayerHeightShadow.h"
#include "PlayerWideShadow.h"
#include "Skill_SummonIceSpear.h"
#include "Skill_IceSpear.h"
#include"TileMap.h"
#include "Effect_Teleport.h"


Player::Player(const string& name, float x, float y)
	: MovingObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Player::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Player", Resources(L"Player/WizardPlayer.png"), 10, 29);
	mImage = ImageManager::GetInstance()->FindImage(L"Player");
	mPlayerState = PlayerState::DownIdle;
	mSpeed = BasicSpeed;
	mSizeX = mImage->GetWidth() / 10;
	mSizeY = mImage->GetHeight() / 25;
	mAngle = 0.f;
	mHp = 200;
	mMp = 0;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMoveAngle = 0;
	mMovingRect = RectMakeCenter(mX, mY + 50, TileSize, TileSize);


	//ouseTracker::Init(mMovingRect.left + (mMovingRect.right - mMovingRect.left), mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) + 20, mAngle);
	//mDownIdleAnimation = new Animation;
	//mDownIdleAnimation->InitFrameByStartEnd(0, 0, 0, 0, true);
	//mDownIdleAnimation->SetIsLoop(false);
	//mDownIdleAnimation->SetFrameUpdateTime(AnimationTime);
	//

	AnimationSet(&mDownIdleAnimation, true, true, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mUpIdleAnimation, true, true, 1, 0, 1, 0, AnimationTime);
	AnimationSet(&mRightIdleAnimation, true, true, 2, 0, 2, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, true, true, 3, 0, 3, 0, AnimationTime);
	AnimationSet(&mDownHitAnimation, true, true, 4, 0, 4, 0, AnimationTime);
	AnimationSet(&mUpHitAnimation, true, true, 5, 0, 5, 0, AnimationTime);
	AnimationSet(&mLeftHitAnimation, true, true, 6, 0, 6, 0, AnimationTime);
	AnimationSet(&mRightHitAnimation, true, true, 0, 7, 0, 7, AnimationTime);
	AnimationSet(&mDownRunAnimation, false, true, 0, 1, 9, 1, 0.1f);
	AnimationSet(&mUpRunAnimation, false, true, 0, 2, 9, 2, 0.1f);
	AnimationSet(&mRightRunAnimation, false, true, 0, 3, 9, 3, 0.1f);
	AnimationReverseSet(&mLeftRunAnimation, false, true, 9, 4, 0, 4, 0.1f);
	AnimationSet(&mDownAttackAnimation, false, false, 0, 5, 9, 5, 0.05);
	AnimationSet(&mRightDashAnimation, false, false, 0, 7, 9, 7, AnimationTime);
	AnimationSet(&mRightDiagonalUpDashAnimation, false, false, 0, 7, 9, 7, AnimationTime);
	AnimationSet(&mRightDiagonalDownDashAnimation, false, false, 0, 7, 9, 7, AnimationTime);
	AnimationSet(&mLeftDashAnimation, false, false, 0, 8, 9, 8, AnimationTime);
	AnimationSet(&mLeftDiagonalUpDashAnimation, false, false, 0, 8, 9, 8, AnimationTime);
	AnimationSet(&mLeftDiagonalDownDashAnimation, false, false, 0, 8, 9, 8, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 9, 9, 9, AnimationTime);
	AnimationSet(&mUpAttackAnimation, false, false, 0, 11, 9, 11, 0.05);
	AnimationSet(&mDownThrowSkillAnimation, false, false, 0, 6, 9, 6, AnimationTime);
	AnimationSet(&mUpThrowSkillAnimation, false, false, 0, 14, 9, 14, AnimationTime);
	AnimationReverseSet(&mLeftThrowSkillandAttackAnimation, false, false, 7, 13, 0, 13, 0.05);
	AnimationSet(&mRightThrowSkillandAttackAnimation, false, false, 0, 12, 7, 12, 0.05);
	AnimationSet(&mUpDashAnimation, false, false, 0, 18, 9, 18, AnimationTime);
	AnimationSet(&mDownDashAnimation, false, false, 0, 19, 9, 19, AnimationTime);
	AnimationSet(&mUpThrowWatingAnimation, false, false, 1, 14, 1, 14, AnimationTime);
	AnimationSet(&mDownThrowWatingAnimation, false, false, 0, 6, 0, 6, AnimationTime);
	AnimationSet(&mRightThrowWationgAnimation, false, false, 1, 12, 1, 12, AnimationTime);
	AnimationSet(&mLeftThrowWatingAnimation, false, false, 6, 12, 6, 12, AnimationTime);
	AnimationReverseSet(&mUpAttackAnimation2, false, false, 9, 28, 0, 28, 0.05);
	AnimationSet(&mDownAttackAnimation2, false, false, 0, 25, 9, 25, 0.05);
	AnimationSet(&mLeftThrowSkillandAttackAnimation2, false, false, 0, 26, 7, 26, 0.05);
	AnimationReverseSet(&mRightThrowSkillandAttackAnimation2, false, false, 7, 27, 0, 27, 0.05);

	mAttackMotion = 1;
	mCurrentAnimation = mDownIdleAnimation;
	mCurrentAnimation->Play();

	mLB_ButtonSkill = SkillManager::GetInstance()->GetPlayerLBSkill();
	mRB_ButtonSkill = SkillManager::GetInstance()->GetPlayerRBSkill();
	mSpacebar_ButtonSkill = SkillManager::GetInstance()->GetPlayerSpaceSkill();
	mQ_ButtonSkill = SkillManager::GetInstance()->GetPlayerQSkill();
	mSkillStackCount = SkillManager::GetInstance()->GetPlayerSkillStack();

	mIsFalling = 0;
	mYtemp = 0;
	//���콺Ʈ��Ŀ
	if (mMouseTracker == nullptr)
	{
		mMouseTracker = new MouseTracker("MouseTracker", mMovingRect.left + (mMovingRect.right - mMovingRect.left), mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) + 20, mAngle);
		mMouseTracker->Init();
	}
	//
	mSkillStackCount = SkillManager::GetInstance()->FindSkill(mRB_ButtonSkill)->GetSkillStack();
}

void Player::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mDownIdleAnimation);
	SafeDelete(mUpIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mUpHitAnimation);
	SafeDelete(mDownHitAnimation);
	SafeDelete(mLeftRunAnimation);
	SafeDelete(mRightRunAnimation);
	SafeDelete(mDownRunAnimation);
	SafeDelete(mUpRunAnimation);
	SafeDelete(mDownAttackAnimation);
	SafeDelete(mUpAttackAnimation);
	SafeDelete(mLeftDashAnimation);
	SafeDelete(mRightDashAnimation);
	SafeDelete(mDownDashAnimation);
	SafeDelete(mUpDashAnimation);
	SafeDelete(mDieAnimation);
	SafeDelete(mUpThrowSkillAnimation);
	SafeDelete(mDownThrowSkillAnimation);
	SafeDelete(mLeftThrowSkillandAttackAnimation);
	SafeDelete(mRightThrowSkillandAttackAnimation);


}

void Player::Update()
{
	//int indexY = mY / TileSize;
	//int indexX = mX / TileSize;
	//---------------------------------
	if (mIsSkillChange)
	{
		mLB_ButtonSkill = SkillManager::GetInstance()->GetPlayerLBSkill();
		mRB_ButtonSkill = SkillManager::GetInstance()->GetPlayerRBSkill();
		mSpacebar_ButtonSkill = SkillManager::GetInstance()->GetPlayerSpaceSkill();
		mQ_ButtonSkill = SkillManager::GetInstance()->GetPlayerQSkill();
		mSkillStackCount = SkillManager::GetInstance()->GetPlayerSkillStack();
		mIsSkillChange = false;
	}

	mRB_ButtonSkillCool -= Time::GetInstance()->DeltaTime();
	mQ_ButtonSkillCool -= Time::GetInstance()->DeltaTime();
	D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);

	if (mSkillStackCount < SkillManager::GetInstance()->FindSkill(mRB_ButtonSkill)->GetSkillStack())
	{
		mFrameCount += Time::GetInstance()->DeltaTime();
		if (mFrameCount > SkillManager::GetInstance()->FindSkill(mRB_ButtonSkill)->GetSkillCool())
		{
			mFrameCount = 0;
			mSkillStackCount++;
		}
	}
	mFrameCount += Time::GetInstance()->DeltaTime();
	//-----
	//�׸���-------
	if (mHp > 0)
	{


		if (mPlayerNormalShadow == nullptr)
		{
			if (mCurrentAnimation == mDownIdleAnimation || mCurrentAnimation == mRightIdleAnimation || mCurrentAnimation == mLeftIdleAnimation ||
				mCurrentAnimation == mUpIdleAnimation || mCurrentAnimation == mUpHitAnimation || mCurrentAnimation == mDownHitAnimation || mCurrentAnimation == mRightHitAnimation ||
				mCurrentAnimation == mLeftHitAnimation)
			{
				mPlayerNormalShadow = new PlayerNormalShadow("PlayerNormalShadow", mMovingRect.left + (mMovingRect.right - mMovingRect.left), mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) + 30);
				mPlayerNormalShadow->Init();
			}

		}

		if (mPlayerHeightShadow == nullptr)
		{
			if (mCurrentAnimation == mUpThrowWatingAnimation || mCurrentAnimation == mDownThrowWatingAnimation || mCurrentAnimation == mDownAttackAnimation || mCurrentAnimation == mUpAttackAnimation ||
				mCurrentAnimation == mUpThrowSkillAnimation || mCurrentAnimation == mDownThrowSkillAnimation)
			{
				mPlayerHeightShadow = new PlayerHeightShadow("PlayerHeightShadow", mMovingRect.left + (mMovingRect.right - mMovingRect.left), mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) + 30);
				mPlayerHeightShadow->Init();
			}
		}

		if (mPlayerWideShadow == nullptr)
		{
			if (mCurrentAnimation == mUpDashAnimation || mCurrentAnimation == mDownDashAnimation || mCurrentAnimation == mLeftDashAnimation || mCurrentAnimation == mRightDashAnimation ||
				mCurrentAnimation == mRightThrowSkillandAttackAnimation || mCurrentAnimation == mLeftThrowSkillandAttackAnimation || mCurrentAnimation == mRightRunAnimation ||
				mCurrentAnimation == mLeftRunAnimation || mCurrentAnimation == mUpRunAnimation || mCurrentAnimation == mDownRunAnimation || mCurrentAnimation == mRightThrowWationgAnimation
				|| mCurrentAnimation == mLeftThrowWatingAnimation)
			{
				mPlayerWideShadow = new PlayerWideShadow("PlayerWideShadow", mMovingRect.left + (mMovingRect.right - mMovingRect.left), mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) + 30);
				mPlayerWideShadow->Init();
			}
		}
		if ((mPlayerState != PlayerState::DownIdle && mPlayerState != PlayerState::LeftIdle &&
			mPlayerState != PlayerState::RightIdle && mPlayerState != PlayerState::UpIdle && mPlayerState != PlayerState::DownHit
			&& mPlayerState != PlayerState::UpHit && mPlayerState != PlayerState::RightHit && mPlayerState != PlayerState::LeftHit))
		{
			{
				SafeDelete(mPlayerNormalShadow)
			}
		}
		if ((mPlayerState != PlayerState::UpThrowWating && mPlayerState != PlayerState::DownThorwWating &&
			mPlayerState != PlayerState::DownAttack && mPlayerState != PlayerState::UpAttack && mPlayerState != PlayerState::UpThrowSkill
			&& mPlayerState != PlayerState::DownThorwWating))
		{
			{
				SafeDelete(mPlayerHeightShadow)
			}
		}
		if ((mPlayerState != PlayerState::UpDash && mPlayerState != PlayerState::DownDash &&
			mPlayerState != PlayerState::LeftDash && mPlayerState != PlayerState::RightDash && mPlayerState != PlayerState::RightThrowSkillandAttack
			&& mPlayerState != PlayerState::LeftThrowSkillandAttack && mPlayerState != PlayerState::RightRun && mPlayerState != PlayerState::LeftRun && mPlayerState != PlayerState::UpRun
			&& mPlayerState != PlayerState::DownRun && mPlayerState != PlayerState::RightAttack && mPlayerState != PlayerState::LeftAttack && mPlayerState != PlayerState::LeftThrowWaitng
			&& mPlayerState != PlayerState::RightThrowWating))
		{
			{
				SafeDelete(mPlayerWideShadow)
			}
		}
		//��Ű
		if (!mIsFalling)
		{
			if (Input::GetInstance()->GetKey('W') && !Input::GetInstance()->GetKey('D') && !Input::GetInstance()->GetKey('A') && mCurrentAnimation != mUpDashAnimation)
			{
				if (mPlayerState == PlayerState::UpRun || mPlayerState == PlayerState::UpIdle || mPlayerState == PlayerState::RightRun || mPlayerState == PlayerState::LeftRun)
				{
					mPlayerState = PlayerState::UpRun;

					if (mCurrentAnimation != mUpRunAnimation && mCurrentAnimation != mLeftRunAnimation && mCurrentAnimation != mRightRunAnimation) AnimationChange(mUpRunAnimation);
					mMoveAngle = PI / 2;
					mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();

					if (Input::GetInstance()->GetKeyDown('A'))
					{
						if (mCurrentAnimation == mUpRunAnimation && mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
						mPlayerState = PlayerState::LeftRun;
					}
					if (Input::GetInstance()->GetKey('A'))
					{
						mMoveAngle = PI;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}

					if (Input::GetInstance()->GetKeyDown('D'))
					{
						if (mCurrentAnimation == mUpRunAnimation && mCurrentAnimation != mRightRunAnimation) AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;
					}
					if (Input::GetInstance()->GetKey('D'))
					{
						mMoveAngle = 0;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}

					if (Input::GetInstance()->GetKey('S'))
					{
						mMoveAngle = PI / 2 + PI;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						if (mCurrentAnimation != mUpIdleAnimation) AnimationChange(mUpIdleAnimation);
						mPlayerState = PlayerState::UpIdle;
					}
					if (Input::GetInstance()->GetKeyUp('S'))
					{
						if (mCurrentAnimation != mUpRunAnimation) AnimationChange(mUpRunAnimation);
						mPlayerState = PlayerState::UpRun;
					}
					if (Input::GetInstance()->GetKeyUp('D'))
					{
						if (mCurrentAnimation != mUpRunAnimation) AnimationChange(mUpRunAnimation);
						mPlayerState = PlayerState::UpRun;
					}
					if (Input::GetInstance()->GetKeyUp('A'))
					{
						if (mCurrentAnimation != mUpRunAnimation) AnimationChange(mUpRunAnimation);
						mPlayerState = PlayerState::UpRun;
					}
				}
			}
			else if (Input::GetInstance()->GetKey('S') && !Input::GetInstance()->GetKey('D') && !Input::GetInstance()->GetKey('A') && mCurrentAnimation != mDownDashAnimation)
			{
				if (mPlayerState == PlayerState::DownRun || mPlayerState == PlayerState::DownIdle || mPlayerState == PlayerState::RightRun || mPlayerState == PlayerState::LeftRun)
				{
					mPlayerState = PlayerState::DownRun;
					if (mCurrentAnimation != mDownRunAnimation && mCurrentAnimation != mLeftRunAnimation && mCurrentAnimation != mRightRunAnimation) AnimationChange(mDownRunAnimation);
					mMoveAngle = PI / 2 + PI;
					mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();


					if (Input::GetInstance()->GetKeyDown('A'))
					{
						if (mCurrentAnimation == mDownRunAnimation && mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
						mPlayerState = PlayerState::LeftRun;
					}
					if (Input::GetInstance()->GetKey('A'))
					{
						mMoveAngle = 0;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}
					if (Input::GetInstance()->GetKeyDown('D'))
					{
						if (mCurrentAnimation == mDownRunAnimation && mCurrentAnimation != mRightRunAnimation) AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;
					}
					if (Input::GetInstance()->GetKey('D'))
					{
						mMoveAngle = 0;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}

					if (Input::GetInstance()->GetKey('W'))
					{
						mMoveAngle = PI / 2;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						if (mCurrentAnimation != mDownIdleAnimation) AnimationChange(mDownIdleAnimation);
						mPlayerState = PlayerState::DownIdle;
					}
					if (Input::GetInstance()->GetKeyUp('W'))
					{
						if (mCurrentAnimation != mDownRunAnimation) AnimationChange(mDownRunAnimation);
						mPlayerState = PlayerState::DownRun;
					}
					if (Input::GetInstance()->GetKeyUp('D'))
					{
						if (mCurrentAnimation != mDownRunAnimation) AnimationChange(mDownRunAnimation);
						mPlayerState = PlayerState::DownRun;
					}
					if (Input::GetInstance()->GetKeyUp('A'))
					{
						if (mCurrentAnimation != mDownRunAnimation) AnimationChange(mDownRunAnimation);
						mPlayerState = PlayerState::DownRun;
					}
				}
			}

			else if (Input::GetInstance()->GetKey('D') && mCurrentAnimation != mRightDashAnimation)
			{

				if (mPlayerState == PlayerState::UpRun || mPlayerState == PlayerState::DownRun || mPlayerState == PlayerState::RightRun || mPlayerState == PlayerState::RightIdle)
				{
					if (mCurrentAnimation != mRightRunAnimation && mCurrentAnimation != mUpRunAnimation && mCurrentAnimation != mDownRunAnimation)
						AnimationChange(mRightRunAnimation);
					mPlayerState = PlayerState::RightRun;
					mMoveAngle = 0;
					mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();


					if (Input::GetInstance()->GetKeyDown('W'))
					{
						/*if (mCurrentAnimation == mRightRunAnimation && mCurrentAnimation != mUpRunAnimation) AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;*/
					}
					if (Input::GetInstance()->GetKey('W'))
					{
						mMoveAngle = PI / 2;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}
					if (Input::GetInstance()->GetKeyDown('S'))
					{
						if (mCurrentAnimation == mDownRunAnimation && mCurrentAnimation != mRightRunAnimation) AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;
					}
					if (Input::GetInstance()->GetKey('S'))
					{
						mMoveAngle = PI / 2 + PI;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}
					if (Input::GetInstance()->GetKey('A'))
					{
						//mX -= mSpeed*cosf(mAngle);
						mMoveAngle = PI;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						if (mCurrentAnimation != mRightIdleAnimation)
							AnimationChange(mRightIdleAnimation);
						mPlayerState = PlayerState::RightIdle;
					}
					if (Input::GetInstance()->GetKeyUp('A'))
					{
						if (mCurrentAnimation != mRightRunAnimation)
							AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;
					}
					if (Input::GetInstance()->GetKeyUp('W'))
					{
						if (mCurrentAnimation != mRightRunAnimation) AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;
					}
					if (Input::GetInstance()->GetKeyUp('S'))
					{
						if (mCurrentAnimation != mRightRunAnimation) AnimationChange(mRightRunAnimation);
						mPlayerState = PlayerState::RightRun;
					}

				}

			}


			else if (Input::GetInstance()->GetKey('A') && mCurrentAnimation != mLeftDashAnimation)
			{
				if (mPlayerState == PlayerState::LeftRun || mPlayerState == PlayerState::LeftIdle || mPlayerState == PlayerState::UpRun || mPlayerState == PlayerState::DownRun)
				{

					if (mCurrentAnimation != mLeftRunAnimation && mCurrentAnimation != mUpRunAnimation && mCurrentAnimation != mDownRunAnimation)
						AnimationChange(mLeftRunAnimation);
					mPlayerState = PlayerState::LeftRun;
					mMoveAngle = PI;
					mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					if (Input::GetInstance()->GetKey('W'))
					{
						mMoveAngle = PI / 2;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}
					if (Input::GetInstance()->GetKeyDown('S'))
					{
						if (mCurrentAnimation == mDownRunAnimation && mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
						mPlayerState = PlayerState::LeftRun;
					}
					if (Input::GetInstance()->GetKey('S'))
					{
						mMoveAngle = PI / 2 + PI;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
					}
					if (Input::GetInstance()->GetKey('D'))
					{
						mMoveAngle = 0;
						mX += cosf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY -= sinf(mMoveAngle) * mSpeed * Time::GetInstance()->DeltaTime();
						if (mCurrentAnimation != mLeftIdleAnimation) AnimationChange(mLeftIdleAnimation);
						mPlayerState = PlayerState::LeftIdle;
					}
					if (Input::GetInstance()->GetKeyUp('D'))
					{
						if (mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
						mPlayerState = PlayerState::LeftRun;
					}
					if (Input::GetInstance()->GetKeyUp('W'))
					{
						if (mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
						mPlayerState = PlayerState::LeftRun;
					}
					if (Input::GetInstance()->GetKeyUp('S'))
					{
						if (mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
						mPlayerState = PlayerState::LeftRun;
					}
				}
			}
			if (!Input::GetInstance()->GetKey('S'))
			{
				if (Input::GetInstance()->GetKeyDown('W') && !Input::GetInstance()->GetKey('D') && !Input::GetInstance()->GetKey('A'))
				{
					if (mCurrentAnimation != mUpRunAnimation) AnimationChange(mUpRunAnimation);
					mPlayerState = PlayerState::UpRun;
				}
			}
			if (!Input::GetInstance()->GetKey('W'))
			{
				if (Input::GetInstance()->GetKeyDown('S') && !Input::GetInstance()->GetKey('D') && !Input::GetInstance()->GetKey('A'))
				{
					if (mCurrentAnimation != mDownRunAnimation) AnimationChange(mDownRunAnimation);
					mPlayerState = PlayerState::DownRun;
				}

			}
			if (!Input::GetInstance()->GetKey('A'))
			{
				if (Input::GetInstance()->GetKeyDown('D'))
				{
					if (mCurrentAnimation != mRightRunAnimation) AnimationChange(mRightRunAnimation);
					mPlayerState = PlayerState::RightRun;
				}
			}
			if (!Input::GetInstance()->GetKey('D'))
			{
				if (Input::GetInstance()->GetKeyDown('A'))
				{
					if (mCurrentAnimation != mLeftRunAnimation) AnimationChange(mLeftRunAnimation);
					mPlayerState = PlayerState::LeftRun;
				}
			}



			// ��Ű��
			if (!Input::GetInstance()->GetKey('S') &&
				!Input::GetInstance()->GetKey('A') &&
				!Input::GetInstance()->GetKey('D'))
			{
				if (Input::GetInstance()->GetKeyUp('W'))
				{
					AnimationChange(mUpIdleAnimation);
					mPlayerState = PlayerState::UpIdle;
				}
			}
			if (!Input::GetInstance()->GetKey('W') &&
				!Input::GetInstance()->GetKey('A') &&
				!Input::GetInstance()->GetKey('D'))
			{
				if (Input::GetInstance()->GetKeyUp('S'))
				{
					AnimationChange(mDownIdleAnimation);
					mPlayerState = PlayerState::DownIdle;
				}
			}
			if (!Input::GetInstance()->GetKey('A') &&
				!Input::GetInstance()->GetKey('W') &&
				!Input::GetInstance()->GetKey('S'))
			{
				if (Input::GetInstance()->GetKeyUp('D'))
				{
					AnimationChange(mRightIdleAnimation);
					mPlayerState = PlayerState::RightIdle;
				}
			}
			if (!Input::GetInstance()->GetKey('D') &&
				!Input::GetInstance()->GetKey('W') &&
				!Input::GetInstance()->GetKey('S'))
			{
				if (Input::GetInstance()->GetKeyUp('A'))
				{
					AnimationChange(mLeftIdleAnimation);
					mPlayerState = PlayerState::LeftIdle;
				}
			}
			//����
			if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{

				if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
				{
					if (mAttackMotion == 1)
					{
						AnimationChange(mRightThrowSkillandAttackAnimation);
						mAttackMotion = 2;
						if(mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle + PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 2)
					{
						AnimationChange(mRightThrowSkillandAttackAnimation2);
						mAttackMotion = 3;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle - PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 3)
					{
						AnimationChange(mRightThrowSkillandAttackAnimation);
						mAttackMotion = 1;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					mPlayerState = PlayerState::RightAttack;
					if (mLB_ButtonSkill == "WindSlash")
						mX += 15;

				}
				else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
				{
					if (mAttackMotion == 1)
					{
						AnimationChange(mUpAttackAnimation);
						mAttackMotion = 2;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle + PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 2)
					{
						AnimationChange(mUpAttackAnimation2);
						mAttackMotion = 3;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle - PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 3)
					{
						AnimationChange(mUpAttackAnimation);
						mAttackMotion = 1; 
						SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
						
					}

					mPlayerState = PlayerState::UpAttack;
					if (mLB_ButtonSkill == "WindSlash")
						mY -= 15;

				}
				else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
				{
					if (mAttackMotion == 1)
					{
						AnimationChange(mLeftThrowSkillandAttackAnimation);
						mAttackMotion = 2;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle + PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 2)
					{
						AnimationChange(mLeftThrowSkillandAttackAnimation2);
						mAttackMotion = 3;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle - PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 3)
					{
						AnimationChange(mLeftThrowSkillandAttackAnimation);
						mAttackMotion = 1;
						SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}

					mPlayerState = PlayerState::LeftAttack;
					if (mLB_ButtonSkill == "WindSlash")
						mX -= 15;
				}
				else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
				{
					if (mAttackMotion == 1)
					{
						AnimationChange(mDownAttackAnimation);
						mAttackMotion = 2;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle + PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 2)
					{
						AnimationChange(mDownAttackAnimation2);
						mAttackMotion = 3;
						if (mLB_ButtonSkill == "WindSlash")
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle - PI / 8);
						else
							SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}
					else if (mAttackMotion == 3)
					{
						AnimationChange(mDownAttackAnimation);
						mAttackMotion = 1;
						SkillManager::GetInstance()->SkillCasting(mLB_ButtonSkill, lineX, lineY, mAngle);
					}

					mPlayerState = PlayerState::DownAttack;
					if (mLB_ButtonSkill == "WindSlash")
						mY += 15;
				}
			}

			// ��Ŭ�� ��ų
			if ((Input::GetInstance()->GetKeyDown(VK_RBUTTON) && mRB_ButtonSkillCool < 0) ||
				(Input::GetInstance()->GetKeyDown(VK_RBUTTON) && mSkillStackCount != 0))
			{
				if (mSkillStackCount == 0) return;
				mSkillStackCount--;
				if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
				{
					AnimationChange(mRightThrowWationgAnimation);
					mPlayerState = PlayerState::RightThrowWating;

				}
				else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
				{
					AnimationChange(mUpThrowWatingAnimation);
					mPlayerState = PlayerState::UpThrowWating;

				}
				else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
				{
					AnimationChange(mLeftThrowWatingAnimation);
					mPlayerState = PlayerState::LeftThrowWaitng;

				}
				else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
				{
					AnimationChange(mDownThrowWatingAnimation);
					mPlayerState = PlayerState::DownThorwWating;

				}
			}

			if ((Input::GetInstance()->GetKey(VK_RBUTTON) && mRB_ButtonSkillCool < 0) ||
				(Input::GetInstance()->GetKeyDown(VK_RBUTTON) && mSkillStackCount != 0))
			{
				//SkillObject* skill = nullptr;
				if (mIsAct == false)
				{
					if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
					{
						if (mRB_ButtonSkill == "DragonArc")
						{
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle, mIsUp);
							mIsUp = !mIsUp;
						}
						else
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle);
						//SkillManager::GetInstance()->SummonIceSpearSkill("SummonIceSpear", mX -20, mY, mAngle);
					}
					else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
					{
						if (mRB_ButtonSkill == "DragonArc")
						{
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle, mIsUp);
							mIsUp = !mIsUp;
						}
						else
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX, mY, mAngle);
						//SkillManager::GetInstance()->SummonIceSpearSkill("SummonIceSpear", mX, mY, mAngle);
					}
					else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
					{
						if (mRB_ButtonSkill == "DragonArc")
						{
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle, mIsUp);
							mIsUp = !mIsUp;
						}
						else
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX + 35, mY - 20, mAngle);
						//SkillManager::GetInstance()->SummonIceSpearSkill("SummonIceSpear", mX + 35, mY - 20, mAngle);
					}
					else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
					{
						if (mRB_ButtonSkill == "DragonArc")
						{
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle, mIsUp);
							mIsUp = !mIsUp;
						}
						else
							SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX + 20, mY - 20, mAngle);
						//SkillManager::GetInstance()->SummonIceSpearSkill("SummonIceSpear", mX + 20, mY - 20, mAngle);
					}
					mIsAct = true;
				}

				//if (skill == nullptr)
				SkillObject* skill = (SkillObject*)ObjectManager::GetInstance()->FindObject(mRB_ButtonSkill);
				if (skill == nullptr) return;
				if (skill->GetName() == "IceSpear")
				{
					if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
					{
						AnimationChange(mRightThrowWationgAnimation);
						mPlayerState = PlayerState::RightThrowWating;
						skill->SetX(mX - 25);
						skill->SetY(mY - 5);
						skill->SetAngle(mAngle);

					}
					else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
					{
						AnimationChange(mUpThrowWatingAnimation);
						mPlayerState = PlayerState::UpThrowWating;
						skill->SetX(mX);
						skill->SetY(mY);
						skill->SetAngle(mAngle);
					}
					else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
					{
						AnimationChange(mLeftThrowWatingAnimation);
						mPlayerState = PlayerState::LeftThrowWaitng;
						skill->SetX(mX + 55);
						skill->SetY(mY - 20);
						skill->SetAngle(mAngle);
					}
					else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
					{
						AnimationChange(mDownThrowWatingAnimation);
						mPlayerState = PlayerState::DownThorwWating;
						skill->SetX(mX + 25);
						skill->SetY(mY - 50);
						skill->SetAngle(mAngle);
					}
				}
			}
			if ((Input::GetInstance()->GetKeyUp(VK_RBUTTON) && mRB_ButtonSkillCool < 0) ||
				(Input::GetInstance()->GetKeyDown(VK_RBUTTON) && mSkillStackCount != 0))
			{
				mRB_ButtonSkillCool = SkillManager::GetInstance()->FindSkill(mRB_ButtonSkill)->GetSkillCool();
				SkillObject* skill = (SkillObject*)ObjectManager::GetInstance()->FindObject(mRB_ButtonSkill);
				if (skill == nullptr)
				{
					mIsAct = false;
					return;
				}
				if (skill->GetSkillType() == SkillType::Hold && skill->GetName() == "IceSpear")
				{
					skill->SetSkillType(SkillType::Throw);
				}

				if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
				{
					AnimationChange(mRightThrowSkillandAttackAnimation);
					mPlayerState = PlayerState::RightAttack;

					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle);
				}
				else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
				{
					AnimationChange(mUpThrowSkillAnimation);
					mPlayerState = PlayerState::UpAttack;
					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX, mY, mAngle);
				}
				else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
				{
					AnimationChange(mLeftThrowSkillandAttackAnimation);
					mPlayerState = PlayerState::LeftAttack;
					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX + 35, mY - 20, mAngle);
				}
				else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
				{
					AnimationChange(mDownThrowSkillAnimation);
					mPlayerState = PlayerState::DownAttack;
					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX + 20, mY - 20, mAngle);
				}

				mIsAct = false;
			}
			// Q스킬

			if (Input::GetInstance()->GetKeyDown('Q') && mQ_ButtonSkillCool < 0)
			{

				if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
				{
					AnimationChange(mRightThrowSkillandAttackAnimation);
					mPlayerState = PlayerState::RightThrowWating;
					SkillManager::GetInstance()->SkillCasting(mQ_ButtonSkill, lineX, lineY, mAngle);
				}
				else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
				{
					AnimationChange(mUpThrowSkillAnimation);
					mPlayerState = PlayerState::UpThrowWating;
					SkillManager::GetInstance()->SkillCasting(mQ_ButtonSkill, lineX, lineY, mAngle);
				}
				else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
				{
					AnimationChange(mLeftThrowSkillandAttackAnimation);
					mPlayerState = PlayerState::LeftThrowWaitng;
					SkillManager::GetInstance()->SkillCasting(mQ_ButtonSkill, lineX, lineY, mAngle);
				}
				else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
				{
					AnimationChange(mDownThrowSkillAnimation);
					mPlayerState = PlayerState::DownThorwWating;
					SkillManager::GetInstance()->SkillCasting(mQ_ButtonSkill, lineX, lineY, mAngle);
				}
			}
			if (Input::GetInstance()->GetKeyUp('Q') && mQ_ButtonSkillCool < 0)
			{
				mQ_ButtonSkillCool = SkillManager::GetInstance()->FindSkill(mQ_ButtonSkill)->GetSkillCool();

				if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
				{
					AnimationChange(mRightIdleAnimation);
					mPlayerState = PlayerState::RightIdle;

					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX - 20, mY, mAngle);
				}
				else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
				{
					AnimationChange(mUpIdleAnimation);
					mPlayerState = PlayerState::UpIdle;
					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX, mY, mAngle);
				}
				else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
				{
					AnimationChange(mLeftIdleAnimation);
					mPlayerState = PlayerState::LeftIdle;
					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX + 35, mY - 20, mAngle);
				}
				else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
				{
					AnimationChange(mDownIdleAnimation);
					mPlayerState = PlayerState::DownIdle;
					//SkillManager::GetInstance()->SkillCasting(mRB_ButtonSkill, mX + 20, mY - 20, mAngle);
				}

				mIsAct = false;
			}

			//�뽬
			if (mCurrentAnimation != mLeftDashAnimation && mCurrentAnimation != mRightDashAnimation && mCurrentAnimation != mDownDashAnimation && mCurrentAnimation != mUpDashAnimation &&
				mCurrentAnimation != mRightDiagonalDownDashAnimation && mCurrentAnimation != mRightDiagonalUpDashAnimation && mCurrentAnimation != mLeftDiagonalDownDashAnimation && mCurrentAnimation != mLeftDiagonalUpDashAnimation ||
				mRightDashAnimation->GetNowFrameX() == 9 || mLeftDashAnimation->GetNowFrameX() == 9 || mUpDashAnimation->GetNowFrameX() == 9 || mDownDashAnimation->GetNowFrameX() == 9)
			{
				if (Input::GetInstance()->GetKey('W') && Input::GetInstance()->GetKey('D') && Input::GetInstance()->GetKeyDown(VK_SPACE))
				{

					mPlayerState = PlayerState::RightDiagonalUpDash;
					AnimationChange(mRightDiagonalUpDashAnimation);

				}
				else if (Input::GetInstance()->GetKey('W') && Input::GetInstance()->GetKey('A') && Input::GetInstance()->GetKeyDown(VK_SPACE))
				{
					mPlayerState = PlayerState::LeftDiagonalUpDash;
					AnimationChange(mLeftDiagonalUpDashAnimation);

				}
				else if (Input::GetInstance()->GetKey('S') && Input::GetInstance()->GetKey('A') && Input::GetInstance()->GetKeyDown(VK_SPACE))
				{

					mPlayerState = PlayerState::LeftDiagonalDownDash;
					AnimationChange(mLeftDiagonalDownDashAnimation);

				}
				else if (Input::GetInstance()->GetKey('S') && Input::GetInstance()->GetKey('D') && Input::GetInstance()->GetKeyDown(VK_SPACE))
				{

					mPlayerState = PlayerState::RightDiagonalDownDash;
					AnimationChange(mRightDiagonalDownDashAnimation);

				}

				if (Input::GetInstance()->GetKeyDown(VK_SPACE))
				{
					SoundPlayer::GetInstance()->LoadFromFile(L"PlayerDashSound", Resources(L"Sound/PlayerDash.wav"), false);
					SoundPlayer::GetInstance()->Play(L"PlayerDashSound", 1.f);
					//if (mCurrentAnimation == mRightRunAnimation || mCurrentAnimation == mRightIdleAnimation || mCurrentAnimation == mRightDashAnimation)
					if (mPlayerState == PlayerState::RightRun || mPlayerState == PlayerState::RightIdle || mPlayerState == PlayerState::RightDash)
					{

						mPlayerState = PlayerState::RightDash;
						AnimationChange(mRightDashAnimation);

					}
					if (mPlayerState == PlayerState::LeftRun || mPlayerState == PlayerState::LeftIdle || mPlayerState == PlayerState::LeftDash)
					{


						mPlayerState = PlayerState::LeftDash;
						AnimationChange(mLeftDashAnimation);

					}
					if (mPlayerState == PlayerState::UpRun || mPlayerState == PlayerState::UpIdle || mPlayerState == PlayerState::UpDash)
					{

						mPlayerState = PlayerState::UpDash;

						AnimationChange(mUpDashAnimation);

					}
					if (mPlayerState == PlayerState::DownRun || mPlayerState == PlayerState::DownIdle || mPlayerState == PlayerState::DownDash)
					{

						mPlayerState = PlayerState::DownDash;

						AnimationChange(mDownDashAnimation);

					}
					mMoveCount = abs(mX) + abs(mY);
					mIsDashEffect = false;
				}


			}


			if (mCurrentAnimation == mRightDashAnimation)
			{

				mMoveAngle = 0;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 1000 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 1000 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX - 70, mY, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mRightDiagonalUpDashAnimation)
			{

				mMoveAngle = PI / 4;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX - 70, mY, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mRightDiagonalDownDashAnimation)
			{

				mMoveAngle = PI + PI / 4 + PI / 2;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX - 70, mY, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mLeftDashAnimation)
			{

				mMoveAngle = PI;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX + 70, mY, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mLeftDiagonalUpDashAnimation)
			{

				mMoveAngle = PI / 4 + PI / 2;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX + 70, mY, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mLeftDiagonalDownDashAnimation)
			{

				mMoveAngle = PI + PI / 4;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX + 70, mY, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mUpDashAnimation)
			{

				mMoveAngle = PI / 2;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX, mY + 70, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}
			else if (mCurrentAnimation == mDownDashAnimation)
			{

				mMoveAngle = PI / 2 + PI;
				mX += cosf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				mY -= sinf(mMoveAngle) * 0 * Time::GetInstance()->DeltaTime();
				if (mCurrentAnimation->GetNowFrameX() <= 6)
				{
					mX += cosf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					mY -= sinf(mMoveAngle) * 900 / (mCurrentAnimation->GetNowFrameX() + 1) * Time::GetInstance()->DeltaTime();
					int temp = abs(mX) + abs(mY);
					if (abs(mMoveCount - temp) > 100 && mIsDashEffect == false)
					{
						ParticleManager::GetInstance()->MakeDashEffectParticle(mX, mY - 70, mMoveAngle);
						mIsDashEffect = true;
					}
				}
			}

			if (mCurrentAnimation == mRightDashAnimation && mRightDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mLeftDashAnimation && mLeftDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mUpDashAnimation && mUpDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mDownDashAnimation && mDownDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mRightDiagonalDownDashAnimation && mRightDiagonalDownDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mRightDiagonalUpDashAnimation && mRightDiagonalUpDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mLeftDiagonalDownDashAnimation && mLeftDiagonalDownDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}
			else if (mCurrentAnimation == mLeftDiagonalUpDashAnimation && mLeftDiagonalUpDashAnimation->GetNowFrameX() == 5)
			{
				ParticleManager::GetInstance()->MakeDustParticle(mX, mMovingRect.bottom, mMoveAngle * PI, 2.f);
			}

			if (mCurrentAnimation == mRightDashAnimation && mRightDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::RightIdle;
				AnimationChange(mRightIdleAnimation);
			}
			else if (mCurrentAnimation == mRightDiagonalDownDashAnimation && mRightDiagonalDownDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::RightIdle;
				AnimationChange(mRightIdleAnimation);
			}
			else if (mCurrentAnimation == mRightDiagonalUpDashAnimation && mRightDiagonalUpDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::RightIdle;
				AnimationChange(mRightIdleAnimation);
			}
			else if (mCurrentAnimation == mLeftDashAnimation && mLeftDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::LeftIdle;
				AnimationChange(mLeftIdleAnimation);

			}
			else if (mCurrentAnimation == mLeftDiagonalDownDashAnimation && mLeftDiagonalDownDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::LeftIdle;
				AnimationChange(mLeftIdleAnimation);

			}
			else if (mCurrentAnimation == mLeftDiagonalUpDashAnimation && mLeftDiagonalUpDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::LeftIdle;
				AnimationChange(mLeftIdleAnimation);

			}
			else if (mCurrentAnimation == mUpDashAnimation && mUpDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::UpIdle;
				AnimationChange(mUpIdleAnimation);
			}
			else if (mCurrentAnimation == mDownDashAnimation && mDownDashAnimation->GetIsPlay() == false)
			{
				mPlayerState = PlayerState::DownIdle;
				AnimationChange(mDownIdleAnimation);
			}


			//---------------------------------
			//if (indexY != 0 && indexX != 0)
			//{
			//	for (int y = indexY - 1; y < indexY + 1; ++y)
			//	{
			//		for (int x = indexX - 1; x < indexX + 1; ++x)
			//		{
			//			RECT rc;
			//			RECT TileRect = TileList[y][x]->GetRect();
			//			if (IntersectRect(&rc, &mRect, &TileRect))
			//			{
			//				if (TileList[y][x]->GetTileState() == TileState::slow)
			//				{
			//					mSpeed = 2.f;
			//				}
			//				if (TileList[y][x]->GetTileState() == TileState::Normal)
			//				{
			//					mSpeed = 5.f;
			//				}
			//
			//				else if (TileList[y][x]->GetTileState() == TileState::Wall)
			//				{
			//					if ((rc.bottom - rc.top) < (rc.right - rc.left) && rc.bottom == mRect.bottom)
			//						mY -= rc.bottom - rc.top;
			//					if ((rc.bottom - rc.top) < (rc.right - rc.left) && rc.top == mRect.top)
			//						mY += rc.bottom - rc.top;
			//					if ((rc.bottom - rc.top) > (rc.right - rc.left) && rc.left == mRect.left)
			//						mX += rc.right - rc.left;
			//					if ((rc.bottom - rc.top) > (rc.right - rc.left) && rc.right == mRect.right)
			//						mX -= rc.right - rc.left;
			//
		//				}
		//			}
		//
		//
		//		}
		//	}
		//}

			//�������� ����--
			//-------
			if (mPlayerNormalShadow != nullptr) mPlayerNormalShadow->Update();
			if (mPlayerHeightShadow != nullptr) mPlayerHeightShadow->Update();
			if (mPlayerWideShadow != nullptr) mPlayerWideShadow->Update();
			mMouseTracker->Update();
			mCurrentAnimation->Update();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			mMovingRect = RectMakeCenter(mX, mY + 25, TileSize, TileSize);
			float mMovingX = (mMovingRect.left + (mMovingRect.right - mMovingRect.left) / 2);
			float mMovingY = (mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) / 2);

			lineX = mX + 50 * cosf(mAngle);
			lineY = mY + 50 * -sinf(mAngle);

			TileMap* tilemap = (TileMap*)ObjectManager::GetInstance()->FindObject("TileMap");
			vector<vector<Tile*>> tilelist = tilemap->GetTileList();
			for (int y = mMovingY / TileSize - 1; y < mMovingY / TileSize + 1; y++)
			{
				for (int x = mMovingX / TileSize - 1; x < mMovingX / TileSize + 1; x++)
				{
					if (tilelist[y][x]->GetType() == Type::Wall)
					{
						D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
						D2D1_RECT_F tempRect;
						if (tilelist[y][x]->GetType() == Type::Wall)
						{
							if (IntersectRect(tempRect, &tileRect, &mMovingRect))
							{
								float width = tempRect.right - tempRect.left;
								float height = tempRect.bottom - tempRect.top;
								if (y == (int)mMovingY / TileSize && x == (int)mMovingX / TileSize - 1)
									mX += width / 2;
								else if (y == (int)mMovingY / TileSize && x == (int)mMovingX / TileSize + 1)
									mX -= width / 2;
								else if (y == (int)mMovingY / TileSize - 1 && x == (int)mMovingX / TileSize)
									mY += height / 2;
								else if (y == (int)mMovingY / TileSize + 1 && x == (int)mMovingX / TileSize)
									mY -= height / 2;


							}
						}
					}
				}
			}
			//if (mCurrentAnimation == mRightDashAnimation || mCurrentAnimation == mRightDiagonalDownDashAnimation || mCurrentAnimation == mRightDiagonalUpDashAnimation || mCurrentAnimation == mUpDashAnimation ||
			//	mCurrentAnimation == mDownDashAnimation || mCurrentAnimation == mLeftDashAnimation || mCurrentAnimation == mLeftDiagonalDownDashAnimation || mCurrentAnimation == mLeftDiagonalUpDashAnimation)
			if (mPlayerState == PlayerState::DownDash || mPlayerState == PlayerState::UpDash || mPlayerState == PlayerState::RightDash || mPlayerState == PlayerState::RightDiagonalDownDash || mPlayerState == PlayerState::RightDiagonalUpDash ||
				mPlayerState == PlayerState::LeftDash || mPlayerState == PlayerState::LeftDiagonalDownDash || mPlayerState == PlayerState::LeftDiagonalUpDash || mPlayerState == PlayerState::LeftDiagonalDownDash ||
				mPlayerState == PlayerState::RightIdle || mPlayerState == PlayerState::LeftIdle || mPlayerState == PlayerState::UpIdle || mPlayerState == PlayerState::DownIdle)
			{

				for (int y = mMovingY / TileSize - 1; y < mMovingY / TileSize + 1; y++)
				{
					for (int x = mMovingX / TileSize - 1; x < mMovingX / TileSize + 1; x++)
					{
						if (tilelist[y][x]->GetType() == Type::Cliff)
						{
							D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
							D2D1_RECT_F tempRect;
							if (tilelist[y][x]->GetType() == Type::Cliff)
							{
								if (IntersectRect(tempRect, &tileRect, &mMovingRect))
								{
									if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.bottom == mMovingRect.bottom)
										mY -= 0;
									if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.top == mMovingRect.top)
										mY += 0;
									if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.left == mMovingRect.left)
										mX += 0;
									if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.right == mMovingRect.right)
										mX -= 0;


								}
							}
						}

					}
				}
			}
			//else if (mPlayerState == PlayerState::RightIdle || mPlayerState == PlayerState::LeftIdle || mPlayerState == PlayerState::UpIdle || mPlayerState == PlayerState::DownIdle)
			//{
			//	for (int y = mMovingY / TileSize - 1; y < mMovingY / TileSize + 1; y++)
			//	{
			//		for (int x = mMovingX / TileSize - 1; x < mMovingX / TileSize + 1; x++)
			//		{
			//			if (tilelist[y][x]->GetType() == Type::Cliff)
			//			{
			//				D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
			//				D2D1_RECT_F tempRect;
			//				if (tilelist[y][x]->GetType() == Type::Cliff)
			//				{
			//					if (IntersectRect(tempRect, &tileRect, &mMovingRect))
			//					{
			//						if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.bottom == mMovingRect.bottom)
			//							mY -= TileSize;
			//						if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.top == mMovingRect.top)
			//							mY += TileSize;
			//						if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.left == mMovingRect.left)
			//							mX += TileSize;
			//						if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.right == mMovingRect.right)
			//							mX -= TileSize;
			//
			//
			//					}
			//				}
			//			}
			//
			//		}
			//	}
			//}
			else
			{

				for (int y = mMovingY / TileSize - 1; y < mMovingY / TileSize + 1; y++)
				{
					for (int x = mMovingX / TileSize - 1; x < mMovingX / TileSize + 1; x++)
					{
						if (tilelist[y][x]->GetType() == Type::Cliff)
						{
							D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
							D2D1_RECT_F tempRect;
							//if (mCurrentAnimation == mRightDashAnimation || mCurrentAnimation == mRightDiagonalDownDashAnimation || mCurrentAnimation == mRightDiagonalUpDashAnimation || mCurrentAnimation == mUpDashAnimation ||
							//	mCurrentAnimation == mDownDashAnimation || mCurrentAnimation == mLeftDashAnimation || mCurrentAnimation == mLeftDiagonalDownDashAnimation || mCurrentAnimation == mLeftDiagonalUpDashAnimation)
							{
								if (tilelist[y][x]->GetType() == Type::Cliff)
								{
									if (IntersectRect(tempRect, &tileRect, &mMovingRect))
									{
										if (IntersectRect(tempRect, &tileRect, &mMovingRect))
										{
											float width = tempRect.right - tempRect.left;
											float height = tempRect.bottom - tempRect.top;
											if (y == (int)mMovingY / TileSize && x == (int)mMovingX / TileSize - 1)
												mX += width / 2;
											else if (y == (int)mMovingY / TileSize && x == (int)mMovingX / TileSize + 1)
												mX -= width / 2;
											else if (y == (int)mMovingY / TileSize - 1 && x == (int)mMovingX / TileSize)
												mY += height / 2;
											else if (y == (int)mMovingY / TileSize + 1 && x == (int)mMovingX / TileSize)
												mY -= height / 2;


										}
										//mHp -= 25;

									}
								}
							}

						}
					}

				}

			}
			if (tilelist[mMovingY / TileSize][mMovingX / TileSize]->GetType() == Type::Cliff)
			{
				if (mPlayerState != PlayerState::DownDash &&
					mPlayerState != PlayerState::UpDash &&
					mPlayerState != PlayerState::RightDash &&
					mPlayerState != PlayerState::RightDiagonalDownDash &&
					mPlayerState != PlayerState::RightDiagonalUpDash &&
					mPlayerState != PlayerState::LeftDash &&
					mPlayerState != PlayerState::LeftDiagonalDownDash &&
					mPlayerState != PlayerState::LeftDiagonalUpDash)
				{
					mCurrentAnimation->Stop();
					mCurrentAnimation = mDownHitAnimation;
					mCurrentAnimation->Play();
					mPlayerState = PlayerState::DownHit;
					SoundPlayer::GetInstance()->Play(L"FallSound", 1.f);
					mIsFalling = 1;
					mYtemp = mY;
				}
			}

			//	}
			for (int y = mMovingY / TileSize - 1; y < mMovingY / TileSize + 1; y++)
			{
				for (int x = mMovingX / TileSize - 1; x < mMovingX / TileSize + 1; x++)
				{
					if (tilelist[y][x]->GetType() == Type::Floor)
					{
						D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
						D2D1_RECT_F tempRect;
						if (tilelist[y][x]->GetType() == Type::Floor)
						{

							mSpeed = BasicSpeed;



						}
					}
				}
			}



			for (int y = mMovingY / TileSize - 1; y < mMovingY / TileSize + 1; y++)
			{
				for (int x = mMovingX / TileSize - 1; x < mMovingX / TileSize + 1; x++)
				{
					if (tilelist[y][x]->GetType() == Type::Thorn)
					{
						D2D1_RECT_F tileRect = tilelist[y][x]->GetRect();
						D2D1_RECT_F tempRect;
						if (tilelist[y][x]->GetType() == Type::Thorn)
						{
							if (IntersectRect(tempRect, &tileRect, &mMovingRect))
							{
								mSpeed = BasicSpeed - 100.f;

							}

						}
					}
				}
			}







			// �˹�
			if (mSkillHitPower > 0)
			{
				mX += cosf(mSkillHitAngle) * mSkillHitPower;
				mY += -sinf(mSkillHitAngle) * mSkillHitPower;
				mSkillHitPower -= 0.2f;
			}
		}
		else
		{
			if (mYtemp + 50 > mY)
			{
				mY++;

			}
			else
			{
				if (mPlayerState == PlayerState::DownHit)
				{
					mX = mX + 200;
					mY = mY - 50;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftIdleAnimation;
					mCurrentAnimation->Play();
					mPlayerState = PlayerState::LeftIdle;
					mHp -= 25;
				}
				Effect_Teleport* t = new Effect_Teleport(mX, mY + 50, false);
				mIsFalling = 0;
			}

			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		// 넉백
		if (mSkillHitPower > 0)
		{
			mX += cosf(mSkillHitAngle) * mSkillHitPower;
			mY += -sinf(mSkillHitAngle) * mSkillHitPower;
			mSkillHitPower -= 0.2f;

		}
	}
	if (mHp <= 0)
	{

		if (mCurrentAnimation != mDieAnimation)
		{
			AnimationChange(mDieAnimation);
			mPlayerState = PlayerState::Die;
			mPlayerState = PlayerState::Die;

		}

		mHp = 0;
	}

	//if (mTileList[(int)mPlayer->GetY() / TileSize][(int)mPlayer->GetX() / TileSize]->GetType() == Type::Cliff)
	//{
	//
	//}
	//else if (mTileList[(int)mPlayer->GetY() / TileSize][(int)mPlayer->GetX() / TileSize]->GetType() == Type::Floor)
	//{
	//
	//}

}

void Player::Render()
{
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	//for (int y = 0; y < TileCountY; ++y)
	//{
	//	for (int x = 0; x < TileCountX; ++x)
	//	{
	//		RenderRect(hdc,TileList[y][x]->mRect);
	//	}
	//}
	mMouseTracker->Render();
	if (mPlayerNormalShadow != nullptr)mPlayerNormalShadow->Render();
	if (mPlayerHeightShadow != nullptr)mPlayerHeightShadow->Render();
	if (mPlayerWideShadow != nullptr)mPlayerWideShadow->Render();
	mImage->SetScale(1.5f);
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	//wstring str = to_wstring(mSkillStackCount);
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, 100, str, 30.f);
	//string str = to_string(_mousePosition.x) + "," + to_string(_mousePosition.y);
	//wstring wstr;
	//wstr.assign(str.begin(), str.end());
	//D2DRenderer::GetInstance()->RenderText(100, WINSIZEY / 100, wstr, 30.f);
	//D2DRenderer::GetInstance()->RenderText(300, WINSIZEY / 200, to_wstring(mAngle), 30.f);

}

void Player::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Player::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Player::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}
