#include "pch.h"
#include "Scene_Loading.h"
#include "Image.h"


void Scene_Loading::Func()
{
	mIsThread = true;

	this_thread::sleep_for(chrono::milliseconds(1000));

	function<void(void)> func = mLoadList[mLoadIndex];
	func();

	mLoadIndex++;
	mCharacterX += 200;
	mStr += ("\n" + mStr2);
	if (mLoadIndex == 1)
	{
		mStr2 = "Load Image & Sound";
	}

	if (mLoadIndex == 2)
	{
		mStr2 = "Create Random Map";
	}
	if (mLoadIndex == 3)
	{
		mStr2 = "Put Roads Between the Rooms";
	}
	if (mLoadIndex == 4)
	{
		mStr2 = "Are You Ready?";
	}

	mTextY += 10;

	mIsThread = false;
}
void Scene_Loading::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}


void Scene_Loading::Init()
{
	mTime = 0.f;
	mLoadIndex = 0;
	mCharacterX = 50;
	mTextY = WINSIZEY - 250;
}

void Scene_Loading::Release()
{
}

void Scene_Loading::Update()
{
	//정규분포 mt19937 vs 그냥 랜덤 시간비교를위한 타임체크.
	mClock = clock();


	if (mLoadIndex >= mLoadList.size())
	{
		SceneManager::GetInstance()->LoadScene(L"Field");
		return;
	}

	float deltaTime = Time::GetInstance()->DeltaTime();
	mTime += deltaTime;
	if (mTime >= 0.5f)
	{
		mTime = 0.f;
		mTemp++;
		if (mTemp >= 5)
		{
			mTemp = 0;
		}
	}

	if (mIsThread == false)
	{
		if(mThread.joinable())
			mThread.join();
		mThread = thread(&Scene_Loading::Func, this);
	}

	if (mLoadIndex==0)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void Scene_Loading::Render()
{
	ImageManager::GetInstance()->FindImage(L"Loading")->Render(WINSIZEX/2, WINSIZEY/2);
	ImageManager::GetInstance()->FindImage(L"LoadingCharacter")->Render(mCharacterX, 200);

	string str = "";
	for (int i = 0; i < mTemp; i++)
	{
		str += ".";
	}
	string tempStr = mStr2 + str;
	
	wstring wstr,wstr2; 
	wstr.assign(mStr.begin(), mStr.end());
	wstr2.assign(tempStr.begin(), tempStr.end());
	D2DRenderer::GetInstance()->RenderText(
		WINSIZEX / 2 - 100,
		mTextY,
		wstr,
		COLORREF(RGB(255, 255, 255)),
		0.5f,
		20.f,
		DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING
	);
	D2DRenderer::GetInstance()->RenderText(
		WINSIZEX / 2 - 100,
		mTextY+70,
		wstr2,
		COLORREF(RGB(255, 255, 255)),
		1.0f,
		20.f,
		DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING
	);
	
	//시간 그려주기.
	string str2 = to_string(mClock);
	wstring wstr3;
	wstr3.assign(str2.begin(), str2.end());
	D2DRenderer::GetInstance()->RenderText(
		WINSIZEX - 100,
		WINSIZEY - 100,
		wstr3,
		COLORREF(RGB(0, 255, 0)),
		1.0f,
		20.f,
		DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING
	);

}
