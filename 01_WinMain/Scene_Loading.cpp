#include "pch.h"
#include "Scene_Loading.h"
#include "Image.h"
void Scene_Loading::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}


void Scene_Loading::Init()
{
	mLoadIndex = 0;
	mCharacterX = 50;
	mTextY = WINSIZEY - 250;
}

void Scene_Loading::Release()
{
}

void Scene_Loading::Update()
{
	if (mLoadIndex >= mLoadList.size())
	{
		SceneManager::GetInstance()->LoadScene(L"Field");
		return;
	}

	function<void(void)> func = mLoadList[mLoadIndex];
	func();
	mLoadIndex++;
	mCharacterX += 200;
	mStr += ("\n" + mStr2);
	if (mLoadIndex == 1)
	{
		mStr2 = "Load Image...\nLoad Sound...";
	}

	if (mLoadIndex == 2)
	{
		mStr2 = "Create Random Map...";
	}
	if (mLoadIndex == 3)
		mStr2 = "Put Roads Between the Rooms...";
	if (mLoadIndex == 4)
		mStr2 = "Are You Ready?";
	
	mTextY += 10;
}

void Scene_Loading::Render()
{
	ImageManager::GetInstance()->FindImage(L"Loading")->Render(WINSIZEX/2, WINSIZEY/2);
	ImageManager::GetInstance()->FindImage(L"LoadingCharacter")->Render(mCharacterX, 200);

	
	wstring wstr,wstr2; 
	wstr.assign(mStr.begin(), mStr.end());
	wstr2.assign(mStr2.begin(), mStr2.end());
	D2DRenderer::GetInstance()->RenderText(
		WINSIZEX / 2 - 100,
		mTextY,
		wstr,
		COLORREF(RGB(255, 255, 255)),
		0.5f,
		20.f,
		DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING
	);
	D2DRenderer::GetInstance()->RenderText(
		WINSIZEX / 2 - 100,
		mTextY+70,
		wstr2,
		COLORREF(RGB(255, 255, 255)),
		1.0f,
		20.f,
		DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING
	);
	
}
