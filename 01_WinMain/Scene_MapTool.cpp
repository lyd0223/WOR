#include "pch.h"
#include "TilePallete.h"
#include "Scene_MapTool.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "ICommand.h"
#include "Gizmo.h"
#include "Button.h"

#include <fstream>

void Scene_MapTool::Init()
{
	mClickType = ClickType::TileSetClick;
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	ImageManager::GetInstance()->LoadFromFile(L"Set", Resources(L"Tile/Set.bmp"));
	mBackGroundImage = ImageManager::GetInstance()->FindImage(L"Set");
	Image* tileImage2 = ImageManager::GetInstance()->FindImage(L"TutorialTile");
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TileSet");

	mPalleteDownButton = new Button("PalleteDown", 1130, 700, 30, 30);
	mPalleteUpButton = new Button("PalleteUpButton", 1130, 115, 30, 30);
	mPalleteLeftButton = new Button("PalleteLeftButton", 990, 400, 30, 30);
	mPalleteRihgtButton = new Button("PalleteRihgtButton", 1270, 400, 30, 30);

	mPalletePageX = 0; 
	mPalletePageY = 0;

	//타일 만들기
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			mTileList[y][x] = new Tile
			(
				tileImage,
				TileSize *x, TileSize*y, 
				TileSize, TileSize,
				0,0
			);
		}
	}

	//빠레트만들기
	int palleteStartX = WINSIZEX - 275;
	int palleteStartY = 130;
	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{
			mPallete[y][x] = new TilePallete();
			mPallete[y][x]->Image = tileImage;
			mPallete[y][x]->PositionX = palleteStartX + TileSize/2 * x;
			mPallete[y][x]->PositionY = palleteStartY + TileSize/2 * y;
			mPallete[y][x]->Width = TileSize/2;
			mPallete[y][x]->Height = TileSize/2;
			mPallete[y][x]->Rect = RectMake(mPallete[y][x]->PositionX, mPallete[y][x]->PositionY, mPallete[y][x]->Width, mPallete[y][x]->Height);
			mPallete[y][x]->FrameX = x;
			mPallete[y][x]->FrameY = y;
			
		}
	}
	//튜토리얼 파레트
	mPallete2 = new TilePallete();
	mPallete2->Image = tileImage2;
	mPallete2->PositionX = palleteStartX;
	mPallete2->PositionY = palleteStartY + 300;
	mPallete2->Width = TileSize * 4;
	mPallete2->Height = TileSize * 2;
	mPallete2->Rect = RectMake(mPallete2->PositionX, mPallete2->PositionY, mPallete2->Width, mPallete2->Height);
	
	mSaveButton = new Button("SaveButton", WINSIZEX - 150, 25, 100, 50);
	mLoadButton = new Button("LoadButton", WINSIZEX - 150, 75, 100, 50); 
	mRedoButton = new Button("RedoButton", WINSIZEX - 50, 25, 100, 50); 
	mUndoButton = new Button("UndoButton", WINSIZEX - 50, 75, 100, 50); 
	mGameStartButton = new Button("GameStartButton", WINSIZEX - 250,50, 100, 100); 
	mCurrentPallete = mPallete[0][0];

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
	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{
			SafeDelete(mPallete[y][x]);
		}
	}
}

