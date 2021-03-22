#pragma once
/****************************************************************************
## D2DRenderer ##
*****************************************************************************/
class D2DRenderer final
{
public:
	static D2DRenderer* GetInstance()
	{
		static D2DRenderer instance;
		return &instance;
	}
private:
	D2DRenderer();
	virtual ~D2DRenderer();
public:
	enum class DefaultBrush : UINT
	{
		White = 0, Black, Yellow, Red, Blue, Green, Gray, End
	};
private:
	typedef map<wstring, IDWriteTextFormat*>::iterator TextIter;
private:
	ID2D1Factory* mD2DFactory;
	ID2D1HwndRenderTarget* mD2DRenderTarget;

	IDWriteFactory* mDWFactory;

	ID2D1SolidColorBrush* mDefaultBrushList[((UINT)DefaultBrush::End)];
	map<wstring, IDWriteTextFormat*> mFontList;
public:
	void BeginRender(const D2D1::ColorF& backgroundColor);
	void EndRender();
private:
	void CreateFactory();
	void CreateRenderTarget();
	void CreateDefaultBrush();
public:
	void AddTextFormat(const wstring& font, const float& defaultSize = 1.f);
	inline ID2D1RenderTarget* const GetRenderTarget()const { return this->mD2DRenderTarget; }
public:
	//�ؽ�Ʈ ���(�⺻ �귯�� ���) 
	void RenderText(const int x, const int y, const wstring& text, const int size,
		const DefaultBrush& defaultBrush = DefaultBrush::Black,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"�������");
	//�ؽ�Ʈ ��� (���ϴ� ����� ���İ����� �귯�� �����ؼ� ���)
	void RenderText(const int x, const int y, const wstring& text, const COLORREF& color, const float alpha, const int size,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"�������");
	//�ؽ�Ʈ �ʵ� ��� (�⺻ �귯�� ���) 
	void RenderTextField(const int x, const int y, const wstring& text, const int size, const int width, const int height,
		const DefaultBrush& defaultBrush = DefaultBrush::Black,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"�������");
	//�ؽ�Ʈ �ʵ� ���(���ϴ� ����� ���İ����� �귯�� �����ؼ� ���)
	void RenderTextField(const int x, const int y, const wstring& text, const COLORREF& color,
		const int size, const int width, const int height,
		const float alpha = 1.0f,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"�������");
	//��Ʈ�� �ؽ�Ʈ ���
	void DrawTextToRect(D2D1_RECT_F rect, const wstring& text, const COLORREF& color,
		const int size, 
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_CENTER,
		const wstring& font = L"�������");
};

#define _D2DRenderer D2DRenderer::GetInstance()