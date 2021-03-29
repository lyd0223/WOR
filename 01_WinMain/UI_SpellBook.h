#pragma once
#include "UserInterface.h"
#include "SkillObject.h"

class Image;
class Player;
class UI_SpellBook : public UserInterface
{	
	UIObject* mSpellbookUI;
	UIObject* mSpellbookUIText;
	UIObject* mSpellbookUISkillType;
	UIObject* mSpellbookUIElementalPage;
	UIObject* mSpellbookUISkillElementalOn;
	UIObject* mSpellbookUILeftArrow;
	UIObject* mSpellbookUIRightArrow;
	UIObject* mSpellbookUIUpArrow;
	UIObject* mSpellbookUIDownArrow;
	
	map<SkillElement, vector<SkillObject*>> mSkillList;
	map<SkillElement, vector<UIObject*>> mSkillCardList;
	map<SkillElement, UIObject*> mSpellbookUISkillElemantalList;

	vector<SkillElement> mSkillElementList;

	Player* mPlayer;
	SkillElement mCurrentSkillElement;
	SkillArcana mCurrentSkillArcana;
	SkillObject* mCurrentSkill;

	
	int mIndexY;
public:
	UI_SpellBook(const string& name, int index);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void GetSkillList();
	void AddSkillList(SkillElement element, SkillObject * skillObject);
	void MakeSpellbookUISkillElemental();
};