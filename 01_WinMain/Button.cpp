#include "pch.h"
#include "Button.h"
#include "Image.h"

Button::Button(string name,float x, float y, float sizex, float sizey)
{
	mName = name;
	mX = x;
	mY = y;
	mSizeX = sizex;
	mSizeY = sizey;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	wstring wstrtemp;
	wstrtemp.assign(mName.begin(), mName.end());
	mImage = ImageManager::GetInstance()->FindImage(wstrtemp);
}

void Button::Init()
{
	
}

void Button::Update()
{
	if (PtInRect(&mRect, _mousePosition))
	{
		mImage->SetScale(2.1f);
	}
	else
	mImage->SetScale(2.0f);
}

void Button::Release()
{
}

void Button::Render()
{
	mImage->Render(mX, mY);
	
}

void Button::BookOpen()
{
	mX--;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Button::BookClose()
{
	mX++;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}