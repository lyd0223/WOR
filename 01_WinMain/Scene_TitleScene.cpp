#include "pch.h"
#include "Scene_TitleScene.h"
#include "Image.h"

void Scene_TitleScene::Init()
{
	if (!mBackImageList.empty()) return;
	SoundPlayer::GetInstance()->Play(L"TitleScreen", 0.5f);

	ImageManager::GetInstance()->LoadFromFile(L"BackGround0", Resources(L"Title/BackGround0.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround1", Resources(L"Title/BackGround1.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround2", Resources(L"Title/BackGround2.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround3", Resources(L"Title/BackGround3.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround4", Resources(L"Title/BackGround4.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround5", Resources(L"Title/BackGround5.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround6", Resources(L"Title/BackGround6.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround7", Resources(L"Title/BackGround7.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BackGround8", Resources(L"Title/BackGround8.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Title", Resources(L"Title/Title.png"));

	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround0"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround1"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround2"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround3"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround4"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround5"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround6"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround7"));
	mBackImageList.push_back(ImageManager::GetInstance()->FindImage(L"BackGround8"));
	mTitleImage = ImageManager::GetInstance()->FindImage(L"Title");
	
	TitleButton temp0{ RectMakeCenter(WINSIZEX / 2, 350 + 0 * 55, 200, 40), L"새로운 게임" , 20, true };
	mButtonList.push_back(temp0);
	TitleButton temp1{ RectMakeCenter(WINSIZEX / 2, 350 + 1 * 55, 200, 40), L"맵툴", 20, true };
	mButtonList.push_back(temp1);
	TitleButton temp2{ RectMakeCenter(WINSIZEX / 2, 350 + 2 * 55, 200, 40), L"대전", 20, false };
	mButtonList.push_back(temp2);
	TitleButton temp3{ RectMakeCenter(WINSIZEX / 2, 350 + 3 * 55, 200, 40), L"옵션", 20, false };
	mButtonList.push_back(temp3);
	TitleButton temp4{ RectMakeCenter(WINSIZEX / 2, 350 + 4 * 55, 200, 40), L"제작진", 20, false };
	mButtonList.push_back(temp4);
	TitleButton temp5{ RectMakeCenter(WINSIZEX / 2, 350 + 5 * 55, 200, 40), L"종료", 20, true };
	mButtonList.push_back(temp5);
	
	for (int i = 0; i < mButtonList.size(); i++) 
	{
		D2D1_RECT_F rect = RectMakeCenter(WINSIZEX / 2, 350 + i * 55, 200, 40);
	}

	mFontSize = 20.f;
	mPressWstr = L"PRESS SPACE BUTTON";
	mTitlePoint.x = WINSIZEX / 2;
	mTitlePoint.y = WINSIZEY / 2;

	mBackGroundCount = 0;
	mButtonCount = 0;
	mAlpha = 1.f;

	mTitleState = TitleState::Scene1;
}

void Scene_TitleScene::Release()
{
	
}

void Scene_TitleScene::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();
	
	switch (mTitleState)
	{
	case TitleState::Scene1:
		if (Input::GetInstance()->GetKeyDown(VK_LEFT))
		{
			mBackGroundCount--;
			if (mBackGroundCount < 0) mBackGroundCount = 8;
		}

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
		{
			mBackGroundCount++;
			if (mBackGroundCount > 8) mBackGroundCount = 0;
		}

		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			mIsTitleMove = true;
			mAlpha = 1.f;
		}

		if (mFrameCount > 0.3)
		{
			mFrameCount = 0;
		}
		break;
	case TitleState::Scene2:
		if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		{
			mIsTitleMove = true;
		}

		if (Input::GetInstance()->GetKeyDown(VK_UP))
		{
			mButtonCount--;
			if (mButtonCount < 0) mButtonCount = 5;
			SoundPlayer::GetInstance()->Play(L"MenuMove", 1.f);
		}

		if (Input::GetInstance()->GetKeyDown(VK_DOWN))
		{
			mButtonCount++;
			if (mButtonCount > 5) mButtonCount = 0;
			SoundPlayer::GetInstance()->Play(L"MenuMove", 1.f);
		}

		if ((Input::GetInstance()->GetKeyDown(VK_SPACE) && mButtonList[mButtonCount].IsActive) ||
			(PtInRect(&mButtonList[mButtonCount].Rect, _mousePosition) && (Input::GetInstance()->GetKeyDown(VK_LBUTTON) && mButtonList[mButtonCount].IsActive)))
		{
			switch (mButtonCount)
			{
			case 0:
				SoundPlayer::GetInstance()->Stop(L"TitleScreen");
				SceneManager::GetInstance()->LoadScene(L"Tutorial");
				break;
			case 1:
				SoundPlayer::GetInstance()->Stop(L"TitleScreen");
				SceneManager::GetInstance()->LoadScene(L"MapTool");
				break;
			case 5:
				PostQuitMessage(0);
				break;
			}
		}
		break;	
	}

	for (int i = 0; i < mButtonList.size(); i++)
	{
		if (PtInRect(&mButtonList[i].Rect, _mousePosition)) 
		{
			mButtonCount = i;
		}
	}

	if (mIsTitleMove)
	{
		switch (mTitleState)
		{
		case TitleState::Scene1:
			mTitlePoint.y -= 5.f;
			mAlpha -= 0.02f;

			if (mTitlePoint.y < 250.f)
			{
				mIsTitleMove = false;
				mAlpha = 0.3f;
				mTitleState = TitleState::Scene2;
			}
			break;
		case TitleState::Scene2:
			mTitlePoint.y += 5.f;
			mAlpha += 0.02f;
			

			if (mTitlePoint.y > WINSIZEY / 2)
			{
				mTitleState = TitleState::Scene1;
				mIsTitleMove = false;
				mAlpha = 1.f;
			}
			break;
		}
	}

	for (int i = 0; i < mButtonList.size(); i++)
	{
		if (i == mButtonCount)
		{
			mButtonList[i].FontSize = 25;
			if (mButtonList[i].IsActive)
				mButtonList[i].Brush = D2DRenderer::DefaultBrush::White;
			else
				mButtonList[i].Brush = D2DRenderer::DefaultBrush::Gray;
		}
		
		else
		{
			mButtonList[i].FontSize = 20;
			mButtonList[i].Brush = D2DRenderer::DefaultBrush::Gray;
		}
	}
}

void Scene_TitleScene::Render()
{
	switch (mTitleState)
	{
	case TitleState::Scene1:
		mBackImageList[mBackGroundCount]->SetAlpha(mAlpha);
		mBackImageList[mBackGroundCount]->Render(WINSIZEX / 2, WINSIZEY / 2);
		D2DRenderer::GetInstance()->RenderText(
			WINSIZEX / 5 + 50,
			WINSIZEY - 150,
			mPressWstr,
			COLORREF(RGB(255, 255, 255)),
			mAlpha,
			40.f,
			DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER
		);
		break;
	case TitleState::Scene2:
		mBackImageList[mBackGroundCount]->SetAlpha(mAlpha);
		mBackImageList[mBackGroundCount]->Render(WINSIZEX / 2, WINSIZEY / 2);
		for (int i = 0; i < mButtonList.size(); i++) 
		{
			//RenderRect(mButtonList[i].Rect);
			D2DRenderer::GetInstance()->RenderTextField(mButtonList[i].Rect.left, mButtonList[i].Rect.top,
				mButtonList[i].Name, mButtonList[i].FontSize, mButtonList[i].Rect.right - mButtonList[i].Rect.left,
				mButtonList[i].Rect.bottom - mButtonList[i].Rect.top, mButtonList[i].Brush,
				DWRITE_TEXT_ALIGNMENT_CENTER);
			//D2DRenderer::GetInstance()->RenderText(
			//);
		}
		break;
	}
	
	mTitleImage->Render(mTitlePoint.x, mTitlePoint.y);
}