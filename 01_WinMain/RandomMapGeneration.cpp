#include "pch.h"
#include <stack>
#include "RandomMapGeneration.h"

void RandomMapGeneration::Init()
{
	mRoot = new Node(0, 0, WINSIZEX, WINSIZEY);
	mRoot->mLineNum = 0;

	mCurrentNode = nullptr;


}

void RandomMapGeneration::Update()
{
	if (Input::GetInstance()->GetKeyDown(VK_TAB))
	{
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
	}
	if (Input::GetInstance()->GetKeyDown(VK_RETURN))
	{
		s.push(mRoot);
		MakeRoad();
		int i = 0;
	}
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))

	{
		/*
		//한단계씩진행
		if (mCurrentNode == nullptr)
			mCurrentNode = mRoot;
		else
		{
			mCurrentNode = q.front();
			q.pop();
		}
		Devide(mCurrentNode);*/
		mRoot->MakeRoom();

	}

}

void RandomMapGeneration::Render()
{

	mRoot->Render();

	ID2D1SolidColorBrush* brush = nullptr;
	D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &brush);
	for (int i = 0; i < mRoadList.size(); i++)
	{

		D2DRenderer::GetInstance()->GetRenderTarget()->DrawLine({ mRoadList[i].x1,mRoadList[i].y1 }, { mRoadList[i].x2, mRoadList[i].y2 }, brush);
	}

}

Node::Node(float x, float y, float sizex, float sizey)
{
	mX = x;
	mY = y;
	mSizeX = sizex;
	mSizeY = sizey;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

	mLeftNode = nullptr;
	mRightNode = nullptr;
	mParentNode = nullptr;
}
void Node::Render()
{
	RenderRect(mRect);
	if (mLeftNode == nullptr)
	{
		RenderRect(mSelectRoom, D2D1::ColorF::Red);
	}
	if (mLeftNode != nullptr)
	{
		mLeftNode->Render();
	}
	if (mRightNode != nullptr)
	{
		mRightNode->Render();
	}
}

void RandomMapGeneration::Devide(Node* node)
{

	bool direction = Random::GetInstance()->RandomInt(0, 1);
	if (!direction && node->mSizeX < 400)
	{
		direction = 1;
	}
	else if (direction && node->mSizeY < 400)
	{
		direction = 0;
	}
	if (direction == 0 && node->mSizeX > 400)//세로로짜르기
	{
		float x = 0;
		while (x < 200 || node->mSizeX - x < 200)
		{
			if (x < 200 && node->mSizeY - x < 200)
				return;
			x = Random::GetInstance()->RandomInt(node->mSizeX * 0.3f, node->mSizeX * 0.7f);
		}
		Node* leftnode = new Node(node->mX, node->mY, x, node->mSizeY);
		Node* rightnode = new Node(node->mX + x, node->mY, node->mSizeX - x, node->mSizeY);
		leftnode->mParentNode = node;
		rightnode->mParentNode = node;
		node->mLeftNode = leftnode;
		node->mRightNode = rightnode;
		node->mLeftNode->mLineNum = node->mLineNum + 1;
		node->mRightNode->mLineNum = node->mLineNum + 1;
		q.push(node->mLeftNode);
		q.push(node->mRightNode);
	}
	else if (direction == 1 && node->mSizeY > 400)          // 가로로짜르기
	{
		float y = 0;
		while (y < 200 || node->mSizeY - y < 200)
		{
			if (y < 200 && node->mSizeY - y < 200)
				return;
			y = Random::GetInstance()->RandomInt(node->mSizeY * 0.3f, node->mSizeY * 0.7f);
		}
		Node* leftnode = new Node(node->mX, node->mY, node->mSizeX, y);
		Node* rightnode = new Node(node->mX, node->mY + y, node->mSizeX, node->mSizeY - y);
		leftnode->mParentNode = node;
		rightnode->mParentNode = node;
		node->mLeftNode = leftnode;
		node->mRightNode = rightnode;
		node->mLeftNode->mLineNum = node->mLineNum + 1;
		node->mRightNode->mLineNum = node->mLineNum + 1;
		q.push(node->mLeftNode);
		q.push(node->mRightNode);

	}


}

void Node::MakeRoom()
{
	if (mLeftNode != nullptr)
	{
		mLeftNode->MakeRoom();

		for (int i = 0; i < mLeftNode->mRoomList.size(); i++)
		{
			mRoomList.push_back(mLeftNode->mRoomList[i]);
		}
	}
	if (mRightNode != nullptr)
	{
		mRightNode->MakeRoom();

		for (int i = 0; i < mRightNode->mRoomList.size(); i++)
		{
			mRoomList.push_back(mRightNode->mRoomList[i]);
		}
	}
	if (mLeftNode == nullptr)
	{
		float x = 5 * Random::GetInstance()->RandomInt(5, 10);
		float y = 5 * Random::GetInstance()->RandomInt(5, 10);
		mSelectRoom = RectMake(
			mX + x,
			mY + y,
			mSizeX - Random::GetInstance()->RandomInt(x + 25, 100),
			mSizeY - Random::GetInstance()->RandomInt(y + 25, 100)
		);
		mRoomList.push_back(mSelectRoom);
	}
}

