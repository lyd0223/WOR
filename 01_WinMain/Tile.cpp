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

void Tile::Render()
{
	if (mImage != nullptr)
	{
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX+mSizeX/2, mY+mSizeY/2, mFrameIndexX, mFrameIndexY);
	}

	CameraManager::GetInstance()->GetMainCamera()->RenderGizmoRect(mRect);
	
}

