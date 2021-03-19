#pragma once
#include"MovingObject.h"

class Image;
class Player;
class MonsterObject :public MovingObject
{
protected:
	Image* mImage;
	Player* mPlayer;
	vector<class Tile*> mPathList;

public:
	MonsterObject(const string& name);

	vector<class Tile*> GetPathList() { return mPathList; }
	void SetPathList(vector<class Tile*> pathList) { mPathList = pathList; }
};

