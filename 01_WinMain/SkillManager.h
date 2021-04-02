#pragma once
#include "SkillObject.h"

class SkillManager
{
	Singleton(SkillManager)

private:
	map<SkillElement, vector<SkillObject*>> mSkillList;

	string mPlayerLBSkill;
	string mPlayerRBSkill;
	string mPlayerSpaceSkill;
	string mPlayerQSkill;
	int mPlayerSkillStack;

	bool mIsUp;

	float mFrameCount;
public:
	SkillManager();

	void AddSkillList(SkillElement element, SkillObject* skillObject);
	void SkillCasting(const string& name, float x, float y, float angle);
	void SkillCasting(const string& name, float x, float y, float angle, bool b);
	SkillObject* MakeSkillClass(const string& name, float x, float y, float angle);
	SkillObject* MakeSkillClass(const string& name, float x, float y, float angle, bool b);

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
	void WaterBallSkill(const string& name, float x, float y, float angle, float temp);
	void MonsterSmallSlashSkill(const string& name, float x, float y, float angle);
	void SpearSkill(const string& name, float x, float y, float angle);
	void SpearWaveSkill(const string& name, float x, float y, float angle);
	void MonsterMiddleSlashSkill(const string& name, float x, float y, float angle);
	void ThunderBolt(const string& name, float x, float y, float angle);
	void LightRing(const string& name, float x, float y, float angle);

	void SetPlayerLBSkill(string skill) { mPlayerLBSkill = skill; }
	string GetPlayerLBSkill() { return mPlayerLBSkill; }
	void SetPlayerSpaceSkill(string skill) { mPlayerSpaceSkill = skill; }
	string GetPlayerSpaceSkill() { return mPlayerSpaceSkill; }
	void SetPlayerRBSkill(string skill) { mPlayerRBSkill = skill; }
	string GetPlayerRBSkill() { return mPlayerRBSkill; }
	void SetPlayerQSkill(string skill) { mPlayerQSkill = skill; }
	string GetPlayerQSkill() { return mPlayerQSkill; }
	void SetPlayerSkillStack(int stack) { mPlayerSkillStack = stack; }
	int GetPlayerSkillStack() { return mPlayerSkillStack; }

	map<SkillElement, vector<SkillObject*>> GetSkillList() { return mSkillList; }
	vector<SkillObject*> GetSkillElementList(SkillElement element) { return mSkillList.find(element)->second; }
	SkillObject* FindSkill(string name);
};