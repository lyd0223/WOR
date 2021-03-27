#include "pch.h"
#include "RandomMapGeneration.h"
#include "TileMap.h"
#include "Tile.h"
void RandomMapGeneration::Init()
{
	mRoot = new Node(0, 0, 150, 150);

	mCurrentNode = nullptr;


}

void RandomMapGeneration::CreateRandomMap(TileMap* tilemap)
{
	Init();
	//맵나누기 큐
	mCurrentNode = nullptr;
	while (1)
	{
		if (mCurrentNode == nullptr)
			mCurrentNode = mRoot;
		else
		{
			mCurrentNode = q.front();
			q.pop();
		}
		Devide(mCurrentNode);
		if (q.empty())
			break;
	}

	//방 만들기 재귀
	mRoot->MakeRoom(tilemap);

	//길 만들기 스택
	/*s.push(mRoot);
	MakeRoad();*/
}


Node::Node(int x1, int y1, int sizex, int sizey)
{
	mX = x1;
	mY = y1;
	mSizeX = sizex;
	mSizeY = sizey;
	mLeftNode = nullptr;
	mRightNode = nullptr;
	mParentNode = nullptr;
}

void RandomMapGeneration::Devide(Node* node)
{

	bool direction = Random::GetInstance()->RandomInt(0, 1);
	if (!direction && node->mSizeX < 30)
	{
		direction = 1;
	}
	else if (direction && node->mSizeY < 30)
	{
		direction = 0;
	}
	if (direction == 0 && node->mSizeX > 30)//세로로짜르기
	{
		float x = 0;
		while (x < 27 || node->mSizeX - x < 27)
		{
			if (x < 27 && node->mSizeY - x < 27)
				return;
			x = Random::GetInstance()->RandomInt(node->mSizeX * 0.3f, node->mSizeX * 0.7f);
		}
		Node* leftnode = new Node(node->mX, node->mY, x, node->mSizeY);
		Node* rightnode = new Node(node->mX + x, node->mY, node->mSizeX - x, node->mSizeY);
		leftnode->mParentNode = node;
		rightnode->mParentNode = node;
		node->mLeftNode = leftnode;
		node->mRightNode = rightnode;
		q.push(node->mLeftNode);
		q.push(node->mRightNode);
	}
	else if (direction == 1 && node->mSizeY > 30)          // 가로로짜르기
	{
		float y = 0;
		while (y < 27 || node->mSizeY - y < 27)
		{
			if (y < 27 && node->mSizeY - y < 27)
				return;
			y = Random::GetInstance()->RandomInt(node->mSizeY * 0.3f, node->mSizeY * 0.7f);
		}
		Node* leftnode = new Node(node->mX, node->mY, node->mSizeX, y);
		Node* rightnode = new Node(node->mX, node->mY + y, node->mSizeX, node->mSizeY - y);
		leftnode->mParentNode = node;
		rightnode->mParentNode = node;
		node->mLeftNode = leftnode;
		node->mRightNode = rightnode;
		q.push(node->mLeftNode);
		q.push(node->mRightNode);

	}
	//if (!direction && node->mSizeX < 50)
	//{
	//	direction = 1;
	//}
	//else if (direction && node->mSizeY < 50)
	//{
	//	direction = 0;
	//}
	//if (direction == 0 && node->mSizeX > 50)//세로로짜르기
	//{
	//	float x = Random::GetInstance()->RandomInt(node->mSizeX * 0.3f, node->mSizeX * 0.7f);
	//	
	//	Node* leftnode = new Node(node->mX, node->mY, x, node->mSizeY);
	//	Node* rightnode = new Node(node->mX + x, node->mY, node->mSizeX - x, node->mSizeY);
	//	leftnode->mParentNode = node;
	//	rightnode->mParentNode = node;
	//	node->mLeftNode = leftnode;
	//	node->mRightNode = rightnode;
	//	/*node->mLeftNode->mLineNum = node->mLineNum + 1;
	//	node->mRightNode->mLineNum = node->mLineNum + 1;*/
	//	q.push(node->mLeftNode);
	//	q.push(node->mRightNode);
	//}
	//else if (direction == 1 && node->mSizeY > 50)          // 가로로짜르기
	//{
	//	float y = Random::GetInstance()->RandomInt(node->mSizeY * 0.3f, node->mSizeY * 0.7f);
	//	
	//	Node* leftnode = new Node(node->mX, node->mY, node->mSizeX, y);
	//	Node* rightnode = new Node(node->mX, node->mY + y, node->mSizeX, node->mSizeY - y);
	//	leftnode->mParentNode = node;
	//	rightnode->mParentNode = node;
	//	node->mLeftNode = leftnode;
	//	node->mRightNode = rightnode;
	//	/*node->mLeftNode->mLineNum = node->mLineNum + 1;
	//	node->mRightNode->mLineNum = node->mLineNum + 1;*/
	//	q.push(node->mLeftNode);
	//	q.push(node->mRightNode);

	//}
	


}

