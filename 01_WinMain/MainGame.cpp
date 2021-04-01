#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include"Scene_Tutorial.h"
#include "Scene_MapTool.h"
#include "Scene_House.h"
#include "Scene_Field.h"
#include "Scene_Boss.h"
#include "Scene_TitleScene.h"
#include "Scene_House.h"
#include "Scene_Loading.h"
#include "Load_Image.h"
#include "RandomMapGeneration.h"

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
	ImageManager::GetInstance()->LoadFromFile(L"Loading", Resources(L"UI/Loading.png"));
	ImageManager::GetInstance()->LoadFromFile(L"LoadingCharacter", Resources(L"UI/LoadingCharacter.png"));

	SoundSet::GetInstance();

	//로딩씬 함수채워넣기
	Scene_Loading* loadingScene = new Scene_Loading();
	loadingScene->AddLoadFunc([]() { Load_Image::GetInstance()->LoadSceneMapToolImage(); });
	loadingScene->AddLoadFunc([]() { RandomMapGeneration::GetInstance()->CreateRandomMap1(); });
	loadingScene->AddLoadFunc([]() { RandomMapGeneration::GetInstance()->CreateRandomMap2(); });
	loadingScene->AddLoadFunc([]() {
		Scene_Field* sf = (Scene_Field*)SceneManager::GetInstance()->FindScene(L"Field");
		sf->SetTileMap( RandomMapGeneration::GetInstance()->GetTileMap());
		});
	SceneManager::GetInstance()->AddScene(L"FieldLoading", loadingScene);

	SceneManager::GetInstance()->AddScene(L"MapTool", new Scene_MapTool);
	SceneManager::GetInstance()->AddScene(L"House", new Scene_House);
	SceneManager::GetInstance()->AddScene(L"Tutorial", new Scene_Tutorial);
	SceneManager::GetInstance()->AddScene(L"Field", new Scene_Field);
	SceneManager::GetInstance()->AddScene(L"Boss", new Scene_Boss);
	SceneManager::GetInstance()->AddScene(L"Title", new Scene_TitleScene);
	SceneManager::GetInstance()->LoadScene(L"House");
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
	SceneManager::GetInstance()->Update();
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);
	//이 안에서 그려라
	{
		SceneManager::GetInstance()->Render();

	}
	D2DRenderer::GetInstance()->EndRender();
}