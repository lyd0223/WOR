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
#include "UserInterface.h"
#include "Effect_EnemyCreate.h"
#include "MouseTracker.h"
#include "Load_Image.h"
#include "Structure.h"

void Scene_Tutorial::Init()
{
	Load_Image::GetInstance()->LoadSceneMapToolImage();

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

	//타일맵추가
	UserInterface* ui = new UserInterface();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	mTileMap = new TileMap("Tutorial");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//
	//스트럭쳐 받아오기
	mStructureList = mTileMap->GetStructureList();
	for (int i = 0; i < mStructureList.size(); i++)
	{
		if (mStructureList[i]->GetName() == "Portal" || mStructureList[i]->GetName() == "Penta")
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mStructureList[i]);
		else
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, mStructureList[i]);
	}
	//

	//방추가 , 우측상단부터 1,2,3,4번
	mRoomList.push_back({ 41,4,31,11 });
	mRoomList.push_back({ 27,4,11,10 });
	mRoomList.push_back({ 25,24,19,14 });
	mRoomList.push_back({ 1,24,19,14 });

	mPlayer = new Player("Player",87*TileSize + TileSize/2, 10 * TileSize + TileSize / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);

	//몬스터추가하기
	ParticleManager::GetInstance()->MakeEnemyCreate(32 * TileSize, 11 * TileSize, MonsterName::RapidZombie, mRoomList[1]);
	ParticleManager::GetInstance()->MakeEnemyCreate(32 * TileSize, 9 * TileSize, MonsterName::Zombie, mRoomList[1]);
	ParticleManager::GetInstance()->MakeEnemyCreate(35 * TileSize, 9 * TileSize, MonsterName::Zombie, mRoomList[1]);
	ParticleManager::GetInstance()->MakeEnemyCreate(35 * TileSize, 11 * TileSize, MonsterName::Zombie, mRoomList[1]);

	ParticleManager::GetInstance()->MakeEnemyCreate(32 * TileSize, 31 * TileSize, MonsterName::SwoardMan, mRoomList[2]);
	ParticleManager::GetInstance()->MakeEnemyCreate(32 * TileSize, 29* TileSize, MonsterName::SwoardMan, mRoomList[2]);
	ParticleManager::GetInstance()->MakeEnemyCreate(35 * TileSize, 29* TileSize, MonsterName::SwoardMan, mRoomList[2]);
	ParticleManager::GetInstance()->MakeEnemyCreate(35 * TileSize, 31 * TileSize, MonsterName::SwoardMan, mRoomList[2]);

	ParticleManager::GetInstance()->MakeEnemyCreate(12 * TileSize, 29 * TileSize, MonsterName::BigZombie, mRoomList[3]);
	ParticleManager::GetInstance()->MakeEnemyCreate(15 * TileSize, 31 * TileSize, MonsterName::BigZombie, mRoomList[3]);
	ParticleManager::GetInstance()->MakeEnemyCreate(10 * TileSize, 29 * TileSize, MonsterName::Slime, mRoomList[3]);
	ParticleManager::GetInstance()->MakeEnemyCreate(10 * TileSize, 31 * TileSize, MonsterName::Slime, mRoomList[3]);
	ParticleManager::GetInstance()->MakeEnemyCreate(10 * TileSize, 20 * TileSize, MonsterName::Slime, mRoomList[3]);
	ParticleManager::GetInstance()->MakeEnemyCreate(10 * TileSize, 32 * TileSize, MonsterName::Slime, mRoomList[3]);
	//


	mGolem = new Monster_Golem("Golem", 200, 2000);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mGolem);

	mMuscleMan = new Monster_MuscleMan("MuscleMan", 200, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mMuscleMan);

	mBigZombie = new Monster_BigZombie("BigZombie", 400, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mBigZombie);

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
	
	//mSpearMan = new Monster_SpearMan("SpearMan", 200, 1300);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mSpearMan);
	
	mWard = new Monster_Ward("Ward", 1200, 1800);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mWard);
	
	mZombie = new Monster_Zombie("Zombie", 1200, 1600);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mZombie);

	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "BigZombie"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Golem"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Mazition"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MazitionBullet"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MuscleMan"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "RapidZombie"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Slime"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SpearMan"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "SwoardMan"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Ward"));
	//mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "Zombie"));
	mMonsterList.push_back((MonsterObject*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "MuscleMan"));

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

	for (int i = 0; i < mMonsterList.size(); i++)
	{
		if (mMonsterList[i]->GetIsActive())
		{
			D2D1_RECT_F rc = mMonsterList[i]->GetMovingRect();
			float centerX = (rc.left + (rc.right - rc.left) / 2) / TileSize;
			float centerY = (rc.top + (rc.bottom - rc.top) / 2) / TileSize;
			mMonsterList[i]->SetPathList(
				PathFinder::GetInstance()->FindPath(
					(TileMap*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Tile, "TileMap"),
					centerX, centerY,
					mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize)
			);
		}
	}


}

void Scene_Tutorial::Render()
{
	ObjectManager::GetInstance()->Render();
	


}
