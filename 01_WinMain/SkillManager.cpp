#include "pch.h"
#include "SkillManager.h"
#include "GameObject.h"
#include "Effect_MagicCircle.h"
#include "Skill_FireBall.h"
#include"WindSlash.h"
#include "Skill_Flame.h"

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
	mFrameCount += Time::GetInstance()->DeltaTime();

	//if (mFrameCount > 4) {
	//	vector<GameObject*> temp = ObjectManager::GetInstance()->FindObjects("Flame");
	//	for (int i = 0; i < temp.size(); i++) {
	//		temp[i]->SetIsDestroy(true);
	//	}
	//	mFrameCount = 0;
	//}
}


void SkillManager::Render()
{

}



void SkillManager::FlameSkill(const string& name, float x, float y, float angle)
{
	Effect_MagicCircle* magicCircle = new Effect_MagicCircle(name, x, y, CastingSkill::Burn);
	magicCircle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, magicCircle);
}

void SkillManager::FireBallSkill(const string& name, float x, float y, float angle, int delay)
{
	Skill_FireBall* fireBall = new Skill_FireBall(name, x, y, angle);
	fireBall->Init();
	fireBall->SetDelay(delay);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, fireBall);
}

void SkillManager::MeteorSkill(const string& name, float x, float y)
{
	Effect_MagicCircle* magicCircle = new Effect_MagicCircle(name, x, y, CastingSkill::Meteor);
	magicCircle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, magicCircle);
}

void SkillManager::KickFlame(const string & name, float x, float y, float angle, float endX, float endY)
{
	Skill_Flame* flame = new Skill_Flame(name, x, y, angle);
	flame->Init();
	flame->SetEndPositionX(endX);
	flame->SetEndPositionY(endY);
	flame->SetIsMove();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, flame);
}

void SkillManager::WindSlashSkill(const string& name, float x, float y, float angle)
{
	WindSlash* windSlash = new WindSlash(name, x, y, angle);
	windSlash->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, windSlash);
}

vector<GameObject*> SkillManager::FindSkillList(const string key)
{
	vector<GameObject*> result;

	SkillIter iter = mSkillList.find(key);

	if (iter != mSkillList.end()) {
		
	}

	return result;
}