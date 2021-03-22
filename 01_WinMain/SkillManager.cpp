#include "pch.h"
#include "SkillManager.h"
#include "GameObject.h"
#include "Effect_MagicCircle.h"
#include "Skill_FireBall.h"
#include "Skill_WindSlash.h"
#include "Skill_Flame.h"
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
		SkillObject* skill = (SkillObject*) skillList[i];
		if (skill->GetSkillType() == SkillType::Throw) 
		{
			D2D1_RECT_F temp;
			int index = (skill->GetRect().right - skill->GetRect().left) / TileSize + 1;
			
			// 몬스터 충돌
			for (int j = 0; j < monsterList.size(); j++) 
			{
				if (IntersectRect(temp, &skillList[i]->GetRect(), &monsterList[j]->GetRect())) 
				{
					skill->SetIsDestroy(true);
					break;
				}
			}
			
			// 스킬 벽 충돌 했을때
			for (int y = (skill->GetY() / TileSize) - index; y < (skill->GetY() / TileSize) + index; y++)
			{
				for (int x = (skill->GetX() / TileSize) - index; x < (skill->GetX() / TileSize) + index; x++)
				{
					TileMap* tileMap = (TileMap*)tileList[0];
					Tile* tile = (Tile*)tileMap->GetTileList(x, y);

					if (tile->GetType() == Type::Wall && IntersectRect(temp, &skill->GetRect(), &tile->GetRect()))
					{
						skill->SetIsDestroy(true);
						break;
					}
				}
			}
		}
	}
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