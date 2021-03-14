
#include"pch.h"
#include"Image.h"
#include"Animation.h"
#include "Player.h"
#include"Tile.h"



Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{

	ImageManager::GetInstance()->LoadFromFile(L"Player", Resources(L"Player/WizardPlayer.png"), 10, 25);
	mImage = ImageManager::GetInstance()->FindImage(L"Player");
	mPlayerState = PlayerState::DownIdle;
	mSpeed = 5.f;
	mSizeX = TileSize - 10;
	mSizeY = TileSize - 10;
	mAngle = 0.f;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

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
	AnimationSet(&mDownRunAnimation, false, true, 0, 1, 9, 1, AnimationTime);
	AnimationSet(&mUpRunAnimation, false, true, 0, 2, 9, 2, AnimationTime);
	AnimationSet(&mRightRunAnimation, false, true, 0, 3, 9, 3, AnimationTime);
	AnimationReverseSet(&mLeftRunAnimation, false, true, 9, 4, 0, 4, AnimationTime);
	AnimationSet(&mDownAttackAnimation, false, false, 0, 5, 9, 5, AnimationTime);
	AnimationSet(&mRightDashAnimation, false, false, 0, 7, 9, 7, AnimationTime);
	AnimationSet(&mLeftDashAnimation, false, false, 0, 8, 9, 8, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 9, 9, 9, AnimationTime);
	AnimationSet(&mUpAttackAnimation, false, false, 0, 11, 9, 11, AnimationTime);
	AnimationSet(&mDownThrowSkillAnimation, false, false, 0, 6, 9, 6, AnimationTime);
	AnimationSet(&mUpThrowSkillAnimation, false, false, 0, 14, 9, 14, AnimationTime);
	AnimationReverseSet(&mLeftThrowSkillandAttackAnimation, false, false, 7, 13, 0, 13, AnimationTime);
	AnimationSet(&mRightThrowSkillandAttackAnimation, false, false, 0, 12, 7, 12, AnimationTime);
	AnimationSet(&mUpDashAnimation, false, false, 0, 18, 9, 18, AnimationTime);
	AnimationSet(&mDownDashAnimation, false, false, 0, 19, 9, 19, AnimationTime);

	mCurrentAnimation = mDownIdleAnimation;
	mCurrentAnimation->Play();
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
	//위
	if (Input::GetInstance()->GetKeyDown('W'))
	{

		AnimationChange(mUpRunAnimation);
		mPlayerState = PlayerState::UpRun;
	}
	if (Input::GetInstance()->GetKey('W'))
	{
		mY -= mSpeed;
	}
	if (Input::GetInstance()->GetKeyUp('W'))
	{
		AnimationChange(mUpIdleAnimation);
		mPlayerState = PlayerState::UpIdle;
	}
	//아래
	if (Input::GetInstance()->GetKeyDown('S'))
	{

		AnimationChange(mDownRunAnimation);
		mPlayerState = PlayerState::DownRun;
	}
	if (Input::GetInstance()->GetKey('S'))
	{
		mY += mSpeed;
	}
	if (Input::GetInstance()->GetKeyUp('S'))
	{
		AnimationChange(mDownIdleAnimation);
		mPlayerState = PlayerState::DownIdle;
	}
	//오른쪽
	if (Input::GetInstance()->GetKeyDown('D'))
	{

		AnimationChange(mRightRunAnimation);
		mPlayerState = PlayerState::RightRun;
	}
	if (Input::GetInstance()->GetKey('D'))
	{
		mX += mSpeed;
	}
	if (Input::GetInstance()->GetKeyUp('D'))
	{
		AnimationChange(mRightIdleAnimation);
		mPlayerState = PlayerState::RightIdle;
	}
	//왼쪽
	if (Input::GetInstance()->GetKeyDown('A'))
	{
		AnimationChange(mLeftRunAnimation);
		mPlayerState = PlayerState::LeftRun;
	}
	if (Input::GetInstance()->GetKey('A'))
	{
		mX -= mSpeed;
	}
	if (Input::GetInstance()->GetKeyUp('A'))
	{
		AnimationChange(mLeftIdleAnimation);
		mPlayerState = PlayerState::LeftIdle;
	}
	//공격
	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		mAngle = Math::GetAngle(mX, mY, _mousePosition.x, _mousePosition.y);
		if (mAngle < (PI / 4) || mAngle >(PI2 - (PI / 4)))
		{
			AnimationChange(mRightThrowSkillandAttackAnimation);
			mPlayerState = PlayerState::RightAttack;
		}
		else if (mAngle > PI / 4 && mAngle < ((PI / 2) + (PI / 4)))
		{
			AnimationChange(mUpAttackAnimation);
			mPlayerState = PlayerState::UpAttack;
		}
		else if (mAngle > ((PI / 2) + (PI / 4)) && mAngle < (PI + (PI / 4)))
		{
			AnimationChange(mLeftThrowSkillandAttackAnimation);
			mPlayerState = PlayerState::LeftAttack;
		}
		else if (mAngle > (PI + (PI / 4)) && mAngle < (PI2 - (PI / 4)))
		{
			AnimationChange(mDownAttackAnimation);
			mPlayerState = PlayerState::DownAttack;
		}
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

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render()
{
	RenderRect( mRect);
	//for (int y = 0; y < TileCountY; ++y)
	//{
	//	for (int x = 0; x < TileCountX; ++x)
	//	{
	//		RenderRect(hdc,TileList[y][x]->mRect);
	//	}
	//}

	mImage->FrameRender( mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
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
