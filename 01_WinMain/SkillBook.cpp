#include "pch.h"
#include "SkillBook.h"
#include "Animation.h"
#include "Time.h"
#include "Camera.h"
#include "Image.h"
SkillBook::SkillBook(float x, float y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"SkillBook");
	mName = "SkillBook";
	mX = x;
	mY = y;
	mSizeX = mImage->GetWidth()/13 * 2;
	mSizeY = mImage->GetHeight()/3 * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void SkillBook::Init()
{
	mBookIsOpen = 0;
	
	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 3, 0, true);
	mIdleAnimation->SetIsLoop(false);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mOpenAnimation = new Animation();
	mOpenAnimation->InitFrameByStartEnd(0, 1, 13, 1, false);
	mOpenAnimation->SetIsLoop(false);
	mOpenAnimation->SetFrameUpdateTime(0.3f);
	mCloseAnimation = new Animation();
	mCloseAnimation->InitFrameByBackStartEnd(13, 1, 0, 1, false);
	mCloseAnimation->SetIsLoop(false);
	mCloseAnimation->SetFrameUpdateTime(0.3f);
	mCurrentAnimation = mIdleAnimation;
}

void SkillBook::Release()
{
}

void SkillBook::Update()
{
	mCurrentAnimation->Update();
	if (!mBookIsOpen)
	{
		if ((int)(Time::GetInstance()->GetWorldTime()) % 100 == 0)
			mCurrentAnimation->Play();
		D2D1_RECT_F rctemp;
		D2D1_RECT_F playerRect = ObjectManager::GetInstance()->FindObject("Player")->GetRect();
		if (IntersectRect(rctemp, &playerRect, &mRect))
		{
			mCurrentAnimation = mOpenAnimation;
			mCurrentAnimation->Play();
			if (Input::GetInstance()->GetKeyDown('F'))
			{
				//여기에 추가


				//
			}
		}
		else
		{
			mCurrentAnimation = mCloseAnimation;
			mCurrentAnimation->Play();
		}
	}
	else
	{

	}
}

void SkillBook::Render()
{
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	mImage->SetScale(2.0f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}
