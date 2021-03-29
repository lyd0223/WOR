#pragma once
#include "GameObject.h"
#include "MonsterObject.h"

class Image;
class Animation;
class Effect_EnemyCreate : public GameObject
{
	Image* mImage;
	Animation* mEnemyCreateAnimation;
	MonsterName mMonsterName;

	int mAnimationIndex;
	float mScale;

public:
	Effect_EnemyCreate(const string& name, float x, float y, MonsterName monsterName);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
	Animation* GetAnimation() { return mEnemyCreateAnimation; }
	int GetAnimationIndex() { return mAnimationIndex; }
};
