#pragma once
#include "Scene.h"


class Scene_Boss : public Scene
{
	class Player* mPlayer;
	class Monster_FireBoss* mFireBoss;
	class TileMap* mTileMap;
	vector<class Structure*> mStructureList;
	bool mMapIsOpen;
	vector<Room*> mRoomList;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	//void Load();
};

