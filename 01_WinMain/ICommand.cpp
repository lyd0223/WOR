#include "pch.h"
#include "ICommand.h"
#include "Tile.h"
#include "TilePallete.h"
#include "Image.h"
IBrushTile::IBrushTile(Tile* tile, TilePallete* excuteData)
{
	mTargetTile = tile;
	mExecutePalleteData = excuteData;

	//mSaveImageKey = mTargetTile->GetImage()->GetKeyName();
	mSaveFrameX = tile->GetFrameIndexX();
	mSaveFrameY = tile->GetFrameIndexY();
}

void IBrushTile::Excute()
{
	//mTargetTile->SetImage(IMAGEMANAGER->FindImage(mExecutePalleteData->GetImage()->GetKeyName()));
	mTargetTile->SetFrameIndexX(mExecutePalleteData->GetFrameX());
	mTargetTile->SetFrameIndexY(mExecutePalleteData->GetFrameY());
}

void IBrushTile::Redo()
{
	//mTargetTile->SetImage(IMAGEMANAGER->FindImage(mSaveImageKey));
	mTargetTile->SetFrameIndexX(mSaveFrameX);
	mTargetTile->SetFrameIndexY(mSaveFrameY);
}

void IBrushTile::Undo()
{
}
