#pragma once
#include "Scene.h"
//
//#define TileCountX 100
//#define TileCountY 100
//#define TileSize 48

class Scene_Tutorial : public Scene
{
	class Player* mPlayer;
	class Monster_BigZombie* mBigZombie;
	class Monster_Golem* mGolem;
	class Monster_Mazition* mMazition;
	class Monster_MazitionBullet* mMazitionBullet;
	class Monster_MuscleMan* mMuscleMan;
	class Monster_RapidZombie* mRapidZombie;
	class Monster_Slime* mSlime;
	class Monster_SpearMan* mSpearMan;
	class Monster_SwoardMan* mSwoardMan;
	class Monster_Ward* mWard;
	class Monster_Zombie* mZombie;
	//class MonsterObject* mMonsterList[11];
	vector<class MonsterObject*> mMonsterList;
	//class Tile* mTileList[TileCountY][TileCountX];
	class TileMap* mTileMap;
	

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	//void Load();
};

