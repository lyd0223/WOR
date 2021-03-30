#include "pch.h"
#include "UI_ESC.h"
#include "Image.h"
#include "Scene_TitleScene.h"

UI_ESC::UI_ESC(const string & name)
{
	mName = name;
}

void UI_ESC::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"ESCImage", Resources(L"UI/ESCImage.png"));
	mEscImage = ImageManager::GetInstance()->FindImage(L"ESCImage");

	mEscTextList.push_back(new EscText(RectMakeCenter(WINSIZEX / 2, 320, 200, 30), L"계속", 25.f, true, D2DRenderer::DefaultBrush::Gray));
	mEscTextList.push_back(new EscText(RectMakeCenter(WINSIZEX / 2, 376, 200, 30), L"타이틀 화면", 25.f, true, D2DRenderer::DefaultBrush::Gray));
	mEscTextList.push_back(new EscText(RectMakeCenter(WINSIZEX / 2, 442, 200, 30), L"게임 종료", 25.f, true, D2DRenderer::DefaultBrush::Gray));
	
	mIndex = 0;
}

void UI_ESC::Release()
{
}

void UI_ESC::Update()
{
	if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
	{
		ObjectManager::GetInstance()->PopInterface();
	}

	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		switch (mIndex)
		{
		case 0:
			ObjectManager::GetInstance()->PopInterface();
			break;
		case 1:
			ObjectManager::GetInstance()->InterfaceClear();
			//SceneManager::GetInstance()->DeleteScene(L"Title");
			//SceneManager::GetInstance()->AddScene(L"Title", new Scene_TitleScene());
			SceneManager::GetInstance()->LoadScene(L"Title");
			break;
		case 2:
			PostQuitMessage(0);
			break;
		}
	}

	if (Input::GetInstance()->GetKeyDown(VK_UP))
	{
		mIndex--;
		if (mIndex < 0) mIndex = 2;
	}

	else if (Input::GetInstance()->GetKeyDown(VK_DOWN))
	{
		mIndex++;
		if (mIndex > 2) mIndex = 0;
	}

	for (int i = 0; i < mEscTextList.size(); i++)
	{
		if (i == mIndex)
		{
			mEscTextList[i]->FontSize = 25;
			if (mEscTextList[i]->IsActive)
				mEscTextList[i]->Brush = D2DRenderer::DefaultBrush::White;
			else
				mEscTextList[i]->Brush = D2DRenderer::DefaultBrush::Gray;
		}

		else
		{
			mEscTextList[i]->FontSize = 20;
			mEscTextList[i]->Brush = D2DRenderer::DefaultBrush::Gray;
		}
	}
}

void UI_ESC::Render()
{
	mEscImage->Render(WINSIZEX / 2, WINSIZEY / 2);
	for (int i = 0; i < mEscTextList.size(); i++)
	{
		D2DRenderer::GetInstance()->RenderTextField(
			mEscTextList[i]->Rect.left,
			mEscTextList[i]->Rect.top,
			mEscTextList[i]->Name,
			mEscTextList[i]->FontSize,
			mEscTextList[i]->Rect.right - mEscTextList[i]->Rect.left,
			mEscTextList[i]->Rect.bottom - mEscTextList[i]->Rect.top,
			mEscTextList[i]->Brush,
			DWRITE_TEXT_ALIGNMENT_CENTER
		);
	}
}
