#include "pch.h"
#include "SceneManager.h"

#include "Scene.h"
#include "LoadingScene.h"

SceneManager::SceneManager()
	:mCurrentScene(nullptr),mLoadingThread(nullptr),mTargetScene(nullptr),mLoadingScene(nullptr),
mIsLoadingEnd(false){}

SceneManager::~SceneManager()
{
	SceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		//iter->second->Release();
		SafeDelete(iter->second);
	}
}

void SceneManager::Update()
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Update();
}

void SceneManager::Render()
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Render();
}

void SceneManager::AddScene(const wstring& sceneName,Scene * scene)
{
	SceneIter iter = mSceneList.find(sceneName);
	//이미 해당이름의 데이터가 맵안에 있다
	if (iter != mSceneList.end())
		return;

	mSceneList.insert(make_pair(sceneName, scene));
}

void SceneManager::LoadScene(const wstring & sceneName)
{
	SceneIter iter = mSceneList.find(sceneName);
	//못찾았으면 return (돌아가라)
	if (iter == mSceneList.end())
		return;

	if (mCurrentScene == iter->second)
		return;
	
	Scene* targetScene = iter->second;

	if (mCurrentScene)
		mCurrentScene->Release();

	if(!targetScene->GetIsAlreadyInit())
		targetScene->Init();

	mCurrentScene = targetScene;
}

void SceneManager::DeleteScene(const wstring& sceneName)
{
	SceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		if (iter == mSceneList.end())
		{
			break;
		}
		//iter->second->Release();
		if (iter->first == sceneName)
		{
			SafeDelete(iter->second);
			mSceneList.erase(sceneName);
		}
	}
}

Scene* SceneManager::FindScene(const wstring& sceneName)
{
	SceneIter iter = mSceneList.find(sceneName);
	//못찾았으면 return (돌아가라)
	if (iter == mSceneList.end())
		return nullptr;

	if (mCurrentScene == iter->second)
		return nullptr;

	Scene* targetScene = iter->second;


	return targetScene;
}


//잘 개조해서 써봐. 잘 모르고 괜히 쓰면 면접때 털림
void SceneManager::LoadScene(const wstring & targetSceneName, const wstring & loadingSceneName)
{
	SceneIter iter = mSceneList.find(targetSceneName);
	if (iter != mSceneList.end())
		mTargetScene = iter->second;

	iter = mSceneList.find(loadingSceneName);
	if (iter != mSceneList.end())
		mLoadingScene = iter->second;

	if (mTargetScene == nullptr || mLoadingScene == nullptr ||
		mTargetScene == mCurrentScene || mLoadingScene == mCurrentScene)
	{
		mTargetScene = nullptr;
		mLoadingScene = nullptr;
		return;
	}

	function<void(void)> threadFunc = bind(&SceneManager::LoadingThread, this);
	//스레드는 메모리 할당해주는 순간부터 바로 돌기 시작한다.
	mLoadingThread = new thread(threadFunc);
}

void SceneManager::LoadingThread()
{
	//데드락 주의!! 찾아봐!

	Scene* prevScene = mCurrentScene;
	
	mCurrentScene = mLoadingScene;
	mCurrentScene->Init();

	prevScene->Release();

	mTargetScene->Init();
	
	mCurrentScene = mTargetScene;


	mLoadingScene->Release();

	mTargetScene = nullptr;
	mLoadingScene = nullptr;
	mIsLoadingEnd = true;
}
