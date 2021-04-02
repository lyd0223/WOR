#pragma once
class Storage
{
	Singleton(Storage)

	float mGameTime;
	int mMonsterDeathCount;
public:

	float GetGameTime() { return mGameTime; }
	void SetGameTime(float time) { mGameTime = time; }
	int GetMonsterDeathCount() { return mMonsterDeathCount; }
	void SetMonsterDeathCount(int count) { mMonsterDeathCount = count; }
};

