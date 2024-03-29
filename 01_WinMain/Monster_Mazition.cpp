#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_Mazition.h"
#include "Tile.h"
#include"TileMap.h"

Monster_Mazition::Monster_Mazition(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_Mazition::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Mazition", Resources(L"Monster/Mazition.png"), 6, 5);
	
	mImage = ImageManager::GetInstance()->FindImage(L"Mazition");
	mMonsterActState = MonsterActState::RightIdle;
	mMonsterState = MonsterState::Idle;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mSpeed = 500.f;
		mHp = 50;
	mSizeX = mImage->GetFrameSize().__typeToGetX() *2;
	mSizeY = mImage->GetFrameSize().__typeToGetY()  * 2 - 20;
	mIsAct = false;

	mRect = RectMakeCenter(mX, mY - 20, mSizeX, mSizeY);
	mMonsterType = MonsterType::Normal;
	mMonsterName = MonsterName::Mazition;
	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 4, 2, 4, 2, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 1, 0, 3, 0, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 3, 2, 1, 2, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 0, 1, 4, 1, 0.5f);
	AnimationReverseSet(&mLeftAttackAnimation, false, false, 4, 3, 0, 3, 0.5f);
	AnimationSet(&mRightHitAnimation, false, false, 5, 0, 5, 0, AnimationTime);
	AnimationSet(&mLeftHitAnimation, false, false, 5, 1, 5, 1, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 4, 5, 4, AnimationTime);


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_Mazition::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightHitAnimation);
	SafeDelete(mLeftHitAnimation);
	SafeDelete(mDieAnimation);
}

void Monster_Mazition::Update()
{
	mHitTime += Time::GetInstance()->DeltaTime();
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

			//아이들
			if (mMonsterToPlayerDistance >= 20.5f)
			{
				AnimationChange(mRightIdleAnimation);
				mMonsterActState = MonsterActState::RightIdle;
				mMonsterState = MonsterState::Idle;
				//mPathList.clear();
				mIsAct = false;

			}
			//추격
			
				if (mMonsterToPlayerDistance < 20.5f && mMonsterToPlayerDistance >= 15.f)
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
						
					//길찾기
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
			

			if (mCurrentAnimation->GetIsPlay() == false)
			{
				if (mMonsterToPlayerDistance < 15.5f)
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
							if (mCurrentAnimation->GetNowFrameX() == 4 && mCurrentAnimation->GetNowFrameY() == 1)
							{
								SkillManager::GetInstance()->WaterBallSkill("WaterBall", lineX, lineY, mMonsterToPlayerAngle, 0);
							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::RightAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mRightAttackAnimation->GetNowFrameX() == 4)
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
							if (mCurrentAnimation->GetNowFrameX() == 0 && mCurrentAnimation->GetNowFrameY() == 3)
							{
								SkillManager::GetInstance()->WaterBallSkill("WaterBall", lineX, lineY, mMonsterToPlayerAngle, 0);

							}
							int frame = mCurrentAnimation->GetNowFrameX();
							mMonsterActState = MonsterActState::LeftAttack;
							mMonsterState = MonsterState::Attack;
							mIsAct = false;
							if (mLeftAttackAnimation->GetNowFrameX() == 0)
							{
								AnimationChange(mLeftIdleAnimation);
							}
						}

						mIsAct = true;
					}

				}
			}
			

		}
		if (mHp <= 0)
		{
			if (mCurrentAnimation != mDieAnimation)
			{
				SoundPlayer::GetInstance()->Play(L"EnemyDeadSound", 1.f);
				AnimationChange(mDieAnimation);
				mMonsterActState = MonsterActState::Die;
				mMonsterState = MonsterState::Die;

			}
		}
		//공격 라인--
		lineX = mX + 100 * cosf(mMonsterToPlayerAngle);
		lineY = mY + 100 * -sinf(mMonsterToPlayerAngle);
		//---
		mCurrentAnimation->Update();
		mRect = RectMakeCenter(mX, mY - 20 , mSizeX, mSizeY);
		mMovingRect = RectMakeCenter(mX, mY + 10, TileSize, TileSize);
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
	if (mDieAnimation->GetNowFrameX() == 5)mIsDestroy = true;
	return;
}

void Monster_Mazition::Render()
{
	mImage->SetScale(3.f);
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{

		CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	}
	//string str = to_string(Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize);
	//wstring wstr;
	//wstr.assign(str.begin(), str.end());
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, wstr, 30.f);
}
void Monster_Mazition::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Mazition::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_Mazition::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}