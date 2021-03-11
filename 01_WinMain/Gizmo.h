#pragma once
//디버그용 렉트 그릴때 사용
class Gizmo final
{
	Singleton(Gizmo)
public:
	enum class Color : int
	{
		Red, Blue, Green, End
	};
private:
	map<Color, HPEN> mPenList;
	HBRUSH mNullBrush;

	typedef map<Color, HBRUSH>::iterator BrushIter;
	typedef map<Color, HPEN>::iterator PenIter;
	Gizmo();
	~Gizmo();
public:
	void DrawRect(D2D1_RECT_F rc, D2D1::ColorF::Enum color);
	void DrawEllipse(HDC hdc, float x, float y, float radius, Color color);
};

