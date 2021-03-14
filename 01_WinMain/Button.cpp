#include "pch.h"
#include "Button.h"

Button::Button(string name,float x, float y, float sizex, float sizey)
{
	mName = name;
	mX = x;
	mY = y;
	mSizeX = sizex;
	mSizeY = sizey;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Button::Init()
{
	
}

void Button::Update()
{
	
}

void Button::Release()
{
}

void Button::Render()
{
	RenderRect(mRect);
	wstring name;
	name.assign(mName.begin(), mName.end());
	D2DRenderer::GetInstance()->RenderText(mRect.left, mRect.top, name, 10.f, D2DRenderer::DefaultBrush::Blue);
}
