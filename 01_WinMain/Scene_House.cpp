#include "pch.h"
#include "Scene_House.h"
#include "Image.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "TileMap.h"
#include "Gizmo.h"
#include "Load_Image.h"
#include <fstream>

void Scene_House::Init()
{
	Load_Image::GetInstance()->LoadSceneMapToolImage();
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");

	
	//Å¸ÀÏ¸ÊÃß°¡

	mTileMap = new TileMap("House");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//


	mPlayer = new Player("Player", 55*TileSize, 55*TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);

	
	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
}

void Scene_House::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene_House::Update()
{
	mTileMap;
	CameraManager::GetInstance()->Update();
	SkillManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();

	
}

void Scene_House::Render()
{
	ObjectManager::GetInstance()->Render();

}
