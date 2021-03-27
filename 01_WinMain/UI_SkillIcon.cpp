#include "pch.h"
#include "UI_SkillIcon.h"
#include "Image.h"

UI_SkillIcon::UI_SkillIcon(const string & name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void UI_SkillIcon::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SkillIcon", Resources(L"UI/SkillIcon.png"), 4, 4);
	mImage = ImageManager::GetInstance()->FindImage(L"SkillIcon");

	mSkillIndexList.insert(make_pair("FireBall", Vector2(0, 0)));	// FireBall
	mSkillIndexList.insert(make_pair("DragonArc", Vector2(1, 0)));	// DragonArc
	mSkillIndexList.insert(make_pair("WindSlash", Vector2(0, 1)));	// WindSlash
	mSkillIndexList.insert(make_pair("IceSpear", Vector2(0, 2)));	// IceSpear
	
}

void UI_SkillIcon::Release()
{
}

void UI_SkillIcon::Update()
{
}

void UI_SkillIcon::Render()
{
	
}
