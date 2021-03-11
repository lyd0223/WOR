#include "pch.h"
#include "TilePallete.h"
#include "Scene_MapTool.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "ICommand.h"
#include "Gizmo.h"
#include <fstream>

void Scene_MapTool::Init()
{
	
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 512, 512, 16, 16, false);
	ImageManager::GetInstance()->LoadFromFile(L"Set", Resources(L"Tile/Set.bmp"), 300, 720, false);
	mBackGroundImage = IMAGEMANAGER->FindImage(L"Set");
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TileSet");

	mPalleteDownButton = RectMakeCenter(1130,700,30,30);
	mPalleteUpButton = RectMakeCenter(1130,115,30,30);
	mPalleteLeftButton = RectMakeCenter(990,400,30,30);
	mPalleteRihgtButton = RectMakeCenter(1270,400,30,30);

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
			mPallete[y][x]->PositionX = palleteStartX + TileSize * x;
			mPallete[y][x]->PositionY = palleteStartY + TileSize * y;
			mPallete[y][x]->Width = TileSize;
			mPallete[y][x]->Height = TileSize;
			mPallete[y][x]->Rect = RectMake(mPallete[y][x]->PositionX, mPallete[y][x]->PositionY, mPallete[y][x]->Width, mPallete[y][x]->Height);
			mPallete[y][x]->FrameX = x;
			mPallete[y][x]->FrameY = y;
			
		}
	}
	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{
			mPallete[y][x] = new TilePallete();
			mPallete[y][x]->Image = tileImage;
			mPallete[y][x]->PositionX = palleteStartX + TileSize * x;
			mPallete[y][x]->PositionY = palleteStartY + TileSize * y;
			mPallete[y][x]->Width = TileSize;
			mPallete[y][x]->Height = TileSize;
			mPallete[y][x]->Rect = RectMake(mPallete[y][x]->PositionX, mPallete[y][x]->PositionY, mPallete[y][x]->Width, mPallete[y][x]->Height);
			mPallete[y][x]->FrameX = x;
			mPallete[y][x]->FrameY = y;

		}
	}
	mSaveButton = RectMake(WINSIZEX-200,0,100,50);
	mLoadButton = RectMake(WINSIZEX-200,50,100,50);
	mRedoButton = RectMake(WINSIZEX - 100, 0, 100, 50);
	mUndoButton = RectMake(WINSIZEX - 100, 50, 100, 50);
	mGameStartButton = RectMake(WINSIZEX - 300, 0, 100, 100);
	mCurrentPallete = mPallete[0][0];

	Camera* camera = new Camera();
	camera->ChangeMode(Camera::Mode::Free);
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
	CameraManager::GetInstance()->GetMainCamera()->Update();
	if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		int i = 0;
	}
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
		if (PtInRect(&mLoadButton, _mousePosition))
		{
			Load();
		}
		else if (PtInRect(&mSaveButton, _mousePosition))
		{
			Save();
		}
		else if (PtInRect(&mGameStartButton, _mousePosition))
		{
			SceneManager::GetInstance()->LoadScene(L"Scene_Game");
			return;
		}
		else if (PtInRect(&mRedoButton, _mousePosition))
			Redo();
		else if (PtInRect(&mUndoButton, _mousePosition))
			Undo();

		else if (PtInRect(&mPalleteRihgtButton, _mousePosition))
		{
			mPalletePageX++;
		}
		else if (PtInRect(&mPalleteLeftButton, _mousePosition))
		{
			mPalletePageX--;
		}
		if (PtInRect(&mPalleteUpButton, _mousePosition))
		{
			mPalletePageY--;
		}
		if (PtInRect(&mPalleteDownButton, _mousePosition))
		{
			mPalletePageY++;
		}
	}
	

	if (Input::GetInstance()->GetKey(VK_LBUTTON))
	{
		
		for (int y = 0; y < TileCountY; y++)
		{
			for (int x = 0; x < TileCountX; x++)
			{
				Camera* camera = CameraManager::GetInstance()->GetMainCamera();

				RECT rctemp = mTileList[y][x]->GetRect();
				//마우스가 목표타일안에있을때.
				if ( _mousePosition.x < WINSIZEX-300 &&					 
					PtInRect(&rctemp, { _mousePosition.x - WINSIZEX/2+150 + (LONG)camera->GetX() , _mousePosition.y -WINSIZEY/2+ (LONG)camera->GetY()}))						   	
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

	
	int palleteStartX = WINSIZEX - 275;
	int palleteStartY = 130;

	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{

			mPallete[y][x]->PositionX = palleteStartX + TileSize * x;
			mPallete[y][x]->PositionY = palleteStartY + TileSize * y;
			mPallete[y][x]->Width = TileSize;
			mPallete[y][x]->Height = TileSize;
			mPallete[y][x]->Rect = RectMake(mPallete[y][x]->PositionX, mPallete[y][x]->PositionY, mPallete[y][x]->Width, mPallete[y][x]->Height);
			mPallete[y][x]->FrameX = x + mPalletePageX;
			mPallete[y][x]->FrameY = y + mPalletePageY;

		}
	}
}

void Scene_MapTool::Render(HDC hdc)
{
	RECT cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			RECT tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				mTileList[y][x]->Render(hdc);
			}
		}
	}
	
	mBackGroundImage->Render(hdc, WINSIZEX - 300, 0);
	for (int y = 0; y < PalleteSizeY; y++)
	{
		for (int x = 0; x < PalleteSizeX; x++)
		{
			
			mPallete[y][x]->Image->ScaleFrameRender
			(
				hdc,
				mPallete[y][x]->Rect.left, 
				mPallete[y][x]->Rect.top, 
				mPallete[y][x]->FrameX,
				mPallete[y][x]->FrameY,
				mPallete[y][x]->Width, 
				mPallete[y][x]->Height

			);
			Gizmo::GetInstance()->DrawRect(hdc, mPallete[y][x]->Rect, Gizmo::Color::Red);
		}
	}
	RenderRect(hdc, mPalleteDownButton);
	RenderRect(hdc, mPalleteUpButton);
	RenderRect(hdc, mPalleteLeftButton);
	RenderRect(hdc, mPalleteRihgtButton);
	RenderRect(hdc, mSaveButton);
	wstring saveStr = L"Save";
	TextOut(hdc, mSaveButton.left, mSaveButton.top, saveStr.c_str(), saveStr.length());
	RenderRect(hdc, mLoadButton);
	wstring saveStr2 = L"Load";
	TextOut(hdc, mLoadButton.left, mLoadButton.top, saveStr2.c_str(), saveStr2.length());
	RenderRect(hdc, mGameStartButton);
	wstring saveStr3 = L"Start";
	TextOut(hdc, mGameStartButton.left, mGameStartButton.top, saveStr3.c_str(), saveStr3.length());
	RenderRect(hdc, mRedoButton);
	wstring saveStr4 = L"Redo";
	TextOut(hdc, mRedoButton.left, mRedoButton.top, saveStr4.c_str(), saveStr4.length());
	RenderRect(hdc, mUndoButton);
	wstring saveStr5 = L"Undo";
	TextOut(hdc, mUndoButton.left, mUndoButton.top, saveStr5.c_str(), saveStr5.length());

	TextOut(hdc, 50, 50, to_wstring(_mousePosition.x).c_str(), to_wstring(_mousePosition.x).length());
	TextOut(hdc, 50, 70, to_wstring(_mousePosition.y).c_str(), to_wstring(_mousePosition.x).length());

	if(_mousePosition.x < WINSIZEX-300)
		mCurrentPallete->Image->AlphaFrameRender(hdc, _mousePosition.x -TileSize/2, _mousePosition.y -TileSize/2, mCurrentPallete->FrameX,mCurrentPallete->FrameY,0.1f);
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
				wstring key = mTileList[y][x]->GetImage()->GetKeyName();
				str.assign(key.begin(),key.end());

				saveStream << str.c_str();
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
						IndexY = stoi(tempstr.substr(tempint, t));
						tempint = i + 1;
						n++;
					}
					else if ( i == tempstr.length()-1 && n == 2)
					{
						int t = i - tempint+1;
						IndexX = stoi(tempstr.substr(tempint, t));

					}
				}
				wstring wstr;
				wstr.assign(key.begin(), key.end());
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
