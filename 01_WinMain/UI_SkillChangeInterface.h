#pragma once
#include "UserInterface.h"

class Image;
class Player;
class UI_SkillChangeInterface : public UserInterface
{
	UIObject* mSkillChangeInterface;
	UIObject* mCardSelect;
	UIObject* mBasicSkillIcon;
	UIObject* mDashSkillIcon;
	UIObject* mStandardSkillIcon;
	UIObject* mSignatureSkillIcon;

	map<string, Vector2> mSkillIndexList;

	Player* mPlayer;
	vector<Vector2> mCardPostion;

	int mIndex;
public:
	UI_SkillChangeInterface();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

