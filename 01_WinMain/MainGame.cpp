#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#include "Scene_MapTool.h"
#include "Scene_Game.h"
#include "FireBoss.h"
#include "Player.h"
#include "FireBall.h"
/*
Scene : 스테이지 단위를 씬이라고 함
*/

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
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
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제


}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
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
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	////백버퍼의 HDC 가져온다
	//HDC backDC = mBackBuffer->GetHDC();
	////HDC 영역을 특정 색으로 밀어버리는 녀석
	//PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//// ==================================================
	//{
	//	SceneManager::GetInstance()->Render(backDC);
	//}
	////====================================================
	////후면버퍼 내용을 윈도우 창에 고속 복사
	//mBackBuffer->Render(hdc, 0, 0);

	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Aqua);
	//이 안에서 그려라
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
		//	->RenderText(WINSIZEX / 2-150, WINSIZEY / 2-100, L"쓰는건 알아서 씁시다 ",
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

