#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Slime.h"
#include "Tile.h"
#include"TileMap.h"

Monster_Slime::Monster_Slime(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Slime::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Slime", Resources(L"Monster/Slime.png"), 10, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"Slime");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mMonsterActState = MonsterActState::RightIdle;
	mMonsterState = MonsterState::Idle;
	mHp = 1;
	mSpeed = 100.f;
	mSizeX = TileSize / 2;
	mSizeY = TileSize/2;
	mRect = RectMakeCenter(mX, mY + 10, mSizeX, mSizeY);
	mMonsterType = MonsterType::Normal;
	mMonsterName = MonsterName::Slime;
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 9, 3, 9, 3, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 1, 0, 7, 0, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 9, 2, 2, 2, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 0, 1, 4, 1, AnimationTime);
	AnimationReverseSet(&mLeftHitAnimation, false, false, 7, 3, 3, 3, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 5, 1, 9, 1, AnimationTime);



	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Slime::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mDieAnimation);

}

void Monster_Slime::Update()
{
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
		mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
		mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		
			if (mHp > 0)
			{
				if (mMonsterActState == MonsterActState::LeftHit && mCurrentAnimation == mLeftHitAnimation)
				{
					AnimationChange(mLeftIdleAnimation);
					mMonsterActState = MonsterActState::LeftIdle;
					mIsHit = false;
				}
				if (mMonsterActState == MonsterActState::RightHit && mCurrentAnimation == mRightHitAnimation)
				{
					AnimationChange(mRightIdleAnimation);
					mMonsterActState = MonsterActState::RightIdle;
					mIsHit = false;
				}

				if (mIsHit)
				{
					if (mMonsterToPlayerAngle > PI / 2 && mMonsterToPlayerAngle < PI / 2 + PI)
					{

						
						AnimationChange(mLeftHitAnimation);
						mMonsterActState = MonsterActState::LeftHit;
					}
					if (mMonsterToPlayerAngle <PI / 2 || mMonsterToPlayerAngle > PI / 2 + PI)
					{
						
						AnimationChange(mRightHitAnimation);
						mMonsterActState = MonsterActState::RightHit;
					}
				}

				//아이들
				if (mMonsterToPlayerDistance >= 5.5f)
				{
					AnimationChange(mRightIdleAnimation);
					mMonsterActState = MonsterActState::RightIdle;
					mMonsterState = MonsterState::Idle;
					//mPathList.clear();
					mIsAct = false;

				}
				//추격
				if (mMonsterToPlayerDistance < 5.5f)
				{

					if (mRightWalkAnimation->GetIsPlay() == false)mIsAct = false;
					if (mLeftWalkAnimation->GetIsPlay() == false)mIsAct = false;
					if (mCurrentAnimation->GetIsPlay() == false)
					{
						if (mMonsterToPlayerAngle <PI / 2 || mMonsterToPlayerAngle > PI / 2 + PI)
						{

							if (mIsAct == false)
							{
								AnimationChange(mRightWalkAnimation);
								mMonsterActState = MonsterActState::RightWalk;
								mMonsterState = MonsterState::Chase;
								mIsAct = true;
							}
						}
						if (mMonsterToPlayerAngle > PI / 2 && mMonsterToPlayerAngle < PI / 2 + PI)
						{
							if (mIsAct == false)
							{
								AnimationChange(mLeftWalkAnimation);
								mMonsterActState == MonsterActState::LeftWalk;
								mMonsterState = MonsterState::Chase;
								mIsAct = true;
							}
						}
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
		

		mCurrentAnimation->Update();
		mRect = RectMakeCenter(mX, mY + 10, mSizeX, mSizeY);
		mMovingRect = RectMakeCenter(mX, mY, TileSize, TileSize);
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

void Monster_Slime::Render()
{
	mImage->SetScale(1.f); 
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY+15, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	}
}
void Monster_Slime::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Slime::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Slime::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}