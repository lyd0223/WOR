#include "pch.h"
#include "Scene_Ending.h"
#include "Image.h"

void Scene_Ending::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Ending", Resources(L"UI/Ending.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"Ending");

	mAlpha = 1.f;

	mRectList.push_back(RectMake(640, 213, 320, 20));
	mRectList.push_back(RectMake(640, 248, 320, 20));
	
	float time = Storage::GetInstance()->GetGameTime();
	int minute = (int)time / 60;
	int second = (int)time % 100;
	string str = to_string(minute) + " : " + to_string(second);
	mTime.assign(str.begin(), str.end());
	mMonsterCount = to_wstring(Storage::GetInstance()->GetMonsterDeathCount());
}

void Scene_Ending::Release()
{
}

void Scene_Ending::Update()
{	
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		SceneManager::GetInstance()->LoadScene(L"House");
	if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		SceneManager::GetInstance()->LoadScene(L"Title");
}

void Scene_Ending::Render()
{
	mImage->SetAlpha(mAlpha);
	mImage->Render(WINSIZEX / 2, WINSIZEY / 2);

	D2DRenderer::GetInstance()->RenderTextField(mRectList[0].left, mRectList[0].top, mTime, D2D1::ColorF::White,
		20, 320, 20, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
	D2DRenderer::GetInstance()->RenderTextField(mRectList[1].left, mRectList[1].top, mMonsterCount,
		D2D1::ColorF::White, 20, 320, 20, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
}
