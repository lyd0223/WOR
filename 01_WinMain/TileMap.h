#pragma once
#include "GameObject.h"

#define TileCountX 100
#define TileCountY 100
#define TileSize 64

class TileMap : public GameObject
{

	vector<vector<class Tile*>> mTileList;
	vector<class Structure*> mStructureList;
	
public:
	TileMap(string sceneName);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render()override;
	void Load(string sceneName);
	inline vector<class Structure*> GetStructureList() { return mStructureList; };
	inline vector<vector<class Tile*>> GetTileList() { return mTileList; };
	inline Tile* GetTileList(int x, int y) { return mTileList[y][x]; };
};

