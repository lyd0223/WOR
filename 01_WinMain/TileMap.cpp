#include "pch.h"
#include "TileMap.h"
#include "Tile.h"
#include "Camera.h"
#include "Gizmo.h"
#include "Structure.h"
#include <fstream>
#include "Image.h"

TileMap::TileMap(string sceneName)
{
	mName = "TileMap";
	for (int y = 0; y < TileCountY; y++)
	{
		vector<Tile*> tilelist;
		mTileList.push_back(tilelist);
		for (int x = 0; x < TileCountX; x++)
		{
			Tile* tile = new Tile
			(
				NULL,
				TileSize * x, TileSize * y,
				TileSize, TileSize,
				0,0
			);
			mTileList[y].push_back(tile);
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
				//CameraManager::GetInstance()->GetMainCamera()->RenderGizmoRect({ tileRect.left + 1, tileRect.top + 1,tileRect.right - 1,tileRect.bottom - 1 }, D2D1::ColorF::Red);
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
		//스트럭쳐 불러오기
		while (true)
		{
			string tempstr;
			string key;
			int IndexX = 0;
			int IndexY = 0;
			getline(loadStream, tempstr);
			if (tempstr == "/")
			{
				return;
			}
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
					int t = i - tempint + 1;
					IndexY = stoi(tempstr.substr(tempint, t));
					tempint = i + 1;
					n++;
				}
				else if (i == tempstr.length() - 1 && n == 2)
				{
					int t = i - tempint + 2;
					IndexX = stoi(tempstr.substr(tempint, t));

				}
			}
			wstring wstr;
			wstr.assign(key.begin(), key.end());
			Structure* st = new Structure
			(
				key,
				ImageManager::GetInstance()->FindImage(wstr),
				(float)IndexX * TileSize + TileSize / 2,
				(float)IndexY * TileSize + TileSize / 2,
				ImageManager::GetInstance()->FindImage(wstr)->GetWidth(),
				ImageManager::GetInstance()->FindImage(wstr)->GetHeight()
			);
			mStructureList.push_back(st);
		}
	}
}

