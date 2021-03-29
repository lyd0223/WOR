#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Zombie.h"
#include "Tile.h"
#include "TileMap.h"

Monster_Zombie::Monster_Zombie(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Zombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Zombie", Resources(L"Monster/Zombie.png"), 10, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"Zombie");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize;
	mSizeY = TileSize;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMonsterType = MonsterType::Normal;
	mMonsterName = MonsterName::Zombie;

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 5, 0, 5, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, true, 1, 0, 2, 0, AnimationTime);
	AnimationReverseSet(&mLeftAttackAnimation, false, true, 4, 0, 3, 0, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, true, 0, 1, 5, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, true, 5, 2, 0, 2, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 0, 3, 0, 3, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 6, 2, 6, 2, AnimationTime);
	AnimationSet(&mDieAnimation, false, true, 0, 3, 9, 3, AnimationTime);

	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Zombie::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mDieAnimation);

}

void Monster_Zombie::Update()
{

	mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
	mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	if (mCurrentAnimation->GetIsPlay() == false)
	{
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
			//추격
			if (mMonsterToPlayerDistance < 5.5f && mMonsterToPlayerDistance >= 1.5f)
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


			if (mMonsterToPlayerDistance < 1.5f)
			{

				//오른쪽 공격

				if (mMonsterToPlayerAngle <= PI / 2 || mMonsterToPlayerAngle >= PI + PI / 2)
				{
					if (mIsAct == true)
					{
						if (mCurrentAnimation != mRightAttackAnimation)
						{
							AnimationChange(mRightAttackAnimation);
						}
						if (mCurrentAnimation->GetNowFrameX() == 3 && mCurrentAnimation->GetNowFrameY() == 0)
						{
							SkillManager::GetInstance()->MonsterSmallSlashSkill("MonsterSmallSlash", lineX, lineY, mMonsterToPlayerAngle);
						}
						int frame = mCurrentAnimation->GetNowFrameX();
						mMonsterActState = MonsterActState::RightAttack;
						mMonsterState = MonsterState::Attack;
						mIsAct = false;
						if (mRightAttackAnimation->GetNowFrameX() == 3)
						{
							AnimationChange(mRightIdleAnimation);
						}
					}

					mIsAct = true;
				}


				//왼쪽공격
				else if (mMonsterToPlayerAngle > PI / 2 && mMonsterToPlayerAngle < PI + PI / 2)
				{
					if (mIsAct == true)
					{
						if (mCurrentAnimation != mLeftAttackAnimation)
						{
							AnimationChange(mLeftAttackAnimation);
						}
						if (mCurrentAnimation->GetNowFrameX() == 4 && mCurrentAnimation->GetNowFrameY() == 0)
						{
							SkillManager::GetInstance()->MonsterSmallSlashSkill("MonsterSmallSlash", lineX, lineY, mMonsterToPlayerAngle);
						}
						int frame = mCurrentAnimation->GetNowFrameX();
						mMonsterActState = MonsterActState::LeftAttack;
						mMonsterState = MonsterState::Attack;
						mIsAct = false;
						if (mLeftAttackAnimation->GetNowFrameX() == 4)
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
	//공격 라인--
	lineX = mX + 50 * cosf(mMonsterToPlayerAngle);
	lineY = mY + 50 * -sinf(mMonsterToPlayerAngle);
	//---
	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	TileMap* tilemap = (TileMap*)ObjectManager::GetInstance()->FindObject("TileMap");
	vector<vector<Tile*>> tilelist = tilemap->GetTileList();
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
				if (tilelist[y][x]->GetType() == Type::Cliff)
				{
					if (IntersectRect(tempRect, &tileRect, &mRect))
					{

						if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.bottom == mRect.bottom)
							mY -= TileSize;
						if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.top == mRect.top)
							mY += TileSize;
						if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.left == mRect.left)
							mX += TileSize;
						if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.right == mRect.right)
							mX -= TileSize;
					}

				}
				if (tilelist[y][x]->GetType() == Type::Floor)
				{
					if (IntersectRect(tempRect, &tileRect, &mRect))
					{
						mSpeed = BasicSpeed;

					}

				}
				if (tilelist[y][x]->GetType() == Type::Thorn)
				{
					if (IntersectRect(tempRect, &tileRect, &mRect))
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

void Monster_Zombie::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);

	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	}

}
void Monster_Zombie::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Zombie::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Zombie::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}