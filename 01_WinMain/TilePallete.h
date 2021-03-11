#pragma once

class TilePallete
{
	class Image* Image;
	int FrameX;
	int FrameY;
	float PositionX;
	float PositionY;
	RECT Rect;
	float Width;
	float Height;

	friend class Scene_MapTool;

public:
	class Image* GetImage() { return Image; };
	int GetFrameX() { return FrameX; };
	int GetFrameY() { return FrameY; };

	
};
