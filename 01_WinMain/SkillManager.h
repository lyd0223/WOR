#pragma once
#include "SkillObject.h"

class SkillManager
{
	Singleton(SkillManager)

private:
	map<SkillElement, vector<SkillObject*>> mSkillList;

	bool mIsUp;

	float mFrameCount;
public:
	SkillManager();

	void AddSkillList(SkillElement element, SkillObject* skillObject);
	void SkillCasting(const string& name, float x, float y, float angle);
	SkillObject* MakeSkillClass(const string& name, float x, float y, float angle);

	void Update();

	void DragonArcSkill(const string& name, float x, float y, float angle, bool isUp);
	void FlameSkill(const string& name, float x, float y, float angle);
	void FireBallSkill(const string& name, float x, float y, float angle, int delay);
	void MeteorSkill(const string& name, float x, float y);
	void KickFlame(const string& name, float x, float y, float angle, float endX, float endY);
	void WindSlashSkill(const string& name, float x, float y, float angle);
	void IceSpearSkill(const string& name, float x, float y, float angle);
	void SummonIceSpearSkill(const string& name, float x, float y, float angle);
	void IceSwordSkill(const string& name, float x, float y, float angle);
	void MonsterBigSlashSkill(const string& name, float x, float y, float angle);
	void WaterBallSkill(const string& name, float x, float y, float angle);
	void MonsterSmallSlashSkill(const string& name, float x, float y, float angle);
	void SpearSkill(const string& name, float x, float y, float angle);
	void SpearWaveSkill(const string& name, float x, float y, float angle);
	void MonsterMiddleSlashSkill(const string& name, float x, float y, float angle);
	void ThunderBolt(const string& name, float x, float y, float angle);

	map<SkillElement, vector<SkillObject*>> GetSkillList() { return mSkillList; }
	vector<SkillObject*> GetSkillElementList(SkillElement element) { return mSkillList.find(element)->second; }
	SkillObject* FindSkill(string name);
};