void Scene_MapTool::Update()
{
	if (Input::GetInstance()->GetKeyDown('0')) mClickType = ClickType::FloorTypeSetClick;
	if (Input::GetInstance()->GetKeyDown('1')) mClickType = ClickType::WallTypeSetClick;
	if (Input::GetInstance()->GetKeyDown('2')) mClickType = ClickType::CliffTypeSetClick;
	if (Input::GetInstance()->GetKeyDown('3')) mClickType = ClickType::ThornTypeSetClick;
	if (Input::GetInstance()->GetKeyDown('4')) mClickType = ClickType::TileSetClick;

	CameraManager::GetInstance()->GetMainCamera()->Update();
	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{

		for (int y = 0; y < PalleteSizeY; y++)
		{
			for (int x = 0; x < PalleteSizeX; x++)
			{
				if (PtInRect(&mPallete[y][x]->Rect, _mousePosition))
				{
					mCurrentPallete = mPallete[y][x];
				}
			}
		}
		//튜토리얼파레트
		if (PtInRect(&mPallete2->Rect, _mousePosition))
		{
			mCurrentPallete = mPallete2;
		}

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
		rctemp = mGameStartButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			SceneManager::GetInstance()->LoadScene(L"Tutorial");
			return;
		}
		rctemp = mRedoButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
			Redo();
		rctemp = mUndoButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
			Undo();
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
		rctemp = mPalleteUpButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			mPalletePageY--;
		}
		rctemp = mPalleteDownButton->GetRect();
		if (PtInRect(&rctemp, _mousePosition))
		{
			mPalletePageY++;
		}
	}
	
	//타일 바꾸기
	
		if (Input::GetInstance()->GetKey(VK_LBUTTON))
		{
			if (mClickType == ClickType::TileSetClick)
			{
				//튜토리얼빠레트일때
				
				if (mCurrentPallete->Image->GetKey() == L"TutorialTile")
				{
					if (_mousePosition.x < WINSIZEX - 300)
					{
						for (int y = 0; y < 43; y++)
						{
							for (int x = 0; x < 74; x++)
							{
								mTileList[y][x]->SetImage(mCurrentPallete->Image);
							}
						}
						for (int y = 0; y < 43; y++)
						{
							for (int x = 0; x < 74; x++)
							{
								
								mTileList[y][x]->SetFrameIndexY(y);
								mTileList[y][x]->SetFrameIndexX(x);
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
							if (_mousePosition.x < WINSIZEX - 300 &&
								PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + 150 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }))
							{
								//빠레트와 목표 타일이 다를때.
								if (mTileList[y][x]->GetImage() != mCurrentPallete->GetImage() ||
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
						if (_mousePosition.x < WINSIZEX - 300 &&
							PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + 150 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }))
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
	

	
	int palleteStartX = WINSIZEX - 275;
	int palleteStartY = 130;

	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{

			mPallete[y][x]->PositionX = palleteStartX + TileSize/2 * x;
			mPallete[y][x]->PositionY = palleteStartY + TileSize/2 * y;
			mPallete[y][x]->Width = TileSize/2;
			mPallete[y][x]->Height = TileSize/2;
			mPallete[y][x]->Rect = RectMake(mPallete[y][x]->PositionX, mPallete[y][x]->PositionY, mPallete[y][x]->Width, mPallete[y][x]->Height);
			mPallete[y][x]->FrameX = x + mPalletePageX;
			mPallete[y][x]->FrameY = y + mPalletePageY;

		}
	}
}

void Scene_MapTool::Render()
{
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				mTileList[y][x]->Render();
				CameraManager::GetInstance()->GetMainCamera()->RenderText
				(
					mTileList[y][x]->GetX() + 5, mTileList[y][x]->GetY() + 5,
					to_wstring(y) + L"," + to_wstring(x), 10
				);
				CameraManager::GetInstance()->GetMainCamera()->RenderText
				(
					mTileList[y][x]->GetX() + 5, mTileList[y][x]->GetY() + 15,
					to_wstring((int)mTileList[y][x]->GetType()) ,10
				);
				
			}
			
		}
	}
	
	mBackGroundImage->ScaleRender(WINSIZEX - 150, WINSIZEY/2,300,WINSIZEY);
	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{
			
			mPallete[y][x]->Image->ScaleFrameRender
			(
				(mPallete[y][x]->Rect.right + mPallete[y][x]->Rect.left)/2 ,
				(mPallete[y][x]->Rect.top + mPallete[y][x]->Rect.bottom)/2,
				mPallete[y][x]->FrameX,
				mPallete[y][x]->FrameY,
				mPallete[y][x]->Width, 
				mPallete[y][x]->Height

			);
			Gizmo::GetInstance()->DrawRect(mPallete[y][x]->Rect, D2D1::ColorF::Red);
		}
	}
	mPallete2->Image->SetScale(4.0f);
	mPallete2->Image->Render(
		(mPallete2->Rect.right + mPallete2->Rect.left) / 2,
		(mPallete2->Rect.top + mPallete2->Rect.bottom) / 2);
	Gizmo::GetInstance()->DrawRect(mPallete2->Rect, D2D1::ColorF::Red);
	
	mPalleteDownButton->Render();
	mPalleteUpButton->Render();
	mPalleteLeftButton->Render();
	mPalleteRihgtButton->Render();
	mSaveButton->Render();
	mLoadButton->Render();
	mGameStartButton->Render();
	mRedoButton->Render();
	mUndoButton->Render();
	


	if (_mousePosition.x < WINSIZEX - 300)
	{
		mCurrentPallete->Image->SetAlpha(0.5f);
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
	}
}

void Scene_MapTool::Load()
{
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
