#include "pch.h"
#include "MagicCircle.h"
#include "Image.h"
#include "Animation.h"
#include "Meteor.h"
#include "Flame.h"
#include "Camera.h"

MagicCircle::MagicCircle(const string & name, float x, float y, CastingSkill castingSkill)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mCastingSkill = castingSkill;
	mIsActive = true;
}

void MagicCircle::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MagicCircle", Resources(L"Skill/Circle.png"), 25, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MagicCircle");
	mSizeX = mImage->GetWidth() / 24;
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAngle = Random::GetInstance()->RandomInt(360);

	mCircleMakeAnimation = new Animation();
	mCircleMakeAnimation->InitFrameByStartEnd(0, 0, 23, 0, false);
	mCircleMakeAnimation->SetFrameUpdateTime(0.02f);

	mCircleMakeAnimation->Play();
}

void MagicCircle::Release()
{
	SafeDelete(mCircleMakeAnimation)
}

void MagicCircle::Update()
{
	mCircleMakeAnimation->Update();
	mFrameIndexX = mCircleMakeAnimation->GetNowFrameX();
	if (mCircleMakeAnimation->GetNowFrameX() == 15 && mCastingSkill == CastingSkill::Meteor) {
		mMeteor = new Meteor("Meteor", mX, mY);
		mMeteor->Init();
	}
	
 	mTimeCount1 += Time::GetInstance()->DeltaTime();
	mTimeCount2 += Time::GetInstance()->DeltaTime();
	if (mCircleMakeAnimation->GetNowFrameX() == 23) {
		if (mTimeCount1 > 0.5) {
			MakeFlameList();
			mTimeCount1 = 0;
		}

		if (mTimeCount2 > 2) {
			mIsActive = false;
			//mIsDestroy = true;
			mTimeCount2 = 0;
		}
	}

	/*if ((mCircleMakeAnimation->GetNowFrameX() == 23 && mMeteor == nullptr)) {
		mHitSpark = new HitSpark("HitSpark", mX, mY, 0);
		mHitSpark->Init();
		mIsDestroy = true;
	}*/

	if (mMeteor != nullptr) {
		mMeteor->Update();
		if (mX < mMeteor->GetX()) {
			mMeteor->Release();
			SafeDelete(mMeteor)
		} 
	}

	for (int i = 0; i < mFlameList.size(); i++) {
		mFlameList[i]->Update();
		if (mFlameList[i]->GetIsDestroy()) {
			mFlameList[i]->Release();
			SafeDelete(mFlameList[i]);
			mFlameList.erase(mFlameList.begin() + i);
			i--;
		}
	}
}

void MagicCircle::Render()
{
	if (mIsActive) {
		mImage->SetScale(1.5f);
		mImage->SetAngle(mAngle * -(180 / PI));
		CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCircleMakeAnimation->GetNowFrameX(), mCircleMakeAnimation->GetNowFrameY());
		for (Flame* flame : mFlameList) flame->Render();
	}
	if(mMeteor != nullptr) mMeteor->Render();
	//if (mHitSpark != nullptr) mHitSpark->Render();
}

void MagicCircle::MakeFlameList()
{
	float radius = mSizeX / 3;
	float endX = mX;
	float endY = mY - mSizeY ;
	for (int i = 1; i < 14; i++) {
		float x = mX + (cosf(PI / 6 * i) * radius);
		float y = mY - (sinf(PI / 6 * i) * radius);
		float angle = Math::GetAngle(x, y, endX, endY) * 180 / PI;
		Flame* flame = new Flame("Flame" + i, x, y, angle);
		flame->Init();
		flame->SetIsMove();
		flame->SetEndPositionX(endX);
		flame->SetEndPositionY(endY);
		mFlameList.push_back(flame);
	}
	Flame* flame = new Flame("Flame", mX, mY, 0);
	flame->Init();
	flame->SetEndPositionX(endX);
	flame->SetEndPositionY(endY);
	mFlameList.push_back(flame);
}
