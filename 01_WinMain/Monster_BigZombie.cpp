#include "pch.h"
#include "Image.h"
#include"Camera.h"
#include"Animation.h"
#include"Player.h"
#include"Monster_BigZombie.h"
#include "Tile.h"
#include "TileMap.h"

Monster_BigZombie::Monster_BigZombie(const string& name, float x, float y)
	:MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
	//mIsActive = false;
}

void Monster_BigZombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"BigZombie", Resources(L"Monster/Bigzombie.png"), 7, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"BigZombie");
	mMonsterActState = MonsterActState::RightIdle;
	mMonsterState = MonsterState::Idle;
	mSpeed = 10.f;
	mSizeX = mImage->GetFrameSize().__typeToGetX() * 4 - 120;
	mSizeY = mImage->GetFrameSize().__typeToGetY() * 4 - 100;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHp = 5;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
	mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 1, 0, 5, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 0, 1, 4, 1, AnimationTime);
	AnimationSet(&mLeftAttackAnimation, false, false, 0, 2, 4, 2, AnimationTime);
	AnimationSet(&mSpecialAttackAnimation, false, false, 0, 3, 5, 3, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 4, 5, 4, AnimationTime);
	mMonsterType = MonsterType::MiddleBoss;
	mMonsterName = MonsterName::BigZombie;
	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();


}

void Monster_BigZombie::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mSpecialAttackAnimation);
	SafeDelete(mDieAnimation);
}

void Monster_BigZombie::Update()
{
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
		

		mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
		mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		if (mHp > 0)
		{

			//아이들
			if (mMonsterToPlayerDistance >= 10.5f)
			{
				AnimationChange(mRightIdleAnimation);
				mMonsterActState = MonsterActState::RightIdle;
				mMonsterState = MonsterState::Idle;
				//mPathList.clear();
				mIsAct = false;

			}
			
				if (mMonsterToPlayerDistance < 10.5f && mMonsterToPlayerDistance >= 2.1f)
				{

					if (mRightWalkAnimation->GetIsPlay() == false)mIsAct = false;
					if (mIsAct == false)
					{
						AnimationChange(mRightWalkAnimation);
						mMonsterActState = MonsterActState::RightWalk;
						mMonsterState = MonsterState::Chase;
						mIsAct = true;
					}
					// 이동

					if (mPathList.size() > 1)
					{
						float centerX = (mMovingRect.left + (mMovingRect.right - mMovingRect.left) / 2);
						float centerY = (mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) / 2);
						float nextX = mPathList[1]->GetX() + (TileSize / 2);
						float nextY = mPathList[1]->GetY() + (TileSize / 2);
						float angle = Math::GetAngle(centerX, centerY, nextX, nextY);

						POINT point;
						point.x = mMovingRect.left + (mMovingRect.right - mMovingRect.left);
						point.y = mMovingRect.top + (mMovingRect.bottom - mMovingRect.top);

						D2D1_RECT_F rctemp = mPathList[0]->GetRect();
						if (!PtInRect(&rctemp, point))
						{
							mPathList.erase(mPathList.begin());
						}

						mX += cosf(angle) * mSpeed * Time::GetInstance()->DeltaTime();
						mY += -sinf(angle) * mSpeed * Time::GetInstance()->DeltaTime();
					}
				}

				if (mCurrentAnimation->GetIsPlay() == false)
				{
				if (mMonsterToPlayerDistance < 2.1f)
				{

					//오른쪽 공격
					if (mMonsterToPlayerAngle <= PI / 2 || mMonsterToPlayerAngle >= PI + PI / 2)
					{
						if (mIsAct == true && mCurrentAnimation != mRightAttackAnimation)
						{
							AnimationChange(mRightAttackAnimation);
							mMonsterActState = MonsterActState::RightAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
						}
						if (mRightAttackAnimation->GetIsPlay() == false)mIsAct = true;
						if (mRightAttackAnimation->GetIsPlay() == false)
							mRect = RectMakeCenter(mX, mY, 150, mSizeX);
					}
					//왼쪽공격
					if (mMonsterToPlayerAngle > PI / 2 && mMonsterToPlayerAngle < PI + PI / 2)
					{
						if (mLeftAttackAnimation->GetIsPlay() == false)mIsAct == true;
						if (mIsAct == true && mCurrentAnimation != mLeftAttackAnimation)
						{
							AnimationChange(mLeftAttackAnimation);
							mMonsterActState = MonsterActState::LeftAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
						}

						if (mLeftAttackAnimation->GetIsPlay() == false)
							mRect = RectMakeCenter(mX, mY, 150, mSizeX);

					}
				}
			}

			if (mHp <= 0)
			{
				if (mIsAct == false)

				{
					AnimationChange(mDieAnimation);
					mMonsterActState = MonsterActState::Die;
					mMonsterState = MonsterState::Die;
					mIsAct = true;
				}
			}
		}


		mCurrentAnimation->Update();

		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mMovingRect = RectMakeCenter(mX, mY + 55, TileSize * 2, TileSize);
		//발판상호작용
		float mMovingX = (mMovingRect.left + (mMovingRect.right - mMovingRect.left) / 2);
		float mMovingY = (mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) / 2);
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
					if (tilelist[y][x]->GetType() == Type::Cliff)
					{
						if (IntersectRect(tempRect, &tileRect, &mMovingRect))
						{

							if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.bottom == mMovingRect.bottom)
								mY -= TileSize;
							if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.top == mMovingRect.top)
								mY += TileSize;
							if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.left == mMovingRect.left)
								mX += TileSize;
							if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.right == mMovingRect.right)
								mX -= TileSize;
						}

					}
					if (tilelist[y][x]->GetType() == Type::Floor)
					{
						if (IntersectRect(tempRect, &tileRect, &mMovingRect))
						{
							mSpeed = BasicSpeed;

						}

					}
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

		// 넉백
		if (mSkillHitPower > 0)
		{
			mX += cosf(mSkillHitAngle) * mSkillHitPower;
			mY += -sinf(mSkillHitAngle) * mSkillHitPower;
			mSkillHitPower -= 0.2f;
		}
	}
}

void Monster_BigZombie::Render()
{
	if (mIsActive == false)
	{
		return;
	}
	mImage->SetScale(4.f);
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect(); 
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
		CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY + 20, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	}

	//string str = to_string(Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY())/ TileSize);
	//wstring wstr;
	//wstr.assign(str.begin(), str.end());
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX/2, WINSIZEY / 2, wstr, 30.f);

}

void Monster_BigZombie::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_BigZombie::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_BigZombie::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}