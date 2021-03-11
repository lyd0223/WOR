#pragma once
enum class Type
{
	Normal,
	Wall,
	Slow
};
class Tile
{
	class Image* mImage;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	D2D1_RECT_F mRect;
	int mFrameIndexX;
	int mFrameIndexY;
	Type mType;
	
public:
	Tile(class Image* image, float x, float y, float sizeX, float sizeY, int frameIndexX, int frameIndexY);
	void Render();

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