void Node::MakeRoom(TileMap* tilemap)
{
	if (mLeftNode != nullptr)
	{
		mLeftNode->MakeRoom(tilemap);
		
		for (int i = 0; i < mLeftNode->mRoomList.size(); i++)
		{
			mRoomList.push_back(mLeftNode->mRoomList[i]);
		}
	}
	if (mRightNode != nullptr)
	{
		mRightNode->MakeRoom(tilemap);

		for (int i = 0; i < mRightNode->mRoomList.size(); i++)
		{
			mRoomList.push_back(mRightNode->mRoomList[i]);
		}
	}
	if (mLeftNode == nullptr)
	{
		int x =  Random::GetInstance()->RandomInt(5, 8);
		int y =  Random::GetInstance()->RandomInt(5, 8);
		mSelectRoom = {
			mX + x,
			mY + y,
			mSizeX - Random::GetInstance()->RandomInt(8 , 12),
			mSizeY - Random::GetInstance()->RandomInt(8 , 12) 
		};
		for (int y = mSelectRoom.y; y < mSelectRoom.y + mSelectRoom.sizeY; y++)
		{
			for (int x = mSelectRoom.x; x < mSelectRoom.x + mSelectRoom.sizeX; x++)
			{
				tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireFloor"));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(Random::GetInstance()->RandomInt(6));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(Random::GetInstance()->RandomInt(1));
			}
		}
		mRoomList.push_back(mSelectRoom);
	}
}
//
//void RandomMapGeneration::MakeRoad()
//{
//	while (!s.empty())
//	{
//		Node* nodetemp = s.top();
//		s.pop();
//		if (nodetemp->mLeftNode != nullptr)
//		{
//			if (!nodetemp->mIsVisit)
//			{
//				s.push(nodetemp);
//				s.push(nodetemp->mRightNode);
//				s.push(nodetemp->mLeftNode);
//				nodetemp->mIsVisit = 1;
//			}
//			else
//			{
//
//				//좌측방의 셀렉트룸설정.
//				float x = (nodetemp->mRightNode->mRect.left + nodetemp->mRightNode->mRect.right) / 2;
//				float y = (nodetemp->mRightNode->mRect.top + nodetemp->mRightNode->mRect.bottom) / 2;
//				float distance = 100000;
//
//				for (int i = 0; i < nodetemp->mLeftNode->mRoomList.size(); i++)
//				{
//					float x2 = (nodetemp->mLeftNode->mRoomList[i].left + nodetemp->mLeftNode->mRoomList[i].right) / 2;
//					float y2 = (nodetemp->mLeftNode->mRoomList[i].top + nodetemp->mLeftNode->mRoomList[i].bottom) / 2;
//					float distance2 = Math::GetDistance(x, y, x2, y2);
//					if (distance > distance2)
//					{
//						distance = distance2;
//						nodetemp->mLeftNode->mSelectRoom = nodetemp->mLeftNode->mRoomList[i];
//					}
//				}
//
//
//				//우측방의 셀렉트룸설정.
//				x = (nodetemp->mLeftNode->mSelectRoom.left + nodetemp->mLeftNode->mSelectRoom.right) / 2;
//				y = (nodetemp->mLeftNode->mSelectRoom.top + nodetemp->mLeftNode->mSelectRoom.bottom) / 2;
//				distance = 100000;
//
//				for (int i = 0; i < nodetemp->mRightNode->mRoomList.size(); i++)
//				{
//					float x2 = (nodetemp->mRightNode->mRoomList[i].left + nodetemp->mRightNode->mRoomList[i].right) / 2;
//					float y2 = (nodetemp->mRightNode->mRoomList[i].top + nodetemp->mRightNode->mRoomList[i].bottom) / 2;
//					float distance2 = Math::GetDistance(x, y, x2, y2);
//					if (distance > distance2)
//					{
//						distance = distance2;
//						nodetemp->mRightNode->mSelectRoom = nodetemp->mRightNode->mRoomList[i];
//					}
//				}
//
//
//				//가로로 잘랏을때
//				if (nodetemp->mLeftNode->mX == nodetemp->mRightNode->mX)
//				{
//					float x1, y1, x2, y2;
//					if (nodetemp->mLeftNode->mSelectRoom.right - nodetemp->mLeftNode->mSelectRoom.left >
//						nodetemp->mRightNode->mSelectRoom.right - nodetemp->mRightNode->mSelectRoom.left)
//					{
//						x1 = (nodetemp->mRightNode->mSelectRoom.left + nodetemp->mRightNode->mSelectRoom.right) / 2;
//						x2 = x1;
//						y1 = nodetemp->mRightNode->mSelectRoom.top;
//						y2 = nodetemp->mLeftNode->mSelectRoom.bottom;
//					}
//					else
//					{
//						x1 = (nodetemp->mLeftNode->mSelectRoom.left + nodetemp->mLeftNode->mSelectRoom.right) / 2;
//						x2 = x1;
//						y1 = nodetemp->mLeftNode->mSelectRoom.bottom;
//						y2 = nodetemp->mRightNode->mSelectRoom.top;
//
//					}
//
//					Line road = { x1,y1,x2,y2 };
//					mRoadList.push_back(road);
//
//				}
//				//세로로 잘랏을때
//				else if (nodetemp->mLeftNode->mY == nodetemp->mRightNode->mY)
//				{
//					float x1, y1, x2, y2;
//					if (nodetemp->mLeftNode->mSelectRoom.bottom - nodetemp->mLeftNode->mSelectRoom.top >
//						nodetemp->mRightNode->mSelectRoom.bottom - nodetemp->mRightNode->mSelectRoom.top)
//					{
//						x1 = nodetemp->mRightNode->mSelectRoom.left;
//						x2 = nodetemp->mLeftNode->mSelectRoom.right;
//						y1 = (nodetemp->mRightNode->mSelectRoom.top + nodetemp->mRightNode->mSelectRoom.bottom) / 2;
//						y2 = y1;
//					}
//					else
//					{
//						x1 = nodetemp->mLeftNode->mSelectRoom.right;
//						x2 = nodetemp->mRightNode->mSelectRoom.left;
//						y1 = (nodetemp->mLeftNode->mSelectRoom.top + nodetemp->mLeftNode->mSelectRoom.bottom) / 2;
//						y2 = y1;
//					}
//
//					Line road = { x1,y1,x2,y2 };
//					mRoadList.push_back(road);
//				}
//			}
//		}
//		else
//		{
//
//
//		}
//	}
//
//}
