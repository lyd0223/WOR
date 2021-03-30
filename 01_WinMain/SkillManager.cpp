#include "pch.h"
#include "SkillManager.h"
#include "GameObject.h"
#include "MonsterObject.h"
#include "Player.h"

#include "Effect_MagicCircle.h"
#include "Effect_FireParticle.h"
#include "Effect_HitSpark.h"

#include "Skill_FireBall.h"
#include "Skill_DragonArc.h"
#include "Skill_WindSlash.h"
#include "Skill_Flame.h"
#include "Skill_IceSpear.h"
#include "Skill_SummonIceSpear.h"
#include "Skill_IceSword.h"
#include "Skill_MonsterBigSlash.h"
#include "Skill_WaterBall.h"
#include "Skill_MonsterSmallSlash.h"
#include "Skill_Spear.h"
#include "Skill_SpearWave.h"
#include "Skill_MonsterMiddleSlash.h"
#include "Skill_ThunderBolt.h"
#include "Skill_Meteor.h"
#include "Skill_WaterBall.h"

#include "MouseTracker.h"
#include "Tile.h"
#include "TileMap.h"
#include "Camera.h"

#define TileSize 48

SkillManager::SkillManager()
{
	for (int i = 0; i < (int)SkillElement::End; ++i)
	{
		vector<SkillObject*> emptyVector;
		mSkillList.insert(make_pair((SkillElement)i, emptyVector));
	}

	AddSkillList(SkillElement::Fire, new Skill_FireBall("FireBall", 0, 0, 0));
	AddSkillList(SkillElement::Fire, new Skill_DragonArc("DragonArc", 0, 0, 0, false));
	AddSkillList(SkillElement::Fire, new Skill_Meteor("Meteor", 0, 0));
	AddSkillList(SkillElement::Wind, new Skill_WindSlash("WindSlash", 0, 0, 0));
	AddSkillList(SkillElement::Water, new Skill_IceSpear("IceSpear", 0, 0, 0));
	AddSkillList(SkillElement::Water, new Skill_WaterBall("WaterBall", 0, 0, 0));
	AddSkillList(SkillElement::Elect, new Skill_ThunderBolt("ThunderBolt", 0, 0, 0));
}

void SkillManager::AddSkillList(SkillElement element, SkillObject * skillObject)
{
	mSkillList[element].push_back(skillObject);
}

void SkillManager::SkillCasting(const string & name, float x, float y, float angle)
{
	SkillObject* skill = MakeSkillClass(name, x, y, angle);

	skill->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, skill);
}

SkillObject * SkillManager::MakeSkillClass(const string & name, float x, float y, float angle)
{
	!mIsUp;

	if (name == "IceSpear")
	{
		
		SoundPlayer::GetInstance()->Play(L"IceSpearSound", 1.f);
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

		SoundPlayer::GetInstance()->Play(L"WindSlashSound", 1.f);
		Skill_WindSlash* windSlash = new Skill_WindSlash(name, x, y, angle);
		return windSlash;
	}
	if (name == "ThunderBolt")
	{
		Skill_ThunderBolt* thunderBolt = new Skill_ThunderBolt(name, x, y, angle);
		return thunderBolt;
	}
	if (name == "WaterBall")
	{
		Skill_WaterBall* waterBall = new Skill_WaterBall(name, x, y, angle);
		return waterBall;
	}
	if (name == "Meteor")
	{
		float X = CameraManager::GetInstance()->GetMainCamera()->GetMousePosition().x;
		float Y = CameraManager::GetInstance()->GetMainCamera()->GetMousePosition().y;
		Effect_MagicCircle* magicCircle = new Effect_MagicCircle(name, 
			CameraManager::GetInstance()->GetMainCamera()->GetMousePosition().x,
			CameraManager::GetInstance()->GetMainCamera()->GetMousePosition().y, 
			CastingSkill::Meteor);
		return magicCircle;
	}
	return nullptr;
}

