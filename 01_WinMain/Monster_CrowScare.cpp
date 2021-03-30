#include "pch.h"
#include "Image.h"
#include"Camera.h"
#include"Animation.h"
#include"Player.h"
#include"Monster_CrowScare.h"
#include "Tile.h"
#include "TileMap.h"

Monster_CrowScare::Monster_CrowScare(const string& name, float x, float y)
	:MonsterObject(name)
{
	wstring str;
	str.assign(name.begin(),name.end());
	mImage = ImageManager::GetInstance()->FindImage(str);
	mName = name;
	mX = x;
	mY = y;
	//mIsActive = false;aaaa
}

void Monster_CrowScare::Init()
{
	mSizeX = mImage->GetFrameSize().__typeToGetX() * 4 - 120;
	mSizeY = mImage->GetFrameSize().__typeToGetY() * 4 - 200;
	mRect = RectMakeCenter(mX, mY-20, mSizeX, mSizeY);
	mMonsterType = MonsterType::Normal;
}

void Monster_CrowScare::Release()
{
	
}

void Monster_CrowScare::Update()
{
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
		

		mRect = RectMakeCenter(mX, mY-20, mSizeX, mSizeY);
	

		// ³Ë¹é
		if (mSkillHitPower > 0)
		{
			mX += cosf(mSkillHitAngle) * mSkillHitPower;
			mY += -sinf(mSkillHitAngle) * mSkillHitPower;
			mSkillHitPower -= 0.2f;
		}
	}
}

void Monster_CrowScare::Render()
{
	if (mIsActive == false)
	{
		return;
	}
	mImage->SetScale(1.5f);
	D2D1_RECT_F cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (cameraRect.right > mRect.left && cameraRect.left < mRect.right && cameraRect.bottom > mRect.top && cameraRect.top < mRect.bottom)
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(mRect);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(mMovingRect);
		CameraManager::GetInstance()->GetMainCamera()->FrameRenderFromBottom(mImage, mX, mY + 20, 0, 0);
	}

	//string str = to_string(Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY())/ TileSize);
	//wstring wstr;
	//wstr.assign(str.begin(), str.end());
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX/2, WINSIZEY / 2, wstr, 30.f);

}

