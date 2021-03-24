#pragma once
class ParticleManager
{
	Singleton(ParticleManager)

public:
	void MakeShorkWaveParticle(float x, float y, float scale);
	void MakeHitSparkParticle(float x, float y);
	void MakeIceBreakParticle(float x, float y, float power);
	void MakeFireCircleParticle(float x, float y);
	void MakeFireParticle(float x, float y, float power);
};