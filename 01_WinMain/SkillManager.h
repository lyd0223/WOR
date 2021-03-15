#pragma once

class SkillManager
{
	Singleton(SkillManager)

private:
	typedef vector<class GameObject*>::iterator SkillIter;
	vector<class GameObject*> mSkillList;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	void FlameSkill(const string& name, float x, float y, float angle);
	void FireBallSkill(const string& name, float x, float y, float angle);
	void MeteorSkill(float x, float y, float angle);

	vector<GameObject*> GetSkillList() { return mSkillList; }
	class GameObject* FindSkill(const string key);
};