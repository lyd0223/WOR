#include "pch.h"
#include "Scene_Tutorial.h"
#include "Image.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include"BigZombie.h"
#include"Golem.h"
#include"Mazition.h"
#include"MazitionBullet.h"
#include"MuscleMan.h"
#include"RapidZombie.h"
#include"Slime.h"
#include"SpearMan.h"
#include"SwoardMan.h"
#include"Ward.h"
#include"Zombie.h"
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

	mBigZombie = new BigZombie("BigZombie", 400, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mBigZombie);

	mGolem = new Golem("Golem", 200, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mGolem);

	mMazition = new Mazition("Mazition", 800, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMazition);

	mMazitionBullet = new MazitionBullet("MazitionBullet", 1000, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMazitionBullet);

	mMuscleMan = new MuscleMan("MuscleMan", 200, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMuscleMan);

	mRapidZombie = new RapidZombie("RapidZombie", 400, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mRapidZombie);

	mSlime = new Slime("Slime", 600, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSlime);

	mSwoardMan = new SwoardMan("SwoardMan", 800, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSwoardMan);

	mSpearMan = new SpearMan("SpearMan", 1000, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSpearMan);

	mWard = new Ward("Ward", 1200, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mWard);

	mZombie = new Zombie("Zombie", 1200, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mZombie);



	mMonsterList[0] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "BigZombie");
	mMonsterList[1] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Golem");
	mMonsterList[2] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Mazition");
	mMonsterList[3] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MazitionBullet");
	mMonsterList[4] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MuscleMan");
	mMonsterList[5] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "RapidZombie");
	mMonsterList[6] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Slime");
	mMonsterList[7] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SpearMan");
	mMonsterList[8] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SwoardMan");
	mMonsterList[9] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Ward");
	mMonsterList[10] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Zombie");

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, new FireBoss("FireBoss", mPlayer->GetX() + 150, mPlayer->GetY() + 150));

	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mBigZombie);
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

	//플레이어가 벽을느낄때
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

	//몬스터가 벽을느낄때
	for (int z = 0; z < 11; z++)
	{
		for (int y = mMonsterList[z]->GetY() / TileSize - 1; y < mMonsterList[z]->GetY() / TileSize + 1; y++)
		{
			for (int x = mMonsterList[z]->GetX() / TileSize - 1; x < mMonsterList[z]->GetX() / TileSize + 1; x++)
			{
				D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
				D2D1_RECT_F monsterRect = mMonsterList[z]->GetRect();
				D2D1_RECT_F tempRect;
				if (mTileList[y][x]->GetType() == Type::Wall)
				{
					if (IntersectRect(tempRect, &tileRect, &monsterRect))
					{
						if (y == (int)mMonsterList[z]->GetY() / TileSize && x == (int)mMonsterList[z]->GetX() / TileSize - 1)
							mMonsterList[z]->SetX(mMonsterList[z]->GetX() + (tempRect.right-tempRect.left));
						else if (y == (int)mMonsterList[z]->GetY() / TileSize && x == (int)mMonsterList[z]->GetX() / TileSize + 1)
							mMonsterList[z]->SetX(mMonsterList[z]->GetX() - (tempRect.right - tempRect.left));
						else if (y == (int)mMonsterList[z]->GetY() / TileSize - 1 && x == (int)mMonsterList[z]->GetX() / TileSize)
							mMonsterList[z]->SetY(mMonsterList[z]->GetY() + (tempRect.bottom - tempRect.top));
						else if (y == (int)mMonsterList[z]->GetY() / TileSize + 1 && x == (int)mMonsterList[z]->GetX() / TileSize)
							mMonsterList[z]->SetY(mMonsterList[z]->GetY() - (tempRect.bottom - tempRect.top));
					}
				}
				if (mTileList[y][x]->GetType() == Type::Cliff)
				{
					if (IntersectRect(tempRect, &tileRect, &monsterRect))
					{
						float monsterX = mMonsterList[z]->GetX();
						float monsterY = mMonsterList[z]->GetY();
						if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.bottom == monsterRect.bottom)
							monsterY -= TileSize;
						if ((tempRect.bottom - tempRect.top) < (tempRect.right - tempRect.left) && tempRect.top == monsterRect.top)
							monsterY += TileSize;
						if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.left == monsterRect.left)
							monsterX += TileSize;
						if ((tempRect.bottom - tempRect.top) > (tempRect.right - tempRect.left) && tempRect.right == monsterRect.right)
							monsterX -= TileSize;
					}

				}
			}
		}
	}
	for (int z = 0; z < 11; z++)
	{
		if (mTileList[(int)mMonsterList[z]->GetY() / TileSize][(int)mMonsterList[z]->GetX() / TileSize]->GetType() == Type::Floor)
		{
			mMonsterList[z]->GetSpeed();
		}
		else if (mTileList[(int)mMonsterList[z]->GetY() / TileSize][(int)mMonsterList[z]->GetX() / TileSize]->GetType() == Type::Thorn)
		{
			mMonsterList[z]->GetSpeed() - 2.f;
		}
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
