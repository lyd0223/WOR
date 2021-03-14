#pragma once

/*
1. 애니메이션 
2. 이벤트 만드는 법
*/

class Image;
class FireBoss;
class FireBall;
class Player;
class MainGame
{

	FireBoss* mFireBoss;
	FireBall* mFireBall;
	
	D2D1_RECT_F mRect;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	float mAngle;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	void RenderTime(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

