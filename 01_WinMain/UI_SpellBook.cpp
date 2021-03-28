#include "pch.h"
#include "UI_SpellBook.h"
#include "SkillObject.h"
#include "Image.h"
#include "Player.h"

void UI_SpellBook::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUI", Resources(L"UI/SpellbookUI.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIText", Resources(L"UI/SpellbookUIText.png"), 1, 4);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillType", Resources(L"UI/SpellbookUISkillType"), 3, 2);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIElementalPages", Resources(L"UI/SpellbookUIElementalPages.png"), 3, 2);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementOn", Resources(L"UI/SpellbookUISkillElementOn.png"), 1, 5);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementOff", Resources(L"UI/SpellbookUISkillElementOff.png"), 1, 5);

	mSpellbookUI;
	mSpellbookUIText;
	mSpellbookUISkillType;
	mSpellbookUIElementalPage;
	mSpellbookUISkillUIElementalOn;
	mSpellbookUISkillUIElementalOff;

	mSpellbookUI = new UIObject(400, 400,
		ImageManager::GetInstance()->FindImage(L"SpellbookUI")->GetWidth(),
		ImageManager::GetInstance()->FindImage(L"SpellbookUI")->GetHeight(),
		ImageManager::GetInstance()->FindImage(L"SpellbookUI"));
}

void UI_SpellBook::Release()
{
}

void UI_SpellBook::Update()
{
}

void UI_SpellBook::Render()
{
	if (mIsActive)
	{
		mSpellbookUI->Image->Render(mSpellbookUI->X, mSpellbookUI->Y);
	}
}
