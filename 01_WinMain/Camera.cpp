#include "pch.h"
#include "Camera.h"
#include "Gizmo.h"
#include "Image.h"

void Camera::Init()
{
	mTarget = nullptr;
	mX = 0;
	mY = 0;
	mSizeX = WINSIZEX;
	mSizeY = WINSIZEY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMousePosition.x = _mousePosition.x - mRect.left;
	mMousePosition.y = _mousePosition.y - mRect.top;
	mMoveSpeed = 10.f;
	
}

void Camera::Release()
{
	//얘도 쓸일이 없다 . . . 
}

void Camera::Update()
{
	mMousePosition.x = _mousePosition.x - mRect.left;
	mMousePosition.y = _mousePosition.y - mRect.top;
	switch (mMode)
	{
	case Camera::Mode::Follow:
		if (mTarget)
		{
			mX = mTarget->GetX();
			mY = mTarget->GetY();
			//멀리있으면 빨리 쫓아가야하고 가까이 있으면 천천히 쫓아가야함
			mX = Math::Lerp(mX, mTarget->GetX(), 2.f * Time::GetInstance()->DeltaTime());
			mY = Math::Lerp(mY, mTarget->GetY(), 2.f * Time::GetInstance()->DeltaTime());

			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		break;
	case Camera::Mode::Free:
		if (Input::GetInstance()->GetKey('A'))mX -= mMoveSpeed;
		if (Input::GetInstance()->GetKey('D'))mX += mMoveSpeed;
		if (Input::GetInstance()->GetKey('W'))mY -= mMoveSpeed;
		if (Input::GetInstance()->GetKey('S'))mY += mMoveSpeed;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		break;
	case Camera::Mode::MapTool:
		mSizeX = WINSIZEX;
		mSizeY = WINSIZEY;
		if (Input::GetInstance()->GetKey('A'))mX -= mMoveSpeed;
		if (Input::GetInstance()->GetKey('D'))mX += mMoveSpeed;
		if (Input::GetInstance()->GetKey('W'))mY -= mMoveSpeed;
		if (Input::GetInstance()->GetKey('S'))mY += mMoveSpeed;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		break;
	}
}

void Camera::Render()
{
	//쓸일이 없다 . . . . 
}

void Camera::Render(Image * image, float x, float y)
{
	image->Render(x - mRect.left, y - mRect.top);
}
void Camera::RenderFromBottom(Image* image, float x, float y)
{
	image->RenderFromBottom(x - mRect.left, y - mRect.top);
}
//void Camera::Render(HDC hdc, Image * image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight)
//{
//	image->Render(hdc, x - mRect.left, y - mRect.top, tempX, tempY, tempWidth, tempHeight);
//}
//
void Camera::FrameRender(Image * image, float x, float y, int frameX, int frameY)
{
	image->FrameRender(x - mRect.left, y - mRect.top, frameX, frameY);
}
void Camera::FrameRenderFromBottom(Image* image, float x, float y, int frameX, int frameY)
{
	image->FrameRenderFromBottom(x - mRect.left, y - mRect.top, frameX, frameY);
}
//
//void Camera::AlphaRender(HDC hdc, Image * image, int x, int y, float alpha)
//{
//	image->AlphaRender(hdc, x - mRect.left, y - mRect.top, alpha);
//}
//
//void Camera::AlphaFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, float alpha)
//{
//	image->AlphaFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, alpha);
//}
//
//void Camera::ScaleRender(HDC hdc, Image * image, int x, int y, int width, int height)
//{
//	image->ScaleRender(hdc, x - mRect.left, y - mRect.top, width, height);
//}
//
//void Camera::ScaleFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, int width, int height)
//{
//	image->ScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height);
//}
//
//void Camera::AlphaScaleRender(HDC hdc, Image * image, int x, int y, int width, int height, float alpha)
//{
//	image->AlphaScaleRender(hdc, x - mRect.left, y - mRect.top, width, height, alpha);
//}
//
//void Camera::AlphaScaleFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, int width, int height, float alpha)
//{
//	image->AlphaScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height, alpha);
//}

void Camera::RenderText(float x1, float y1, wstring text, int size)
{
	D2DRenderer::GetInstance()->RenderText(x1-mRect.left, y1-mRect.top, text, size,D2DRenderer::DefaultBrush::Red);
}

void Camera::RenderRect(D2D1_RECT_F rc, D2D1::ColorF color)
{
	rc.left -= mRect.left;
	rc.right -= mRect.left;
	rc.top -= mRect.top;
	rc.bottom -= mRect.top;
	::RenderRect(rc,color);
}

void Camera::RenderGizmoRect( D2D1_RECT_F rc, D2D1::ColorF::Enum color)
{
	rc.left -= mRect.left;
	rc.right -= mRect.left;
	rc.top -= mRect.top;
	rc.bottom -= mRect.top;
	Gizmo::GetInstance()->DrawRect(rc,color);
}

//void Camera::RenderEllipse(HDC hdc, float x, float y, float radius)
//{
//	RenderEllipse(hdc, x - mRect.left, y - mRect.top, radius);
//}

bool Camera::IsInCameraArea(float x, float y, float width, float height)
{
	D2D1_RECT_F rc = RectMakeCenter(x, y, width, height);
	return IsInCameraArea(rc);
}

bool Camera::IsInCameraArea(D2D1_RECT_F rc)
{
	if (rc.right < mRect.left)return false;
	if (rc.left > mRect.right)return false;
	if (rc.bottom < mRect.top)return false;
	if (rc.top > mRect.bottom)return false;

	return true;
}
