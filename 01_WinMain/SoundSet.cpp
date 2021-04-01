#include "pch.h"
#include "SoundSet.h"

SoundSet::SoundSet()
{
	// �����
	SoundPlayer::GetInstance()->LoadFromFile(L"Fire", Resources(L"Sound/Fire.wav"), true);
	SoundPlayer::GetInstance()->LoadFromFile(L"TitleScreen", Resources(L"Sound/TitleScreen.wav"), true);
	SoundPlayer::GetInstance()->LoadFromFile(L"Tutorial", Resources(L"Sound/Tutorial.wav"), true);
	SoundPlayer::GetInstance()->LoadFromFile(L"PlayerRoom", Resources(L"Sound/PlayerRoom.wav"), true);
	SoundPlayer::GetInstance()->LoadFromFile(L"Boss", Resources(L"Sound/Boss.wav"), true);

	// ȿ����
	SoundPlayer::GetInstance()->LoadFromFile(L"WaterBall", Resources(L"Sound/WaterBall.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"WaterExplode", Resources(L"Sound/WaterExplode.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBallCast", Resources(L"Sound/FireballCast.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBallExplode", Resources(L"Sound/FireballExplode.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireArcStart", Resources(L"Sound/FireArcStart.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireArcEnd", Resources(L"Sound/FireArcEnd.wav"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossFlex0", Resources(L"Sound/FireBossFlex0.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossFlex1", Resources(L"Sound/FireBossFlex1.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossHurt0", Resources(L"Sound/FireBossHurt0.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossHurt1", Resources(L"Sound/FireBossHurt1.wav"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossHurt0", Resources(L"Sound/FireBossHurt0.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossHurt1", Resources(L"Sound/FireBossHurt1.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireBossHurt2", Resources(L"Sound/FireBossHurt2.wav"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"FireChargeup", Resources(L"Sound/FireChargeup.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FireSpinLoop", Resources(L"Sound/FireSpinLoop.wav"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"MenuOpen", Resources(L"Sound/MenuOpen.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"MenuMove", Resources(L"Sound/MenuMove.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"MenuClose", Resources(L"Sound/MenuClose.wav"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"ThunderBounce", Resources(L"Sound/ThunderBounce.wav"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"PlayerDashSound", Resources(L"Sound/PlayerDash.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"EnemyHitSound", Resources(L"Sound/EnemyHit.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"WindSlashSound", Resources(L"Sound/WindSlash.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"IceSpearSound", Resources(L"Sound/IceSpear.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"SummonIceSpearSound", Resources(L"Sound/SummonIceSpear.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"GolemAttackSound", Resources(L"Sound/GolemAttack.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"WaterBallSound", Resources(L"Sound/WaterBall.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"ZombieAttackSound", Resources(L"Sound/ZombieAttack.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"SwoardManAttackSound", Resources(L"Sound/SwoardManAttack.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"ThunderBoltSound", Resources(L"Sound/ThunderBolt.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"Teleport", Resources(L"Sound/Teleport.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"RoomUnLock", Resources(L"Sound/RoomUnLock.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"RoomLock", Resources(L"Sound/RoomLock.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"FallSound", Resources(L"Sound/Fall.wav"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"EnemyDeadSound", Resources(L"Sound/EnemyDead.wav"), false);
}