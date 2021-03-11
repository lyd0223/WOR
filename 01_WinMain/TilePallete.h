#pragma once

class TilePallete
{
	class Image* Image;
	int FrameX;
	int FrameY;
	float PositionX;
	float PositionY;
	D2D1_RECT_F Rect;
	float Width;
	float Height;

	friend class Scene_MapTool;

public:
	class Image* GetImage() { return Image; };
	int GetFrameX() { return FrameX; };
	int GetFrameY() { return FrameY; };

	
};
