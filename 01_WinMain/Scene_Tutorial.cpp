#include "pch.h"
#include "Scene_Tutorial.h"
#include "Image.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "Monster_BigZombie.h"
#include "Monster_Golem.h"
#include "Monster_Mazition.h"
#include "Monster_MazitionBullet.h"
#include "Monster_MuscleMan.h"
#include "Monster_RapidZombie.h"
#include "Monster_Slime.h"
#include "Monster_SpearMan.h"
#include "Monster_SwoardMan.h"
#include "Monster_Ward.h"
#include "Monster_Zombie.h"
#include "Monster_FireBoss.h"
#include "TileMap.h"
#include "Gizmo.h"
#include <fstream>

void Scene_Tutorial::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");

	/*for (int y = 0; y < TileCountY; y++)
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
	Load();*/

	//Å¸ÀÏ¸ÊÃß°¡

	mTileMap = new TileMap("Tutorial");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//


	mPlayer = new Player("Player",600,1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);

	mBigZombie = new Monster_BigZombie("BigZombie", 400, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mBigZombie);
	
	mGolem = new Monster_Golem("Golem", 200, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mGolem);
	
	mMazition = new Monster_Mazition("Mazition", 800, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMazition);
	
	mMazitionBullet = new Monster_MazitionBullet("MazitionBullet", 1000, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMazitionBullet);
	
	mMuscleMan = new Monster_MuscleMan("MuscleMan", 200, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMuscleMan);
	
	mRapidZombie = new Monster_RapidZombie("RapidZombie", 400, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mRapidZombie);
	
	mSlime = new Monster_Slime("Slime", 600, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSlime);
	
	mSwoardMan = new Monster_SwoardMan("SwoardMan", 800, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSwoardMan);
	
	mSpearMan = new Monster_SpearMan("SpearMan", 1000, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSpearMan);
	
	mWard = new Monster_Ward("Ward", 1200, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mWard);
	
	mZombie = new Monster_Zombie("Zombie", 1200, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mZombie);



	//mMonsterList[0] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "BigZombie");
	//mMonsterList[1] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Golem");
	//mMonsterList[2] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Mazition");
	//mMonsterList[3] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MazitionBullet");
	//mMonsterList[4] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MuscleMan");
	//mMonsterList[5] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "RapidZombie");
	//mMonsterList[6] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Slime");
	//mMonsterList[7] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SpearMan");
	//mMonsterList[8] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SwoardMan");
	//mMonsterList[9] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Ward");
	//mMonsterList[10] = (MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Zombie");

	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "BigZombie"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Golem"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Mazition"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MazitionBullet"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MuscleMan"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "RapidZombie"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Slime"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SpearMan"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SwoardMan"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Ward"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Zombie"));

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, new Monster_FireBoss("FireBoss", mPlayer->GetX() + 150, mPlayer->GetY() + 150));

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

	vector<Tile*> path = PathFinder::GetInstance()->FindPath((TileMap*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Tile, "TileMap"),
		mMonsterList[0]->GetX() / TileSize, mMonsterList[0]->GetY() / TileSize,
		mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);

	mMonsterList[0]->SetPathList(path);

	for (int i = 0; i < mMonsterList.size(); i++)
	{
		if (mMonsterList[i]->GetIsActive())
		{
			mMonsterList[i]->SetPathList(
				PathFinder::GetInstance()->FindPath(
					(TileMap*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Tile, "TileMap"),
					mMonsterList[i]->GetX() / TileSize, mMonsterList[i]->GetY() / TileSize,
					mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize)
			);
		}
	}
}

void Scene_Tutorial::Render()
{
	ObjectManager::GetInstance()->Render();
	


}
