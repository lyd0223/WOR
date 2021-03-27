#pragma once
#include "Scene.h"


class Scene_Boss : public Scene
{
	class Player* mPlayer;
	class TileMap* mTileMap;
	vector<class Structure*> mStructureList;
	bool mMapIsOpen;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	//void Load();
};

