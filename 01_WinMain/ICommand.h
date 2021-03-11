#pragma once
class ICommand
{
public:
	virtual void Excute() = 0;
	virtual void Redo() = 0;
	virtual void Undo() = 0;
};

class IBrushTile : public ICommand
{
	class Tile* mTargetTile;
	wstring mSaveImageKey;
	int mSaveFrameX;
	int mSaveFrameY;

	class TilePallete* mExecutePalleteData;

public : 
	IBrushTile(Tile* tile, TilePallete* excuteData);
	void Excute()override;
	void Redo()override;
	void Undo()override;
};

