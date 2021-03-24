#include "pch.h"
#include "Image.h"
#include "Player.h"
#include"Camera.h"
#include"Animation.h"
#include"Monster_MuscleMan.h"
#include "Tile.h"
#include "TileMap.h"

Monster_MuscleMan::Monster_MuscleMan(const string& name, float x, float y)
	: MonsterObject(name)
{
	mName = name;
	mX = x;
	mY = y;
}

void Monster_MuscleMan::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MuscleMan", Resources(L"Monster/MuscleMan.png"), 6, 2);
	mImage = ImageManager::GetInstance()->FindImage(L"MuscleMan");
	mMonsterActState = MonsterActState::RightIdle;
	mSpeed = 3.f;
	mSizeX = TileSize + 50;
	mSizeY = TileSize + 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	AnimationSet(&mIdleAnimation, false, false, 0, 0, 0, 0, AnimationTime);
	AnimationSet(&mDieAnimation, false, false, 0, 1, 5, 1, AnimationTime);
	AnimationSet(&mAttackAnimation, false, false, 4, 0, 4, 0, AnimationTime);
	AnimationSet(&mAttackReadyAnimation, false, false, 1, 0, 3, 0, AnimationTime);

	mMovingRect = RectMakeCenter(mX, mY + 50, TileSize, TileSize);

	mCurrentAnimation = mIdleAnimation;
	mCurrentAnimation->Play();
}

void Monster_MuscleMan::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mDieAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mAttackReadyAnimation);

}

void Monster_MuscleMan::Update()
{
	if (mPathList.size() > 1)
	{
		float nextX = mPathList[1]->GetX();
		float nextY = mPathList[1]->GetY();
		float angle = Math::GetAngle(mX, mY, nextX, nextY);
		
		POINT point;
		point.x = mMovingRect.left + (mMovingRect.right - mMovingRect.left);
		point.y = mMovingRect.top + (mMovingRect.bottom - mMovingRect.top);

		if (PtInRect(&mPathList[0]->GetRect(), point))
		{
			mPathList.erase(mPathList.begin());
		}

		mX += cosf(angle) * mSpeed;
		mY += -sinf(angle) * mSpeed;
	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
<<<<<<< Updated upstream
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
=======
	mMovingRect = RectMakeCenter(mX, mY + 50, TileSize, TileSize);
>>>>>>> Stashed changes
}

void Monster_MuscleMan::Render()
{
	mImage->SetScale(2.f);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	for (int i = 0; i < mPathList.size(); i++)
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(mPathList[i]->GetRect());
	}

}
void Monster_MuscleMan::AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;

	a->InitFrameByStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Reverse);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_MuscleMan::AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime)
{
	*animation = new Animation;
	Animation* a = *animation;
	a->InitFrameByBackStartEnd(StartindexX, StartindexY, EndindexX, EndindexY, Rivers);
	a->SetIsLoop(Loop);
	a->SetFrameUpdateTime(animationTime);

}

void Monster_MuscleMan::AnimationChange(Animation* changeanimation)
{
	mCurrentAnimation->Stop();
	mCurrentAnimation = changeanimation;
	mCurrentAnimation->Play();
}