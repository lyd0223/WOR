#include "pch.h"
#include "SkillManager.h"
#include "GameObject.h"
#include "MagicCircle.h"
#include "FireBall.h"
#include "Flame.h"

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

void SkillManager::MeteorSkill(const string& name, float x, float y)
{
	MagicCircle* magicCircle = new MagicCircle(name, x, y, CastingSkill::Meteor);
	magicCircle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, magicCircle);
}

void SkillManager::KickFlame(const string & name, float x, float y, float angle)
{
	Flame* flame = new Flame(name, x, y, angle);
	flame->Init();
	flame->SetIsMove();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, flame);
}

vector<GameObject*> SkillManager::FindSkillList(const string key)
{
	vector<GameObject*> result;

	SkillIter iter = mSkillList.find(key);

	if (iter != mSkillList.end()) {
		
	}

	return result;
}