#pragma once
#include "Scene.h"

#define TileCountX 100
#define TileCountY 100
#define TileSize 32

class Scene_Game : public Scene
{
	class Player* mPlayer;
	class Tile* mTileList[TileCountY][TileCountX];

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Load();
};

