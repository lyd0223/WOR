#include "pch.h"
#include "Scene_Game.h"
#include "Camera.h"
#include <fstream>
#include "Tile.h"
#include "Player.h"
#include "Image.h"
void Scene_Game::Init()
{
	mPlayer = new Player("Player", 200, 500);

	mPlayer->Init();

	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TileSet");
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

		}
	}

	Load();
	
	Camera* camera = new Camera();
	
	camera->Init();
	camera->SetTarget(mPlayer);
	camera->ChangeMode(Camera::Mode::Follow);
	CameraManager::GetInstance()->SetMainCamera(camera);
}

void Scene_Game::Release()
{
	SafeDelete(mPlayer);
}

void Scene_Game::Update()
{
	CameraManager::GetInstance()->GetMainCamera()->Update();
	mPlayer->Update();

	//º®À»´À³¥¶§
	for (int y = mPlayer->GetY() / TileSize - 1; y < mPlayer->GetY() / TileSize + 1; y++)
	{
		for (int x = mPlayer->GetX() / TileSize - 1; x < mPlayer->GetX() / TileSize + 1; x++)
		{
			RECT tileRect = mTileList[y][x]->GetRect();
			RECT playerRect = mPlayer->GetRect();
			RECT tempRect;
			if (mTileList[y][x]->GetType() == Type::Wall)
			{
				if (IntersectRect(&tempRect, &tileRect, &playerRect))
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
		}
	}
	if (mTileList[(int)mPlayer->GetY() / TileSize][(int)mPlayer->GetX() / TileSize]->GetType() == Type::Slow)
	{
		mPlayer->SetSpeed(2.f);
	}
	else if (mTileList[(int)mPlayer->GetY() / TileSize][(int)mPlayer->GetX() / TileSize]->GetType() == Type::Normal)
	{
		mPlayer->SetSpeed(5.f);
	}
	

}

void Scene_Game::Render(HDC hdc)
{
	
	RECT cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			RECT tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				mTileList[y][x]->Render(hdc);
			}
		}
	}
	mPlayer->Render(hdc);
}

void Scene_Game::Load()
{
	ifstream loadStream(L"../04_Datas/Test.txt");
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
						IndexY = stoi(tempstr.substr(tempint, t));
						tempint = i + 1;
						n++;
					}
					else if (i == tempstr.length() - 1 && n == 2)
					{
						int t = i - tempint + 1;
						IndexX = stoi(tempstr.substr(tempint, t));

					}
				}
				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mTileList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mTileList[y][x]->SetFrameIndexX(IndexX);
				mTileList[y][x]->SetFrameIndexY(IndexY);
				if (mTileList[y][x]->GetFrameIndexX() == 0 && mTileList[y][x]->GetFrameIndexY() == 0)
					mTileList[y][x]->SetType(Type::Normal);
				else if (mTileList[y][x]->GetFrameIndexX() == 1 && mTileList[y][x]->GetFrameIndexY() == 0)
					mTileList[y][x]->SetType(Type::Wall);
				else if (mTileList[y][x]->GetFrameIndexX() == 0 && mTileList[y][x]->GetFrameIndexY() == 1)
					mTileList[y][x]->SetType(Type::Slow);
				else
					mTileList[y][x]->SetType(Type::Normal);
			}
		}

	}
}