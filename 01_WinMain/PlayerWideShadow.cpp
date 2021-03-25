#include "pch.h"
#include"Image.h"
#include"Camera.h"
#include "PlayerWideShadow.h"
#include "MovingObject.h"
#include "Player.h"

PlayerWideShadow::PlayerWideShadow(const string& name, float x, float y)
	: GameObject(name)
{
	mName = name;
	mX = x;
	mY = y;

}
void PlayerWideShadow::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"PlayerWideShadow", Resources(L"Player/PlayerWideShadow.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"PlayerWideShadow");

	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
}
void PlayerWideShadow::Init(float x, float y)
{
	ImageManager::GetInstance()->LoadFromFile(L"PlayerWideShadow", Resources(L"Player/PlayerWideShadow.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"PlayerWideShadow");
	mX = x;
	mY = y;



}

void PlayerWideShadow::Release()
{
}

void PlayerWideShadow::Update()
{
	D2D1_RECT_F moveRc = mPlayer->GetMovingRect();

	mX = moveRc.left + (moveRc.right - moveRc.left) / 2;
	mY = moveRc.top + (moveRc.bottom - moveRc.top) / 2 + 30;

	mRect = RectMakeCenter(mX, mY, mImage->GetWidth() * 3, mImage->GetWidth() * 3);
}

void PlayerWideShadow::Render()
{
	mImage->SetScale(3.f);
	mImage->SetAlpha(0.5f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, 0, 0);
}
