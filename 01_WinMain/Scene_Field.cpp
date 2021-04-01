#include "pch.h"
#include "Scene_Field.h"
#include "Load_Image.h"
#include "Image.h"
#include "UserInterface.h"
#include "TileMap.h"
#include "Tile.h"
#include "Structure.h"
#include "Player.h"
#include "Camera.h"
#include "RandomMapGeneration.h"
#include "Effect_Teleport.h"

void Scene_Field::Init()
{
	SoundPlayer::GetInstance()->Play(L"Fire", 0.5f);
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");

	UserInterface* ui = new UserInterface();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	mMapIsOpen = 0;
	
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//
	
	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player") == nullptr)
	{
		mPlayer = new Player("Player", 0, 0);
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);
	}
	else
		mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");

	RandomMapGeneration::GetInstance()->RandomPlayerPosition(mPlayer);
	RandomMapGeneration::GetInstance()->RandomMonsterCreate();
	mRoomList = RandomMapGeneration::GetInstance()->GetRoomList();
	
	mPortal = (Structure*)ObjectManager::GetInstance()->FindObject("Portal");
	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();
	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);

	Effect_Teleport* teleport = new Effect_Teleport(mPlayer->GetX(), mPlayer->GetY() + 50, false);
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
	if (mPortal->GetPortalOn())
	{

		if (Input::GetInstance()->GetKeyDown('F'))
		{
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy).clear();
			Effect_Teleport* teleport = new Effect_Teleport(mPortal->GetX(), mPortal->GetY(), true, L"Field", L"Boss");
			SoundPlayer::GetInstance()->Stop(L"Field");
			return;
		}
	}
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
					for (int j = 0; j < mRoomList[i]->roadList.size(); j++)
					{
						//왼쪽
						if (mRoomList[i]->x == mRoomList[i]->roadList[j].x2)
						{
							for (int y = mRoomList[i]->roadList[j].y2; y < mRoomList[i]->roadList[j].y2 + 3; y++)
							{
								int x = mRoomList[i]->roadList[j].x2;
								if (mTileMap->GetTileList()[y][x]->GetType() != Type::Wall)
								{
									mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
									Structure* structure = new Structure(
										"VerticalPrison",
										ImageManager::GetInstance()->FindImage(L"VerticalPrison"),
										mTileMap->GetTileList()[y][x]->GetX() + TileSize / 2,
										mTileMap->GetTileList()[y][x]->GetY() + TileSize / 2,
										ImageManager::GetInstance()->FindImage(L"VerticalPrison")->GetWidth() * 0.5f,
										ImageManager::GetInstance()->FindImage(L"VerticalPrison")->GetHeight() * 0.5f);
									ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, structure);
								}
							}
						}
						//오른쪽
						else if ((mRoomList[i]->x + mRoomList[i]->sizeX) == mRoomList[i]->roadList[j].x1)
						{

							for (int y = mRoomList[i]->roadList[j].y1; y < mRoomList[i]->roadList[j].y1 + 3; y++)
							{
								int x = mRoomList[i]->roadList[j].x1;
								if (mTileMap->GetTileList()[y][x]->GetType() != Type::Wall)
								{
									mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
									Structure* structure = new Structure(
										"VerticalPrison",
										ImageManager::GetInstance()->FindImage(L"VerticalPrison"),
										mTileMap->GetTileList()[y][x]->GetX() + TileSize / 2,
										mTileMap->GetTileList()[y][x]->GetY() + TileSize / 2,
										ImageManager::GetInstance()->FindImage(L"VerticalPrison")->GetWidth() * 0.5f,
										ImageManager::GetInstance()->FindImage(L"VerticalPrison")->GetHeight() * 0.5f);
									ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, structure);
								}

							}
						}
						//위
						else if (mRoomList[i]->y == mRoomList[i]->roadList[j].y2)
						{
							for (int x = mRoomList[i]->roadList[j].x2 - 1; x < mRoomList[i]->roadList[j].x2 + 2; x++)
							{
								int y = mRoomList[i]->roadList[j].y2;
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
						//아래
						else if ((mRoomList[i]->y + mRoomList[i]->sizeY) == mRoomList[i]->roadList[j].y1)
						{
							for (int x = mRoomList[i]->roadList[j].x1 - 1; x < mRoomList[i]->roadList[j].x1 + 2; x++)
							{
								int y = mRoomList[i]->roadList[j].y1;
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
				}
			}
			else
			{
				if (ObjectManager::GetInstance()->FindObject("VerticalPrison") !=nullptr ||
					ObjectManager::GetInstance()->FindObject("HorizonalPrison") != nullptr)
				{
					SoundPlayer::GetInstance()->Play(L"RoomUnLock", 1.0f);
					ObjectManager::GetInstance()->DeleteObjects(ObjectLayer::Structure);
					for (int j = 0; j < mRoomList[i]->roadList.size(); j++)
					{
						//왼쪽
						if (mRoomList[i]->x == mRoomList[i]->roadList[j].x2)
						{
							for (int y = mRoomList[i]->roadList[j].y2; y < mRoomList[i]->roadList[j].y2 + 3; y++)
							{
								int x = mRoomList[i]->roadList[j].x2;
								if (mTileMap->GetTileList()[y][x]->GetType() == Type::Wall)
								{
									mTileMap->GetTileList()[y][x]->SetType(Type::Floor);
								}
							}
						}
						//오른쪽
						else if ((mRoomList[i]->x + mRoomList[i]->sizeX) == mRoomList[i]->roadList[j].x1)
						{

							for (int y = mRoomList[i]->roadList[j].y1; y < mRoomList[i]->roadList[j].y1 + 3; y++)
							{
								int x = mRoomList[i]->roadList[j].x1;
								if (mTileMap->GetTileList()[y][x]->GetType() == Type::Wall)
								{
									mTileMap->GetTileList()[y][x]->SetType(Type::Floor);

								}

							}
						}
						//위
						else if (mRoomList[i]->y == mRoomList[i]->roadList[j].y2)
						{
							for (int x = mRoomList[i]->roadList[j].x2 - 1; x < mRoomList[i]->roadList[j].x2 + 2; x++)
							{
								int y = mRoomList[i]->roadList[j].y2;
								if (mTileMap->GetTileList()[y][x]->GetType() == Type::Wall)
								{

									mTileMap->GetTileList()[y][x]->SetType(Type::Floor);
								}
							}
						}
						//아래
						else if ((mRoomList[i]->y + mRoomList[i]->sizeY) == mRoomList[i]->roadList[j].y1)
						{
							for (int x = mRoomList[i]->roadList[j].x1 - 1; x < mRoomList[i]->roadList[j].x1 + 2; x++)
							{
								int y = mRoomList[i]->roadList[j].y1;
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
		
}

void Scene_Field::Render()
{
	ObjectManager::GetInstance()->Render();
	TileMap* tilemap = (TileMap*)ObjectManager::GetInstance()->FindObject("TileMap");
	if (mMapIsOpen)
		tilemap->MiniMapRender();
}
