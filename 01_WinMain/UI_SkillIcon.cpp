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
