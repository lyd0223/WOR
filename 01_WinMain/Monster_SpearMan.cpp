#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_SpearMan.h"
#include "Tile.h"
#include"TileMap.h"

Monster_SpearMan::Monster_SpearMan(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_SpearMan::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SpearMan", Resources(L"Monster/SpearMan.png"), 8, 6);
	mImage = ImageManager::GetInstance()->FindImage(L"SpearMan");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mHp = 1;
	mSizeX = mImage->GetFrameSize().__typeToGetX()* 2 ;
	mSizeY = mImage->GetFrameSize().__typeToGetY()*1.5;
	mRect = RectMakeCenter(mX, mY+50, mSizeX, mSizeY);

	
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 1, 0, 1, 0, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 2, 0, 2, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, true, false, 0, 2, 4, 2, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, true, false, 5, 3, 1, 3, AnimationTime);
	AnimationSet(&mDownAttackAnimation, false, false, 0, 4, 1, 4, 1.f);
	AnimationSet(&mUpAttackAnimation, false, false, 2, 4, 3, 4, 1.f);
	AnimationSet(&mLeftAttackAnimation, false, false, 4, 4, 5, 4, 1.f);
	AnimationReverseSet(&mRightAttackAnimation, false, false, 7, 4, 6, 4, 1.f);
	AnimationSet(&mDieAnimation, false, false, 0, 5, 6, 5, AnimationTime);


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_SpearMan::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mDownAttackAnimation);
	SafeDelete(mUpAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mDieAnimation);

}

void Monster_SpearMan::Update()
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

				SoundPlayer::GetInstance()->Play(L"EnemyHitSound", 1.f);
				AnimationChange(mLeftHitAnimation);
				mMonsterActState = MonsterActState::LeftHit;
			}
			if (mMonsterToPlayerAngle <PI / 2 || mMonsterToPlayerAngle > PI / 2 + PI)
			{
				SoundPlayer::GetInstance()->Play(L"EnemyHitSound", 1.f);
				AnimationChange(mRightHitAnimation);
				mMonsterActState = MonsterActState::RightHit;
			}
		}
		if (mCurrentAnimation->GetIsPlay() == false)
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
				//길 찾기
				if (mPathList.size() != 0)
				{
					float nextX = mPathList[1]->GetX();
					float nextY = mPathList[1]->GetY();
					float angle = Math::GetAngle(mX, mY, nextX, nextY);
					float distance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY());

					mX += cosf(angle) * mSpeed;
					mY += -sinf(angle) * mSpeed;
				}
			}


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
							SkillManager::GetInstance()->SpearSkill("MonsterBigSlash", mX, mY+75, mMonsterToPlayerAngle);
						if (mCurrentAnimation->GetNowFrameX() == 6 && mCurrentAnimation->GetNowFrameY() == 4)
						{
						}
						int frame = mCurrentAnimation->GetNowFrameX();
						mMonsterActState = MonsterActState::RightAttack;
						mMonsterState = MonsterState::Attack;
						mIsAct = false;
						if (mRightAttackAnimation->GetNowFrameX() == 6)
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
							SkillManager::GetInstance()->SpearSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
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
							SkillManager::GetInstance()->SpearSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
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
							SkillManager::GetInstance()->SpearSkill("MonsterBigSlash", lineX, lineY, mMonsterToPlayerAngle);
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
	//lineX = mX + 100 * cosf(mMonsterToPlayerAngle);
	//lineY = mY + 100 * -sinf(mMonsterToPlayerAngle);
	//---
	mRect = RectMakeCenter(mX, mY+50, mSizeX, mSizeY);
	mMovingRect = RectMakeCenter(mX, mY + 80, TileSize , TileSize);
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

void Monster_SpearMan::Render()
{
	mImage->SetScale(3.f);

	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	
}
void Monster_SpearMan::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_SpearMan::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_SpearMan::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}