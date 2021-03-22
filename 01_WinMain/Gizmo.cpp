#include "pch.h"
#include "Gizmo.h"

Gizmo::Gizmo()
{
	mNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	mPenList.insert(make_pair(Color::Red, redPen));
	mPenList.insert(make_pair(Color::Green, greenPen));
	mPenList.insert(make_pair(Color::Blue, bluePen));
}

Gizmo::~Gizmo()
{
	PenIter iter = mPenList.begin();
	for (; iter != mPenList.end(); ++iter)
	{
		DeleteObject(iter->second);
	}
	DeleteObject(mNullBrush);
}

void Gizmo::DrawRect(D2D1_RECT_F rc, D2D1::ColorF::Enum color)
{
	D2D1_RECT_F rect = rc;

	ID2D1SolidColorBrush* brush;
	D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color, 1.0f), &brush);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

	D2DRenderer::GetInstance()->GetRenderTarget()->DrawRectangle(D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom),	brush, 1.0f);

	string str = to_string((int)rect.left / 64) + ", " + to_string((int)rect.top / 64);
	wstring wstr;
	wstr.assign(str.begin(), str.end());

	D2DRenderer::GetInstance()->RenderText(rect.left, rect.top, wstr, 15.f);

	brush->Release();
}

//void Gizmo::DrawEllipse(HDC hdc, float x, float y, float radius, Color color)
//{
//	HPEN pen = mPenList[color];
//
//	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, mNullBrush);
//	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
//	RenderEllipse(hdc, x, y, radius);
//	SelectObject(hdc, oldPen);
//	SelectObject(hdc, oldBrush);
//}
