#pragma once
#include "TileMap.h"

struct Line
{
	int x1, y1, x2, y2;
};
class Room
{
public:
	int x, y, sizeX, sizeY;
	int centerX;
	int centerY;
	vector<Line> roadList;
	vector<GameObject*> monsterList;
public:
	Room();
	Room(int X, int Y, int SizeX, int SizeY)
	{
		x = X;
		y = Y;
		sizeX = SizeX;
		sizeY = SizeY;
		centerX = (x + sizeX + x) / 2;
		centerY = (y + sizeY + y) / 2;
	}
	bool PlayerInRoom()
	{
		D2D1_RECT_F playerRect = ObjectManager::GetInstance()->FindObject("Player")->GetRect();
		D2D1_RECT_F roomRect = RectMake(x * TileSize, y * TileSize, sizeX * TileSize, sizeY * TileSize);
		D2D1_RECT_F rctemp;
		if (IntersectRect(rctemp, &playerRect, &roomRect))
		{
			return true;
		}
		return false;
	}
};
class Node
{
	friend class RandomMapGeneration;
	int mX, mY;
	int mSizeX;
	int mSizeY;
	bool mIsVisit = 0;
	D2D1_RECT_F mRect;
	vector<Room*> mRoomList;
	Room* mSelectRoom; // 길을 이어주기에 가장 최적화된 방을찾는다.

	Node* mLeftNode;
	Node* mRightNode;
	Node* mParentNode;

public:
	Node(int x1, int y1, int x2, int y2);

	void MakeRoom(class TileMap* tilemap);
};
class RandomMapGeneration
{
	Singleton(RandomMapGeneration)

	queue<Node*> q;
	stack<Node*> s;
	Node* mSCurrentNode;
	Node* mCurrentNode;
	Node* mRoot;
	int mNodeNum;
	vector<Line> mRoadList;
	vector<Room*> mRoomList;
	class TileMap* mTileMap;
	vector<class MonsterObject*> mMonsterList;
	int mPlayerSpawnRoomNum, mPortalRoomNum;
	vector<int> mEnemyRoomNum;
public:
	void Init();
	void CreateRandomMap1();
	void CreateRandomMap2();
	void Devide(Node* node);
	void MakeRoad();
	void RandomMonsterCreate();
	void RandomPlayerPosition(class Player* player);
	
	vector<Room*> GetRoomList() { return mRoomList; }
	class TileMap* GetTileMap() { return mTileMap; }

};

