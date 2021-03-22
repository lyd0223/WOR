#pragma once
#include "Scene.h"
#define TileCountX 100
#define TileCountY 100
#define TileSize 64
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
	bool mBookIsOpen;
	//class Tile* mTileList[TileCountY][TileCountX]; 
	vector<vector<class Tile*>> mTileList;
	
	ClickType mClickType;

	PalletePage mPalletePage;
		
	Image* mPalleteImage;
	class TilePallete* mPallete_Floor1[2][8];
	class TilePallete* mPallete_Floor2[5][8];
	class TilePallete* mPallete_Wall1[2][2];
	class TilePallete* mPallete_Wall2[3][3];
	class TilePallete* mPallete_Wall3[2][2];
	class TilePallete* mPallete_Wall4[3][3];
	vector<class TilePallete*> mPallete_WallList;
	
	class TilePallete* mPallete2;

	vector<class TilePallete*> mPallete_Structure;
	vector<class TilePallete*> mPallete_Structure2;
	vector<class TilePallete*> mPallete_Structure3;
	vector<class TilePallete*> mPallete_BackGround;

	D2D1_RECT_F mShiftRect;
	int mPalletePageX;

	class TilePallete* mCurrentPallete;
	Image* mBackGroundImage;
	float mBackGroundX;
	
	//¹öÆ°
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

