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
Scene : �������� ������ ���̶�� ��
*/

/*
Initialize : �ʱ�ȭ
������ ������ �����ϱ� ���� �ʱ�ȭ �� ������ ���⼭ ����
���� �����ϱ� ���� �� �ѹ��� ����Ǵ� �Լ�
*/
void MainGame::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"Loading", Resources(L"UI/Loading.png"));
	ImageManager::GetInstance()->LoadFromFile(L"LoadingCharacter", Resources(L"UI/LoadingCharacter.png"));

	SoundSet::GetInstance();

	//�ε��� �Լ�ä���ֱ�
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
	SceneManager::GetInstance()->Update();
}

/*
Render : �� ������ ����Ǵ� �Լ�, Update�� ������ Render�� ����ȴ�.
ȭ�鿡 �׷��ִ� �͵��� ���� ���⼭ ó��

�Ű����� hdc : ������ â�� HDC�� ����
*/
void MainGame::Render(HDC hdc)
{
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);
	//�� �ȿ��� �׷���
	{
		SceneManager::GetInstance()->Render();

	}
	D2DRenderer::GetInstance()->EndRender();
}