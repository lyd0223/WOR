#pragma once
#include "D2DRenderer.h"
inline D2D1_RECT_F RectMake(float x, float y, float width, float height)
{
	return { x,y,x + width, y + height };
}

inline D2D1_RECT_F RectMakeCenter(float x, float y, float width, float height)
{
	return { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
}

inline D2D1_RECT_F RectMakeBottom(float x, float y, float width, float height)
{
	D2D1_RECT_F result;
	result.left = x - width / 2;
	result.right = x + width / 2; 
	result.top = y - height;
	result.bottom = y;
	return result;
}

inline void RenderRect(D2D1_RECT_F rc, D2D1::ColorF color = D2D1::ColorF::Black , float strokewidth = 1.0f)
{

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	ID2D1SolidColorBrush* brush;
	D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(color, &brush);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawRectangle(rc,brush,strokewidth);
	brush->Release();
}

//inline void RenderEllipse(D2D1_RECT_F rc)
//{
//	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
//}

////원이 가지고 있는 구성요소 : 중심점, 반지름
//inline void RenderEllipse(HDC hdc,int x, int y, int radius)
//{
//	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
//}
//
//inline void RenderLine(HDC hdc,int startX, int startY, int endX, int endY)
//{
//	MoveToEx(hdc, startX, startY, NULL);
//	LineTo(hdc, endX, endY);
//}

inline float GetDistance(int aX, int aY, int bX, int bY)
{
	float width = aX - bX;
	float height = aY - bY;

	return sqrtf(width * width + height * height);
}
//
//inline bool IntersectRectToCircle(RECT rc, int x, int y, int radius)
//{
//	if ((rc.left <= x && x <= rc.right) ||
//		(rc.top <= y && y <= rc.bottom))
//	{
//		RECT newRect = rc;
//		newRect.left -= radius;
//		newRect.right += radius;
//		newRect.top -= radius;
//		newRect.bottom += radius;
//
//		if ((newRect.left <= x && x <= newRect.right) &&
//			(newRect.top <= y && y <= newRect.bottom))
//		{
//			return true;
//		}
//	}
//	
//
//	//꼭지점 비교
//	//좌상단
//	if (radius >= GetDistance(x, y, rc.left, rc.top))return true;
//	//우상단
//	if (radius >= GetDistance(x, y, rc.right, rc.top))return true;
//	//좌하단
//	if (radius >= GetDistance(x, y, rc.left, rc.bottom))return true;
//	//우하단
//	if (radius >= GetDistance(x, y, rc.right, rc.bottom))return true;
//
//	//코드가 여기까지 도달했다는 것은 위에 조건에 한번도 걸리지 않았다는 것
//	//충돌하지 않았다
//	return false;
//}

inline bool PtInRect(D2D1_RECT_F* rc, POINT pt)
{
	if (pt.x > rc->left && pt.x < rc->right &&pt.y> rc->top && pt.y < rc->bottom)
	{
		return true;
	}

	//코드가 여기까지 도달했다는 것은 위에 조건에 한번도 걸리지 않았다는 것
	//충돌하지 않았다
	return false;
}

inline bool IntersectRect(D2D1_RECT_F& rc,const D2D1_RECT_F* rc1,const D2D1_RECT_F* rc2)
{
	
	if (rc1->top <= rc2->bottom &&
		rc1->right >= rc2->left &&
		rc1->left <= rc2->right &&
		rc1->bottom >= rc2->top)
	{
		if (rc1->top > rc2->top) rc.top = rc1->top;
		else if (rc1->top < rc2->top) rc.top = rc2->top;

		if (rc1->bottom < rc2->bottom) rc.bottom = rc1->bottom;
		else if (rc1->bottom > rc2->bottom) rc.bottom = rc2->bottom;

		if (rc1->left > rc2->left) rc.left = rc1->left;
		else if(rc1->left < rc2->left) rc.left = rc2->left;

		if (rc1->right < rc2->right) rc.right = rc1->right;
		else if (rc1->right > rc2->right) rc.right = rc2->right;
		
		return true;
	}

	//코드가 여기까지 도달했다는 것은 위에 조건에 한번도 걸리지 않았다는 것
	//충돌하지 않았다
	return false;
}