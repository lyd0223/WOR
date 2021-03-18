#pragma once

class SkillManager
{
	Singleton(SkillManager)

private:
	typedef map<string, vector<class GameObject*>>::iterator SkillIter;
	map<string, vector<class GameObject*>> mSkillList;

	float mFrameCount;
public:
	void Init();
	void Release();
	void Update();
	void Render();

	void FlameSkill(const string& name, float x, float y, float angle);
	void FireBallSkill(const string& name, float x, float y, float angle, int delay);
	void MeteorSkill(const string& name, float x, float y);
	void KickFlame(const string& name, float x, float y, float angle, float endX, float endY);

	map<string, vector<class GameObject*>> GetSkillList() { return mSkillList; }
	class vector<GameObject*> FindSkillList(const string key);
};