void SkillManager::Update()
{
	mFrameCount += Time::GetInstance()->DeltaTime();

	vector<GameObject*> skillList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Skill);
	vector<GameObject*> tileList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Tile);
	vector<GameObject*> monsterList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	Player* player = (Player*) ObjectManager::GetInstance()->FindObject("Player");

	for (int i = 0; i < skillList.size(); i++) 
	{
		SkillObject* skill = (SkillObject*)skillList[i];
		D2D1_RECT_F temp;
		D2D1_RECT_F skillrc = skill->GetRect();
		
		int index = (skill->GetRect().right - skill->GetRect().left) / TileSize + 1;
		int skillX = skill->GetX();
		int skillY = skill->GetY();

		// 스킬 to 벽
		for (int y = (skill->GetY() / TileSize) - index; y < (skill->GetY() / TileSize) + index; y++)
		{
			for (int x = (skill->GetX() / TileSize) - index; x < (skill->GetX() / TileSize) + index; x++)
			{
				if (x < 0) continue;
				if (y < 0) continue;
				TileMap* tileMap = (TileMap*)tileList[0];
				Tile* tile = (Tile*)tileMap->GetTileList(x, y);
				D2D1_RECT_F skillrc = skill->GetRect();
				D2D1_RECT_F tilerc = tile->GetRect();
				if (tile->GetType() == Type::Wall && IntersectRect(temp, &skillrc, &tilerc) && skill->GetSkillType() == SkillType::Throw)
				{
					if (skill->GetName() == "FireBall")
					{
						if (skill->GetSkillTarget() == SkillTarget::Enemy)
						{
							return;
						}
						ParticleManager::GetInstance()->MakeFireExlposionParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
						SoundPlayer::GetInstance()->Play(L"FireBallExplode", 1.f);
					}

					if (skill->GetName() == "DragonArc")
					{
						ParticleManager::GetInstance()->MakeFireExlposionParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
						SoundPlayer::GetInstance()->Play(L"FireArcEnd", 1.f);
					}

					if (skill->GetName() == "IceSpear")
					{
						ParticleManager::GetInstance()->MakeIceBreakParticle(skillX, skillY, 10);
						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
					}

					if (skill->GetName() == "WaterBall")
					{
						ParticleManager::GetInstance()->MakeWaterExplosion(skillX, skillY);
						SoundPlayer::GetInstance()->Play(L"WaterExplode", 1.f);
					}

					ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
					skill->SetIsDestroy(true);
					break;
				}
			}
		}

		// 스킬 충돌 적 or 플레이어
		for (int j = 0; j < monsterList.size(); j++)
		{
			MonsterObject* monster = (MonsterObject*)monsterList[j];
			D2D1_RECT_F monsterrc = monsterList[j]->GetRect();

			// 플레이어 -> 적
			if (skill->GetSkillTarget() == SkillTarget::Player)
			{
				// 근접
				if (skill->GetSkillType() == SkillType::Melee)
				{
					bool isCollision = false;
					if (IntersectRect(temp, &skillrc, &monsterrc))
					{
						if (monster->GetName() == "FireBoss")
						{
							float temp = monster->GetHitCount();
							temp += skill->GetSkillDamege();
							monster->SetHitCount(temp);
							return;
						}
						ParticleManager::GetInstance()->MakeHitSparkParticle(temp.left, temp.top);
						monster->SetSkillHitAngle(skill->GetAngle());
						monster->SetSkillHitPower(skill->GetSkillPower());
					}
				}

				// 투척
				if (skill->GetSkillType() == SkillType::Throw) 
				{
					
					if (IntersectRect(temp, &skillrc, &monsterrc))
					{
						if (skill->GetName() == "FireBall")
						{
							ParticleManager::GetInstance()->MakeFireExlposionParticle(skillX, skillY, 10);
							SoundPlayer::GetInstance()->Play(L"FireBallExplode", 1.f);
							monster->SetSkillHitAngle(skill->GetAngle());
							monster->SetSkillHitPower(skill->GetSkillPower());
						}
						
						if (skill->GetName() == "DragonArc")
						{
							ParticleManager::GetInstance()->MakeFireExlposionParticle(skillX, skillY, 10);
							ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
							SoundPlayer::GetInstance()->Play(L"FireArcEnd", 1.f);
							monster->SetSkillHitAngle(skill->GetAngle());
							monster->SetSkillHitPower(skill->GetSkillPower());
						}

						if (skill->GetName() == "IceSpear")
						{
							ParticleManager::GetInstance()->MakeIceBreakParticle(skillX, skillY, 10);
							monster->SetSkillHitAngle(skill->GetAngle());
							monster->SetSkillHitPower(skill->GetSkillPower());
						}

						if (skill->GetName() == "WaterBall")
						{
							ParticleManager::GetInstance()->MakeWaterExplosion(skillX, skillY);
							SoundPlayer::GetInstance()->Play(L"WaterExplode", 1.f);
							monster->SetSkillHitAngle(skill->GetAngle());
							monster->SetSkillHitPower(skill->GetSkillPower());
						}

						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
						skill->SetIsDestroy(true);

						if (monster->GetName() == "FireBoss")
						{
							int temp = monster->GetHP();
							temp -= skill->GetSkillDamege();
							monster->SetHP(temp);
							return;
						}

						break;
					}
				}
			}

			// 적 -> 플레이어 충돌
			if (skill->GetSkillTarget() == SkillTarget::Enemy)
			{
				D2D1_RECT_F temp;
				D2D1_RECT_F playerRc = player->GetRect();


				if (IntersectRect(temp, &skillrc, &playerRc))
				{
					// 근접
					if (skill->GetSkillType() == SkillType::Melee)
					{

					}

					// 투척
					if (skill->GetSkillType() == SkillType::Throw)
					{

						if (skill->GetName() == "FireBall")
						{
							ParticleManager::GetInstance()->MakeFireExlposionParticle(skillX, skillY, 10);
							SoundPlayer::GetInstance()->Play(L"FireBallExplode", 1.f);
							player->SetSkillHitAngle(skill->GetAngle());
							player->SetSkillHitPower(skill->GetSkillPower());
						}

						if (skill->GetName() == "WaterBall")
						{
							ParticleManager::GetInstance()->MakeWaterExplosion(skillX, skillY);
							SoundPlayer::GetInstance()->Play(L"WaterExplode", 1.f);
							player->SetSkillHitAngle(skill->GetAngle());
							player->SetSkillHitPower(skill->GetSkillPower());
						}

						ParticleManager::GetInstance()->MakeHitSparkParticle(skillX, skillY);
						skill->SetIsDestroy(true);
						break;
					}
				}
			}
		}
	}
}

