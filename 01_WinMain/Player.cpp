#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"Player.bmp"), 64, 128, 2, 4,true);
	mImage = IMAGEMANAGER->FindImage(L"Player");

	mSpeed = 5;

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Release()
{
}

void Player::Update()
{
	if (Input::GetInstance()->GetKey('W'))
	{
		mY -= mSpeed;
	}
	else if (Input::GetInstance()->GetKey('S'))
	{
		mY += mSpeed;
	}
	else if (Input::GetInstance()->GetKey('A'))
	{
		mX -= mSpeed;
	}
	else if (Input::GetInstance()->GetKey('D'))
	{
		mX += mSpeed;
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	

}

void Player::Render(HDC hdc)
{
	
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top,0,2);

	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnimation->GetNowFrameX(),
	//	mCurrentAnimation->GetNowFrameY());
}
