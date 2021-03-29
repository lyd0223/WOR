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

	ImageManager::GetInstance()->LoadFromFile(L"EnemyCreate", Resources(L"Effect/EnemyCreate.png"), 1, 30);
	mImage = ImageManager::GetInstance()->FindImage(L"EnemyCreate");

	mEnemyCreateAnimation = new Animation();
	mEnemyCreateAnimation->InitFrameByStartEnd(0, 0, 0, 29, false);
	mEnemyCreateAnimation->SetIsLoop(false);
	mEnemyCreateAnimation->SetFrameUpdateTime(0.13f);
	mEnemyCreateAnimation->Play();
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

	mEnemyCreateAnimation->Update();
	
	if (mEnemyCreateAnimation->GetNowFrameY() == 26)
	{
		//ObjectManager::GetInstance()->FindObject(mName)->SetIsActive(true);
		if (mMonsterName == MonsterName::BigZombie)
		{
			Monster_BigZombie* bigzombie = new Monster_BigZombie("BigZombie", mX, mY);
			bigzombie->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, bigzombie);
		}
		else if (mMonsterName == MonsterName::Golem)
		{
			Monster_Golem* golem = new Monster_Golem("Golem", mX, mY);
			golem->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, golem);
		}
		else if (mMonsterName == MonsterName::Mazition)
		{
			Monster_Mazition* mazition = new Monster_Mazition("Mazition", mX, mY);
			mazition->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mazition);
		}
		else if (mMonsterName == MonsterName::RapidZombie)
		{
			Monster_RapidZombie* rapidZombie = new Monster_RapidZombie("RapidZombie", mX, mY);
			rapidZombie->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, rapidZombie);
		}
		else if (mMonsterName == MonsterName::Slime)
		{
			Monster_Slime* slime = new Monster_Slime("Slime", mX, mY);
			slime->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, slime);
		}
		else if (mMonsterName == MonsterName::SwoardMan)
		{
			Monster_SwoardMan* swoardMan = new Monster_SwoardMan("SwoardMan", mX, mY);
			swoardMan->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, swoardMan);
		}
		else if (mMonsterName == MonsterName::Zombie)
		{
			Monster_Zombie* zombie = new Monster_Zombie("Zombie", mX, mY);
			zombie->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, zombie);
		}

	}
	if (mEnemyCreateAnimation->GetNowFrameY() == 29)
	{
		mIsDestroy = true;
	}
}

void Effect_EnemyCreate::Render()
{
	mImage->SetScale(3.f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mEnemyCreateAnimation->GetNowFrameX(), mEnemyCreateAnimation->GetNowFrameY());
}