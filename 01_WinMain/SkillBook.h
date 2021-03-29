#pragma once
#include "GameObject.h"
class SkillBook : public GameObject
{
	class Animation* mIdleAnimation;
	class Animation* mOpenAnimation;
	class Animation* mCloseAnimation;
	class Animation* mCurrentAnimation;
	Image* mImage;
	bool mBookIsOpen;
public:
	SkillBook(float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
};

