#include "pch.h"
#include "Image.h"
#include"Camera.h"
#include"Animation.h"
#include "Player.h"
#include"Monster_RapidZombie.h"
#include "Tile.h"
#include"TileMap.h"

Monster_RapidZombie::Monster_RapidZombie(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_RapidZombie::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"RapidZombie", Resources(L"Monster/RapidZombie.png"), 6, 5);
	mImage = ImageManager::GetInstance()->FindImage(L"RapidZombie");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mHp = 1;
	mSizeX = mImage->GetWidth()/6 ;
	mSizeY = mImage->GetHeight()/5 + 30 ;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 1, 0, 1, 0, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 2, 0, 3, 0, 0.5f);
	AnimationReverseSet(&mLeftAttackAnimation, false, false, 5, 0, 4, 0, 0.5f);
	AnimationSet(&mRightWalkAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 5, 2, 0, 2, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 3, 3, 4, AnimationTime);
	


	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_RapidZombie::Release()
{
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRightWalkAnimation);
	SafeDelete(mLeftWalkAnimation);
	SafeDelete(mDieAnimation);
	
}

void Monster_RapidZombie::Update()
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
	mMovingRect = RectMakeCenter(mX, mY+15, TileSize, TileSize);
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
}

void Monster_RapidZombie::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	//string str = to_string(Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize);
	//wstring wstr;
	//wstr.assign(str.begin(), str.end());
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, wstr, 30.f);
}
void Monster_RapidZombie::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_RapidZombie::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_RapidZombie::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}