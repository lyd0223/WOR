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
	/*if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&mRect, _mousePosition))
		{
			if(mName=="Load")
				Load();
		}
		else if (PtInRect(&mSaveButton, _mousePosition))
		{
			Save();
		}
		else if (PtInRect(&mGameStartButton, _mousePosition))
		{
			SceneManager::GetInstance()->LoadScene(L"Tutorial");
			return;
		}
		else if (PtInRect(&mRedoButton, _mousePosition))
			Redo();
		else if (PtInRect(&mUndoButton, _mousePosition))
			Undo();

		else if (PtInRect(&mPalleteRihgtButton, _mousePosition))
		{

			mPalletePageX++;
		}
		else if (PtInRect(&mPalleteLeftButton, _mousePosition))
		{

			mPalletePageX--;
		}
		if (PtInRect(&mPalleteUpButton, _mousePosition))
		{
			mPalletePageY--;
		}
		if (PtInRect(&mPalleteDownButton, _mousePosition))
		{
			mPalletePageY++;
		}
	}*/
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
