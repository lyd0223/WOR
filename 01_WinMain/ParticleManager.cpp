#include "pch.h"
#include "ParticleManager.h"
#include "Effect_FireParticle.h"
#include "Effect_IceBreakParticle.h"
#include "Effect_HitSpark.h"
#include "Effect_ShorkWave.h"
#include "Effect_WaterFormParticle.h"
#include "Effect_WaterExplosion.h"
#include "Effect_DashEffect.h"
#include "Effect_GlassShards.h"

void ParticleManager::MakeDustParticle(float x, float y, float angle, float scale)
{
	Effect_GlassShards* glassShards;
	float tempAngle = 0;
	float tempScale = 0;
	for (int i = 0; i < 10; i++)
	{
		int randomInt = Random::GetInstance()->RandomInt(3);
		tempAngle += 0.1f;
		tempScale += 0.3f;
		glassShards = new Effect_GlassShards("GlassShards", x, y, angle + tempAngle, scale + tempScale, randomInt);
		glassShards->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, glassShards);
	}
}

void ParticleManager::MakeDashEffectParticle(float x, float y, float angle)
{
	Effect_DashEffect* dashEffect;
	dashEffect = new Effect_DashEffect("DashEffect", x, y, angle);
	dashEffect->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, dashEffect);
}

void ParticleManager::MakeShorkWaveParticle(float x, float y, float scale)
{
	Effect_ShorkWave* shorkWave;
	shorkWave = new Effect_ShorkWave("MeteorShockWave", x, y);
	shorkWave->Init();
	shorkWave->SetScale(scale);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, shorkWave);
}

void ParticleManager::MakeHitSparkParticle(float x, float y)
{
	Effect_HitSpark* hitSpark;
	
	int randomInt = Random::GetInstance()->RandomInt(3);
	hitSpark = new Effect_HitSpark("HitSpark", x, y, randomInt);
	hitSpark->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, hitSpark);
}

void ParticleManager::MakeIceBreakParticle(float x, float y, float power)
{
	Effect_IceBreakParticle* iceBreakParticle;
	
	for (int i = 0; i < 8; i++)
	{
		int randomInt = Random::GetInstance()->RandomInt(12);
		float endX = x + (cosf(PI / 6 * randomInt) * 200);
		float endY = y + (-sinf(PI / 6 * randomInt) * 200);
		float angle = Math::GetAngle(x, y, endX, endY);

		iceBreakParticle = new Effect_IceBreakParticle("IceBreakParticle", x, y, angle);
		iceBreakParticle->Init();
		iceBreakParticle->SetIsMove(true);
		iceBreakParticle->SetSpeed(power);
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, iceBreakParticle);
	}
}

void ParticleManager::MakeFireParticle(float x, float y, float angle)
{
	Effect_FireParticle* fireParticle;
	fireParticle = new Effect_FireParticle("FireParticle", x, y, angle);
	fireParticle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, fireParticle);
}

void ParticleManager::MakeFireCircleParticle(float x, float y)
{
	Effect_FireParticle* fireParticle;
	fireParticle = new Effect_FireParticle("FireParticle", x, y, 0);
	fireParticle->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, fireParticle);

	for (int i = 0; i < 12; i++)
	{
		float dx;
		float dy;
		float distance = 30;

		dx = x + (cosf(PI / 6 * i) * distance);
		dy = y + -(sinf(PI / 6 * i) * distance);
		fireParticle = new Effect_FireParticle("FireParticle", dx, dy, 0);
		fireParticle->Init();
		fireParticle->SetIsMove();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, fireParticle);
	}
}

void ParticleManager::MakeFireExlposionParticle(float x, float y, float power)
{
	MakeFireCircleParticle(x, y);

	Effect_FireParticle* fireParticle;


	for (int i = 0; i < 4; i++)
	{
		float dx;
		float dy;

		for (int j = 0; j < 6; j++)
		{
			int randomInt = Random::GetInstance()->RandomInt(180);
			float angle = randomInt / PI;
			dx = x + (cosf(angle / 4 * i) * 50);
			dy = y + -(sinf(angle / 4 * i) * 50);
			fireParticle = new Effect_FireParticle("FireParticle", dx, dy, angle);
			fireParticle->Init();
			fireParticle->SetIsMove();
			fireParticle->SetSpeed(power);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, fireParticle);
		}
	}
}

void ParticleManager::MakeWaterFormPartile(float x, float y, D2D1_RECT_F rc)
{
	Effect_WaterFormParticle* waterFormParticle;
	float radius = rc.right - rc.left;
	int waterCount = radius / 5;

	for (int i = 0; i < waterCount; i++)
	{
		float randomX = 0;
		float randomY = 0;

		waterFormParticle = new Effect_WaterFormParticle("WaterFormParticle", randomX, randomY);
		waterFormParticle->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, waterFormParticle);
	}
}

void ParticleManager::MakeWaterExplosion(float x, float y)
{
	Effect_WaterExplosion* waterExplosion;

	waterExplosion = new Effect_WaterExplosion("WaterExplosion", x, y);
	waterExplosion->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Particle, waterExplosion);
}
