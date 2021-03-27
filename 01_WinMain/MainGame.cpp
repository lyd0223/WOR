#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include"Scene_Tutorial.h"
#include "Scene_MapTool.h"
#include "Scene_Game.h"
#include "Scene_TitleScene.h"

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
	SceneManager::GetInstance()->AddScene(L"MapTool", new Scene_MapTool);
	SceneManager::GetInstance()->AddScene(L"Tutorial", new Scene_Tutorial);
	SceneManager::GetInstance()->AddScene(L"Title", new Scene_TitleScene);
	SceneManager::GetInstance()->LoadScene(L"Tutorial");
	SkillCastingManager::GetInstance()->Init();
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