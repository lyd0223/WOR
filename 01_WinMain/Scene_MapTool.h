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
enum class PalletePage
{
	Main,
	Floors,
	Walls,
	Cliffs,
	Thorns,
	Structures,
	Maps
};
class Scene_MapTool :public Scene
{
	//vector<vector<class Tile*>> mTileList;
	vector<class Structure*> mStructureList;
	class Tile* mTileList[TileCountY][TileCountX];
	
	ClickType mClickType;

	PalletePage mPalletePage;
	

	class TilePallete* mPallete[PalleteSizeY][PalleteSizeX];
	class TilePallete* mPallete2;

	// struct페이지
	class TilePallete* mPallete_Structure1;
	class TilePallete* mPallete_Structure2;
	class TilePallete* mPallete_Structure3;
	class TilePallete* mPallete_Structure4;

	int mPalletePageX;
	int mPalletePageY;

	class TilePallete* mCurrentPallete;
	Image* mBackGroundImage;
	
	//버튼
	class Button* mPalleteMainButton;
	class Button* mPalleteFloorButton;
	class Button* mPalleteWallButton;
	class Button* mPalleteCliffButton;
	class Button* mPalleteThornButton;
	class Button* mPalleteStructureButton;
	class Button* mPalleteMapButton;
	class Button* mSaveButton;
	class Button* mLoadButton;
	class Button* mGameStartButton;
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

