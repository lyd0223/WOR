#pragma once
class ParticleManager
{
	Singleton(ParticleManager)

public:
	void MakeShorkWaveParticle(float x, float y, float scale);
	void MakeHitSparkParticle(float x, float y);
	void MakeIceBreakParticle(float x, float y, float power);
	void MakeFireParticle(float x, float y, float angle);
	void MakeFireCircleParticle(float x, float y);
	void MakeFireExlposionParticle(float x, float y, float power);
	void MakeWaterFormPartile(float x, float y, D2D1_RECT_F rc);
	void MakeWaterExplosion(float x, float y);
};