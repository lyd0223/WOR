#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#include "Scene_MapTool.h"
#include "Scene_Game.h"
/*
Scene : �������� ������ ���̶�� ��
*/

/*
Initialize : �ʱ�ȭ
������ ������ �����ϱ� ���� �ʱ�ȭ �� ������ ���⼭ ����
���� �����ϱ� ���� �� �ѹ��� ����Ǵ� �Լ�
*/
void MainGame::Init()
{
	/*mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);
	SceneManager::GetInstance()->AddScene(L"MapTool", new Scene_MapTool);
	SceneManager::GetInstance()->AddScene(L"Scene_Game", new Scene_Game);
	SceneManager::GetInstance()->LoadScene(L"MapTool");*/
	ImageManager::GetInstance()->LoadFromFile(L"ex", Resources(L"FinalBossArena-sharedassets14.assets-5.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"ex");

	mAngle = 0.f;
}

/*
Release : �޸� ������ �� �ҷ��ִ� �Լ�
����Ƽ��� OnDestroy
�ش� Ŭ���� �ν��Ͻ��� �޸� ���� �� �� �� �ѹ� ȣ�����ִ� �༮
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//�̱��� �ν��Ͻ� ����


}

/*
Update : �� ������ ����Ǵ� �Լ�, ���⼭ ���� ó�� �Ѵ�.
*/
void MainGame::Update()
{
	mAngle += 360.f * Time::GetInstance()->DeltaTime();
}

/*
Render : �� ������ ����Ǵ� �Լ�, Update�� ������ Render�� ����ȴ�.
ȭ�鿡 �׷��ִ� �͵��� ���� ���⼭ ó��

�Ű����� hdc : ������ â�� HDC�� ����
*/
void MainGame::Render(HDC hdc)
{
	////������� HDC �����´�
	//HDC backDC = mBackBuffer->GetHDC();
	////HDC ������ Ư�� ������ �о������ �༮
	//PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//// ==================================================
	//{
	//	SceneManager::GetInstance()->Render(backDC);
	//}
	////====================================================
	////�ĸ���� ������ ������ â�� ��� ����
	//mBackBuffer->Render(hdc, 0, 0);

	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);
	//�� �ȿ��� �׷���
	{
		mImage->SetSize(Vector2(100, 100));
		mImage->SetScale(2.0f);
		mImage->SetAngle(mAngle);
		mImage->SetAlpha(0.3f);
		mImage->Render(Vector2(WINSIZEX / 2, WINSIZEY / 2));

		D2DRenderer::GetInstance()
			->RenderText(WINSIZEX / 2-150, WINSIZEY / 2-100, L"���°� �˾Ƽ� ���ô� ",
				30.f, D2DRenderer::DefaultBrush::Blue);
	}
	D2DRenderer::GetInstance()->EndRender();
}

void MainGame::RenderTime(HDC hdc)
{
	float worldTime = Time::GetInstance()->GetWorldTime();
	float deltaTime = Time::GetInstance()->DeltaTime();
	ULONG fps = Time::GetInstance()->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	TextOut(hdc, 10, 10, strWorldTime.c_str(), strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), strFPS.length());
}

