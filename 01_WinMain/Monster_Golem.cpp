#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Golem.h"
#include"SkillObject.h"
#include "Tile.h"
#include"TileMap.h"


Monster_Golem::Monster_Golem(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Golem::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Golem", Resources(L"Monster/Golem.png"), 6, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"Golem");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mMonsterActState = MonsterActState::RightIdle;
	mMonsterState = MonsterState::Idle;
	mSpeed = 100.f;
	mSizeX = mImage->GetFrameSize().__typeToGetX() * 4 - 120;
	mSizeY = mImage->GetFrameSize().__typeToGetY() * 4 - 50;
	mIsAct = false;
	mHp = 1;
	mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
	mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMonsterType = MonsterType::MiddleBoss;
	mMonsterName = MonsterName::Golem;
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 5, 2, 0, 2, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 1, 0, 2, 0, 1.f);
	AnimationSet(&mLeftAttackAnimation, false, false, 0, 4, 1, 4, 1.f);
	AnimationSet(&mUpAttackAnimation, false, false, 3, 0, 4, 0, 1.f);
	AnimationSet(&mDownAttackAnimation, false, false, 0, 4, 1, 4, 1.f);
	AnimationSet(&mDieAnimation, false, false, 0, 3, 5, 3, AnimationTime);


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Golem::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mDieAnimation);
}

void Monster_Golem::Update()
{
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{

		mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
		mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		if (mHp > 0)
		{

			
				//아이들
				if (mMonsterToPlayerDistance >= 5.5f)
				{
					AnimationChange(mRightIdleAnimation);
					mMonsterActState = MonsterActState::RightIdle;
					mMonsterState = MonsterState::Idle;
					//mPathList.clear();
					mIsAct = false;

				}
				if (mCurrentAnimation->GetIsPlay() == false)
				{
				//추격
					if (mMonsterToPlayerDistance < 5.5f && mMonsterToPlayerDistance >= 3.1f)
					{

						if (mRightWalkAnimation->GetIsPlay() == false)mIsAct = false;
						if (mLeftWalkAnimation->GetIsPlay() == false)mIsAct = false;
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

					float centerX = (mMovingRect.left + (mMovingRect.right - mMovingRect.left) / 2);
					float centerY = (mMovingRect.top + (mMovingRect.bottom - mMovingRect.top) / 2);
					mPathList = PathFinder::GetInstance()->FindPath(
						(TileMap*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Tile, "TileMap"),
						centerX / TileSize, centerY / TileSize,
						mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);
					if (mPathList.size() > 1)
					{
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
				if (mMonsterToPlayerDistance < 3.1f)
				{

					//오른쪽 공격

					if (mMonsterToPlayerAngle < (PI / 4) || mMonsterToPlayerAngle >(PI2 - (PI / 4)))
					{
						if (mIsAct == true)
						{
							if (mCurrentAnimation != mRightAttackAnimation)
							{
								AnimationChange(mRightAttackAnimation);
							}
							if (mCurrentAnimation->GetNowFrameX() == 2 && mCurrentAnimation->GetNowFrameY() == 0)
							{
								SkillManager::GetInstance()->MonsterBigSlashSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::RightAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mRightAttackAnimation->GetNowFrameX() == 2)
							{
								AnimationChange(mRightIdleAnimation);
							}
						}

						mIsAct = true;

					}

					//왼쪽공격
					else if (mMonsterToPlayerAngle > ((PI / 2) + (PI / 4)) && mMonsterToPlayerAngle < (PI + (PI / 4)))
					{
						if (mIsAct == true)
						{
							if (mCurrentAnimation != mLeftAttackAnimation)
							{
								AnimationChange(mLeftAttackAnimation);
							}
							if (mCurrentAnimation->GetNowFrameX() == 1)
							{
								SkillManager::GetInstance()->MonsterBigSlashSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::LeftAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mLeftAttackAnimation->GetNowFrameX() == 1)
							{
								AnimationChange(mRightIdleAnimation);
							}
						}

						mIsAct = true;
					}
					//위
					else if (mMonsterToPlayerAngle > PI / 4 && mMonsterToPlayerAngle < ((PI / 2) + (PI / 4)))
					{
						if (mIsAct == true)
						{
							if (mCurrentAnimation != mUpAttackAnimation)
							{
								AnimationChange(mUpAttackAnimation);
							}
							if (mCurrentAnimation->GetNowFrameX() == 4 && mCurrentAnimation->GetNowFrameY() == 0)
							{
								SkillManager::GetInstance()->MonsterBigSlashSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::UpAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mUpAttackAnimation->GetNowFrameX() == 4)
							{
								AnimationChange(mRightIdleAnimation);
							}
						}

						mIsAct = true;
					}
					//아래
					else if (mMonsterToPlayerAngle > (PI + (PI / 4)) && mMonsterToPlayerAngle < (PI2 - (PI / 4)))
					{
						if (mIsAct == true)
						{
							if (mCurrentAnimation != mDownAttackAnimation)
							{
								AnimationChange(mDownAttackAnimation);
							}
							if (mCurrentAnimation->GetNowFrameX() == 1 && mCurrentAnimation->GetNowFrameY() == 4)
							{
								SkillManager::GetInstance()->MonsterBigSlashSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::UpAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mDownAttackAnimation->GetNowFrameX() == 1)
							{
								AnimationChange(mRightIdleAnimation);
							}
						}

						mIsAct = true;
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

		//공격 라인--
		lineX = mX + 150 * cosf(mMonsterToPlayerAngle);
		lineY = mY + 150 * -sinf(mMonsterToPlayerAngle);
		//---
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mMovingRect = RectMakeCenter(mX, mY + 85, TileSize * 2, TileSize);
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

void Monster_Golem::Render()
{
	mImage->SetScale(4.f);
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY+45, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
		
	}
	

}
void Monster_Golem::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Golem::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Golem::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}