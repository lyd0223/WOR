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
	mSpeed = 3.f;
	mSizeX = mImage->GetFrameSize().__typeToGetX() * 4 - 120;
	mSizeY = mImage->GetFrameSize().__typeToGetY() * 4 - 50;
	mIsAct = false;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mRightIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mLeftIdleAnimation, false, false, 4, 2, 4, 2, AnimationTime);
	AnimationSet(&mRightWalkAnimation, false, false, 1, 0, 3, 0, AnimationTime);
	AnimationReverseSet(&mLeftWalkAnimation, false, false, 3, 2, 1, 2, AnimationTime);
	AnimationSet(&mRightAttackAnimation, false, false, 0, 1, 4, 1, AnimationTime);
	AnimationReverseSet(&mLeftAttackAnimation, false, false, 4, 3, 0, 3, AnimationTime);
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

	mMonsterToPlayerDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) / TileSize;
	mMonsterToPlayerAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
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
	if (mCurrentAnimation->GetIsPlay() == false)
	{
		if (mMonsterToPlayerDistance < 5.5f && mMonsterToPlayerDistance >= 2.1f)
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


		if (mMonsterToPlayerDistance < 2.1f)
		{

			//오른쪽 공격
			if (mMonsterToPlayerAngle < (PI / 4) || mMonsterToPlayerAngle >(PI2 - (PI / 4)))
			{
				if (mIsAct == true && mCurrentAnimation != mRightAttackAnimation)
				{
					AnimationChange(mRightAttackAnimation);
					mMonsterActState = MonsterActState::RightAttack;
					mMonsterState = MonsterState::Attack;
					mIsAct = false;
				}
				if (mRightAttackAnimation->GetIsPlay() == false)mIsAct = true;

			}
			//왼쪽공격
			else if (mMonsterToPlayerAngle > ((PI / 2) + (PI / 4)) && mMonsterToPlayerAngle < (PI + (PI / 4)))
			{
				if (mLeftAttackAnimation->GetIsPlay() == false)mIsAct == true;
				if (mIsAct == true && mCurrentAnimation != mLeftAttackAnimation)
				{
					AnimationChange(mLeftAttackAnimation);
					mMonsterActState = MonsterActState::LeftAttack;
					mMonsterState = MonsterState::Attack;
					mIsAct = false;
				}
			}
			//위
			else if (mMonsterToPlayerAngle > PI / 4 && mMonsterToPlayerAngle < ((PI / 2) + (PI / 4)))
			{
				if (mUpAttackAnimation->GetIsPlay() == false)mIsAct == true;
				if (mIsAct == true && mCurrentAnimation != mUpAttackAnimation)
				{
					AnimationChange(mUpAttackAnimation);
					mMonsterActState = MonsterActState::UpAttack;
					mMonsterState = MonsterState::Attack;
					mIsAct = false;
				}
			}
			//아래
			else if (mMonsterToPlayerAngle > (PI + (PI / 4)) && mMonsterToPlayerAngle < (PI2 - (PI / 4)))
			{
				if (mUpAttackAnimation->GetIsPlay() == false)mIsAct == true;
				if (mIsAct == true && mCurrentAnimation != mDownAttackAnimation)
				{
					AnimationChange(mDownAttackAnimation);
					mMonsterActState = MonsterActState::DownAttack;
					mMonsterState = MonsterState::Attack;
					mIsAct = false;
				}
			}
		}


	}
	if (mHp <= 0)
	{
		AnimationChange(mDieAnimation);
		mMonsterActState = MonsterActState::Die;
		mMonsterState = MonsterState::Die;
	}

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
}

void Monster_Mazition::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());

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