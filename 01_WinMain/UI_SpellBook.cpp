#include "pch.h"
#include "UI_SpellBook.h"
#include "SkillObject.h"
#include "Image.h"
#include "Player.h"

UI_SpellBook::UI_SpellBook(const string & name, int index)
{
	mName = name;
	mIndexY = index;
	mCurrentSkillArcana = (SkillArcana)index;
}

void UI_SpellBook::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUI", Resources(L"UI/SpellbookUI.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIText", Resources(L"UI/SpellbookUIText.png"), 1, 4);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillType", Resources(L"UI/SpellbookUISkillType.png"), 1, 6);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIElementalPages", Resources(L"UI/SpellbookUIElementalPages.png"), 1, 5);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillUIElementOn", Resources(L"UI/SpellbookUISkillElementOn.png"), 1, 5);
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementFire", Resources(L"UI/SpellbookUISkillElementFire.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementWind", Resources(L"UI/SpellbookUISkillElementWind.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementEarth", Resources(L"UI/SpellbookUISkillElementEarth.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementElect", Resources(L"UI/SpellbookUISkillElementElect.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUISkillElementWater", Resources(L"UI/SpellbookUISkillElementWater.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUILeftArrow", Resources(L"UI/LeftArrow.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIRightArrow", Resources(L"UI/RightArrow.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIUpArrow", Resources(L"UI/UpArrow.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpellbookUIDownArrow", Resources(L"UI/DownArrow.png"));
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");

	mCurrentSkillArcana = (SkillArcana)mIndexY;

	GetSkillList();

	mSpellbookUI = new UIObject(300, WINSIZEY / 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUI")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUI")->GetHeight() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUI"));
	mSpellbookUIText = new UIObject(295, 140,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIText")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIText")->GetHeight() / 4 * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIText"));
	mSpellbookUISkillType = new UIObject(296, 200,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillType")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillType")->GetHeight() / 6 * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillType"));
	mSpellbookUIElementalPage = new UIObject(290, WINSIZEY / 2 - 5,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIElementalPages")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIElementalPages")->GetHeight() / 5 * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIElementalPages"));

	mSpellbookUILeftArrow = new UIObject(mSpellbookUI->X - 150, mSpellbookUI->Y - 80,
		ImageManager::GetInstance()->FindImage(L"SpellbookUILeftArrow")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUILeftArrow")->GetHeight() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUILeftArrow"));
	mSpellbookUIRightArrow = new UIObject(mSpellbookUI->X + 150, mSpellbookUI->Y - 80,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIRightArrow")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIRightArrow")->GetHeight() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIRightArrow"));
	mSpellbookUIUpArrow = new UIObject(mSpellbookUI->X - 4, mSpellbookUISkillType->Y - 18,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIUpArrow")->GetWidth() * 3,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIUpArrow")->GetHeight() * 3,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIUpArrow"));
	mSpellbookUIDownArrow = new UIObject(mSpellbookUI->X - 4, mSpellbookUISkillType->Y + 19,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIDownArrow")->GetWidth() * 3,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIDownArrow")->GetHeight() * 3,
		ImageManager::GetInstance()->FindImage(L"SpellbookUIDownArrow"));


	switch (mCurrentSkillArcana)
	{
	case SkillArcana::Basic:
		mCurrentSkill = SkillManager::GetInstance()->FindSkill(mPlayer->GetLB_ButtonSkill());
		break;
	case SkillArcana::Dash:
		mCurrentSkill = SkillManager::GetInstance()->FindSkill(mPlayer->GetSpacebar_ButtonSkill());
		break;
	case SkillArcana::Standard:
		mCurrentSkill = SkillManager::GetInstance()->FindSkill(mPlayer->GetRB_ButtonSkill());
		break;
	case SkillArcana::Signature:
		mCurrentSkill = SkillManager::GetInstance()->FindSkill(mPlayer->GetQ_ButtonSkill());
		break;
	}

	mCurrentSkillElement = mCurrentSkill->GetSkillElement();

	MakeSpellbookUISkillElemental();

	mSpellbookUISkillElementalOn = new UIObject(
		mSpellbookUISkillElemantalList.find(mCurrentSkillElement)->second->X, 
		mSpellbookUISkillElemantalList.find(mCurrentSkillElement)->second->Y + 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillUIElementOn")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillUIElementOn")->GetHeight() / 5 * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillUIElementOn")
	);

	map<SkillElement, UIObject*>::iterator iter = mSpellbookUISkillElemantalList.begin();
	for (; iter != mSpellbookUISkillElemantalList.end(); iter++)
	{
		mSkillElementList.push_back(iter->first);
	}
}

void UI_SpellBook::Release()
{
}

void UI_SpellBook::Update()
{
	if (mIsActive)
	{
		map<SkillElement, UIObject*>::iterator iter = mSpellbookUISkillElemantalList.find(mCurrentSkillElement);
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W'))
		{
			mSpellbookUIUpArrow->Image->SetScale(1.5f);
			if(iter->first != mSpellbookUISkillElemantalList.begin()->first)
				iter--;
			mCurrentSkillElement = iter->first;
			mSpellbookUISkillElementalOn->X = iter->second->X;
			mSpellbookUISkillElementalOn->Y = iter->second->Y;
		}
		else if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
		{
			mSpellbookUIDownArrow->Image->SetScale(1.5f);
				iter++;
				if (iter == mSpellbookUISkillElemantalList.end())
				{
					iter--;
				}
			mCurrentSkillElement = iter->first;
			mSpellbookUISkillElementalOn->X = iter->second->X;
			mSpellbookUISkillElementalOn->Y = iter->second->Y;
		}
		else if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A'))
		{
			mSpellbookUILeftArrow->Image->SetScale(1.5f);
		}
		else if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
		{
			mSpellbookUIRightArrow->Image->SetScale(1.5f);
		}

		if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		{
			mIsDestroy = true;
		}
	}
}

