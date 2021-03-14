#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#include "Scene_MapTool.h"
#include "Scene_Game.h"
#include "FireBoss.h"
#include "Player.h"
#include "FireBall.h"
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
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);*/
	SceneManager::GetInstance()->AddScene(L"MapTool", new Scene_MapTool);
	SceneManager::GetInstance()->LoadScene(L"MapTool");

	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, new FireBoss);
	float x = 1000;
	float y = 70;
	
	mFireBoss = new FireBoss("FireBoss",  x, y);
	mFireBoss->Init();

	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = 50;
	mSizeY = 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
	mAngle = Math::GetAngle(mFireBoss->GetX(), mFireBoss->GetY(), mX, mY);
	
	mFireBall = new FireBall("FireBall", mFireBoss->GetX(), mFireBoss->GetY(), mAngle);
	mFireBall->Init();
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
	//mAngle += 360 * Time::GetInstance()->DeltaTime();
	//SceneManager::GetInstance()->Update();
	if (Input::GetInstance()->GetKeyDown(VK_SPACE)) {
		mFireBall = new FireBall("FireBall", mFireBoss->GetX(), mFireBoss->GetY(), mAngle);
		mFireBall->Init();
	}
	mAngle = Math::GetAngle(mFireBoss->GetX(), mFireBoss->GetY(), mX, mY);
	mFireBoss->Update();
	mFireBall->Update();
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

	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Aqua);
	//�� �ȿ��� �׷���
	{
		mFireBoss->Render();
		mFireBall->Render();
		RenderRect(mRect);

		//mImage->SetSize(Vector2(100, 100));
		//mImage->SetScale(3.0f);
		//mImage->SetAngle(mAngle);
		//mImage->SetAlpha(0.3f);
		//mImage->FrameRender(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100, 0, 0);
		//D2D1_RECT_F rc = { 100.f,100.f,200.f,200.f };
		//D2D1_RECT_F rc2 = { 150.f,150.f,250.f,250.f };
		//
		//RenderRect(rc, D2D1::ColorF::Red);
		//RenderRect(rc2, D2D1::ColorF::Red);
		//D2D1_RECT_F rctemp;
		//if (IntersectRect(rctemp, &rc, &rc2))
		//{
		//	RenderRect(rctemp, D2D1::ColorF::White);
		//}
		//
		//	
		//D2DRenderer::GetInstance()
		//	->RenderText(WINSIZEX / 2-150, WINSIZEY / 2-100, L"���°� �˾Ƽ� ���ô� ",
		//		30.f, D2DRenderer::DefaultBrush::Blue);

		//SceneManager::GetInstance()->Render();
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

