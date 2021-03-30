#include "pch.h"
#include "Effect_Teleport.h"
#include "Animation.h"
#include "Camera.h"
#include "Image.h"
#include "Scene_House.h"
#include "Scene_Field.h"
#include "Scene_Tutorial.h"
#include "Scene_Boss.h"

Effect_Teleport::Effect_Teleport(float x, float y, bool isSceneChange, wstring nowSceneName, wstring changeSceneName)
{
	mName = "TeleportEffect";
	mImage = ImageManager::GetInstance()->FindImage(L"TeleportEffect");
	mX = x;
	mY = y;
	mIsSceneChange = isSceneChange;
	mRect = RectMakeCenter(mX, mY, 100, 100);
	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mAnimation->SetIsLoop(false);

	mAnimation->SetFrameUpdateTime(0.05f);
	mAnimation->Play();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, this);
	mChangeSceneName = changeSceneName;
	mNowSceneName = nowSceneName;
	
	SoundPlayer::GetInstance()->Play(L"Teleport", 1.f);
}

void Effect_Teleport::Init()
{
}

void Effect_Teleport::Release()
{
	delete(mAnimation);
}

void Effect_Teleport::Update()
{
	mAnimation->Update();
	
	if (mAnimation->GetCurrentFrameIndex() == mAnimation->GetMaxIndex()-1)
	{
		mIsDestroy = true;
		if (mIsSceneChange)
		{
			
			SceneManager::GetInstance()->LoadScene(mChangeSceneName);
			SceneManager::GetInstance()->DeleteScene(mNowSceneName);
			if(mNowSceneName == L"House")
				SceneManager::GetInstance()->AddScene(mNowSceneName, new Scene_House);
			else if (mNowSceneName == L"Tutorial")
				SceneManager::GetInstance()->AddScene(mNowSceneName, new Scene_Tutorial);
			else if (mNowSceneName == L"Boss")
				SceneManager::GetInstance()->AddScene(mNowSceneName, new Scene_Boss);
			else if (mNowSceneName == L"Field")
				SceneManager::GetInstance()->AddScene(mNowSceneName, new Scene_Field);
			return;
		}
	}
}

void Effect_Teleport::Render()
{
	mImage->SetScale(1.5f);
	CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY,mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
