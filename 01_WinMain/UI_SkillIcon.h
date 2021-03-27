#pragma once
#include "GameObject.h"

class Image;
class UI_SkillIcon : public GameObject
{
	Image* mImage;
	
	
public:
	UI_SkillIcon(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