void UI_SpellBook::Render()
{
	if (mIsActive)
	{
		mSpellbookUI->Image->ScaleRender(mSpellbookUI->X, mSpellbookUI->Y, mSpellbookUI->SizeX, mSpellbookUI->SizeY);
		mSpellbookUIText->Image->ScaleFrameRender(mSpellbookUIText->X, mSpellbookUIText->Y, 0, mIndexY, mSpellbookUIText->SizeX, mSpellbookUIText->SizeY);
		mSpellbookUISkillType->Image->ScaleFrameRender(mSpellbookUISkillType->X, mSpellbookUISkillType->Y, 0, (int)mCurrentSkillElement, mSpellbookUISkillType->SizeX, mSpellbookUISkillType->SizeY);
		mSpellbookUIElementalPage->Image->ScaleFrameRender(mSpellbookUIElementalPage->X, mSpellbookUIElementalPage->Y, 0, (int)mCurrentSkillElement, mSpellbookUIElementalPage->SizeX, mSpellbookUIElementalPage->SizeY);
		mSpellbookUILeftArrow->Image->ScaleRender(mSpellbookUILeftArrow->X, mSpellbookUILeftArrow->Y, mSpellbookUILeftArrow->SizeX, mSpellbookUILeftArrow->SizeY);
		mSpellbookUIRightArrow->Image->ScaleRender(mSpellbookUIRightArrow->X, mSpellbookUIRightArrow->Y, mSpellbookUIRightArrow->SizeX, mSpellbookUIRightArrow->SizeY);
		mSpellbookUIUpArrow->Image->ScaleRender(mSpellbookUIUpArrow->X, mSpellbookUIUpArrow->Y, mSpellbookUIUpArrow->SizeX, mSpellbookUIUpArrow->SizeY);
		mSpellbookUIDownArrow->Image->ScaleRender(mSpellbookUIDownArrow->X, mSpellbookUIDownArrow->Y, mSpellbookUIDownArrow->SizeX, mSpellbookUIDownArrow->SizeY);

		map<SkillElement, UIObject*>::iterator iter = mSpellbookUISkillElemantalList.begin();

		for (; iter != mSpellbookUISkillElemantalList.end(); iter++)
		{
			iter->second->Image->ScaleRender(iter->second->X, iter->second->Y, iter->second->SizeX, iter->second->SizeY);
		}

		mSpellbookUISkillElementalOn->Image->ScaleFrameRender(mSpellbookUISkillElementalOn->X, mSpellbookUISkillElementalOn->Y, 0, (int)mCurrentSkillElement, mSpellbookUISkillElementalOn->SizeX, mSpellbookUISkillElementalOn->SizeY);
	}
}

void UI_SpellBook::GetSkillList()
{
	map<SkillElement, vector<SkillObject*>> temp = SkillManager::GetInstance()->GetSkillList();
	
	map<SkillElement, vector<SkillObject*>>::iterator iter = temp.begin();

	//for (int i = 0; i < (int)SkillElement::End; ++i)
	//{
	//	vector<SkillObject*> emptyVector;
	//	mSkillList.insert(make_pair((SkillElement)i, emptyVector));
	//}

	for (; iter != temp.end(); iter++)
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			if (iter->second[i]->GetSkillArcana() == mCurrentSkillArcana)
			{
				AddSkillList(iter->second[i]->GetSkillElement(), iter->second[i]);
			}
		}
	}

}

void UI_SpellBook::AddSkillList(SkillElement element, SkillObject * skillObject)
{
	mSkillList[element].push_back(skillObject);
}

void UI_SpellBook::MakeSpellbookUISkillElemental()
{
	map<SkillElement, vector<SkillObject*>>::iterator iter = mSkillList.begin();

	for (; iter != mSkillList.end(); iter++)
	{
		if (iter->second.size() != 0)
		{
			if (iter->first == SkillElement::Fire)
			{
				mSpellbookUISkillElemantalList.insert(make_pair(iter->first, new UIObject(500, 180,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementFire")->GetWidth() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementFire")->GetHeight() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementFire"))));
				
			}
			else if (iter->first == SkillElement::Wind)
			{
				mSpellbookUISkillElemantalList.insert(make_pair(iter->first, new UIObject(500, 250,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementWind")->GetWidth() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementWind")->GetHeight() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementWind"))));
			}
			else if (iter->first == SkillElement::Earth)
			{
				mSpellbookUISkillElemantalList.insert(make_pair(iter->first, new UIObject(500, 320,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementEarth")->GetWidth() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementEarth")->GetHeight() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementEarth"))));
			}
			else if (iter->first == SkillElement::Elect)
			{
				mSpellbookUISkillElemantalList.insert(make_pair(iter->first, new UIObject(500, 390,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementElect")->GetWidth() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementElect")->GetHeight() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementElect"))));
			}
			else if (iter->first == SkillElement::Water)
			{
				mSpellbookUISkillElemantalList.insert(make_pair(iter->first, new UIObject(500, 460,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementWater")->GetWidth() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementWater")->GetHeight() * 2,
					ImageManager::GetInstance()->FindImage(L"SpellbookUISkillElementWater"))));
			}
		}
	}
}
