#pragma once
#include "UserInterface.h"

class Image;
class UI_SpellBook : public UserInterface
{	
	//map<SkillElement, vector<GameObject*>> 
	UIObject* mSpellbookUI;
	UIObject* mSpellbookUIText;
	UIObject* mSpellbookUISkillType;
	UIObject* mSpellbookUIElementalPage;
	UIObject* mSpellbookUISkillUIElementalOn;
	UIObject* mSpellbookUISkillUIElementalOff;


public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};