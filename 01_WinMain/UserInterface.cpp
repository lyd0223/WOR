#include "pch.h"
#include "UserInterface.h"

#include "Image.h"
#include "Player.h"
#include "UI_SkillChangeInterface.h"
#include "UI_ESC.h"

void UserInterface::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"HPBar", Resources(L"UI/HPBar.png"));
	ImageManager::GetInstance()->LoadFromFile(L"MPBar", Resources(L"UI/MPBar.png"));
	ImageManager::GetInstance()->LoadFromFile(L"Status", Resources(L"UI/Status.png"));
	ImageManager::GetInstance()->LoadFromFile(L"HPBar", Resources(L"UI/HPBar.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SkillBox", Resources(L"UI/SkillBox.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpecialSkillBox", Resources(L"UI/SpecialSkillBox.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SkillIcon", Resources(L"UI/SkillIcon.png"), 4, 4);

	ImageManager::GetInstance()->LoadFromFile(L"MouseLButton", Resources(L"UI/LButton.png"));
	ImageManager::GetInstance()->LoadFromFile(L"MouseRButton", Resources(L"UI/RButton.png"));
	ImageManager::GetInstance()->LoadFromFile(L"QButton", Resources(L"UI/Q.png"));
	ImageManager::GetInstance()->LoadFromFile(L"EButton", Resources(L"UI/E.png"));
	ImageManager::GetInstance()->LoadFromFile(L"SpaceButton", Resources(L"UI/Space.png"));

	ImageManager::GetInstance()->LoadFromFile(L"BossHP", Resources(L"UI/BossHP.png"));

	ImageManager::GetInstance()->LoadFromFile(L"NumberWhite", Resources(L"UI/NumberWhite.png"), 10, 1);
	
	mSkillIndexList.insert(make_pair("FireBall", Vector2(0, 0)));		// FireBall
	mSkillIndexList.insert(make_pair("DragonArc", Vector2(1, 0)));		// DragonArc
	mSkillIndexList.insert(make_pair("Meteor", Vector2(2, 0)));			// Meteor
	mSkillIndexList.insert(make_pair("WindSlash", Vector2(0, 1)));		// WindSlash
	mSkillIndexList.insert(make_pair("WindDash", Vector2(1, 1)));		// WindDash
	mSkillIndexList.insert(make_pair("IceSpear", Vector2(0, 2)));		// IceSpear
	mSkillIndexList.insert(make_pair("WaterBall", Vector2(1, 2)));		// WaterBall
	mSkillIndexList.insert(make_pair("ThunderBolt", Vector2(0, 3)));		// ThunderBolt
	mSkillIndexList.insert(make_pair("LightRing", Vector2(1, 3)));		// LightRing

	mStatus = new UIObject(50, 50, 246, 60, ImageManager::GetInstance()->FindImage(L"Status"));
	mHPBar = new UIObject(107, 60, 183, 24, ImageManager::GetInstance()->FindImage(L"HPBar"));
	mMPBar = new UIObject(107, 90, 144, 12, ImageManager::GetInstance()->FindImage(L"MPBar"));
	mSkillBox1 = new  UIObject( 60, WINSIZEY- 50, 50, 50, ImageManager::GetInstance()->FindImage(L"SkillBox"));
	mSkillBox2 = new  UIObject(115, WINSIZEY - 50, 50, 50, ImageManager::GetInstance()->FindImage(L"SkillBox"));
	mSkillBox3 = new  UIObject( 170, WINSIZEY - 50, 50, 50, ImageManager::GetInstance()->FindImage(L"SkillBox"));
	mSpecialSkillBox = new  UIObject(225, WINSIZEY - 50, 50, 50, ImageManager::GetInstance()->FindImage(L"SpecialSkillBox"));
	mMouseLButton = new  UIObject(60, WINSIZEY - 100, 50, 50, ImageManager::GetInstance()->FindImage(L"MouseLButton"));
	mSpaceButton = new  UIObject(115, WINSIZEY - 100, 50, 50, ImageManager::GetInstance()->FindImage(L"SpaceButton"));
	mMouseRButton = new  UIObject(170, WINSIZEY -100, 50, 50, ImageManager::GetInstance()->FindImage(L"MouseRButton"));
	mQButton = new  UIObject(225, WINSIZEY - 100, 50, 50, ImageManager::GetInstance()->FindImage(L"QButton"));

	mLB_ButtonSkillIcon = new UIObject(60, WINSIZEY - 50, 42, 42, ImageManager::GetInstance()->FindImage(L"SkillIcon"));
	mSpace_ButtonSkillIcon = new UIObject(115, WINSIZEY - 50, 42, 42, ImageManager::GetInstance()->FindImage(L"SkillIcon"));
	mRB_ButtonSkillIcon = new UIObject(170, WINSIZEY - 50, 42, 42, ImageManager::GetInstance()->FindImage(L"SkillIcon"));
	mQ_ButtonSkillIcon = new UIObject(225, WINSIZEY - 50, 42, 42, ImageManager::GetInstance()->FindImage(L"SkillIcon"));

	mBossHP = new UIObject(WINSIZEX / 2, 200, 200, 50, ImageManager::GetInstance()->FindImage(L"BossHP"));
	mBossHPBar = new UIObject(WINSIZEX / 2, 200, 180, 45, ImageManager::GetInstance()->FindImage(L"HPBard"));

	mRB_SkillNumber = new UIObject(mRB_ButtonSkillIcon->X, mRB_ButtonSkillIcon->Y, 25, 40, ImageManager::GetInstance()->FindImage(L"NumberWhite"));
	mQ_SkillNumber = new UIObject(mQ_ButtonSkillIcon->X, mQ_ButtonSkillIcon->Y, 25, 40, ImageManager::GetInstance()->FindImage(L"NumberWhite"));

	mPlayer = (Player*) ObjectManager::GetInstance()->FindObject("Player");

	//mEButton = new  UIObject(320, WINSIZEY - 50, 50, 50, ImageManager::GetInstance()->FindImage(L"SpecialSkillBox"));
}

void UserInterface::Update()
{
	if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
	{
		if (!ObjectManager::GetInstance()->GetInterfaceList().empty())
			ObjectManager::GetInstance()->PopInterface();

		UI_ESC* esc = new UI_ESC("ESC");
		esc->Init();
		ObjectManager::GetInstance()->AddInterface(esc);

	}
}

void UserInterface::Release()
{
}

void UserInterface::Render()
{
	Vector2 LB = mSkillIndexList.find(mPlayer->GetLB_ButtonSkill())->second;
	Vector2 RB = mSkillIndexList.find(mPlayer->GetRB_ButtonSkill())->second;
	Vector2 Space = mSkillIndexList.find(mPlayer->GetSpacebar_ButtonSkill())->second;
	Vector2 Q = mSkillIndexList.find(mPlayer->GetQ_ButtonSkill())->second;

	mStatus->Image->ScaleRenderFromLeft(mStatus->X, mStatus->Y, mStatus->SizeX  , mStatus->SizeY);
	mHPBar->Image->ScaleRenderFromLeft(mHPBar->X, mHPBar->Y, mHPBar->SizeX * mPlayer->GetHP()/500, mHPBar->SizeY); //0.8f에 플레이어체력 %넣으세요
	mMPBar->Image->ScaleRenderFromLeft(mMPBar->X, mMPBar->Y, mMPBar->SizeX * mPlayer->GetMp()/100, mMPBar->SizeY);

	mSkillBox1->Image->ScaleRender(mSkillBox1->X, mSkillBox1->Y, mSkillBox1->SizeX, mSkillBox1->SizeY);
	mSkillBox2->Image->ScaleRender(mSkillBox2->X, mSkillBox2->Y, mSkillBox2->SizeX, mSkillBox2->SizeY);
	mSkillBox3->Image->ScaleRender(mSkillBox3->X, mSkillBox3->Y, mSkillBox3->SizeX, mSkillBox3->SizeY);
	mSpecialSkillBox->Image->ScaleRender(mSpecialSkillBox->X, mSpecialSkillBox->Y, mSpecialSkillBox->SizeX, mSpecialSkillBox->SizeY);

	mMouseLButton->Image->ScaleRender(mMouseLButton->X, mMouseLButton->Y, mMouseLButton->SizeX, mMouseLButton->SizeY);
	mSpaceButton->Image->ScaleRender(mSpaceButton->X, mSpaceButton->Y, mSpaceButton->SizeX, mSpaceButton->SizeY);
	mMouseRButton->Image->ScaleRender(mMouseRButton->X, mMouseRButton->Y, mMouseRButton->SizeX, mMouseRButton->SizeY);
	mQButton->Image->ScaleRender(mQButton->X, mQButton->Y, mQButton->SizeX, mQButton->SizeY);

	mLB_ButtonSkillIcon->Image->ScaleFrameRender(mLB_ButtonSkillIcon->X, mLB_ButtonSkillIcon->Y, LB.X, LB.Y, mLB_ButtonSkillIcon->SizeX, mLB_ButtonSkillIcon->SizeY);
	mSpace_ButtonSkillIcon->Image->ScaleFrameRender(mSpace_ButtonSkillIcon->X, mSpace_ButtonSkillIcon->Y, Space.X, Space.Y, mSpace_ButtonSkillIcon->SizeX, mSpace_ButtonSkillIcon->SizeY);
	
	mRB_ButtonSkillIcon->Image->ScaleFrameRender(mRB_ButtonSkillIcon->X, mRB_ButtonSkillIcon->Y, RB.X, RB.Y, mRB_ButtonSkillIcon->SizeX, mRB_ButtonSkillIcon->SizeY);
	if (mPlayer->GetRB_ButtonSkillCool() > 0)
	{
		mRB_SkillNumber->Image->ScaleFrameRender(mRB_SkillNumber->X, mRB_SkillNumber->Y, (int)mPlayer->GetRB_ButtonSkillCool(), 0, mRB_SkillNumber->SizeX, mRB_SkillNumber->SizeY);
		/*wstring str = to_wstring((int)mPlayer->GetRB_ButtonSkillCool());
		D2DRenderer::GetInstance()->RenderTextField(mRB_ButtonSkillIcon->X, mRB_ButtonSkillIcon->Y,
			str, 15.f, mRB_ButtonSkillIcon->SizeX, mRB_ButtonSkillIcon->SizeY, D2D1::ColorF::Blue,
			DWRITE_TEXT_ALIGNMENT_CENTER);*/
	}
	mQ_ButtonSkillIcon->Image->ScaleFrameRender(mQ_ButtonSkillIcon->X, mQ_ButtonSkillIcon->Y, Q.X, Q.Y, mQ_ButtonSkillIcon->SizeX, mQ_ButtonSkillIcon->SizeY);
	if (mPlayer->GetQ_ButtonSkillCool() > 0)
	{
		mQ_SkillNumber->Image->ScaleFrameRender(mQ_SkillNumber->X, mQ_SkillNumber->Y, (int)mPlayer->GetQ_ButtonSkillCool(), 0, mQ_SkillNumber->SizeX, mQ_SkillNumber->SizeY);
		//wstring str = to_wstring((int)mPlayer->GetQ_ButtonSkillCool());
		//D2DRenderer::GetInstance()->RenderTextField(mQ_ButtonSkillIcon->X, mQ_ButtonSkillIcon->Y,
		//	str, 15.f, mQ_ButtonSkillIcon->SizeX, mQ_ButtonSkillIcon->SizeY, D2D1::ColorF::Blue,
		//	DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	//mSpecialSkillBox->Image->ScaleRender(mSpecialSkillBox->X, mSpecialSkillBox->Y, mSpecialSkillBox->SizeX, mSpecialSkillBox->SizeY);
}