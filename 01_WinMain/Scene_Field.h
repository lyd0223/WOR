#pragma once
#include "Scene.h"
#include "RandomMapGeneration.h"

class Scene_Field : public Scene
{
	class Player* mPlayer;
	class TileMap* mTileMap;
	vector<class Structure*> mStructureList;
	bool mMapIsOpen;
	vector<Room*> mRoomList;
	class Structure* mPortal;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void SetTileMap(class TileMap* tilemap) { mTileMap = tilemap; }
	//void Load();
};

