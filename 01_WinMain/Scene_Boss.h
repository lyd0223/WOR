#pragma once
#include "Scene.h"

struct BossInterface {
	BossInterface(float x, float y, float sizeX, float sizeY, Image* image)
		: X(x), Y(y), SizeX(sizeX), SizeY(sizeY), Image(image) {};

	float X;
	float Y;
	float SizeX;
	float SizeY;
	Image* Image;
};

class Image;
class Scene_Boss : public Scene
{
	class Player* mPlayer;
	class Monster_FireBoss* mFireBoss;
	class TileMap* mTileMap;
	vector<class Structure*> mStructureList;

	BossInterface* mBossHP;
	BossInterface* mBossHPBar;

	bool mMapIsOpen;

	vector<Room*> mRoomList;

	bool mIsInterfaceInit;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	//void Load();
};

