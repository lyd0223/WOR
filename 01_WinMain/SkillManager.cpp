#include "pch.h"
#include "SkillManager.h"
#include "GameObject.h"
#include "MagicCircle.h"
#include "FireBall.h"

void SkillManager::Init()
{
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, new FireBall("FireBall"));
	//mSkillList.insert(make_pair("FireBall", ObjectManager::GetInstance()->FindObject("FireBall")));
}

void SkillManager::Release()
{
}
void SkillManager::Update()
{
}


void SkillManager::Render()
{
}

void SkillManager::FlameSkill(const string& name, float x, float y, float angle)
{
	MagicCircle* magicCircle = new MagicCircle(name, x, y, CastingSkill::Burn);
	magicCircle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, magicCircle);
}

void SkillManager::FireBallSkill(const string& name, float x, float y, float angle)
{
	FireBall* fireBall = new FireBall(name, x, y, angle);
	fireBall->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, fireBall);
}

void SkillManager::MeteorSkill(float x, float y, float angle)
{
}

GameObject * SkillManager::FindSkill(const string key)
{
	//SkillIter iter = mSkillList.;
	//if (iter != mSkillList.end()) {
	//	return iter->second;
	//}

	return nullptr;
}
