#include "pch.h"
#include "Scene_House.h"
#include "Image.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "TileMap.h"
#include "Gizmo.h"
#include "Load_Image.h"
#include "Structure.h"
#include "UserInterface.h"
#include "SkillBook.h"
#include "Effect_Teleport.h"
void Scene_House::Init()
{
	SoundPlayer::GetInstance()->Play(L"PlayerRoom", 1.f);
	Load_Image::GetInstance()->LoadSceneMapToolImage();
	ImageManager::GetInstance()->LoadFromFile(L"SkillBook", Resources(L"Tile/Structure/SkillBook.png"), 14, 2);
	ImageManager::GetInstance()->LoadFromFile(L"TutorialTile", Resources(L"Tile/TutorialMap.png"), 74, 43);
	ImageManager::GetInstance()->LoadFromFile(L"TileSet", Resources(L"Tile/Tile.bmp"), 16, 16);
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"TutorialTile");

	UserInterface* ui = new UserInterface();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	//타일맵추가

	mTileMap = new TileMap("House");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mTileMap);
	//
	//스트럭쳐 받아오기
	mStructureList = mTileMap->GetStructureList();
	for (int i = 0; i < mStructureList.size(); i++)
	{
		if(mStructureList[i]->GetName() == "Portal" || mStructureList[i]->GetName() == "Penta")
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mStructureList[i]);
		else
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Structure, mStructureList[i]);
	}
	mPortal = (Structure*)ObjectManager::GetInstance()->FindObject("Portal");
	//

	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player") != nullptr)
	{
		mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
		mPlayer->SetX(55 * TileSize + TileSize / 2);
		mPlayer->SetY(58 * TileSize + TileSize / 2);
	}
	else
		mPlayer = new Player("Player", 55*TileSize+TileSize/2, 58*TileSize +TileSize/2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);
	
	SkillBook* skillbook = new SkillBook(77 * TileSize - TileSize/2, 51 * TileSize);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, skillbook);

	ObjectManager::GetInstance()->Init();

	Camera* camera = new Camera();

	camera->Init();
	camera->ChangeMode(Camera::Mode::Follow);
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);

	Effect_Teleport* teleport = new Effect_Teleport(mPlayer->GetX(), mPlayer->GetY()+50, false);

}

void Scene_House::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene_House::Update()
{
	CameraManager::GetInstance()->Update();
	SkillManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();

	
	if (mPortal->GetPortalOn())
	{
		
		if (Input::GetInstance()->GetKeyDown('F'))
		{
			Effect_Teleport* teleport = new Effect_Teleport(mPortal->GetX(),mPortal->GetY(),true,L"House",L"FieldLoading");
			SoundPlayer::GetInstance()->Stop(L"PlayerRoom");
			return;
		}
	}
	
}

void Scene_House::Render()
{
	ObjectManager::GetInstance()->Render();

	if (mPortal->GetPortalOn())
	{
		Image* image = ImageManager::GetInstance()->FindImage(L"F");
		image->SetScale(2.0f);
		CameraManager::GetInstance()->GetMainCamera()->Render(image, mPlayer->GetX(), mPlayer->GetY() - 90);
	}
}
