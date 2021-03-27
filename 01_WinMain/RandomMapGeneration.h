#pragma once
struct Line
{
	float x1, y1, x2, y2;
};
struct Room
{
	int x, y, sizeX, sizeY;
};
class Node
{
	friend class RandomMapGeneration;
	int mX, mY;
	int mSizeX;
	int mSizeY;
	bool mIsVisit = 0;
	D2D1_RECT_F mRect;
	vector<Room> mRoomList;
	Room mSelectRoom; // 길을 이어주기에 가장 최적화된 방을찾는다.

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

public:
	void Init();
	void CreateRandomMap(class TileMap* tilemap);
	void Devide(Node* node);
	void MakeRoad();
};

