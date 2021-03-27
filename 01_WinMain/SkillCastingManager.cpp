#include "pch.h"
#include "SkillCastingManager.h"
#include "Skill_WindSlash.h"
#include "Skill_FireBall.h"
#include "Skill_DragonArc.h"
#include "Skill_IceSpear.h"

void SkillCastingManager::Init()
{
	mSkillList.insert(make_pair("WindSlash", new Skill_WindSlash("WindSlash", 0, 0, 0)));
	mSkillList.insert(make_pair("FireBall", new Skill_FireBall("FireBall", 0, 0, 0)));
	mSkillList.insert(make_pair("DragonArc", new Skill_DragonArc("DragonArc", 0, 0, 0, false)));
	mSkillList.insert(make_pair("IceSpear", new Skill_IceSpear("IceSpear", 0, 0, 0)));
}

void SkillCastingManager::CastingSkill(const string & name, float x, float y, float angle)
{
	SkillObject* skill = MakeSkillClass(name, x, y, angle);

	skill->Init();
	
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, skill);
}

SkillObject* SkillCastingManager::MakeSkillClass(const string & name, float x, float y, float angle)
{
	!mIsUp;

	if (name == "IceSpear")
	{
		Skill_IceSpear* iceSpear = new Skill_IceSpear(name, x, y, angle);
		return iceSpear;
	}
	if (name == "FireBall")
	{
		Skill_FireBall* fireBall = new Skill_FireBall(name, x, y, angle);
		return fireBall;
	}
	if (name == "DragonArc")
	{
		Skill_DragonArc* dragonArc = new Skill_DragonArc(name, x, y, angle, mIsUp);
		return dragonArc;
	}
	if (name == "WindSlash")
	{
		Skill_WindSlash* windSlash = new Skill_WindSlash(name, x, y, angle);
		return windSlash;
	}

	return nullptr;
}
