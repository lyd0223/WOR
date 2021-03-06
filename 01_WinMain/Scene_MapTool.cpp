#include "pch.h"
#include "TilePallete.h"
#include "Scene_MapTool.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "ICommand.h"
#include "Gizmo.h"
#include "Button.h"
#include "Structure.h"
#include "Load_Image.h"
#include <fstream>

void Scene_MapTool::Init()
{
	mIsAlreadyInit = 1;

	Load_Image::GetInstance()->LoadSceneMapToolImage();

	mBookIsOpen = 1;
	mClickType = ClickType::TileSetClick;
	

	mBackGroundImage = ImageManager::GetInstance()->FindImage(L"Page");
	mBackGroundX = WINSIZEX - 200;

	Image* tileImage2 = ImageManager::GetInstance()->FindImage(L"TutorialTile");
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TileSet");

	

	//타일 만들기
	
	for (int y = 0; y < TileCountY; y++)
	{
		vector<Tile*> tilelist;
		mTileList.push_back(tilelist);
		for (int x = 0; x < TileCountX; x++)
		{
			Tile* tile = new Tile
			(
				ImageManager::GetInstance()->FindImage(L"Fire8Walls"),
				TileSize *x, TileSize*y, 
				TileSize, TileSize,
				1,1
			);
			mTileList[y].push_back(tile);
		}
	}
	//버튼
	mPalletePageX = 0;

	mSaveButton = new Button("Save", 950, 150, 60, 50);
	mLoadButton = new Button("Load", 1040, 150, 60, 50);
	mRedoButton = new Button("Redo", 1130, 150, 60, 50);
	mUndoButton = new Button("Undo", 1220, 150, 60, 50);
	mTitlebutton = new Button("TitleButton", 1220, 200, 60, 50);
	mPalleteMainButton = new Button("Back", 950, 200, 50, 50);
	mPalleteLeftButton = new Button("Left", 920, 380, 50, 50);
	mPalleteRihgtButton = new Button("Right", 1250, 380, 50, 50);
	mPalleteFloorButton = new Button("Floors", 1080, 250, 100, 50);
	mPalleteWallButton = new Button("Walls", 1080, 300, 100, 50);
	mPalleteCliffButton = new Button("Cliffs", 1080, 350, 100, 50);
	mPalleteThornButton = new Button("Thorns", 1080, 400, 100, 50);
	mPalleteStructureButton = new Button("Structures", 1080, 450, 100, 50);
	mPalleteMapButton = new Button("Maps", 1080, 500, 100, 50);
	//

	//빠레트만들기
	int palleteStartX = WINSIZEX - 320;
	int palleteStartY = 250;
	mPalleteImage = ImageManager::GetInstance()->FindImage(L"Pallete");

	//빠레트초기화
	//Floors
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			mPallete_Floor1[y][x] = new TilePallete();
			mPallete_Floor1[y][x]->Image = ImageManager::GetInstance()->FindImage(L"FireFloor");
			mPallete_Floor1[y][x]->PositionX = palleteStartX + TileSize / 2 * x;
			mPallete_Floor1[y][x]->PositionY = palleteStartY + TileSize / 2 * y;
			mPallete_Floor1[y][x]->Width = TileSize / 2;
			mPallete_Floor1[y][x]->Height = TileSize / 2;
			mPallete_Floor1[y][x]->Rect = RectMake(mPallete_Floor1[y][x]->PositionX, mPallete_Floor1[y][x]->PositionY, mPallete_Floor1[y][x]->Width, mPallete_Floor1[y][x]->Height);
			mPallete_Floor1[y][x]->FrameX = x;
			mPallete_Floor1[y][x]->FrameY = y;
		}
	}
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			mPallete_Floor2[y][x] = new TilePallete();
			mPallete_Floor2[y][x]->Image = ImageManager::GetInstance()->FindImage(L"HouseFloor"); 
			mPallete_Floor2[y][x]->PositionX = palleteStartX + TileSize / 2 * x;
			mPallete_Floor2[y][x]->PositionY = palleteStartY + 100 + TileSize / 2 * y;
			mPallete_Floor2[y][x]->Width = TileSize / 2;
			mPallete_Floor2[y][x]->Height = TileSize / 2;
			mPallete_Floor2[y][x]->Rect = RectMake(mPallete_Floor2[y][x]->PositionX, mPallete_Floor2[y][x]->PositionY, mPallete_Floor2[y][x]->Width, mPallete_Floor2[y][x]->Height);
			mPallete_Floor2[y][x]->FrameX = x;
			mPallete_Floor2[y][x]->FrameY = y;
		}
	}
	//Walls
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			mPallete_Wall1[y][x] = new TilePallete();
			mPallete_Wall1[y][x]->Image = ImageManager::GetInstance()->FindImage(L"Fire4Walls");
			mPallete_Wall1[y][x]->PositionX = palleteStartX + TileSize / 2 * x;
			mPallete_Wall1[y][x]->PositionY = palleteStartY + TileSize / 2 * y;
			mPallete_Wall1[y][x]->Width = TileSize / 2;
			mPallete_Wall1[y][x]->Height = TileSize / 2;
			mPallete_Wall1[y][x]->Rect = RectMake(mPallete_Wall1[y][x]->PositionX, mPallete_Wall1[y][x]->PositionY, mPallete_Wall1[y][x]->Width, mPallete_Wall1[y][x]->Height);
			mPallete_Wall1[y][x]->FrameX = x;
			mPallete_Wall1[y][x]->FrameY = y;
		}
	}
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			mPallete_Wall2[y][x] = new TilePallete();
			mPallete_Wall2[y][x]->Image = ImageManager::GetInstance()->FindImage(L"Fire8Walls");
			mPallete_Wall2[y][x]->PositionX = palleteStartX + 100 + TileSize / 2 * x;
			mPallete_Wall2[y][x]->PositionY = palleteStartY + TileSize / 2 * y;
			mPallete_Wall2[y][x]->Width = TileSize / 2;
			mPallete_Wall2[y][x]->Height = TileSize / 2;
			mPallete_Wall2[y][x]->Rect = RectMake(mPallete_Wall2[y][x]->PositionX, mPallete_Wall2[y][x]->PositionY, mPallete_Wall2[y][x]->Width, mPallete_Wall2[y][x]->Height);
			mPallete_Wall2[y][x]->FrameX = x;
			mPallete_Wall2[y][x]->FrameY = y;
		}
	}
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			mPallete_Wall3[y][x] = new TilePallete();
			mPallete_Wall3[y][x]->Image = ImageManager::GetInstance()->FindImage(L"House4Walls");
			mPallete_Wall3[y][x]->PositionX = palleteStartX + TileSize / 2 * x;
			mPallete_Wall3[y][x]->PositionY = palleteStartY + 130 + TileSize / 2 * y;
			mPallete_Wall3[y][x]->Width = TileSize / 2;
			mPallete_Wall3[y][x]->Height = TileSize / 2;
			mPallete_Wall3[y][x]->Rect = RectMake(mPallete_Wall3[y][x]->PositionX, mPallete_Wall3[y][x]->PositionY, mPallete_Wall3[y][x]->Width, mPallete_Wall3[y][x]->Height);
			mPallete_Wall3[y][x]->FrameX = x;
			mPallete_Wall3[y][x]->FrameY = y;
		}
	}
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			mPallete_Wall4[y][x] = new TilePallete();
			mPallete_Wall4[y][x]->Image = ImageManager::GetInstance()->FindImage(L"House8Walls");
			mPallete_Wall4[y][x]->PositionX = palleteStartX + 100 + TileSize / 2 * x;
			mPallete_Wall4[y][x]->PositionY = palleteStartY + 130 + TileSize / 2 * y;
			mPallete_Wall4[y][x]->Width = TileSize / 2;
			mPallete_Wall4[y][x]->Height = TileSize / 2;
			mPallete_Wall4[y][x]->Rect = RectMake(mPallete_Wall4[y][x]->PositionX, mPallete_Wall4[y][x]->PositionY, mPallete_Wall4[y][x]->Width, mPallete_Wall4[y][x]->Height);
			mPallete_Wall4[y][x]->FrameX = x;
			mPallete_Wall4[y][x]->FrameY = y;
		}
	}
	{
		TilePallete* mPallete_Wall = new TilePallete();
		mPallete_Wall->Image = ImageManager::GetInstance()->FindImage(L"HouseWall1");
		mPallete_Wall->PositionX = palleteStartX - 20;
		mPallete_Wall->PositionY = palleteStartY;
		mPallete_Wall->Width = TileSize * 3 / 2;
		mPallete_Wall->Height = TileSize * 3 / 2;
		mPallete_Wall->Rect = RectMake(mPallete_Wall->PositionX, mPallete_Wall->PositionY, mPallete_Wall->Width, mPallete_Wall->Height);
		mPallete_WallList.push_back(mPallete_Wall);
	}
	{
		TilePallete* mPallete_Wall = new TilePallete();
		mPallete_Wall->Image = ImageManager::GetInstance()->FindImage(L"HouseWall2");
		mPallete_Wall->PositionX = palleteStartX + 80;
		mPallete_Wall->PositionY = palleteStartY;
		mPallete_Wall->Width = TileSize * 3 / 2;
		mPallete_Wall->Height = TileSize * 3 / 2;
		mPallete_Wall->Rect = RectMake(mPallete_Wall->PositionX, mPallete_Wall->PositionY, mPallete_Wall->Width, mPallete_Wall->Height);
		mPallete_WallList.push_back(mPallete_Wall);
	}
	{
		TilePallete* mPallete_Wall = new TilePallete();
		mPallete_Wall->Image = ImageManager::GetInstance()->FindImage(L"HouseWall3");
		mPallete_Wall->PositionX = palleteStartX + 180;
		mPallete_Wall->PositionY = palleteStartY;
		mPallete_Wall->Width = TileSize * 3 / 2;
		mPallete_Wall->Height = TileSize * 3 / 2;
		mPallete_Wall->Rect = RectMake(mPallete_Wall->PositionX, mPallete_Wall->PositionY, mPallete_Wall->Width, mPallete_Wall->Height);
		mPallete_WallList.push_back(mPallete_Wall);
	}
	{
		TilePallete* mPallete_Wall = new TilePallete();

		mPallete_Wall->Image = ImageManager::GetInstance()->FindImage(L"FireWall1");
		mPallete_Wall->PositionX = palleteStartX - 20;
		mPallete_Wall->PositionY = palleteStartY + 100;
		mPallete_Wall->Width = TileSize * 3 / 2;
		mPallete_Wall->Height = TileSize * 3 / 2;
		mPallete_Wall->Rect = RectMake(mPallete_Wall->PositionX, mPallete_Wall->PositionY, mPallete_Wall->Width, mPallete_Wall->Height);
		mPallete_WallList.push_back(mPallete_Wall);
	}
	{
		TilePallete* mPallete_Wall = new TilePallete();
		mPallete_Wall->Image = ImageManager::GetInstance()->FindImage(L"FireWall2");
		mPallete_Wall->PositionX = palleteStartX + 80;
		mPallete_Wall->PositionY = palleteStartY + 100;
		mPallete_Wall->Width = TileSize * 3 / 2;
		mPallete_Wall->Height = TileSize * 3 / 2;
		mPallete_Wall->Rect = RectMake(mPallete_Wall->PositionX, mPallete_Wall->PositionY, mPallete_Wall->Width, mPallete_Wall->Height);
		mPallete_WallList.push_back(mPallete_Wall);
	}
	{
		TilePallete* mPallete_Wall = new TilePallete();
		mPallete_Wall->Image = ImageManager::GetInstance()->FindImage(L"FireWall3");
		mPallete_Wall->PositionX = palleteStartX + 180;
		mPallete_Wall->PositionY = palleteStartY + 100;
		mPallete_Wall->Width = TileSize * 3 / 2;
		mPallete_Wall->Height = TileSize * 3 / 2;
		mPallete_Wall->Rect = RectMake(mPallete_Wall->PositionX, mPallete_Wall->PositionY, mPallete_Wall->Width, mPallete_Wall->Height);
		mPallete_WallList.push_back(mPallete_Wall);
	}
	//Cliffs

	//Thorns

	//Maps
	mPallete_Map1 = new TilePallete();
	mPallete_Map1->Image = ImageManager::GetInstance()->FindImage(L"FireBossMap");
	mPallete_Map1->PositionX = palleteStartX - 20;
	mPallete_Map1->PositionY = palleteStartY;
	mPallete_Map1->Width = TileSize * 3 / 2;
	mPallete_Map1->Height = TileSize * 3 / 2;
	mPallete_Map1->Rect = RectMake(mPallete_Map1->PositionX, mPallete_Map1->PositionY, mPallete_Map1->Width, mPallete_Map1->Height);

	//Structures
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Tree1");
		pallete->PositionX = WINSIZEX - 350;
		pallete->PositionY = 230;
		pallete->Width = TileSize * 3 / 2;
		pallete->Height = TileSize * 4 / 2;
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Tree2");
		pallete->PositionX = WINSIZEX - 250;
		pallete->PositionY = 230;
		pallete->Width = TileSize * 3 / 2;
		pallete->Height = TileSize * 4 / 2;
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Flag");
		pallete->PositionX = WINSIZEX - 150;
		pallete->PositionY = 230;
		pallete->Width = TileSize;
		pallete->Height = TileSize * 4 / 2;
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"BookShelf");
		pallete->PositionX = WINSIZEX - 350;
		pallete->PositionY = 380;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Bed");
		pallete->PositionX = WINSIZEX - 200;
		pallete->PositionY = 380;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Book1");
		pallete->PositionX = WINSIZEX - 360;
		pallete->PositionY = 230;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Book2");
		pallete->PositionX = WINSIZEX - 300;
		pallete->PositionY = 230;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Book3");
		pallete->PositionX = WINSIZEX - 240;
		pallete->PositionY = 230;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Book4");
		pallete->PositionX = WINSIZEX - 180;
		pallete->PositionY = 230;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Book5");
		pallete->PositionX = WINSIZEX - 120;
		pallete->PositionY = 230;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Table");
		pallete->PositionX = WINSIZEX - 350;
		pallete->PositionY = 350;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"SmallTable");
		pallete->PositionX = WINSIZEX - 200;
		pallete->PositionY = 350;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Chair");
		pallete->PositionX = WINSIZEX - 150;
		pallete->PositionY = 350;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Portal");
		pallete->PositionX = WINSIZEX - 350;
		pallete->PositionY = 420;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"ScareCrow");
		pallete->PositionX = WINSIZEX - 200;
		pallete->PositionY = 420;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure2.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Gate");
		pallete->PositionX = WINSIZEX - 350;
		pallete->PositionY = 230;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure3.push_back(pallete);
	}
	{
		TilePallete* pallete = new TilePallete();
		pallete->Image = ImageManager::GetInstance()->FindImage(L"Penta");
		pallete->PositionX = WINSIZEX - 350;
		pallete->PositionY = 370;
		pallete->Width = pallete->Image->GetWidth();
		pallete->Height = pallete->Image->GetHeight();
		pallete->Rect = RectMake(pallete->PositionX, pallete->PositionY, pallete->Width, pallete->Height);
		mPallete_Structure3.push_back(pallete);
	}
	//튜토리얼 파레트
	mPallete2 = new TilePallete();
	mPallete2->Image = tileImage2;
	mPallete2->PositionX = palleteStartX;
	mPallete2->PositionY = palleteStartY + 300;
	mPallete2->Width = TileSize * 4;
	mPallete2->Height = TileSize * 2;
	mPallete2->Rect = RectMake(mPallete2->PositionX, mPallete2->PositionY, mPallete2->Width, mPallete2->Height);
	//
	

	
	//mGameStartButton = new Button("GameStart", WINSIZEX - 250,50, 100, 100); 
	mCurrentPallete = mPallete_Wall2[1][1];
	//

	Camera* camera = new Camera();
	camera->ChangeMode(Camera::Mode::MapTool);
	camera->Init();
	CameraManager::GetInstance()->SetMainCamera(camera);
}

