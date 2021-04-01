#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Zombie.h"
#include "Tile.h"
#include "TileMap.h"
#include "Scene.h"
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
	mSpeed = 100.f;
	mSizeX = mImage->GetWidth() / 10;
	mSizeY = mImage->GetHeight() / 4 + 30;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMonsterType = MonsterType::Normal;
	mMonsterName = MonsterName::Zombie;
	mHp = 100;
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 5, 0, 5, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 1, 0, 2, 0, 0.5f);
	AnimationReverseSet(&mLeftAttackAnimation, false, false, 4, 0, 3, 0, 0.5f);
	AnimationSet(&mRightWalkAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 5, 2, 0, 2, AnimationTime);
	AnimationSet(&mRightHitAnimation, false, false, 0, 3, 0, 3, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 6, 2, 6, 2, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 3, 9, 3, AnimationTime);

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
			//���̵�
			if (mMonsterToPlayerDistance >= 20.5f)
			{
				AnimationChange(mRightIdleAnimation);
				mMonsterActState = MonsterActState::RightIdle;
				mMonsterState = MonsterState::Idle;
				//mPathList.clear();
				mIsAct = false;

			}
			//�߰�
			if (mMonsterToPlayerDistance < 20.5f && mMonsterToPlayerDistance >= 1.5f)
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
				//��ã��
				if (mCurrentAnimation == mRightWalkAnimation || mCurrentAnimation == mLeftWalkAnimation)
				{
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
			}


			if (mMonsterToPlayerDistance < 1.5f)
			{

				//������ ����
				if (mCurrentAnimation->GetIsPlay() == false)
				{
					if (mMonsterToPlayerAngle <= PI / 2 || mMonsterToPlayerAngle >= PI + PI / 2)
					{
						if (mIsAct == true)
						{
							if (mCurrentAnimation != mRightAttackAnimation)
							{
								AnimationChange(mRightAttackAnimation);
							}
							if (mCurrentAnimation->GetNowFrameX() == 2 && mCurrentAnimation->GetNowFrameY() == 0)
							{
								SkillManager::GetInstance()->MonsterSmallSlashSkill("MonsterSmallSlash", lineX, lineY, mMonsterToPlayerAngle);
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


					//���ʰ���
					else if (mMonsterToPlayerAngle > PI / 2 && mMonsterToPlayerAngle < PI + PI / 2)
					{
						if (mIsAct == true)
						{
							if (mCurrentAnimation != mLeftAttackAnimation)
							{
								AnimationChange(mLeftAttackAnimation);
							}
							if (mCurrentAnimation->GetNowFrameX() == 3 && mCurrentAnimation->GetNowFrameY() == 0)
							{
								SkillManager::GetInstance()->MonsterSmallSlashSkill("MonsterSmallSlash", lineX, lineY, mMonsterToPlayerAngle);
							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::LeftAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mLeftAttackAnimation->GetNowFrameX() == 3)
							{
								AnimationChange(mRightIdleAnimation);
							}
						}

						mIsAct = true;
					}
				}
			}
		}



		
		//���� ����--
		lineX = mX + 50 * cosf(mMonsterToPlayerAngle);
		lineY = mY + 50 * -sinf(mMonsterToPlayerAngle);
		//---
		mCurrentAnimation->Update();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mMovingRect = RectMakeCenter(mX, mY + 35, TileSize, TileSize);
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

		// �˹�
		if (mSkillHitPower > 0)
		{
			mX += cosf(mSkillHitAngle) * mSkillHitPower;
			mY += -sinf(mSkillHitAngle) * mSkillHitPower;
			mSkillHitPower -= 0.2f;
			
		}
		if (mHp <= 0)
		{
			if (mCurrentAnimation != mDieAnimation)
			{
				SoundPlayer::GetInstance()->Play(L"EnemyDeadSound", 1.f);
				AnimationChange(mDieAnimation);
				mMonsterActState = MonsterActState::Die;
				mMonsterState = MonsterState::Die;
				if(mRoom != nullptr)
					mRoom->monsterList.pop_back();

			}
		}
	}
	if (mDieAnimation->GetNowFrameX() == 9)mIsDestroy = true;
	return;
}

void Monster_Zombie::Render()
{
	mImage->SetScale(3.f);

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