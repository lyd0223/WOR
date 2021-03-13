#pragma once
#include "Scene.h"

#define TileCountX 100
#define TileCountY 100
#define TileSize 64

class Scene_Tutorial : public Scene
{
	class Player* mPlayer;
	class Tile* mTileList[TileCountY][TileCountX];

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	void Load();
};

