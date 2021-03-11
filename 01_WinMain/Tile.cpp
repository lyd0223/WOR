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

void Tile::Render(HDC hdc)
{
	/*CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
	if (mImage != nullptr)
	{
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(hdc, mImage, mX, mY, mFrameIndexX, mFrameIndexY);
	}

	CameraManager::GetInstance()->GetMainCamera()->RenderGizmoRect(hdc, mRect);*/
	
}