void SkillManager::DragonArcSkill(const string & name, float x, float y, float angle, bool isUp)
{
	Skill_DragonArc* dragonArc = new Skill_DragonArc(name, x, y, angle, isUp);
	dragonArc->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, dragonArc);
}

void SkillManager::FlameSkill(const string& name, float x, float y, float angle)
{
	Effect_MagicCircle* magicCircle = new Effect_MagicCircle(name, x, y, CastingSkill::Burn);
	magicCircle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, magicCircle);
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
	flame->SetEndPositionX(endX);
	flame->SetEndPositionY(endY);
	flame->SetIsMove();
	flame->Init();
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
	
	SoundPlayer::GetInstance()->Play(L"SummonIceSpearSound", 1.f);
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
	
	SoundPlayer::GetInstance()->Play(L"GolemAttackSound", 1.f);
	Skill_MonsterBigSlash* monsterBigSlash = new Skill_MonsterBigSlash(name, x, y, angle);
	monsterBigSlash->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, monsterBigSlash);
}

void SkillManager::WaterBallSkill(const string& name, float x, float y, float angle)
{

	SoundPlayer::GetInstance()->Play(L"WaterBallSound", 1.f);
	Skill_WaterBall* waterBall = new Skill_WaterBall(name, x, y, angle);
	waterBall->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, waterBall);
}

void SkillManager::WaterBallSkill(const string& name, float x, float y, float angle, float temp)
{
	
	SoundPlayer::GetInstance()->Play(L"WaterBallSound", 1.f);
	Skill_WaterBall* waterBall = new Skill_WaterBall(name, x, y, angle, temp);
	waterBall->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, waterBall);
}

void SkillManager::MonsterSmallSlashSkill(const string& name, float x, float y, float angle)
{
	
	SoundPlayer::GetInstance()->Play(L"ZombieAttackSound", 1.f);
	Skill_MonsterSmallSlash* monsterSmallSlash = new Skill_MonsterSmallSlash(name, x, y, angle);
	monsterSmallSlash->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, monsterSmallSlash);
}

void SkillManager::SpearSkill(const string& name, float x, float y, float angle)
{
	Skill_Spear* spear = new Skill_Spear(name, x, y, angle);
	spear->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, spear);
}

void SkillManager::SpearWaveSkill(const string& name, float x, float y, float angle)
{
	Skill_SpearWave* spearWave = new Skill_SpearWave(name, x, y, angle);
	spearWave->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, spearWave);
}

void SkillManager::MonsterMiddleSlashSkill(const string& name, float x, float y, float angle)
{
	
	SoundPlayer::GetInstance()->Play(L"SwoardManAttackSound", 1.f);
	Skill_MonsterMiddleSlash* monsterMiddleSlash = new Skill_MonsterMiddleSlash(name, x, y, angle);
	monsterMiddleSlash->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, monsterMiddleSlash);
}

void SkillManager::ThunderBolt(const string& name, float x, float y, float angle)
{
	
	SoundPlayer::GetInstance()->Play(L"ThunderBoltSound", 1.f);
	for (int i = 0; i < 6; i++)
	{
		float skillX = x + cosf(angle) * 100;
		float skillY = y + -sinf(angle) * 100;
		Skill_ThunderBolt* thunderBolt = new Skill_ThunderBolt(name, skillX, skillY, angle);
		thunderBolt->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Skill, thunderBolt);
	}
}

SkillObject * SkillManager::FindSkill(string name)
{
	SkillObject* skill = nullptr;

	map<SkillElement, vector<SkillObject*>>::iterator iter = mSkillList.begin();

	for (; iter != mSkillList.end(); iter++)
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			if (iter->second[i]->GetName() == name)
			{
				return iter->second[i];
			}
		}
	}

	return skill;
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