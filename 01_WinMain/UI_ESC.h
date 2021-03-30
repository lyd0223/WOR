#include "UserInterface.h"

struct EscText {
	EscText(D2D1_RECT_F rc, wstring name, int fontSize, bool isActive, D2DRenderer::DefaultBrush brush)
		: Rect(rc), Name(name), FontSize(fontSize), IsActive(isActive), Brush(brush) {};
	D2D1_RECT_F Rect;
	wstring Name;
	int FontSize;
	bool IsActive;
	D2DRenderer::DefaultBrush Brush;
};

class Image;
class UI_ESC : public UserInterface
{
	Image* mEscImage;
	
	vector<EscText*> mEscTextList;

	int mIndex;
public:
	UI_ESC(const string& name);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
