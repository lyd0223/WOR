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
	//Struct
	ImageManager::GetInstance()->LoadFromFile(L"Tree1", Resources(L"Tile/Structure/Tree1.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Tree2", Resources(L"Tile/Structure/Tree2.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Flag", Resources(L"Tile/Structure/Flag.png"));

	mBackGroundImage = ImageManager::GetInstance()->FindImage(L"Set");
	Image* tileImage2 = ImageManager::GetInstance()->FindImage(L"TutorialTile");
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TileSet");

	

	//Ÿ�� �����
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
	mPalleteMainButton = new Button("Main", 1010, 200, 50, 50);
	mPalleteLeftButton = new Button("Left", 1200, 200, 50, 50);
	mPalleteRihgtButton = new Button("Rihgt", 1250, 200, 50, 50);

	mPalleteFloorButton = new Button("Floors", 1130, 300, 100, 50);
	mPalleteWallButton = new Button("Walls", 1130, 350, 100, 50);
	mPalleteCliffButton = new Button("Cliffs", 1130, 400, 100, 50);
	mPalleteThornButton = new Button("Thorns", 1130, 450, 100, 50);
	mPalleteStructureButton = new Button("Structures", 1130, 500, 100, 50);
	mPalleteMapButton = new Button("Map", 1130, 550, 100, 50);

	//����Ʈ�����
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
	//Structure
	mPallete_Structure1 = new TilePallete();
	mPallete_Structure1->Image = ImageManager::GetInstance()->FindImage(L"Tree1");
	mPallete_Structure1->PositionX = WINSIZEX - 300;
	mPallete_Structure1->PositionY = 230;
	mPallete_Structure1->Width = TileSize * 3 / 2;
	mPallete_Structure1->Height = TileSize * 4 / 2;
	mPallete_Structure1->Rect = RectMake(mPallete_Structure1->PositionX, mPallete_Structure1->PositionY, mPallete_Structure1->Width, mPallete_Structure1->Height);
	mPallete_Structure2 = new TilePallete();
	mPallete_Structure2->Image = ImageManager::GetInstance()->FindImage(L"Tree2");
	mPallete_Structure2->PositionX = WINSIZEX - 200;
	mPallete_Structure2->PositionY = 230;
	mPallete_Structure2->Width = TileSize * 3 / 2;
	mPallete_Structure2->Height = TileSize * 4 / 2;
	mPallete_Structure2->Rect = RectMake(mPallete_Structure2->PositionX, mPallete_Structure2->PositionY, mPallete_Structure2->Width, mPallete_Structure2->Height);
	mPallete_Structure3 = new TilePallete();
	mPallete_Structure3->Image = ImageManager::GetInstance()->FindImage(L"Flag");
	mPallete_Structure3->PositionX = WINSIZEX - 100;
	mPallete_Structure3->PositionY = 230;
	mPallete_Structure3->Width = TileSize * 3 / 2;
	mPallete_Structure3->Height = TileSize * 4 / 2;
	mPallete_Structure3->Rect = RectMake(mPallete_Structure3->PositionX, mPallete_Structure3->PositionY, mPallete_Structure3->Width, mPallete_Structure3->Height);
	/*mPallete_Structure4 = new TilePallete();
	mPallete_Structure4->Image = ImageManager::GetInstance()->FindImage(L"Tree1");
	mPallete_Structure4->PositionX = WINSIZEX - 300;
	mPallete_Structure4->PositionY = 300;
	mPallete_Structure4->Width = TileSize * 3 / 2;
	mPallete_Structure4->Height = TileSize * 4 / 2;
	mPallete_Structure4->Rect = RectMake(mPallete_Structure4->PositionX, mPallete_Structure4->PositionY, mPallete_Structure4->Width, mPallete_Structure4->Height);*/
	//Ʃ�丮�� �ķ�Ʈ
	mPallete2 = new TilePallete();
	mPallete2->Image = tileImage2;
	mPallete2->PositionX = palleteStartX;
	mPallete2->PositionY = palleteStartY + 300;
	mPallete2->Width = TileSize * 4;
	mPallete2->Height = TileSize * 2;
	mPallete2->Rect = RectMake(mPallete2->PositionX, mPallete2->PositionY, mPallete2->Width, mPallete2->Height);
	//
	

	//��ư
	

	mPalletePageX = 0;
	mPalletePageY = 0;

	mSaveButton = new Button("SaveButton", WINSIZEX - 150, 25, 100, 50);
	mLoadButton = new Button("LoadButton", WINSIZEX - 150, 75, 100, 50); 
	mRedoButton = new Button("RedoButton", WINSIZEX - 50, 25, 100, 50); 
	mUndoButton = new Button("UndoButton", WINSIZEX - 50, 75, 100, 50); 
	mGameStartButton = new Button("GameStartButton", WINSIZEX - 250,50, 100, 100); 
	mCurrentPallete = mPallete[0][0];
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

	
	//����Ʈ����������
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
		//tile type ����
		if (Input::GetInstance()->GetKeyDown('0')) mClickType = ClickType::FloorTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('1')) mClickType = ClickType::WallTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('2')) mClickType = ClickType::CliffTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('3')) mClickType = ClickType::ThornTypeSetClick;
		if (Input::GetInstance()->GetKeyDown('4')) mClickType = ClickType::TileSetClick;
		
		rctemp = mPalleteMainButton->GetRect();
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&rctemp, _mousePosition))
				mPalletePage = PalletePage::Main;
		}
		if (mPalletePage == PalletePage::Floors)
		{

		}
		if (mPalletePage == PalletePage::Walls)
		{

		}
		if (mPalletePage == PalletePage::Cliffs)
		{

		}
		if (mPalletePage == PalletePage::Thorns)
		{

		}
		if (mPalletePage == PalletePage::Structures)
		{
			
			
		}
		if (mPalletePage == PalletePage::Maps)
		{
			if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				rctemp = mPallete_Structure1->Rect;
				if (PtInRect(&rctemp, _mousePosition))
				{
					mCurrentPallete = mPallete_Structure1;
				}
			}
		}

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
		//Ʃ�丮���ķ�Ʈ
		if (PtInRect(&mPallete2->Rect, _mousePosition))
		{
			mCurrentPallete = mPallete2;
		}
		//
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
	}
	
	//Ÿ�� �ٲٱ�
	
	if (Input::GetInstance()->GetKey(VK_LBUTTON))
	{
		if (mClickType == ClickType::TileSetClick)
		{
			//Ʃ�丮�����Ʈ�϶�

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
						//���콺�� ��ǥŸ�Ͼȿ�������.
						if (_mousePosition.x < WINSIZEX - 300 &&
							PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + 150 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }))
						{
							//����Ʈ�� ��ǥ Ÿ���� �ٸ���.
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
					//���콺�� ��ǥŸ�Ͼȿ�������.
					if (_mousePosition.x < WINSIZEX - 300 &&
						PtInRect(&rctemp, { _mousePosition.x - WINSIZEX / 2 + 150 + (LONG)camera->GetX() , _mousePosition.y - WINSIZEY / 2 + (LONG)camera->GetY() }))
					{
						//Ÿ�� �������ֱ�.
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

	//Ÿ�ϱ׸��ºκ�
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			D2D1_RECT_F tileRect = mTileList[y][x]->GetRect();
			if (cameraRect.right > tileRect.left && cameraRect.left < tileRect.right && cameraRect.bottom > tileRect.top && cameraRect.top < tileRect.bottom)
			{
				mTileList[y][x]->Render();
				CameraManager::GetInstance()->GetMainCamera()->RenderGizmoRect(mTileList[y][x]->GetRect());
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

	//����Ʈ�׸��ºκ�
	mBackGroundImage->ScaleRender(WINSIZEX - 150, WINSIZEY/2,300,WINSIZEY);
	mSaveButton->Render();
	mLoadButton->Render();
	mGameStartButton->Render();
	mRedoButton->Render();
	mUndoButton->Render();
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
		if (mPalletePage == PalletePage::Floors)
		{

		}
		else if (mPalletePage == PalletePage::Walls)
		{

		}
		else if (mPalletePage == PalletePage::Cliffs)
		{

		}
		else if (mPalletePage == PalletePage::Structures)
		{
			mPallete_Structure1->Image->ScaleRender
			(
				(mPallete_Structure1->Rect.right + mPallete_Structure1->Rect.left)/2 ,
				(mPallete_Structure1->Rect.top + mPallete_Structure1->Rect.bottom)/2 ,
				mPallete_Structure1->Width,
				mPallete_Structure1->Height
			);
			Gizmo::GetInstance()->DrawRect(mPallete_Structure1->Rect, D2D1::ColorF::Red);
			mPallete_Structure2->Image->ScaleRender
			(
				(mPallete_Structure2->Rect.right + mPallete_Structure2->Rect.left)/2,
				(mPallete_Structure2->Rect.top + mPallete_Structure2->Rect.bottom)/2,
				mPallete_Structure2->Width,
				mPallete_Structure2->Height
			);
			Gizmo::GetInstance()->DrawRect(mPallete_Structure2->Rect, D2D1::ColorF::Red);
			mPallete_Structure3->Image->ScaleRender
			(
				(mPallete_Structure3->Rect.right + mPallete_Structure3->Rect.left) / 2,
				(mPallete_Structure3->Rect.top + mPallete_Structure3->Rect.bottom) / 2,
				mPallete_Structure2->Width,
				mPallete_Structure2->Height
			);
			Gizmo::GetInstance()->DrawRect(mPallete_Structure3->Rect,D2D1::ColorF::Red);
			
		}
		else if (mPalletePage == PalletePage::Maps)
		{
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
			mPallete2->Image->SetScale(4.0f);
			mPallete2->Image->Render(
				(mPallete2->Rect.right + mPallete2->Rect.left) / 2,
				(mPallete2->Rect.top + mPallete2->Rect.bottom) / 2);
			Gizmo::GetInstance()->DrawRect(mPallete2->Rect, D2D1::ColorF::Red);
		}
	}

	
	
	
	
	


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
