#pragma once

class SkillObject;
class SkillCastingManager
{
	Singleton(SkillCastingManager)

	map<string, SkillObject*> mSkillList;

	bool mIsUp;
public:
	void Init();
	void CastingSkill(const string& name, float x, float y, float angle);
	SkillObject* MakeSkillClass(const string& name, float x, float y, float angle);

	SkillObject* FindSkill(const string name) { return mSkillList.find(name)->second; };
	map<string, SkillObject*> GetSkillList() { return mSkillList; }

};

