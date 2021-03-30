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

	ImageManager::GetInstance()->LoadFromFile(L"StandardCard", Resources(L"UI/StandardCard.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SignatureCard", Resources(L"UI/SignatureCard.png"));

	ImageManager::GetInstance()->LoadFromFile(L"SkillIcon", Resources(L"UI/SkillIcon.png"), 4, 4);

	mSkillIcon = ImageManager::GetInstance()->FindImage(L"SkillIcon");

	mSkillIndexList.insert(make_pair("FireBall", Vector2(0, 0)));		// FireBall
	mSkillIndexList.insert(make_pair("DragonArc", Vector2(1, 0)));		// DragonArc
	mSkillIndexList.insert(make_pair("Meteor", Vector2(2, 0)));			// Meteor
	mSkillIndexList.insert(make_pair("WindSlash", Vector2(0, 1)));		// WindSlash
	mSkillIndexList.insert(make_pair("WindDash", Vector2(1, 1)));		// WindDash
	mSkillIndexList.insert(make_pair("IceSpear", Vector2(0, 2)));		// IceSpear
	mSkillIndexList.insert(make_pair("WaterBall", Vector2(1, 2)));		// WaterBall
	mSkillIndexList.insert(make_pair("ThunderBolt", Vector2(0, 3)));	// ThunderBolt

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

	mCardPositionX = 296;
	mCardPositionY = 290;
	rc = RectMakeCenter(mCardPositionX, mCardPositionY,
		ImageManager::GetInstance()->FindImage(L"StandardCard")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"StandardCard")->GetHeight() * 2);

	mCurrentSkillElement = mCurrentSkill->GetSkillElement();

	MakeSpellbookUISkillElemental();

	mSpellbookUISkillElementalOn = new UIObject(
		mSpellbookUISkillElemantalList.find(mCurrentSkillElement)->second->X, 
		mSpellbookUISkillElemantalList.find(mCurrentSkillElement)->second->Y + 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillUIElementOn")->GetWidth() * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillUIElementOn")->GetHeight() / 5 * 2,
		ImageManager::GetInstance()->FindImage(L"SpellbookUISkillUIElementOn")
	);

	// 
	map<SkillElement, UIObject*>::iterator iter = mSpellbookUISkillElemantalList.begin();
	for (; iter != mSpellbookUISkillElemantalList.end(); iter++)
	{
		mSkillElementList.push_back(iter->first);
	}
	
	map<SkillElement, vector<SkillObject*>>::iterator iter2 = mSkillList.begin();
	for (; iter2 != mSkillList.end(); iter2++)
	{
		vector<UIObject*> emptyVector;
		
		mSkillCardList.insert(make_pair(iter2->first, emptyVector));
	}

	iter2 = mSkillList.begin();
	for (; iter2 != mSkillList.end(); iter2++)
	{
		Image* image;

		if ((SkillArcana)mIndexY == SkillArcana::Signature)
		{
			image = ImageManager::GetInstance()->FindImage(L"SignatureCard");
		}
		else
		{
			image = ImageManager::GetInstance()->FindImage(L"StandardCard");
		}

		for (int i = 0; i < iter2->second.size(); i++)
		{
			
			mSkillCardList[iter2->first].push_back(new UIObject(
				mCardPositionX + (i * (image->GetWidth() * 2 + 10)),
				mCardPositionY,
				image->GetWidth() * 2,
				image->GetHeight() * 2,
				image
			));
		}
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
		map<SkillElement, vector<SkillObject*>>::iterator iter2 = mSkillList.find(mCurrentSkillElement);
		int maxIndex = iter2->second.size();
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W'))
		{
			mSpellbookUIUpArrow->Image->SetScale(1.5f);
			mIndex = 0;
			if(iter->first != mSpellbookUISkillElemantalList.begin()->first)
				iter--;
			mCurrentSkillElement = iter->first;
			mCurrentSkill = mSkillList.find(iter->first)->second[0];
			mSpellbookUISkillElementalOn->X = iter->second->X;
			mSpellbookUISkillElementalOn->Y = iter->second->Y;
		}
		else if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
		{
			mSpellbookUIDownArrow->Image->SetScale(1.5f);
			mIndex = 0;
			iter++;
			if (iter == mSpellbookUISkillElemantalList.end())
			{
				iter--;
			}
			mCurrentSkillElement = iter->first;
			mCurrentSkill = mSkillList.find(iter->first)->second[0];
			mSpellbookUISkillElementalOn->X = iter->second->X;
			mSpellbookUISkillElementalOn->Y = iter->second->Y;
		}
		else if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A'))
		{
			mSpellbookUILeftArrow->Image->SetScale(1.5f);
			mIndex--;

			vector<UIObject*> uiVec = mSkillCardList.find(mCurrentSkillElement)->second;
			for (int i = 0; i < uiVec.size(); i++)
			{
				uiVec[i]->X = mCardPositionX + (i * (uiVec[i]->Image->GetWidth() * 2 + 10));
			}

			if (mIndex < 0)
			{
				mIndex++;
			}
			mCurrentSkill = iter2->second[mIndex];
		}
		else if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
		{
			mSpellbookUIRightArrow->Image->SetScale(1.5f);
			mIndex++;

			vector<UIObject*> uiVec = mSkillCardList.find(mCurrentSkillElement)->second;
			reverse(uiVec.begin(), uiVec.end());

			for (int i = 0; i < uiVec.size(); i++)
			{
				uiVec[i]->X = mCardPositionX - (i * (uiVec[i]->Image->GetWidth() * 2 + 10));
			}

			if (mIndex >= maxIndex)
				mIndex--;
			mCurrentSkill = iter2->second[mIndex];
		}
		
		mCurrentSkill;

		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			switch (mCurrentSkillArcana)
			{
			case SkillArcana::Basic:
				mPlayer->SetLB_ButtonSkill(SkillManager::GetInstance()->FindSkill(mCurrentSkill->GetName())->GetName());
				break;
			case SkillArcana::Dash:
				mPlayer->SetSpacebar_ButtonSkill(SkillManager::GetInstance()->FindSkill(mCurrentSkill->GetName())->GetName());
				break;
			case SkillArcana::Standard:
				mPlayer->SetRB_ButtonSkill(SkillManager::GetInstance()->FindSkill(mCurrentSkill->GetName())->GetName());
				break;
			case SkillArcana::Signature:
				mPlayer->SetQ_ButtonSkill(SkillManager::GetInstance()->FindSkill(mCurrentSkill->GetName())->GetName());
				break;
			}
			ObjectManager::GetInstance()->PopInterface();
		}

		if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		{
			ObjectManager::GetInstance()->PopInterface();
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

		// 스펠북 오른쪽 속성종류 출력
		map<SkillElement, UIObject*>::iterator iter = mSpellbookUISkillElemantalList.begin();

		for (; iter != mSpellbookUISkillElemantalList.end(); iter++)
		{
			iter->second->Image->ScaleRender(iter->second->X, iter->second->Y, iter->second->SizeX, iter->second->SizeY);
		}
		
		// 스킬카드 출력
		map<SkillElement, vector<UIObject*>>::iterator iter2 = mSkillCardList.begin();
		
		for (; iter2 != mSkillCardList.end(); iter2++)
		{
			if (mCurrentSkillElement != iter2->first) continue;
			for (int i = 0; i < iter2->second.size(); i++)
			{
				iter2->second[i]->Image->ScaleRender(iter2->second[i]->X, iter2->second[i]->Y, iter2->second[i]->SizeX, iter2->second[i]->SizeY);
				mSkillList[iter2->first];
				Vector2 temp;
				if (mCurrentSkillElement == iter2->first)
				{
					temp = mSkillIndexList.find(mSkillList.find(iter2->first)->second[i]->GetName())->second;
					mSkillIcon->ScaleFrameRender(iter2->second[i]->X, iter2->second[i]->Y, temp.X, temp.Y,
						mSkillIcon->GetWidth() / 4 * 2,
						mSkillIcon->GetHeight() / 4 * 2);
				}
			}
		}
		string temp = mCurrentSkill->GetName();
		wstring str;
		str.assign(temp.begin(), temp.end());
		//D2D1_RECT_F rc = RectMakeCenter(mSpellbookUI->X, mSpellbookUI->Y + 35, 200, 30);
		//RenderRect(rc);
		D2DRenderer::GetInstance()->RenderText(mSpellbookUI->X - 40, mSpellbookUI->Y + 20, str, 20.f);
		//D2DRenderer::GetInstance()->RenderTextField(mSpellbookUI->X, mSpellbookUI->Y, str, 20.f, 200, 30);
		//D2DRenderer::GetInstance()->DrawTextToRect(rc, str, D2D1::ColorF::Gray, 20);
		mSpellbookUISkillElementalOn->Image->ScaleFrameRender(mSpellbookUISkillElementalOn->X, mSpellbookUISkillElementalOn->Y, 0, (int)mCurrentSkillElement, mSpellbookUISkillElementalOn->SizeX, mSpellbookUISkillElementalOn->SizeY);
	}
}

void UI_SpellBook::GetSkillList()
{
	map<SkillElement, vector<SkillObject*>> temp = SkillManager::GetInstance()->GetSkillList();
	
	map<SkillElement, vector<SkillObject*>>::iterator iter = temp.begin();

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
