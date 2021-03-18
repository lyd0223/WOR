#pragma once
#include"MovingObject.h"
class MonsterObject :public MovingObject
{
protected:
	vector<class Tile*> mPathList;

public:
	vector<class Tile*> GetPathList() { return mPathList; }
	void SetPathList(vector<class Tile*> pathList) { mPathList = pathList; }
};

