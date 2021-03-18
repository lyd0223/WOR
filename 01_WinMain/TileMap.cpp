#include "pch.h"
#include "TileMap.h"
#include "Tile.h"
#include "Camera.h"

#include <fstream>

TileMap::TileMap(string sceneName)
{
	mName = "TileMap";
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			mTileList[y][x] = new Tile
			(
				NULL,
				TileSize * x, TileSize * y,
				TileSize, TileSize,
				0, 0
			);

		}
	}
	Load(sceneName);
}
void TileMap::Init()
{
	
}

void TileMap::Update()
{
}

void TileMap::Release()
{
}

void TileMap::Render()
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
			
		}
	}
}

void TileMap::Load(string sceneName)
{
	string str = "../04_Datas/" + sceneName + ".txt";
	wstring name;
	name.assign(str.begin(), str.end());
	ifstream loadStream(name);
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

