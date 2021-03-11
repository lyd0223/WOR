#pragma once
#include "Scene.h"
#define TileCountX 100
#define TileCountY 100
#define TileSize 32
#define PalleteSizeX 8
#define PalleteSizeY 16
#include <stack>

class Scene_MapTool :public Scene
{
	//vector<vector<class Tile*>> mTileList;
	class Tile* mTileList[TileCountY][TileCountX];
	
	class TilePallete* mPallete[PalleteSizeY][PalleteSizeX];
	int mPalletePageX;
	int mPalletePageY;
	class TilePallete* mCurrentPallete;
	Image* mBackGroundImage;
	D2D1_RECT_F mSaveButton;
	D2D1_RECT_F mLoadButton;
	D2D1_RECT_F mGameStartButton;
	D2D1_RECT_F mPalleteUpButton;
	D2D1_RECT_F mPalleteDownButton;
	D2D1_RECT_F mPalleteLeftButton;
	D2D1_RECT_F mPalleteRihgtButton;
	D2D1_RECT_F mRedoButton;
	D2D1_RECT_F mUndoButton;

	stack<class ICommand*> mRedoCommandList;
	stack<class ICommand*> mUndoCommandList;
public :
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void Save();
	void Load();

	void PushCommand(ICommand* command);
	void Undo();
	void Redo();
	
};