void RandomMapGeneration::MakeRoad()
{
	while (!s.empty())
	{
		Node* nodetemp = s.top();
		s.pop();
		if (nodetemp->mLeftNode != nullptr)
		{
			if (!nodetemp->mIsVisit)
			{
				s.push(nodetemp);
				s.push(nodetemp->mRightNode);
				s.push(nodetemp->mLeftNode);
				nodetemp->mIsVisit = 1;
			}
			else
			{

				//좌측방의 셀렉트룸설정.
				float x = (nodetemp->mRightNode->mRect.left + nodetemp->mRightNode->mRect.right) / 2;
				float y = (nodetemp->mRightNode->mRect.top + nodetemp->mRightNode->mRect.bottom) / 2;
				float distance = 100000;

				for (int i = 0; i < nodetemp->mLeftNode->mRoomList.size(); i++)
				{
					float x2 = (nodetemp->mLeftNode->mRoomList[i].left + nodetemp->mLeftNode->mRoomList[i].right) / 2;
					float y2 = (nodetemp->mLeftNode->mRoomList[i].top + nodetemp->mLeftNode->mRoomList[i].bottom) / 2;
					float distance2 = Math::GetDistance(x, y, x2, y2);
					if (distance > distance2)
					{
						distance = distance2;
						nodetemp->mLeftNode->mSelectRoom = nodetemp->mLeftNode->mRoomList[i];
					}
				}


				//우측방의 셀렉트룸설정.
				x = (nodetemp->mLeftNode->mSelectRoom.left + nodetemp->mLeftNode->mSelectRoom.right) / 2;
				y = (nodetemp->mLeftNode->mSelectRoom.top + nodetemp->mLeftNode->mSelectRoom.bottom) / 2;
				distance = 100000;

				for (int i = 0; i < nodetemp->mRightNode->mRoomList.size(); i++)
				{
					float x2 = (nodetemp->mRightNode->mRoomList[i].left + nodetemp->mRightNode->mRoomList[i].right) / 2;
					float y2 = (nodetemp->mRightNode->mRoomList[i].top + nodetemp->mRightNode->mRoomList[i].bottom) / 2;
					float distance2 = Math::GetDistance(x, y, x2, y2);
					if (distance > distance2)
					{
						distance = distance2;
						nodetemp->mRightNode->mSelectRoom = nodetemp->mRightNode->mRoomList[i];
					}
				}


				//가로로 잘랏을때
				if (nodetemp->mLeftNode->mX == nodetemp->mRightNode->mX)
				{
					float x1, y1, x2, y2;
					if (nodetemp->mLeftNode->mSelectRoom.right - nodetemp->mLeftNode->mSelectRoom.left >
						nodetemp->mRightNode->mSelectRoom.right - nodetemp->mRightNode->mSelectRoom.left)
					{
						x1 = (nodetemp->mRightNode->mSelectRoom.left + nodetemp->mRightNode->mSelectRoom.right) / 2;
						x2 = x1;
						y1 = nodetemp->mRightNode->mSelectRoom.top;
						y2 = nodetemp->mLeftNode->mSelectRoom.bottom;
					}
					else
					{
						x1 = (nodetemp->mLeftNode->mSelectRoom.left + nodetemp->mLeftNode->mSelectRoom.right) / 2;
						x2 = x1;
						y1 = nodetemp->mLeftNode->mSelectRoom.bottom;
						y2 = nodetemp->mRightNode->mSelectRoom.top;

					}

					Line road = { x1,y1,x2,y2 };
					mRoadList.push_back(road);

				}
				//세로로 잘랏을때
				else if (nodetemp->mLeftNode->mY == nodetemp->mRightNode->mY)
				{
					float x1, y1, x2, y2;
					if (nodetemp->mLeftNode->mSelectRoom.bottom - nodetemp->mLeftNode->mSelectRoom.top >
						nodetemp->mRightNode->mSelectRoom.bottom - nodetemp->mRightNode->mSelectRoom.top)
					{
						x1 = nodetemp->mRightNode->mSelectRoom.left;
						x2 = nodetemp->mLeftNode->mSelectRoom.right;
						y1 = (nodetemp->mRightNode->mSelectRoom.top + nodetemp->mRightNode->mSelectRoom.bottom) / 2;
						y2 = y1;
					}
					else
					{
						x1 = nodetemp->mLeftNode->mSelectRoom.right;
						x2 = nodetemp->mRightNode->mSelectRoom.left;
						y1 = (nodetemp->mLeftNode->mSelectRoom.top + nodetemp->mLeftNode->mSelectRoom.bottom) / 2;
						y2 = y1;
					}

					Line road = { x1,y1,x2,y2 };
					mRoadList.push_back(road);
				}
			}
		}
		else
		{


		}
	}

}
