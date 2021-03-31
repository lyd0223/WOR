#pragma once
#include "GameObject.h"

enum class NumberColor : int {
	Black,
	White,
	Gray,

	End
};

class Image;
class Effect_Number : public GameObject
{
	Image* mNumberWhite;
	Image* mNumberBlack;
	Image* mNumberGray;
	Image* mNumberRed;

	int mIndex;
	int mTen;
	int mOne;

	float mFrameCount;
	float mScale;
	float mAlpha;
public:
	Effect_Number(const string& name, float x, float y, int index);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

