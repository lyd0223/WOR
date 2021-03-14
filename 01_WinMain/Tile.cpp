#include "pch.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "Gizmo.h"

Tile::Tile(Image* image, float x, float y, float sizeX, float sizeY, int frameIndexX, int frameIndexY)
{
	mImage = image;
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mFrameIndexX = frameIndexX;
	mFrameIndexY = frameIndexY;
}
void Tile::Update()
{
	/*if (mImage->GetKey() == L"")
	{
		mType = Type::Cliff;
	}
	else if (mImage->GetKey() == L"")
	{
		mType = Type::Cliff;
	}
	else if (mImage->GetKey() == L"")
	{
		mType = Type::Cliff;
	}
	else if (mImage->GetKey() == L"")
	{
		mType = Type::Cliff;
	}*/
}

void Tile::Render()
{
	if (mImage != nullptr)
	{
		mImage->SetScale(2.f);
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX+(mSizeX/2.f), mY+(mSizeY/2.f), mFrameIndexX, mFrameIndexY);
		
	}
	
}

