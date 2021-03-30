#include "pch.h"
#include "Load_Image.h"

void Load_Image::LoadSceneHouseImage()
{
}

void Load_Image::LoadSceneMapToolImage()
{

	

	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	ImageManager::GetInstance()->LoadFromFile(L"Set", Resources(L"Tile/Set.bmp"));
	ImageManager::GetInstance()->LoadFromFile(L"Page", Resources(L"Tile/Page.png"));
	ImageManager::GetInstance()->LoadFromFile(L"MainPage", Resources(L"Tile/MainPage.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Pallete", Resources(L"Tile/Pallete.png"));

	//¹öÆ°ÀÌ¹ÌÁö
	ImageManager::GetInstance()->LoadFromFile(L"F", Resources(L"UI/F.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Save", Resources(L"Tile/Button/Save.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Load", Resources(L"Tile/Button/Load.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Redo", Resources(L"Tile/Button/Redo.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Undo", Resources(L"Tile/Button/Undo.png"));
	ImageManager::GetInstance()->LoadFromFile(L"TitleButton", Resources(L"Tile/Button/Title.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Back", Resources(L"Tile/Button/Back.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Left", Resources(L"Tile/Button/Left.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Right", Resources(L"Tile/Button/Right.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Floors", Resources(L"Tile/Button/Floors.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Walls", Resources(L"Tile/Button/Walls.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Cliffs", Resources(L"Tile/Button/Cliffs.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Thorns", Resources(L"Tile/Button/Thorns.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Maps", Resources(L"Tile/Button/Maps.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Structures", Resources(L"Tile/Button/Structures.png"));

	//Floors
	ImageManager::GetInstance()->LoadFromFile(L"FireFloor", Resources(L"Tile/Floor/Fire_Floor.png"), 8, 2);
	ImageManager::GetInstance()->LoadFromFile(L"HouseFloor", Resources(L"Tile/Floor/House_Floor.png"), 8, 5);
	//Walls
	ImageManager::GetInstance()->LoadFromFile(L"Fire4Walls", Resources(L"Tile/Wall/Fire_4Walls.png"), 2, 2);
	ImageManager::GetInstance()->LoadFromFile(L"Fire8Walls", Resources(L"Tile/Wall/Fire_8Walls.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"House4Walls", Resources(L"Tile/Wall/House_4Walls.png"), 2, 2);
	ImageManager::GetInstance()->LoadFromFile(L"House8Walls", Resources(L"Tile/Wall/House_8Walls.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"FireWall1", Resources(L"Tile/Wall/Fire_Wall1.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"FireWall2", Resources(L"Tile/Wall/Fire_Wall2.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"FireWall3", Resources(L"Tile/Wall/Fire_Wall3.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"HouseWall1", Resources(L"Tile/Wall/House_Wall1.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"HouseWall2", Resources(L"Tile/Wall/House_Wall2.png"), 3, 3);
	ImageManager::GetInstance()->LoadFromFile(L"HouseWall3", Resources(L"Tile/Wall/House_Wall3.png"), 3, 3);

	//Cliffs

	//Thorns

	//Maps
	ImageManager::GetInstance()->LoadFromFile(L"FireBossMap", Resources(L"Tile/Floor/Tile_Tutorial_FireTile.png"),16,12);
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);

	//Structs
	ImageManager::GetInstance()->LoadFromFile(L"Tree1", Resources(L"Tile/Structure/Tree1.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Tree2", Resources(L"Tile/Structure/Tree2.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Flag", Resources(L"Tile/Structure/Flag.png"));
	ImageManager::GetInstance()->LoadFromFile(L"BookShelf", Resources(L"Tile/Structure/BookShelf.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Bed", Resources(L"Tile/Structure/Bed.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Chair", Resources(L"Tile/Structure/Chair.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Book1", Resources(L"Tile/Structure/Book1.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Book2", Resources(L"Tile/Structure/Book2.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Book3", Resources(L"Tile/Structure/Book3.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Book4", Resources(L"Tile/Structure/Book4.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Book5", Resources(L"Tile/Structure/Book5.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SmallTable", Resources(L"Tile/Structure/SmallTable.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Table", Resources(L"Tile/Structure/Table.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Gate", Resources(L"Tile/Structure/Gate.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Penta", Resources(L"Tile/Structure/Penta.png"));
	ImageManager::GetInstance()->LoadFromFile(L"HorizonalPrison", Resources(L"Tile/Structure/HorizonalPrison.png"));
	ImageManager::GetInstance()->LoadFromFile(L"VerticalPrison", Resources(L"Tile/Structure/VerticalPrison.png"));

	ImageManager::GetInstance()->LoadFromFile(L"Portal", Resources(L"Tile/Structure/Portal.png"));
	ImageManager::GetInstance()->LoadFromFile(L"PortalOn", Resources(L"Tile/Structure/PortalOn.png"));
	ImageManager::GetInstance()->LoadFromFile(L"PortalEffect", Resources(L"Tile/Structure/PortalEffect.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Carpet1", Resources(L"Tile/Structure/Carpet.png"));
	//ImageManager::GetInstance()->LoadFromFile(L"Carpet2", Resources(L"Tile/Structure/Carpet2.png"));

	ImageManager::GetInstance()->LoadFromFile(L"Mirror", Resources(L"Tile/Structure/Mirror.png"));
	ImageManager::GetInstance()->LoadFromFile(L"ScareCrow", Resources(L"Tile/Structure/ScareCrow.png"));
	ImageManager::GetInstance()->LoadFromFile(L"PaperDebris", Resources(L"Tile/Structure/PaperDebris.png"));

	//Æ÷Å»ÀÌÆåÆ®
	ImageManager::GetInstance()->LoadFromFile(L"TeleportEffect", Resources(L"Tile/Structure/PortalEffect.png"),7,1);
}

void Load_Image::LoadSceneTutorialImage()
{
}
