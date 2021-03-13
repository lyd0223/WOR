#pragma once
#include "GameObject.h"
enum class Type
{
	Floor,
	Wall,
	Cliff,
	Thorn,
};
class Tile : public GameObject
{
	class Image* mImage;
	int mFrameIndexX;
	int mFrameIndexY;
	Type mType;
	
public:
	Tile(class Image* image, float x, float y, float sizeX, float sizeY, int frameIndexX, int frameIndexY);
	void Init()override {};
	void Release()override {};
	void Render()override;
	void Update()override;
	D2D1_RECT_F GetRect() { return mRect; };
	Image* GetImage() { return mImage; };
	int GetFrameIndexX() { return mFrameIndexX; };
	int GetFrameIndexY() { return mFrameIndexY; };
	Type GetType() { return mType; };
	void SetRect(D2D1_RECT_F rc) { mRect = rc; };
	void SetImage(Image* image) { mImage = image; };
	void SetFrameIndexX(int frameX) { mFrameIndexX = frameX; };
	void SetFrameIndexY(int frameY) { mFrameIndexY = frameY; };
	void SetType(Type t) { mType = t; };
	

};

