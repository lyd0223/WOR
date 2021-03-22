#pragma once
#include "GameObject.h"

#define TileCountX 100
#define TileCountY 100
#define TileSize 64

class TileMap : public GameObject
{

	class Tile* mTileList[TileCountY][TileCountX];
	
public:
	TileMap(string sceneName);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render()override;
	void Load(string sceneName);

	inline class Tile* GetTileList(int x, int y) { return mTileList[y][x]; };


};

