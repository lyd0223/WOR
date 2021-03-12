#include "pch.h"
#include "FireBoss.h"
#include "Image.h"
#include "Animation.h"

FireBoss::FireBoss()
{
}

void FireBoss::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"FireBoss", Resources(L"Enemy/FireBoss/FireBoss.png"), 12, 10);
	mImage = ImageManager::GetInstance()->FindImage(L"FireBoss");

	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = 100;
	mSizeY = 100;
	mImage->SetSize(Vector2(mSizeX, mSizeY));

	//mImage->SetSize(Vector2(100, 100));
	//mImage->SetScale(3.0f);
	//mImage->SetAngle(mAngle);
	//mImage->SetAlpha(0.3f);
	//mImage->FrameRender(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100, 0, 0);

	mLeftIdleAnm = new Animation();
	mLeftIdleAnm->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftIdleAnm->SetIsLoop(true);

	mRightIdleAnm = new Animation();
	mRightIdleAnm->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightIdleAnm->SetIsLoop(true);

	mLeftDashAnm = new Animation();
	mLeftDashAnm->InitFrameByStartEnd(1, 1, 3, 1, false);
	mLeftDashAnm->SetIsLoop(true);
	mLeftDashAnm->SetFrameUpdateTime(0.1f);

	mRightDashAnm = new Animation();
	mRightThrowAnm->InitFrameByStartEnd(1, 0, 3, 0, false);
	mRightDashAnm->SetIsLoop(true);
	mRightDashAnm->SetFrameUpdateTime(0.1f);

	mUpDashAnm = new Animation();
	mUpDashAnm->InitFrameByStartEnd(4, 0, 4, 0, false);
	mUpDashAnm->SetIsLoop(true);

	mDownDashAnm = new Animation();
	mDownDashAnm->InitFrameByStartEnd(4, 1, 4, 1, false);
	mDownDashAnm->SetIsLoop(true);

	mLeftSpecialAttackAnm = new Animation();
	mLeftSpecialAttackAnm->InitFrameByStartEnd(9, 1, 11, 1, false);
	mLeftSpecialAttackAnm->SetFrameUpdateTime(0.1f);

	mRightSpecialAttackAnm = new Animation();
	mRightSpecialAttackAnm->InitFrameByStartEnd(9, 0, 11, 0, false);
	mRightSpecialAttackAnm->SetFrameUpdateTime(0.1f);

	mLeftKickAnm = new Animation();
	mLeftKickAnm->InitFrameByStartEnd(0, 3, 11, 3, false);
	mLeftKickAnm->SetFrameUpdateTime(0.1f);

	mRightKickAnm = new Animation();
	mRightKickAnm->InitFrameByStartEnd(0, 2, 11, 2, false);
	mRightKickAnm->SetFrameUpdateTime(0.1f);

	mLeftAttackReadyAnm = new Animation();
	mLeftAttackReadyAnm->InitFrameByStartEnd(0, 5, 3, 5, false);
	mLeftAttackReadyAnm->SetFrameUpdateTime(0.1f);
	/*
	Animation* mLeftKickAnm;			// 0, 3, 11, 3
	Animation* mRightKickAnm;			// 0, 2, 11, 2
	Animation* mLeftAttackReadyAnm;		// 0, 5, 3, 5
	Animation* mRightAttackReadyAnm;	// 0, 4, 3, 4
	Animation* mLeftThrowAnm;			// 10, 5, 11, 5
	Animation* mRigthThrowAnm;			// 10, 4, 11, 4
	Animation* mUpThrowAnm;				// 10, 7, 11, 7
	Animation* mDwonThrowAnm;			// 10, 6, 11, 6
	Animation* mLeftStunAnm;			// 0, 7, 4, 7
	Animation* mRightStunAnm;			// 0, 6, 4, 6
	Animation* mRefreshAnm1;			// 0, 8, 6, 8
	Animation* mRefreshAnm2;			// 0, 9, 6, 9
	Animation* mLeftStempAnm;			// 10, 9, 11, 9
	Animation* mRgithStempAnm;			// 10, 8, 11, 8
	*/
	mCurrentAnm = mLeftKickAnm;
	mCurrentAnm->Play();
}

void FireBoss::Release()
{
}

void FireBoss::Update()
{
	mCurrentAnm->Update();


}

void FireBoss::Render(HDC hdc)
{
	mImage->SetScale(1.5f);
	mImage->FrameRender(mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY());
	wstring AnmXstr = to_wstring(mCurrentAnm->GetNowFrameX());
	wstring AnmYstr = to_wstring(mCurrentAnm->GetNowFrameY());
	TextOut(hdc, 5, 5, AnmXstr.c_str(), AnmXstr.length());
	TextOut(hdc, 5, 20, AnmYstr.c_str(), AnmYstr.length());
}