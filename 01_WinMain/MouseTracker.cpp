#include "pch.h"
#include"Image.h"
#include"Camera.h"
#include "MouseTracker.h"
#include "MovingObject.h"
#include "Player.h"

MouseTracker::MouseTracker(const string& name, float x, float y, float angle)
	: GameObject(name)
{
	mName = name;
	mX = x;
	mY = y;
	mAngle = angle;
}
void MouseTracker::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MouseTracker", Resources(L"UI/MouseTracker.png"), 1, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MouseTracker");

	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
}
void MouseTracker::Init(float x, float y, float angle)
{
	ImageManager::GetInstance()->LoadFromFile(L"MouseTracker", Resources(L"UI/MouseTracker.png"), 1, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MouseTracker");
	mX = x;
	mY = y;

	mAngle = angle;
	
}

void MouseTracker::Release()
{
}

void MouseTracker::Update()
{
	D2D1_RECT_F moveRc = mPlayer->GetMovingRect();
	D2D1_RECT_F rctemp = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	mAngle = Math::GetAngle(mX, mY, _mousePosition.x + rctemp.left, _mousePosition.y + rctemp.top);
	
	mX = moveRc.left + (moveRc.right - moveRc.left) / 2;
	mY = moveRc.top + (moveRc.bottom - moveRc.top) / 2 + 20;
	mAngle = mAngle;

	mRect = RectMakeCenter(mX, mY, mImage->GetWidth() * 3, mImage->GetWidth() * 3);
}

void MouseTracker::Render()
{
	mImage->SetScale(3.f);
	mImage->SetAlpha(0.7f);
	mImage->SetAngle((mAngle) * -(180 / PI));

	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, 0, 0);
}
