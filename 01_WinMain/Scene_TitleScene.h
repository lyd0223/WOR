#pragma once
#include "Scene.h"

enum class TitleState : int {
	Scene1,
	Scene2,

	End
};

struct TitleButton {
	D2D1_RECT_F Rect;
	wstring Name;
	int FontSize;
	bool IsActive;
	D2DRenderer::DefaultBrush Brush;
};

class Image;
class Scene_TitleScene : public Scene
{
	vector<Image*> mBackImageList;
	Image* mTitleImage;

	TitleState mTitleState;
	vector<TitleButton> mButtonList;
	wstring mPressWstr;

	POINT mTitlePoint;

	int mBackGroundCount;
	int mButtonCount;
	
	float mFontSize;
	float mAlpha;
	float mFrameCount;

	bool mIsTitleMove;
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

