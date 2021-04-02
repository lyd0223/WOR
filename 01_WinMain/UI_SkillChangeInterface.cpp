#include "pch.h"
#include "UI_SkillChangeInterface.h"
#include "UI_SpellBook.h"
#include "Image.h"
#include "Player.h"

UI_SkillChangeInterface::UI_SkillChangeInterface()
{
	mName = "SkillChangeInterface";
}

void UI_SkillChangeInterface::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"SpellChangeInterface", Resources(L"UI/SpellChangeInterface.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SelectCard", Resources(L"UI/CardSelect.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SkillIcon", Resources(L"UI/SkillIcon.png"), 4, 4);

	mSkillIndexList.insert(make_pair("FireBall", Vector2(0, 0)));		// FireBall
	mSkillIndexList.insert(make_pair("DragonArc", Vector2(1, 0)));		// DragonArc
	mSkillIndexList.insert(make_pair("Meteor", Vector2(2, 0)));			// Meteor
	mSkillIndexList.insert(make_pair("WindSlash", Vector2(0, 1)));		// WindSlash
	mSkillIndexList.insert(make_pair("WindDash", Vector2(1, 1)));		// WindDash
	mSkillIndexList.insert(make_pair("IceSpear", Vector2(0, 2)));		// IceSpear
	mSkillIndexList.insert(make_pair("WaterBall", Vector2(1, 2)));		// WaterBall
	mSkillIndexList.insert(make_pair("ThunderBolt", Vector2(0, 3)));	// ThunderBolt
	mSkillIndexList.insert(make_pair("LightRing", Vector2(1, 3)));		// LightRing

	mPlayer = (Player*) ObjectManager::GetInstance()->FindObject("Player");

	mCardPostion.push_back(Vector2(135, WINSIZEY - 86));
	mCardPostion.push_back(Vector2(279, WINSIZEY - 86));
	mCardPostion.push_back(Vector2(423, WINSIZEY - 86));
	mCardPostion.push_back(Vector2(567, WINSIZEY - 86));

	mSkillChangeInterface = new UIObject(350, WINSIZEY, 
		ImageManager::GetInstance()->FindImage(L"SpellChangeInterface")->GetWidth(),
		ImageManager::GetInstance()->FindImage(L"SpellChangeInterface")->GetHeight(),
		ImageManager::GetInstance()->FindImage(L"SpellChangeInterface"));

	mBasicSkillIcon = new UIObject(mCardPostion[0].X, mCardPostion[0].Y, 55, 55, ImageManager::GetInstance()->FindImage(L"SkillIcon"));
	mDashSkillIcon = new UIObject(mCardPostion[1].X, mCardPostion[1].Y, 55, 55, ImageManager::GetInstance()->FindImage(L"SkillIcon"));
	mStandardSkillIcon = new UIObject(mCardPostion[2].X, mCardPostion[2].Y, 55, 55, ImageManager::GetInstance()->FindImage(L"SkillIcon"));
	mSignatureSkillIcon = new UIObject(mCardPostion[3].X, mCardPostion[3].Y, 55, 55, ImageManager::GetInstance()->FindImage(L"SkillIcon"));

	mCardSelect = new UIObject(mBasicSkillIcon->X, mBasicSkillIcon->Y,
		ImageManager::GetInstance()->FindImage(L"SelectCard")->GetWidth(),
		ImageManager::GetInstance()->FindImage(L"SelectCard")->GetHeight(),
		ImageManager::GetInstance()->FindImage(L"SelectCard"));

	mIndex = 0;
}

void UI_SkillChangeInterface::Release()
{
}

void UI_SkillChangeInterface::Update()
{
	if (mIsActive)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE) && mIndex != 1)
		{
			UI_SpellBook* spellBook = new UI_SpellBook("SpellBook", mIndex);
			spellBook->Init();
			//ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, spellBook);
			ObjectManager::GetInstance()->AddInterface(spellBook);
		}

		if (Input::GetInstance()->GetKeyDown(VK_LEFT) ||
			Input::GetInstance()->GetKeyDown('A'))
		{
			mIndex--;
			if (mIndex < 0) mIndex = 3;
			SoundPlayer::GetInstance()->Play(L"MenuMove", 1.f);
		}

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) ||
			Input::GetInstance()->GetKeyDown('D'))
		{
			mIndex++;
			if (mIndex > 3) mIndex = 0;
			SoundPlayer::GetInstance()->Play(L"MenuMove", 1.f);
		}

		if (mSkillChangeInterface->Y > 400)
		{
			mSkillChangeInterface->Y -= 50.f;
			mBasicSkillIcon->Y -= 50.f;
			mDashSkillIcon->Y -= 50.f;
			mStandardSkillIcon->Y -= 50.f;
			mSignatureSkillIcon->Y -= 50.f;
			for (int i = 0; i < mCardPostion.size(); i++)
			{
				mCardPostion[i].Y = mBasicSkillIcon->Y;
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		{
			ObjectManager::GetInstance()->PopInterface();
		}

		mCardSelect->X = mCardPostion[mIndex].X;
		mCardSelect->Y = mCardPostion[mIndex].Y;

	}
}

void UI_SkillChangeInterface::Render()
{
	if (mIsActive)
	{
		Vector2 Basic = mSkillIndexList.find(SkillManager::GetInstance()->GetPlayerLBSkill())->second;
		Vector2 Dash = mSkillIndexList.find(SkillManager::GetInstance()->GetPlayerSpaceSkill())->second;
		Vector2 Standard = mSkillIndexList.find(SkillManager::GetInstance()->GetPlayerRBSkill())->second;
		Vector2 Signature = mSkillIndexList.find(SkillManager::GetInstance()->GetPlayerQSkill())->second;

		mSkillChangeInterface->Image->Render(mSkillChangeInterface->X, mSkillChangeInterface->Y);
		mBasicSkillIcon->Image->ScaleFrameRender(mBasicSkillIcon->X, mBasicSkillIcon->Y, Basic.X, Basic.Y, mBasicSkillIcon->SizeX, mBasicSkillIcon->SizeY);
		mDashSkillIcon->Image->ScaleFrameRender(mDashSkillIcon->X, mDashSkillIcon->Y, Dash.X, Dash.Y, mDashSkillIcon->SizeX, mDashSkillIcon->SizeY);
		mStandardSkillIcon->Image->ScaleFrameRender(mStandardSkillIcon->X, mStandardSkillIcon->Y, Standard.X, Standard.Y, mStandardSkillIcon->SizeX, mStandardSkillIcon->SizeY);
		mSignatureSkillIcon->Image->ScaleFrameRender(mSignatureSkillIcon->X, mSignatureSkillIcon->Y, Signature.X, Signature.Y, mSignatureSkillIcon->SizeX, mSignatureSkillIcon->SizeY);
		mCardSelect->Image->Render(mCardSelect->X, mCardSelect->Y);
	}
}
