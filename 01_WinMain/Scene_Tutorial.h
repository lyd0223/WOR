#pragma once
#include "Scene.h"
//
//#define TileCountX 100
//#define TileCountY 100
//#define TileSize 64

class Scene_Tutorial : public Scene
{
	class Player* mPlayer;
	class BigZombie* mBigZombie;
	class Golem* mGolem;
	class Mazition* mMazition;
	class MazitionBullet* mMazitionBullet;
	class MuscleMan* mMuscleMan;
	class RapidZombie* mRapidZombie;
	class Slime* mSlime;
	class SpearMan* mSpearMan;
	class SwoardMan* mSwoardMan;
	class Ward* mWard;
	class Zombie* mZombie;
	class MonsterObject* mMonsterList[11];
	//class Tile* mTileList[TileCountY][TileCountX];
	class TileMap* mTileMap;
	

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	//void Load();
};

