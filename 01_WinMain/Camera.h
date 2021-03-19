#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	enum class Mode : int
	{
		MapTool ,Follow, Free
	};
protected:
	Mode mMode;
	GameObject* mTarget;		//ÂÑ¾Æ°¡¾ßÇÒ Å¸°Ù
	POINT mMousePosition;
	float mMoveSpeed;
public:
	void Init()override; 
	void Release()override; 
	void Update()override; 
	void Render()override;

	void SetTarget(GameObject* target) { mTarget = target; }
	void ChangeMode(Mode mode) { mMode = mode; }
public:
	void Render(class Image* image, float x, float y);
	void RenderFromBottom(Image* image, float x, float y);
	//void Render(HDC hdc, class Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
	void FrameRender(class Image* image, float x, float y, int frameX, int frameY);
	void FrameRenderFromBottom(Image* image, float x, float y, int frameX, int frameY);
	/*void ScaleRender(HDC hdc, class Image* image, int x, int y, int width, int height);
	void ScaleFrameRender(HDC hdc,class Image* image, int x, int y, int frameX, int frameY, int width, int height);
	void AlphaScaleRender(HDC hdc,class Image* image, int x, int y, int width, int height, float alpha);
	void AlphaScaleFrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha);*/
	void RenderText(float x1, float y1, wstring text, int size);
	void RenderRect(D2D1_RECT_F rc, D2D1::ColorF color = D2D1::ColorF::Black);
	void RenderGizmoRect( D2D1_RECT_F rc, D2D1::ColorF::Enum color = D2D1::ColorF::Red);
	//void RenderEllipse(HDC hdc, float x, float y, float radius);

	bool IsInCameraArea(float x, float y, float width, float height);
	bool IsInCameraArea(D2D1_RECT_F rc);

	inline float GetMoveSpeed()const { return mMoveSpeed; }
	inline void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
};

