#include "pch.h"
#include "Scene_Boss.h"
#include "Image.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "Monster_FireBoss.h"
#include "TileMap.h"
#include "Gizmo.h"
#include "Load_Image.h"
#include "Structure.h"
#include "UserInterface.h"
#include <fstream>

void Scene_Boss::Init()
{
	SoundPlayer::GetInstance()->Play(L"Boss", 0.5f);
	Load_Image::GetInstance()->LoadSceneMapToolImage();
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");

	UserInterface* ui = new UserInterface();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	//타일맵추가

	mTileMap = new TileMap("FireBoss");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//
	//스트럭쳐 받아오기
	mStructureList = mTileMap->GetStructureList();
	for (int i = 0; i < mStructureList.size(); i++)
	{
		if (mStructureList[i]->GetName() == "Portal")
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mStructureList[i]);
		else
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, mStructureList[i]);
	}
	//

	mPlayer = new Player("Player", 20 * TileSize, 30 * TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);

	mFireBoss = new Monster_FireBoss("FireBoss", 20 * TileSize, 14 * TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mFireBoss);

	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
}

void Scene_Boss::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene_Boss::Update()
{
	CameraManager::GetInstance()->Update();
	SkillManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();


}

void Scene_Boss::Render()
{

	ObjectManager::GetInstance()->Render();

}
