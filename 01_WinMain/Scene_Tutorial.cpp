#include "pch.h"
#include "Scene_Tutorial.h"
#include "Image.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "FireBoss.h"
#include <fstream>

void Scene_Tutorial::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"),74,43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");
	
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			mTileList[y][x] = new Tile
			(
				tileImage,
				TileSize * x, TileSize * y,
				TileSize, TileSize,
				0, 0
			);
			//ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileList[y][x]);
		}
	}
	Load();
	
	mPlayer = new Player("Player",600,1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, new FireBoss("FireBoss", mPlayer->GetX() + 150, mPlayer->GetY() + 150));

	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
}

void Scene_Tutorial::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene_Tutorial::Update()
{
	CameraManager::GetInstance()->Update();
	SkillManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();

	//º®À»´À³¥¶§
	for (int y = mPlayer->GetY() / TileSize - 1; y < mPlayer->GetY() / TileSize + 1; y++)
	{
		for (int x = mPlayer->GetX() / TileSize - 1; x < mPlayer->GetX() / TileSize + 1; x++)
		{
			D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
			D2D1_RECT_F playerRect = mPlayer->GetRect();
			D2D1_RECT_F tempRect;
			if (mTileList[y][x]->GetType() == Type::Wall)
			{
				if (IntersectRect(tempRect, &tileRect, &playerRect))
				{
					if (y == (int)mPlayer->GetY() / TileSize && x == (int)mPlayer->GetX() / TileSize - 1)
						mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed());
					else if (y == (int)mPlayer->GetY() / TileSize && x == (int)mPlayer->GetX() / TileSize + 1)
						mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed());
					else if (y == (int)mPlayer->GetY() / TileSize - 1 && x == (int)mPlayer->GetX() / TileSize)
						mPlayer->SetY(mPlayer->GetY() + mPlayer->GetSpeed());
					else if (y == (int)mPlayer->GetY() / TileSize + 1 && x == (int)mPlayer->GetX() / TileSize)
						mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSpeed());
				}
			}
			if (mTileList[y][x]->GetType() == Type::Cliff)
			{
				if (IntersectRect(tempRect, &tileRect, &playerRect))
				{
					float playerX = mPlayer->GetX();
					float playerY = mPlayer->GetY();
					if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.bottom == playerRect.bottom)
						playerY -= TileSize;
					if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.top == playerRect.top)
						playerY += TileSize;
					if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.left == playerRect.left)
						playerX += TileSize;
					if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.right == playerRect.right)
						playerX -= TileSize;
				}

			}
		}
	}
	
	if (mTileList[(int)mPlayer->GetY() / TileSize][(int)mPlayer->GetX() / TileSize]->GetType() == Type::Floor)
	{
		mPlayer->GetSpeed();
	}
	else if (mTileList[(int)mPlayer->GetY() / TileSize][(int)mPlayer->GetX() / TileSize]->GetType() == Type::Thorn)
	{
		mPlayer->GetSpeed() - 2.f;
	}
}

void Scene_Tutorial::Render()
{
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();

	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				mTileList[y][x]->Render();
			}
			if (Input::GetInstance()->GetKey('J'))
			{
				if (mTileList[y][x]->GetType() == Type::Cliff)
				{
					RenderRect(mTileList[y][x]->GetRect());
				}
			}
		}
	}
	ObjectManager::GetInstance()->Render();
}

void Scene_Tutorial::Load()
{
	ifstream loadStream(L"../04_Datas/TutorialMap.txt");
	if (loadStream.is_open())
	{
		for (int y = 0; y < TileCountY; y++)
		{
			for (int x = 0; x < TileCountX; x++)
			{
				string tempstr;
				string key;
				int IndexX = 0;
				int IndexY = 0;
				int typenum = 0;

				getline(loadStream, tempstr);

				int tempint = 0;
				int n = 0;
				for (int i = 0; i < tempstr.length(); i++)
				{
					if (tempstr[i] == ',' && n == 0)
					{
						int t = i - tempint;
						key = tempstr.substr(tempint, t);
						tempint = i + 1;
						n++;
					}
					else if (tempstr[i] == ',' && n == 1)
					{
						int t = i - tempint;
						typenum = stoi(tempstr.substr(tempint, t));
						tempint = i + 1;
						n++;
					}
					else if (tempstr[i] == ',' && n == 2)
					{
						int t = i - tempint + 1;
						IndexY = stoi(tempstr.substr(tempint, t));
						tempint = i + 1;
						n++;
					}
					else if (i == tempstr.length() - 1 && n == 3)
					{
						int t = i - tempint + 2;
						IndexX = stoi(tempstr.substr(tempint, t));

					}
				}
				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mTileList[y][x]->SetType((Type)typenum);
				mTileList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mTileList[y][x]->SetFrameIndexX(IndexX);
				mTileList[y][x]->SetFrameIndexY(IndexY);
			}
		}
		
	}
}
