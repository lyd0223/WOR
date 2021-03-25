#include "pch.h"
#include"Image.h"
#include"Camera.h"
#include "PlayerHeightShadow.h"
#include "MovingObject.h"
#include "Player.h"

PlayerHeightShadow::PlayerHeightShadow(const string& name, float x, float y)
	: GameObject(name)
{
	mName = name;
	mX = x;
	mY = y;

}
void PlayerHeightShadow::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"PlayerHeightShadow", Resources(L"Player/PlayerHeightShadow.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"PlayerHeightShadow");

	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
}
void PlayerHeightShadow::Init(float x, float y)
{
	ImageManager::GetInstance()->LoadFromFile(L"PlayerHeightShadow", Resources(L"Player/PlayerHeightShadow.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"PlayerHeightShadow");
	mX = x;
	mY = y;



}

void PlayerHeightShadow::Release()
{
}

void PlayerHeightShadow::Update()
{
	D2D1_RECT_F moveRc = mPlayer->GetMovingRect();

	mX = moveRc.left + (moveRc.right - moveRc.left) / 2;
	mY = moveRc.top + (moveRc.bottom - moveRc.top) / 2 + 30;

	mRect = RectMakeCenter(mX, mY, mImage->GetWidth() * 3, mImage->GetWidth() * 3);
}

void PlayerHeightShadow::Render()
{
	mImage->SetScale(3.f);
	mImage->SetAlpha(0.5f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, 0, 0);
}
