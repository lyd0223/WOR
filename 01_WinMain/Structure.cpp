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
	mSizeX = sizex;
	mSizeY = sizey;
}

void Structure::Init()
{

}

void Structure::Update()
{
}

void Structure::Release()
{
}

void Structure::Render()
{
	mImage->SetScale(2.0f);
	CameraManager::GetInstance()->GetMainCamera()->Render(mImage, mX, mY);
}
