#pragma once

class SkillManager
{
	Singleton(SkillManager)

private:
	//typedef map<SkillType, vector<class GameObject*>>::iterator SkillIter;
	//map<SkillType, vector<class GameObject*>> mSkillList;

	float mFrameCount;
public:
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

	//map<string, vector<class GameObject*>> GetSkillList() { return mSkillList; }
	//class vector<GameObject*> FindSkillList(const string key);
};