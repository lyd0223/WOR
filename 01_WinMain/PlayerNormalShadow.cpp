#include "pch.h"
#include"Image.h"
#include"Camera.h"
#include "PlayerNormalShadow.h"
#include "MovingObject.h"
#include "Player.h"

PlayerNormalShadow::PlayerNormalShadow(const string& name, float x, float y)
	: GameObject(name)
{
	mName = name;
	mX = x;
	mY = y;
	
}
void PlayerNormalShadow::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"PlayerNormalShadow", Resources(L"Player/PlayerNormalShadow.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"PlayerNormalShadow");

	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
}
void PlayerNormalShadow::Init(float x, float y)
{
	ImageManager::GetInstance()->LoadFromFile(L"PlayerNormalShadow", Resources(L"Player/PlayerNormalShadow.png"));
	mImage = ImageManager::GetInstance()->FindImage(L"PlayerNormalShadow");
	mX = x;
	mY = y;



}

void PlayerNormalShadow::Release()
{
}

void PlayerNormalShadow::Update()
{
	D2D1_RECT_F moveRc = mPlayer->GetMovingRect();

	mX = moveRc.left + (moveRc.right - moveRc.left) / 2;
	mY = moveRc.top + (moveRc.bottom - moveRc.top) / 2 + 30;

	mRect = RectMakeCenter(mX, mY, mImage->GetWidth() * 3, mImage->GetWidth() * 3);
}

void PlayerNormalShadow::Render()
{
	mImage->SetScale(3.f);
	mImage->SetAlpha(0.5f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, 0, 0);
}
