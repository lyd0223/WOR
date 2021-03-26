#include "pch.h"
#include "Effect_EnemyCreate.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

Effect_EnemyCreate::Effect_EnemyCreate(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Effect_EnemyCreate::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"EnemyCreate", Resources(L""));
	mImage = ImageManager::GetInstance()->FindImage(L"EnemyCreate");

	mAnimation = new Animation();
	
}

void Effect_EnemyCreate::Release()
{
	SafeDelete(mAnimation)
}

void Effect_EnemyCreate::Update()
{
	
}

void Effect_EnemyCreate::Render()
{
	//mImage->SetScale();
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}