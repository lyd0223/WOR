#pragma once
struct Line
{
	float x1, y1, x2, y2;
};
class Node
{
	friend class RandomMapGeneration;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	bool mIsVisit = 0;
	D2D1_RECT_F mRect;
	vector<D2D1_RECT_F> mRoomList;
	D2D1_RECT_F mSelectRoom; // 길을 이어주기에 가장 최적화된 방을찾는다.
	int mLineNum;
	Node* mLeftNode;
	Node* mRightNode;
	Node* mParentNode;

public:
	Node(float x, float y, float sizex, float sizey);

	void Render();
	void MakeRoom();
};
class RandomMapGeneration
{

	D2D1_RECT_F exrc;
	D2D1_RECT_F exrc2;
	queue<Node*> q;
	stack<Node*> s;
	Node* mSCurrentNode;
	Node* mCurrentNode;
	Node* mRoot;
	int mNodeNum;
	vector<Line> mRoadList;
public:
	void Init();
	void Update();
	void Render();
	void Devide(Node* node);
	void MakeRoad();
};

