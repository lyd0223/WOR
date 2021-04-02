#include "pch.h"
#include "Scene_Ending.h"
#include "Image.h"

void Scene_Ending::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"BackGround", Resources(L"Title/BackGround0/png");
	mImage = ImageManager::GetInstance()->FindImage(L"BackGround");

	mAlpha = 1.f;
}

void Scene_Ending::Release()
{
}

void Scene_Ending::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();
	mAlpha -= 0.02f;
	if (mFrameCount > 1.5)
	{
		SceneManager::GetInstance()->LoadScene(L"House");
	}
}

void Scene_Ending::Render()
{
	mImage->SetAlpha(mAlpha);
	mImage->Render(0, 0);
}