void Scene_MapTool::Release()
{
	for (int y = 0; y < TileCountY; ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			SafeDelete(mTileList[y][x]);
		}
	}
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			SafeDelete(mPallete_Wall2[y][x]);
		}
	}
}

void Scene_MapTool::Update()
{
	CameraManager::GetInstance()->GetMainCamera()->Update();
	mPalleteMainButton->Update();
	mPalleteLeftButton->Update();
	mPalleteRihgtButton->Update();
	mPalleteFloorButton->Update();
	mPalleteWallButton->Update();
	mPalleteCliffButton->Update();
	mPalleteThornButton->Update();
	mPalleteStructureButton->Update();
	mPalleteMapButton->Update();
	mSaveButton->Update();
	mLoadButton->Update();
	mRedoButton->Update();
	mUndoButton->Update();
	mTitlebutton->Update();
	if (Input::GetInstance()->GetKeyDown(VK_TAB))
	{
		if (mBookIsOpen)
			mBookIsOpen = 0;
		else
			mBookIsOpen = 1;
	}
	if (mBookIsOpen)
	{
		while(mBackGroundX > WINSIZEX-200)
		{
			mBackGroundX--;
			mPalleteMainButton->BookOpen();
			mPalleteLeftButton->BookOpen();
			mPalleteRihgtButton->BookOpen();
			mPalleteFloorButton->BookOpen();
			mPalleteWallButton->BookOpen();
			mPalleteCliffButton->BookOpen();
			mPalleteThornButton->BookOpen();
			mPalleteStructureButton->BookOpen();
			mPalleteMapButton->BookOpen();
			mSaveButton->BookOpen();
			mLoadButton->BookOpen();
			mRedoButton->BookOpen();
			mUndoButton->BookOpen();
			mTitlebutton->BookOpen();

		}
	}
	else
	{
		while(mBackGroundX < WINSIZEX + 150)
		{
			mBackGroundX++;
			mPalleteMainButton->BookClose();
			mPalleteLeftButton->BookClose();
			mPalleteRihgtButton->BookClose();
			mPalleteFloorButton->BookClose();
			mPalleteWallButton->BookClose();
			mPalleteCliffButton->BookClose();
			mPalleteThornButton->BookClose();
			mPalleteStructureButton->BookClose();
			mPalleteMapButton->BookClose();
			mSaveButton->BookClose();
			mLoadButton->BookClose();
			mRedoButton->BookClose();
			mUndoButton->BookClose();
			mTitlebutton->BookClose();
		}
	}
	
	//빠레트페이지변경
	D2D1_RECT_F rctemp;
	if (mPalletePage == PalletePage::Main)
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			rctemp = mPalleteFloorButton->GetRect();
			if (PtInRect(&rctemp, _mousePosition)) mPalletePage = PalletePage::Floors;
		
			rctemp = mPalleteWallButton->GetRect();
			if (PtInRect(&rctemp, _mousePosition)) mPalletePage = PalletePage::Walls;
		
			rctemp = mPalleteCliffButton->GetRect();
			if (PtInRect(&rctemp, _mousePosition)) mPalletePage = PalletePage::Cliffs;
		
			rctemp = mPalleteThornButton->GetRect();
			if (PtInRect(&rctemp, _mousePosition)) mPalletePage = PalletePage::Thorns;
		
			rctemp = mPalleteMapButton->GetRect();
			if (PtInRect(&rctemp, _mousePosition)) mPalletePage = PalletePage::Maps;
		
			rctemp = mPalleteStructureButton->GetRect();
			if (PtInRect(&rctemp, _mousePosition)) mPalletePage = PalletePage::Structures;
		
		}
	}
	else
	{
		//tile type 변경
		if (Input::GetInstance()->GetKeyDown('0')) mClickType = ClickType::FloorTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('1')) mClickType = ClickType::WallTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('2')) mClickType = ClickType::CliffTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('3')) mClickType = ClickType::ThornTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('4')) mClickType = ClickType::TileSetClick;
		
		rctemp = mPalleteMainButton->GetRect();
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&rctemp, _mousePosition))
			{
				mPalletePage = PalletePage::Main;
				mPalletePageX = 0;

			}

			if (mPalletePage == PalletePage::Floors)
			{
				
				for (int y = 0; y < 2; y++)
				{
					for (int x = 0; x < 8; x++)
					{
						if (mBookIsOpen && PtInRect(&mPallete_Floor1[y][x]->Rect, _mousePosition))
							mCurrentPallete = mPallete_Floor1[y][x];
					}
				}
				for (int y = 0; y < 5; y++)
				{
					for (int x = 0; x < 8; x++)
					{
						if (mBookIsOpen && PtInRect(&mPallete_Floor2[y][x]->Rect, _mousePosition))
							mCurrentPallete = mPallete_Floor2[y][x];
					}
				}

				/*for (int y = 0; y < PalleteSizeY; y++)
				{
					for (int x = 0; x < PalleteSizeX; x++)
					{
						if (PtInRect(&mPallete[y][x]->Rect, _mousePosition))
						{
							mCurrentPallete = mPallete[y][x];
						}
					}
				}*/
			}

			if (mPalletePage == PalletePage::Walls)
			{
				if (mPalletePageX == 0)
				{
					for (int y = 0; y < 2; y++)
					{
						for (int x = 0; x < 2; x++)
						{
							if (mBookIsOpen && PtInRect(&mPallete_Wall1[y][x]->Rect, _mousePosition))
								mCurrentPallete = mPallete_Wall1[y][x];
						}
					}
					for (int y = 0; y < 3; y++)
					{
						for (int x = 0; x < 3; x++)
						{
							if (mBookIsOpen && PtInRect(&mPallete_Wall2[y][x]->Rect, _mousePosition))
								mCurrentPallete = mPallete_Wall2[y][x];
						}
					}
					for (int y = 0; y < 2; y++)
					{
						for (int x = 0; x < 2; x++)
						{
							if (mBookIsOpen && PtInRect(&mPallete_Wall3[y][x]->Rect, _mousePosition))
								mCurrentPallete = mPallete_Wall3[y][x];
						}
					}
					for (int y = 0; y < 3; y++)
					{
						for (int x = 0; x < 3; x++)
						{
							if (mBookIsOpen && PtInRect(&mPallete_Wall4[y][x]->Rect, _mousePosition))
								mCurrentPallete = mPallete_Wall4[y][x];
						}
					}
				}
				else if (mPalletePageX == 1)
				{
					for (int i = 0; i < mPallete_WallList.size(); i++)
					{
						if (mBookIsOpen && PtInRect(&mPallete_WallList[i]->Rect, _mousePosition))
							mCurrentPallete = mPallete_WallList[i];
					}
					
				}
			}
			if (mPalletePage == PalletePage::Cliffs)
			{

			}
			if (mPalletePage == PalletePage::Thorns)
			{

			}
			if (mPalletePage == PalletePage::Maps)
			{
				if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
				{
					if (PtInRect(&mPallete_Map1->Rect, _mousePosition))
					{
						mCurrentPallete = mPallete_Map1;
					}
				}
			}
			if (mPalletePage == PalletePage::Structures)
			{
				if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
				{
					for (int i = 0; i < mPallete_Structure.size(); i++)
					{
						if (mBookIsOpen && mPalletePageX == 0 && PtInRect(&mPallete_Structure[i]->Rect, _mousePosition))
						{
							mCurrentPallete = mPallete_Structure[i];
						}
					}
					for (int i = 0; i < mPallete_Structure2.size(); i++)
					{
						if (mBookIsOpen && mPalletePageX == 1 && PtInRect(&mPallete_Structure2[i]->Rect, _mousePosition))
						{
							mCurrentPallete = mPallete_Structure2[i];
						}
					}
					for (int i = 0; i < mPallete_Structure3.size(); i++)
					{
						if (mBookIsOpen && mPalletePageX == 2 && PtInRect(&mPallete_Structure3[i]->Rect, _mousePosition))
						{
							mCurrentPallete = mPallete_Structure3[i];
						}
					}
					
				}

			}
			
		}
	}


	//버튼들
	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		D2D1_RECT_F rctemp;
		rctemp = mLoadButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			Load();
		}
		rctemp = mSaveButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			Save();
		}
		rctemp = mRedoButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
			Redo();
		rctemp = mUndoButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
			Undo();
		rctemp = mTitlebutton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			SceneManager::GetInstance()->LoadScene(L"Title");

			return;
		}

		rctemp = mPalleteRihgtButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{

			mPalletePageX++;
		}
		rctemp = mPalleteLeftButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			mPalletePageX--;
		}
	}
	
	//타일 바꾸기

	//타일 전체바꾸기
	static int tileXTemp;
	static int tileYTemp;
	
	if (Input::GetInstance()->GetKey(VK_SHIFT))
	{
		for (int y = 0; y < TileCountY; y++)
		{
			for (int x = 0; x < TileCountX; x++)
			{
				Camera* camera = CameraManager::GetInstance()->GetMainCamera();
				D2D1_RECT_F rctemp = mTileList[y][x]->GetRect();
				
				//마우스가 목표타일안에있을때.
				if (!mBookIsOpen &&
					PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }) ||
					(mBookIsOpen && _mousePosition.x < WINSIZEX - 400 &&
						PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() })))
				{
					if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
					{
						tileXTemp = x;
						tileYTemp = y;
					}
					if (Input::GetInstance()->GetKey(VK_LBUTTON))
					{
						mShiftRect = RectMake(mTileList[tileYTemp][tileXTemp]->GetX(),   mTileList[tileYTemp][tileXTemp]->GetY() , (float)(x - tileXTemp+1) * TileSize ,(float)(y - tileYTemp+1) * TileSize );
						
					}
					if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
					{
						for (int y1 = tileYTemp; y1 <= y; y1++)
						{
							for (int x1 = tileXTemp; x1<= x; x1++)
							{
								if (mCurrentPallete->GetImage()->GetKey() == L"HouseFloor")
								{
									mTileList[y1][x1]->SetImage(mCurrentPallete->Image);
									mTileList[y1][x1]->SetFrameIndexY(Random::GetInstance()->RandomInt(5));
									mTileList[y1][x1]->SetFrameIndexX(Random::GetInstance()->RandomInt(8));
								}
								else if (mCurrentPallete->GetImage()->GetKey() == L"FireFloor")
								{
									mTileList[y1][x1]->SetImage(mCurrentPallete->Image);
									mTileList[y1][x1]->SetFrameIndexY(Random::GetInstance()->RandomInt(2));
									mTileList[y1][x1]->SetFrameIndexX(Random::GetInstance()->RandomInt(8));
								}
								else if (mCurrentPallete->GetImage()->GetKey() == L"Fire8Walls")
								{
									mTileList[y1][x1]->SetImage(mCurrentPallete->Image);
									mTileList[y1][x1]->SetFrameIndexY(mCurrentPallete->GetFrameY());
									mTileList[y1][x1]->SetFrameIndexX(mCurrentPallete->GetFrameX());
								}
							}
						}
					}
				}
			}
		}

	}
	else
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{

			if (mClickType == ClickType::TileSetClick)
			{
				for (int y = 0; y < TileCountY; y++)
				{
					for (int x = 0; x < TileCountX; x++)
					{
						Camera* camera = CameraManager::GetInstance()->GetMainCamera();

						D2D1_RECT_F rctemp = mTileList[y][x]->GetRect();
						//마우스가 목표타일안에있을때.
						if (!mBookIsOpen &&
							PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }) ||
							(mBookIsOpen && _mousePosition.x < WINSIZEX - 400 &&
								PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() })))
						{
							if (mCurrentPallete->Image->GetKey() == L"Fire4Walls" ||
								mCurrentPallete->Image->GetKey() == L"Fire8Walls" ||
								mCurrentPallete->Image->GetKey() == L"House4Walls" ||
								mCurrentPallete->Image->GetKey() == L"House8Walls")
							{
								IBrushTile* command = new IBrushTile(mTileList[y][x], mCurrentPallete);
								PushCommand(command);
								mTileList[y][x]->SetType(Type::Wall);
							}
							else if (mCurrentPallete->Image->GetKey() == L"FireWall1" ||
								mCurrentPallete->Image->GetKey() == L"FireWall2" ||
								mCurrentPallete->Image->GetKey() == L"FireWall3" ||
								mCurrentPallete->Image->GetKey() == L"HouseWall1" ||
								mCurrentPallete->Image->GetKey() == L"HouseWall2" ||
								mCurrentPallete->Image->GetKey() == L"HouseWall3")
							{
								for (int y2 = y - 1; y2 <= y + 1; y2++)
								{
									for (int x2 = x - 1; x2 <= x + 1; x2++)
									{
										mTileList[y2][x2]->SetImage(mCurrentPallete->Image);
										mTileList[y2][x2]->SetFrameIndexY(y2 - y + 1);
										mTileList[y2][x2]->SetFrameIndexX(x2 - x + 1);
										mTileList[y2][x2]->SetType(Type::Wall);
									}
								}
							}
							//파이어보스맵일때
							else if (mCurrentPallete->Image->GetKey() == L"FireBossMap")
							{

								for (int y2 = y-6; y2 < y+6; y2++)
								{
									for (int x2 = x-8; x2 < x+8; x2++)
									{
										mTileList[y2][x2]->SetImage(mCurrentPallete->Image);
										mTileList[y2][x2]->SetFrameIndexY(y2 - y + 6);
										mTileList[y2][x2]->SetFrameIndexX(x2 - x + 8);
									}
								}
							}
							else if (mCurrentPallete->Image->GetKey() == L"Tree1")
							{

								Structure* st = new Structure
								(
									"Tree1",
									ImageManager::GetInstance()->FindImage(L"Tree1"),
									mTileList[y-1][x]->GetX() + TileSize / 2,
									mTileList[y-1][x]->GetY() + TileSize / 2,
									mCurrentPallete->Width,
									mCurrentPallete->Height
								);
								mTileList[y][x]->SetType(Type::Wall);
								mStructureList.push_back(st);

							}
							else if (mCurrentPallete->Image->GetKey() == L"Tree2")
							{
								Structure* st = new Structure
								(
									"Tree2",
									ImageManager::GetInstance()->FindImage(L"Tree2"),
									mTileList[y-1][x]->GetX() + TileSize / 2,
									mTileList[y-1][x]->GetY() + TileSize / 2,
									mCurrentPallete->Width,
									mCurrentPallete->Height
								);
								mTileList[y][x]->SetType(Type::Wall);
								mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Flag")
							{
								Structure* st = new Structure
								(
									"Flag",
									ImageManager::GetInstance()->FindImage(L"Flag"),
									mTileList[y][x]->GetX() + TileSize / 2,
									mTileList[y][x]->GetY() + TileSize / 2,
									mCurrentPallete->Width,
									mCurrentPallete->Height
								);
								mTileList[y][x]->SetType(Type::Wall);
								mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"BookShelf")
							{
								Structure* st = new Structure
								(
									"BookShelf",
									ImageManager::GetInstance()->FindImage(L"BookShelf"),
									mTileList[y][x]->GetX() + TileSize / 2,
									mTileList[y][x]->GetY() + TileSize / 2,
									mCurrentPallete->Width,
									mCurrentPallete->Height
								);
								mTileList[y][x]->SetType(Type::Wall);
								mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Bed")
							{
								Structure* st = new Structure
								(
									"Bed",
									ImageManager::GetInstance()->FindImage(L"Bed"),
									mTileList[y][x]->GetX() + TileSize / 2,
									mTileList[y][x]->GetY() + TileSize / 2,
									mCurrentPallete->Width,
									mCurrentPallete->Height
								);
								mTileList[y][x]->SetType(Type::Wall);
								mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Chair")
							{
							Structure* st = new Structure
							(
								"Chair",
								ImageManager::GetInstance()->FindImage(L"Chair"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mTileList[y][x]->SetType(Type::Wall);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Book1")
							{
							Structure* st = new Structure
							(
								"Book1",
								ImageManager::GetInstance()->FindImage(L"Book1"),
								mTileList[y-1][x]->GetX() + TileSize / 2,
								mTileList[y-1][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Book2")
							{
							Structure* st = new Structure
							(
								"Book2",
								ImageManager::GetInstance()->FindImage(L"Book2"),
								mTileList[y-1][x]->GetX() + TileSize / 2,
								mTileList[y-1][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Book3")
							{
							Structure* st = new Structure
							(
								"Book3",
								ImageManager::GetInstance()->FindImage(L"Book3"),
								mTileList[y-1][x]->GetX() + TileSize / 2,
								mTileList[y-1][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Book4")
							{
							Structure* st = new Structure
							(
								"Book4",
								ImageManager::GetInstance()->FindImage(L"Book4"),
								mTileList[y-1][x]->GetX() + TileSize / 2,
								mTileList[y-1][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Book5")
							{
							Structure* st = new Structure
							(
								"Book5",
								ImageManager::GetInstance()->FindImage(L"Book5"),
								mTileList[y-1][x]->GetX() + TileSize / 2,
								mTileList[y-1][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Table")
							{
							Structure* st = new Structure
							(
								"Table",
								ImageManager::GetInstance()->FindImage(L"Table"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mTileList[y][x]->SetType(Type::Wall);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"SmallTable")
							{
							Structure* st = new Structure
							(
								"SmallTable",
								ImageManager::GetInstance()->FindImage(L"SmallTable"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mTileList[y][x]->SetType(Type::Wall);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Portal")
							{
							Structure* st = new Structure
							(
								"Portal",
								ImageManager::GetInstance()->FindImage(L"Portal"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Gate")
							{
							Structure* st = new Structure
							(
								"Gate",
								ImageManager::GetInstance()->FindImage(L"Gate"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"Penta")
							{
							Structure* st = new Structure
							(
								"Penta",
								ImageManager::GetInstance()->FindImage(L"Penta"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}
							else if (mCurrentPallete->Image->GetKey() == L"ScareCrow")
							{
							Structure* st = new Structure
							(
								"ScareCrow",
								ImageManager::GetInstance()->FindImage(L"ScareCrow"),
								mTileList[y][x]->GetX() + TileSize / 2,
								mTileList[y][x]->GetY() + TileSize / 2,
								mCurrentPallete->Width,
								mCurrentPallete->Height
							);
							mStructureList.push_back(st);
							}

							//나머지.
							else if (mTileList[y][x]->GetImage() != mCurrentPallete->GetImage() ||
								mTileList[y][x]->GetFrameIndexX() != mCurrentPallete->GetFrameX() ||
								mTileList[y][x]->GetFrameIndexY() != mCurrentPallete->GetFrameY())
							{
								IBrushTile* command = new IBrushTile(mTileList[y][x], mCurrentPallete);
								PushCommand(command);
							}

						}

					}
				}


			}
			else
			{
				for (int y = 0; y < TileCountY; y++)
				{
					for (int x = 0; x < TileCountX; x++)
					{
						Camera* camera = CameraManager::GetInstance()->GetMainCamera();

						D2D1_RECT_F rctemp = mTileList[y][x]->GetRect();
						//마우스가 목표타일안에있을때.
						if (_mousePosition.x < WINSIZEX - 400 &&
							PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }))
						{
							//타입 설정해주기.
							if (mClickType == ClickType::WallTypeSetClick)
								mTileList[y][x]->SetType(Type::Wall);
							else if (mClickType == ClickType::ThornTypeSetClick)
								mTileList[y][x]->SetType(Type::Thorn);
							else if (mClickType == ClickType::CliffTypeSetClick)
								mTileList[y][x]->SetType(Type::Cliff);
							else if (mClickType == ClickType::FloorTypeSetClick)
								mTileList[y][x]->SetType(Type::Floor);
						}
					}
				}
			}


		}
	}
	int palleteStartX = WINSIZEX - 275;
	int palleteStartY = 130;

	
}

void Scene_MapTool::Render()
{

	//타일그리는부분
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				mTileList[y][x]->Render();
				
			}
		}
	}
	//스트럭쳐 그리는부분
	for (int i = 0; i < mStructureList.size(); i++)
	{
		mStructureList[i]->Render();
	}
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				CameraManager::GetInstance()->GetMainCamera()->RenderGizmoRect(mTileList[y][x]->GetRect());
				CameraManager::GetInstance()->GetMainCamera()->RenderText
				(
					mTileList[y][x]->GetX() + 5, mTileList[y][x]->GetY() + 5,
					to_wstring(y) + L"," + to_wstring(x), 10
				);
				CameraManager::GetInstance()->GetMainCamera()->RenderText
				(
					mTileList[y][x]->GetX() + 5, mTileList[y][x]->GetY() + 15,
					to_wstring((int)mTileList[y][x]->GetType()), 10
				);
			}
			//마우스가 타일렉트안에들어오면, 테두리바까줌
			if (!mBookIsOpen &&
				PtInRect(&tileRect, { _mousePosition.x - WINSIZEX / 2 + (LONG)CameraManager::GetInstance()->GetMainCamera()->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)CameraManager::GetInstance()->GetMainCamera()->GetY() }) ||
				(mBookIsOpen && _mousePosition.x < WINSIZEX - 400 &&
					PtInRect(&tileRect, { _mousePosition.x - WINSIZEX / 2 + (LONG)CameraManager::GetInstance()->GetMainCamera()->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)CameraManager::GetInstance()->GetMainCamera()->GetY() })))
			{
				CameraManager::GetInstance()->GetMainCamera()->RenderGizmoRect({ tileRect.left + 1, tileRect.top + 1,tileRect.right - 1,tileRect.bottom - 1 }, D2D1::ColorF::Red);
			}
		}
	}
	//빠레트그리는부분
	mBackGroundImage->ScaleRender(mBackGroundX, WINSIZEY/2,500,WINSIZEY);
	mSaveButton->Render();
	mLoadButton->Render();
	mRedoButton->Render();
	mUndoButton->Render();
	mTitlebutton->Render();
	if (mPalletePage == PalletePage::Main)     
	{
		mPalleteMainButton->Render();
		mPalleteFloorButton->Render();
		mPalleteWallButton->Render();
		mPalleteCliffButton->Render();
		mPalleteThornButton->Render();
		mPalleteStructureButton->Render();
		mPalleteMapButton->Render();
	}
	else
	{
		mPalleteMainButton->Render();
		mPalleteLeftButton->Render();
		mPalleteRihgtButton->Render();
		if (mBookIsOpen)
		{
			if (mPalletePage == PalletePage::Floors)
			{
				for (int y = 0; y < 2; y++)
				{
					for (int x = 0; x < 8; x++)
					{
						mPallete_Floor1[y][x]->Image->FrameRender
						(
							(mPallete_Floor1[y][x]->Rect.right + mPallete_Floor1[y][x]->Rect.left) / 2,
							(mPallete_Floor1[y][x]->Rect.top + mPallete_Floor1[y][x]->Rect.bottom) / 2,
							mPallete_Floor1[y][x]->FrameX,
							mPallete_Floor1[y][x]->FrameY
						);
						mPalleteImage->ScaleRender(
							(mPallete_Floor1[y][x]->Rect.right + mPallete_Floor1[y][x]->Rect.left) / 2,
							(mPallete_Floor1[y][x]->Rect.top + mPallete_Floor1[y][x]->Rect.bottom) / 2,
							mPallete_Floor1[y][x]->Width,
							mPallete_Floor1[y][x]->Height
						);

					}
				}
				for (int y = 0; y < 5; y++)
				{
					for (int x = 0; x < 8; x++)
					{
						mPallete_Floor2[y][x]->Image->FrameRender
						(
							(mPallete_Floor2[y][x]->Rect.right + mPallete_Floor2[y][x]->Rect.left) / 2,
							(mPallete_Floor2[y][x]->Rect.top + mPallete_Floor2[y][x]->Rect.bottom) / 2,
							mPallete_Floor2[y][x]->FrameX,
							mPallete_Floor2[y][x]->FrameY
						);
						mPalleteImage->ScaleRender(
							(mPallete_Floor2[y][x]->Rect.right + mPallete_Floor2[y][x]->Rect.left) / 2,
							(mPallete_Floor2[y][x]->Rect.top + mPallete_Floor2[y][x]->Rect.bottom) / 2,
							mPallete_Floor2[y][x]->Width,
							mPallete_Floor2[y][x]->Height
						);

					}
				}
			}
			else if (mPalletePage == PalletePage::Walls)
			{
				if (mPalletePageX == 0)
				{
					for (int y = 0; y < 2; y++)
					{
						for (int x = 0; x < 2; x++)
						{
							mPallete_Wall1[y][x]->Image->FrameRender
							(
								(mPallete_Wall1[y][x]->Rect.right + mPallete_Wall1[y][x]->Rect.left) / 2,
								(mPallete_Wall1[y][x]->Rect.top + mPallete_Wall1[y][x]->Rect.bottom) / 2,
								mPallete_Wall1[y][x]->FrameX,
								mPallete_Wall1[y][x]->FrameY
							);
							mPalleteImage->ScaleRender(
								(mPallete_Wall1[y][x]->Rect.right + mPallete_Wall1[y][x]->Rect.left) / 2,
								(mPallete_Wall1[y][x]->Rect.top + mPallete_Wall1[y][x]->Rect.bottom) / 2,
								mPallete_Wall1[y][x]->Width,
								mPallete_Wall1[y][x]->Height
							);

						}
					}
					for (int y = 0; y < 3; y++)
					{
						for (int x = 0; x < 3; x++)
						{
							mPallete_Wall2[y][x]->Image->FrameRender
							(
								(mPallete_Wall2[y][x]->Rect.right + mPallete_Wall2[y][x]->Rect.left) / 2,
								(mPallete_Wall2[y][x]->Rect.top + mPallete_Wall2[y][x]->Rect.bottom) / 2,
								mPallete_Wall2[y][x]->FrameX,
								mPallete_Wall2[y][x]->FrameY
							);
							mPalleteImage->ScaleRender(
								(mPallete_Wall2[y][x]->Rect.right + mPallete_Wall2[y][x]->Rect.left) / 2,
								(mPallete_Wall2[y][x]->Rect.top + mPallete_Wall2[y][x]->Rect.bottom) / 2,
								mPallete_Wall2[y][x]->Width,
								mPallete_Wall2[y][x]->Height
							);

						}
					}
					for (int y = 0; y < 2; y++)
					{
						for (int x = 0; x < 2; x++)
						{
							mPallete_Wall3[y][x]->Image->FrameRender
							(
								(mPallete_Wall3[y][x]->Rect.right + mPallete_Wall3[y][x]->Rect.left) / 2,
								(mPallete_Wall3[y][x]->Rect.top + mPallete_Wall3[y][x]->Rect.bottom) / 2,
								mPallete_Wall3[y][x]->FrameX,
								mPallete_Wall3[y][x]->FrameY
							);
							mPalleteImage->ScaleRender(
								(mPallete_Wall3[y][x]->Rect.right + mPallete_Wall3[y][x]->Rect.left) / 2,
								(mPallete_Wall3[y][x]->Rect.top + mPallete_Wall3[y][x]->Rect.bottom) / 2,
								mPallete_Wall3[y][x]->Width,
								mPallete_Wall3[y][x]->Height
							);

						}
					}
					for (int y = 0; y < 3; y++)
					{
						for (int x = 0; x < 3; x++)
						{
							mPallete_Wall4[y][x]->Image->FrameRender
							(
								(mPallete_Wall4[y][x]->Rect.right + mPallete_Wall4[y][x]->Rect.left) / 2,
								(mPallete_Wall4[y][x]->Rect.top + mPallete_Wall4[y][x]->Rect.bottom) / 2,
								mPallete_Wall4[y][x]->FrameX,
								mPallete_Wall4[y][x]->FrameY
							);
							mPalleteImage->ScaleRender(
								(mPallete_Wall4[y][x]->Rect.right + mPallete_Wall4[y][x]->Rect.left) / 2,
								(mPallete_Wall4[y][x]->Rect.top + mPallete_Wall4[y][x]->Rect.bottom) / 2,
								mPallete_Wall4[y][x]->Width,
								mPallete_Wall4[y][x]->Height
							);

						}
					}
				}
				else if (mPalletePageX == 1)
				{
					for (int i = 0; i < mPallete_WallList.size(); i++)
					{
						mPallete_WallList[i]->Image->SetScale(3.0f);
						mPallete_WallList[i]->Image->Render
						(
							(mPallete_WallList[i]->Rect.right + mPallete_WallList[i]->Rect.left) / 2,
							(mPallete_WallList[i]->Rect.top + mPallete_WallList[i]->Rect.bottom) / 2
						);
						mPalleteImage->ScaleRender(
							(mPallete_WallList[i]->Rect.right + mPallete_WallList[i]->Rect.left) / 2,
							(mPallete_WallList[i]->Rect.top + mPallete_WallList[i]->Rect.bottom) / 2,
							mPallete_WallList[i]->Width,
							mPallete_WallList[i]->Height
						);
					}
					
				}
			}
			else if (mPalletePage == PalletePage::Cliffs)
			{

			}
			else if (mPalletePage == PalletePage::Maps)
			{
				if (mPalletePageX == 0)
				{
					mPallete_Map1->Image->SetScale(3.0f);
					mPallete_Map1->Image->Render
					(
						(mPallete_Map1->Rect.right + mPallete_Map1->Rect.left) / 2,
						(mPallete_Map1->Rect.top + mPallete_Map1->Rect.bottom) / 2
					);
					mPalleteImage->ScaleRender(
						(mPallete_Map1->Rect.right + mPallete_Map1->Rect.left) / 2,
						(mPallete_Map1->Rect.top + mPallete_Map1->Rect.bottom) / 2,
						mPallete_Map1->Width,
						mPallete_Map1->Height
					);
				}
			/*for (int y = 0; y < PalleteSizeY; y++)
			{
				for (int x = 0; x < PalleteSizeX; x++)
				{

					mPallete[y][x]->Image->ScaleFrameRender
					(
						(mPallete[y][x]->Rect.right + mPallete[y][x]->Rect.left) / 2,
						(mPallete[y][x]->Rect.top + mPallete[y][x]->Rect.bottom) / 2,
						mPallete[y][x]->FrameX,
						mPallete[y][x]->FrameY,
						mPallete[y][x]->Width,
						mPallete[y][x]->Height
					);
					Gizmo::GetInstance()->DrawRect(mPallete[y][x]->Rect, D2D1::ColorF::Red);
				}
			}*/
			/*mPallete2->Image->SetScale(4.0f);
			mPallete2->Image->Render(
				(mPallete2->Rect.right + mPallete2->Rect.left) / 2,
				(mPallete2->Rect.top + mPallete2->Rect.bottom) / 2);
			Gizmo::GetInstance()->DrawRect(mPallete2->Rect, D2D1::ColorF::Red);*/
			}
			else if (mPalletePage == PalletePage::Structures)
			{
				if (mPalletePageX == 0)
				{
					for (int i = 0; i < mPallete_Structure.size(); i++)
					{
						mPallete_Structure[i]->Image->SetScale(0.5f);
						mPallete_Structure[i]->Image->Render
						(
							(mPallete_Structure[i]->Rect.right + mPallete_Structure[i]->Rect.left) / 2,
							(mPallete_Structure[i]->Rect.top + mPallete_Structure[i]->Rect.bottom) / 2
						);
						mPalleteImage->ScaleRender(
							(mPallete_Structure[i]->Rect.right + mPallete_Structure[i]->Rect.left) / 2,
							(mPallete_Structure[i]->Rect.top + mPallete_Structure[i]->Rect.bottom) / 2,
							mPallete_Structure[i]->Width,
							mPallete_Structure[i]->Height
						);
					}
				}
				else if(mPalletePageX == 1)
				{
					for (int i = 0; i < mPallete_Structure2.size(); i++)
					{
						mPallete_Structure2[i]->Image->SetScale(0.5f);
						mPallete_Structure2[i]->Image->Render
						(
							(mPallete_Structure2[i]->Rect.right + mPallete_Structure2[i]->Rect.left) / 2,
							(mPallete_Structure2[i]->Rect.top + mPallete_Structure2[i]->Rect.bottom) / 2
						);
						mPalleteImage->ScaleRender(
							(mPallete_Structure2[i]->Rect.right + mPallete_Structure2[i]->Rect.left) / 2,
							(mPallete_Structure2[i]->Rect.top + mPallete_Structure2[i]->Rect.bottom) / 2,
							mPallete_Structure2[i]->Width,
							mPallete_Structure2[i]->Height
						);
					}
				}
				else if (mPalletePageX == 2)
				{
					for (int i = 0; i < mPallete_Structure3.size(); i++)
					{
						mPallete_Structure3[i]->Image->SetScale(0.5f);
						mPallete_Structure3[i]->Image->Render
						(
							(mPallete_Structure3[i]->Rect.right + mPallete_Structure3[i]->Rect.left) / 2,
							(mPallete_Structure3[i]->Rect.top + mPallete_Structure3[i]->Rect.bottom) / 2
						);
						mPalleteImage->ScaleRender(
							(mPallete_Structure3[i]->Rect.right + mPallete_Structure3[i]->Rect.left) / 2,
							(mPallete_Structure3[i]->Rect.top + mPallete_Structure3[i]->Rect.bottom) / 2,
							mPallete_Structure3[i]->Width,
							mPallete_Structure3[i]->Height
						);
					}
				}
			}
			
		}
	}

	
	
	if (Input::GetInstance()->GetKey(VK_SHIFT))
		if (Input::GetInstance()->GetKey(VK_LBUTTON))
			CameraManager::GetInstance()->GetMainCamera()->RenderRect(mShiftRect, D2D1::ColorF::White);
	
	
	

	if (!mBookIsOpen || (mBookIsOpen && _mousePosition.x < WINSIZEX - 400))
	{
		mCurrentPallete->Image->SetAlpha(0.5f);
		mCurrentPallete->Image->SetScale(1.5f);
		if (mCurrentPallete->Image->GetKey() == L"Tree1"|| mCurrentPallete->Image->GetKey() == L"Tree2")
		{
			mCurrentPallete->Image->FrameRenderFromBottom(_mousePosition.x, _mousePosition.y, mCurrentPallete->FrameX, mCurrentPallete->FrameY);
		}
		else if (mCurrentPallete->Image->GetKey() == L"HouseWall1" || mCurrentPallete->Image->GetKey() == L"HouseWall2" || mCurrentPallete->Image->GetKey() == L"HouseWall3"
			|| mCurrentPallete->Image->GetKey() == L"FireWall1" || mCurrentPallete->Image->GetKey() == L"FireWall2" || mCurrentPallete->Image->GetKey() == L"FireWall3"
			|| mCurrentPallete->Image->GetKey() == L"FireBossMap")
		{
			mCurrentPallete->Image->SetScale(4.5f);
			mCurrentPallete->Image->Render(_mousePosition.x, _mousePosition.y);
		}
		else
			mCurrentPallete->Image->FrameRender(_mousePosition.x, _mousePosition.y, mCurrentPallete->FrameX,mCurrentPallete->FrameY);
		
	}
}

void Scene_MapTool::Save()
{
	ofstream saveStream(L"../04_Datas/Test.txt");
	if (saveStream.is_open())
	{
		string tempImageKey;
		int frameX;
		int frameY;

		for (int y = 0; y < TileCountY; y++)
		{
			for (int x = 0; x < TileCountX; x++)
			{
				string str;
				wstring key = mTileList[y][x]->GetImage()->GetKey();
				str.assign(key.begin(),key.end());

				saveStream << str.c_str();
				saveStream << ',';
				saveStream << (int)(mTileList[y][x]->GetType());
				saveStream << ',';
				saveStream << mTileList[y][x]->GetFrameIndexY();
				saveStream << ',';
				saveStream << mTileList[y][x]->GetFrameIndexX();
				saveStream << endl;
			}
		}
		//스트럭쳐 저장하기
		for (int i = 0; i < mStructureList.size(); i++)
		{
			string str;
			wstring key = mStructureList[i]->GetImage()->GetKey();
			str.assign(key.begin(), key.end());

			int x = mStructureList[i]->GetX() / TileSize;
			int y = mStructureList[i]->GetY() / TileSize;
			saveStream << str.c_str();
			saveStream << ',';
			saveStream << y;
			saveStream << ',';
			saveStream << x;
			saveStream << endl;
		}
	}
	saveStream << '/';
}

void Scene_MapTool::Load()
{
	mStructureList.clear();
	ifstream loadStream(L"../04_Datas/Test.txt");
	if (loadStream.is_open())
	{
		for (int y = 0; y < TileCountY; y++)
		{
			for (int x = 0; x < TileCountX; x++)
			{
				string tempstr;
				string key;
				int IndexX = 0;
				int IndexY = 0;
				int typenum = 0;

				getline(loadStream, tempstr);

				int tempint = 0;
				int n = 0;
				for (int i = 0; i < tempstr.length(); i++)
				{
					if (tempstr[i] == ',' && n == 0)
					{
						int t = i - tempint;
						key = tempstr.substr(tempint, t);
						tempint = i + 1;
						n++;
					}
					else if (tempstr[i] == ',' && n == 1)
					{
						int t = i - tempint;
						typenum = stoi(tempstr.substr(tempint, t));
						tempint = i + 1;
						n++;
					}
					else if (tempstr[i] == ',' && n == 2)
					{
						int t = i - tempint+1;
						IndexY = stoi(tempstr.substr(tempint, t));
						tempint = i + 1;
						n++;
					}
					else if ( i == tempstr.length()-1 && n == 3)
					{
						int t = i - tempint+2;
						IndexX = stoi(tempstr.substr(tempint, t));

					}
				}
				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mTileList[y][x]->SetType((Type)typenum);
				mTileList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mTileList[y][x]->SetFrameIndexX(IndexX);
				mTileList[y][x]->SetFrameIndexY(IndexY);
			}
		}
		//스트럭쳐 불러오기
		while (true)
		{
			string tempstr;
			string key;
			int IndexX = 0;
			int IndexY = 0;
			getline(loadStream, tempstr);
			if (tempstr == "/")
			{
				return;
			}
			int tempint = 0;
			int n = 0;
			for (int i = 0; i < tempstr.length(); i++)
			{
				if (tempstr[i] == ',' && n == 0)
				{
					int t = i - tempint;
					key = tempstr.substr(tempint, t);
					tempint = i + 1;
					n++;
				}
				else if (tempstr[i] == ',' && n == 1)
				{
					int t = i - tempint + 1;
					IndexY = stoi(tempstr.substr(tempint, t));
					tempint = i + 1;
					n++;
				}
				else if (i == tempstr.length() - 1 && n == 2)
				{
					int t = i - tempint + 2;
					IndexX = stoi(tempstr.substr(tempint, t));

				}
			}
			wstring wstr;
			wstr.assign(key.begin(), key.end());
			Structure* st = new Structure
			(
				key,
				ImageManager::GetInstance()->FindImage(wstr),
				(float)IndexX*TileSize + TileSize / 2,
				(float)IndexY*TileSize + TileSize / 2,
				ImageManager::GetInstance()->FindImage(wstr)->GetWidth(),
				ImageManager::GetInstance()->FindImage(wstr)->GetHeight()
			);
			mStructureList.push_back(st);
		}
	}
	
}

void Scene_MapTool::PushCommand(ICommand* command)
{
	command->Excute();
	mRedoCommandList.emplace(command);
}

void Scene_MapTool::Undo()
{
	if (mUndoCommandList.size() == 0)
		return;

	mRedoCommandList.emplace(mUndoCommandList.top());
	mUndoCommandList.top()->Excute();
	mUndoCommandList.pop();
}

void Scene_MapTool::Redo()
{
	if (mRedoCommandList.size() == 0)
		return;

	mUndoCommandList.emplace(mRedoCommandList.top());
	mRedoCommandList.top()->Redo();
	mRedoCommandList.pop();
}
