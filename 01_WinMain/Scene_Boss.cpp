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
#include "Effect_Teleport.h"

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
		if (mStructureList[i]->GetName() == "Penta")
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mStructureList[i]);
		else
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, mStructureList[i]);
	}
	//

	mPlayer = new Player("Player", 19 * TileSize, 36 * TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);

	mFireBoss = new Monster_FireBoss("FireBoss", 20 * TileSize, 14 * TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mFireBoss);

	//방만들기
	mRoomList.push_back(new Room(10, 8, 19, 15));
	//방에 파이어보스 넣어주기.
	mFireBoss->SetRoom(mRoomList[0]);
	mRoomList[0]->monsterList.push_back(mFireBoss);

	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);

	Effect_Teleport* teleport = new Effect_Teleport(mPlayer->GetX(), mPlayer->GetY() + 50, false);
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

	for (int i = 0; i < mRoomList.size(); i++)
	{
		if (mRoomList[i]->PlayerInRoom())
		{

			if (mRoomList[i]->monsterList.size() != 0)
			{
				if (Input::GetInstance()->GetKeyDown('K'))
				{
					mRoomList[i]->monsterList.clear();
					ObjectManager::GetInstance()->DeleteObjects(ObjectLayer::Structure);
				}
				if (ObjectManager::GetInstance()->FindObject("VerticalPrison") == nullptr &&
					ObjectManager::GetInstance()->FindObject("HorizonalPrison") == nullptr)
				{
					SoundPlayer::GetInstance()->Play(L"RoomLock", 1.0f);
					
					for (int x = 17; x <= 21; x++)
					{
						int y = 26;
						if (mTileMap->GetTileList()[y][x]->GetType() != Type::Wall)
						{
							mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
							Structure* structure = new Structure(
								"HorizonalPrison",
								ImageManager::GetInstance()->FindImage(L"HorizonalPrison"),
								mTileMap->GetTileList()[y][x]->GetX() + TileSize / 2,
								mTileMap->GetTileList()[y][x]->GetY() + TileSize / 2,
								ImageManager::GetInstance()->FindImage(L"HorizonalPrison")->GetWidth() * 0.5f,
								ImageManager::GetInstance()->FindImage(L"HorizonalPrison")->GetHeight() * 0.5f);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, structure);
						}
					}
				}
			}
			else
			{
				if (ObjectManager::GetInstance()->FindObject("VerticalPrison") != nullptr ||
					ObjectManager::GetInstance()->FindObject("HorizonalPrison") != nullptr)
				{
					SoundPlayer::GetInstance()->Play(L"RoomUnLock", 1.0f);
					ObjectManager::GetInstance()->DeleteObjects(ObjectLayer::Structure);
					
						
					for (int x = 17; x <= 21; x++)
					{
						int y = 24;
						if (mTileMap->GetTileList()[y][x]->GetType() != Type::Wall)
						{
							if (mTileMap->GetTileList()[y][x]->GetType() == Type::Wall)
							{
								mTileMap->GetTileList()[y][x]->SetType(Type::Floor);
							}
						}
					}
						
				}
			}
		}
	}
}

void Scene_Boss::Render()
{

	ObjectManager::GetInstance()->Render();

}
