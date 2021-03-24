#include "pch.h"
#include "SkillManager.h"
#include "GameObject.h"
#include "MonsterObject.h"
#include "Effect_MagicCircle.h"
#include "Effect_FireParticle.h"
#include "Effect_HitSpark.h"
#include "Skill_FireBall.h"
#include "Skill_WindSlash.h"
#include "Skill_Flame.h"
#include "Skill_IceSpear.h"
#include "Skill_SummonIceSpear.h"
#include "Skill_IceSword.h"
#include "Skill_MonsterBigSlash.h"
#include "Tile.h"
#include "TileMap.h"

#define TileSize 64

void SkillManager::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();

	vector<GameObject*> skillList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Skill);
	vector<GameObject*> tileList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Tile);
	vector<GameObject*> monsterList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);

	for (int i = 0; i < skillList.size(); i++) 
	{
		SkillObject* skill = (SkillObject*)skillList[i];
		D2D1_RECT_F temp;
		D2D1_RECT_F skillrc = skill->GetRect();
		
		int index = (skill->GetRect().right - skill->GetRect().left) / TileSize + 1;
		int skillX = skill->GetX();
		int skillY = skill->GetY();

		// 스킬 to 벽 충돌 했을때
		for (int y = (skill->GetY() / TileSize) - index; y < (skill->GetY() / TileSize) + index; y++)
		{
			for (int x = (skill->GetX() / TileSize) - index; x < (skill->GetX() / TileSize) + index; x++)
			{
				TileMap* tileMap = (TileMap*)tileList[0];
				Tile* tile = (Tile*)tileMap->GetTileList(x, y);
				D2D1_RECT_F skillrc = skill->GetRect();
				D2D1_RECT_F tilerc = tile->GetRect();
				if (tile->GetType() == Type::Wall && IntersectRect(temp, &skillrc, &tilerc))
				{
					if (skill->GetSkillElement() == SkillElement::Fire)
					{
						ParticleManager::GetInstance()->MakeFireParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
					}

					if (skill->GetName() == "IceSpear")
					{
						ParticleManager::GetInstance()->MakeIceBreakParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
					}

					skill->SetIsDestroy(true);
					break;
				}
			}
		}

		// 스킬 to 몬스터 충돌
		for (int j = 0; j < monsterList.size(); j++)
		{
			MonsterObject* monster = (MonsterObject*)monsterList[j];
			D2D1_RECT_F monsterrc = monsterList[j]->GetRect();

			// 근접 스킬
			if (skill->GetSkillType() == SkillType::Melee)
			{
				bool isCollision = false;
				if (IntersectRect(temp, &skillrc, &monsterrc) && 
					(skill->GetIsCollision() == false && monster->GetIsCollision() == false))
				{
					monster->SetIsCollision(true);
					ParticleManager::GetInstance()->MakeHitSparkParticle(temp.left, temp.top);
				}
			}

			// 던지는 스킬
			if (skill->GetSkillType() == SkillType::Throw) 
			{
				if (IntersectRect(temp, &skillrc, &monsterrc))
				{

					if (skill->GetSkillElement() == SkillElement::Fire)
					{
						ParticleManager::GetInstance()->MakeFireParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
					}

					if (skill->GetName() == "IceSpear")
					{
						ParticleManager::GetInstance()->MakeIceBreakParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
					}

					skill->SetIsDestroy(true);
					break;
				}
			}
		}
	}

	// 몬스터 맵 충돌 처리
	//for (int i = 0; i < monsterList.size(); i++)
	//{
	//	for (int j = 0; j < tileList.size(); j++)
	//	{
	//
	//	}
	//}
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
	Skill_WindSlash* windSlash = new Skill_WindSlash(name, x, y, angle);
	windSlash->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, windSlash);
}

void SkillManager::IceSpearSkill(const string& name, float x, float y, float angle)
{
	Skill_IceSpear* iceSpear = new Skill_IceSpear(name, x, y, angle);
	iceSpear->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, iceSpear);
}

void SkillManager::SummonIceSpearSkill(const string& name, float x, float y, float angle)
{
	Skill_SummonIceSpear* summonIceSpear = new Skill_SummonIceSpear(name, x, y, angle);
	summonIceSpear->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, summonIceSpear);
}

void SkillManager::IceSwordSkill(const string& name, float x, float y, float angle)
{
	Skill_IceSword* iceSword = new Skill_IceSword(name, x, y, angle);
	iceSword->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, iceSword);
}

void SkillManager::MonsterBigSlashSkill(const string& name, float x, float y, float angle)
{
	Skill_MonsterBigSlash* monsterBigSlash = new Skill_MonsterBigSlash(name, x, y, angle);
	monsterBigSlash->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, monsterBigSlash);
}

//vector<GameObject*> SkillManager::FindSkillList(const string key)
//{
//	vector<GameObject*> result;
//
//	SkillIter iter = mSkillList.find(key);
//
//	if (iter != mSkillList.end()) {
//		
//	}
//
//	return result;
//}