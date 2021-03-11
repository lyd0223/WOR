#include "pch.h"
#include "GameEventManager.h"

#include "GameEvent.h"

GameEventManager::GameEventManager()
{
}

GameEventManager::~GameEventManager()
{
	RemoveAllEvent();
}

void GameEventManager::RemoveAllEvent()
{
	for (int i = 0; i < mEventQueue.size(); ++i)
	{
		SafeDelete(mEventQueue.front());
		mEventQueue.pop();
	}
}

void GameEventManager::Update()
{
	if (mEventQueue.size() == 0)
		return;

	bool isEnd = mEventQueue.front()->Update();
	if (isEnd == true)
	{
		SafeDelete(mEventQueue.front());
		mEventQueue.pop();

		if (mEventQueue.size() != 0)
		{
			mEventQueue.front()->Start();
		}
	}
}

void GameEventManager::PushEvent(IEvent * event)
{
	if (mEventQueue.size() == 0)
	{
		event->Start();
	}
	mEventQueue.push(event);
}
