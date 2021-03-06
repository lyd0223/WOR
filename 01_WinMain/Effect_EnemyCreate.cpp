#include "pch.h"
#include "Effect_EnemyCreate.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "Monster_BigZombie.h"
#include "Monster_Golem.h"
#include "Monster_Mazition.h"
#include "Monster_RapidZombie.h"
#include "Monster_Slime.h"
#include "Monster_SwoardMan.h"
#include "Monster_Zombie.h"

Effect_EnemyCreate::Effect_EnemyCreate(const string & name, float x, float y, MonsterName monsterName)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mMonsterName = monsterName;

	ImageManager::GetInstance()->LoadFromFile(L"EnemyCreate", Resources(L"Effect/EnemyCreate.png"), 1, 31);
	mImage = ImageManager::GetInstance()->FindImage(L"EnemyCreate");

	mEnemyCreateAnimation = new Animation();
	mEnemyCreateAnimation->InitFrameByStartEnd(0, 0, 0, 30, false);
	mEnemyCreateAnimation->SetIsLoop(false);
	mEnemyCreateAnimation->SetFrameUpdateTime(0.13f);
	mEnemyCreateAnimation->Play();
	RespawnOn = true;
}

void Effect_EnemyCreate::Init()
{
	
}

void Effect_EnemyCreate::Release()
{
	
	SafeDelete(mEnemyCreateAnimation)
}

void Effect_EnemyCreate::Update()
{
	D2D1_RECT_F playerRect = ObjectManager::GetInstance()->FindObject("Player")->GetRect();
	D2D1_RECT_F roomRect = RectMake(mRoom->x * TileSize, mRoom->y * TileSize, mRoom->sizeX * TileSize, mRoom->sizeY * TileSize);
	D2D1_RECT_F rctemp;
	if (IntersectRect(rctemp, &playerRect, &roomRect))
	{
		mEnemyCreateAnimation->Update();
	}
	if (mEnemyCreateAnimation->GetNowFrameY() == 27 && RespawnOn == true)
	{
		string str;
		switch (mMonsterName)
		{
		case MonsterName::BigZombie:
			str = "BigZombie";
			break;
		case MonsterName::Golem:
			break;
		case MonsterName::Mazition:
			break;
		case MonsterName::RapidZombie:
			break;
		case MonsterName::Slime:
			break;
		case MonsterName::SwoardMan:
			break;
		case MonsterName::Zombie:
			break;
		}
		//ObjectManager::GetInstance()->FindObject(str)->SetIsActive(true);
		if (mMonsterName == MonsterName::BigZombie)
		{
			Monster_BigZombie* bigzombie = new Monster_BigZombie("BigZombie", mX, mY);
			mRoom->monsterList.push_back(bigzombie);
			bigzombie->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, bigzombie);
			RespawnOn = false;
		}
		else if (mMonsterName == MonsterName::Golem)
		{
			Monster_Golem* golem = new Monster_Golem("Golem", mX, mY);
			mRoom->monsterList.push_back(golem);
			golem->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, golem);
			RespawnOn = false;
		}
		else if (mMonsterName == MonsterName::Mazition)
		{
			Monster_Mazition* mazition = new Monster_Mazition("Mazition", mX, mY);
			mRoom->monsterList.push_back(mazition);
			mazition->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mazition);
			RespawnOn = false;
		}
		else if (mMonsterName == MonsterName::RapidZombie)
		{
			Monster_RapidZombie* rapidZombie = new Monster_RapidZombie("RapidZombie", mX, mY);
			mRoom->monsterList.push_back(rapidZombie);
			rapidZombie->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, rapidZombie);
			RespawnOn = false;
		}
		else if (mMonsterName == MonsterName::Slime)
		{
			Monster_Slime* slime = new Monster_Slime("Slime", mX, mY);
			mRoom->monsterList.push_back(slime);
			slime->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, slime);
			RespawnOn = false;
		}
		else if (mMonsterName == MonsterName::SwoardMan)
		{
			Monster_SwoardMan* swoardMan = new Monster_SwoardMan("SwoardMan", mX, mY);
			mRoom->monsterList.push_back(swoardMan);
			swoardMan->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, swoardMan);
			RespawnOn = false;
		}
		else if (mMonsterName == MonsterName::Zombie)
		{
			Monster_Zombie* zombie = new Monster_Zombie("Zombie", mX, mY);
			zombie->SetRoom(mRoom);
			mRoom->monsterList.push_back(zombie);
			zombie->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, zombie);
			RespawnOn = false;
		}
	}
	if (mEnemyCreateAnimation->GetNowFrameY() == 30)
	{
		mIsDestroy = true;
	}
}

void Effect_EnemyCreate::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mEnemyCreateAnimation->GetNowFrameX(), mEnemyCreateAnimation->GetNowFrameY());
}