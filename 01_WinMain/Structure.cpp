#include "pch.h"
#include "Structure.h"
#include "Image.h"
#include "Camera.h"

Structure::Structure(const string& name,Image *image ,float x, float y, float sizex, float sizey)
{
	mImage = image;
	mName = name;
	mX = x;
	mY = y;
	mSizeX = sizex*1.5f;
	mSizeY = sizey*1.5f;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Structure::Init()
{
	mPortalOn = 0;
	mPortalImage = ImageManager::GetInstance()->FindImage(L"PortalOn");
}

void Structure::Update()
{
	if (mName == "Portal")
	{
		D2D1_RECT_F rc = ObjectManager::GetInstance()->FindObject("Player")->GetRect();
		D2D1_RECT_F rctemp;
		if (IntersectRect(rctemp, &rc, &mRect))
		{
			mPortalOn = 1;
		}
		else
			mPortalOn = 0;
	}
}

void Structure::Release()
{
}

void Structure::Render()
{
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
	mImage->SetScale(1.5f);
	CameraManager::GetInstance()->GetMainCamera()->Render(mImage, mX, mY);
	
	
	if (mPortalOn)
	{
		mPortalImage->SetScale(1.5f);
		CameraManager::GetInstance()->GetMainCamera()->Render(mPortalImage, mX, mY);

	}
}
