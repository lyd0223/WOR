#pragma once
#include "Scene.h"
#define TileCountX 100
#define TileCountY 100
#define TileSize 64
#define PalleteSizeX 8
#define PalleteSizeY 8
#include <stack>

enum class ClickType
{
	FloorTypeSetClick = 0,
	WallTypeSetClick = 1,
	CliffTypeSetClick = 2,
	ThornTypeSetClick = 3,
	TileSetClick = 4
};
class Scene_MapTool :public Scene
{
	//vector<vector<class Tile*>> mTileList;
	class Tile* mTileList[TileCountY][TileCountX];
	
	ClickType mClickType;
	
	class TilePallete* mPallete[PalleteSizeY][PalleteSizeX];
	class TilePallete* mPallete2;
	int mPalletePageX;
	int mPalletePageY;
	class TilePallete* mCurrentPallete;
	Image* mBackGroundImage;
	class Button* mSaveButton;
	class Button* mLoadButton;
	class Button* mGameStartButton;
	class Button* mPalleteUpButton;
	class Button* mPalleteDownButton;
	class Button* mPalleteLeftButton;
	class Button* mPalleteRihgtButton;
	class Button* mRedoButton;
	class Button* mUndoButton;

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

