#include "pch.h"
#include "Scene_Field.h"
#include "Load_Image.h"
#include "Image.h"
#include "UserInterface.h"
#include "TileMap.h"
#include "Structure.h"
#include "Player.h"
#include "Camera.h"
#include "RandomMapGeneration.h"

void Scene_Field::Init()
{
	Load_Image::GetInstance()->LoadSceneMapToolImage();
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");

	UserInterface* ui = new UserInterface();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	mMapIsOpen = 0;
	
	//타일맵추가
	mTileMap = new TileMap();
	RandomMapGeneration::GetInstance()->CreateRandomMap(mTileMap);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//
	//스트럭쳐 받아오기
	
	//

	/*mPlayer = new Player("Player", 55 * TileSize, 55 * TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);*/


	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::MapTool);
	//camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
}

void Scene_Field::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene_Field::Update()
{
	CameraManager::GetInstance()->Update();
	SkillManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();
	
	if(Input::GetInstance()->GetKeyDown('M'))
	{
		if (mMapIsOpen)
			mMapIsOpen = 0;
		else
			mMapIsOpen = 1;
	}
	
		
}

void Scene_Field::Render()
{
	ObjectManager::GetInstance()->Render();
	TileMap* tilemap = (TileMap*)ObjectManager::GetInstance()->FindObject("TileMap");
	if (mMapIsOpen)
		tilemap->MiniMapRender();
}
