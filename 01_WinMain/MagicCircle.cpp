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
}

void MagicCircle::Init()
{
	ImageManager::GetInstance()->LoadFromFile(L"MagicCircle", Resources(L"Skill/Circle.png"), 24, 1);
	mImage = ImageManager::GetInstance()->FindImage(L"MagicCircle");
	mSizeX = mImage->GetWidth() / 24;
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAngle = Random::GetInstance()->RandomInt(360);

	mCircleMakeAnimation = new Animation();
	mCircleMakeAnimation->InitFrameByStartEnd(0, 0, 23, 0, false);
	mCircleMakeAnimation->SetFrameUpdateTime(0.05f);

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
	
 	mTimeCount += Time::GetInstance()->DeltaTime();
	if (mCircleMakeAnimation->GetNowFrameX() == 23) {
		if (mTimeCount > 1) {
			MakeFlameList();
			mTimeCount = 0;
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
	mImage->SetAngle(mAngle * -(180 / PI));
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(mImage, mX, mY, mCircleMakeAnimation->GetNowFrameX(), mCircleMakeAnimation->GetNowFrameY());
	if(mMeteor != nullptr) mMeteor->Render();
	//if (mHitSpark != nullptr) mHitSpark->Render();
	for (Flame* flame : mFlameList) flame->Render();
}

void MagicCircle::MakeFlameList()
{
	float radius = mSizeX / 3;
	float endX = mX;
	float endY = mY - mSizeY ;
	for (int i = 1; i < 7; i++) {
		float x = mX + (cosf(PI / 3 * i) * radius);
		float y = mY - (sinf(PI / 3 * i) * radius);
		float angle = Math::GetAngle(x, y, endX, endY) * 180 / PI;
		Flame* flame = new Flame("Flame" + i, x, y, angle);
		flame->Init();
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
