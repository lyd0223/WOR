#include "pch.h"
#include "RandomMapGeneration.h"
#include "TileMap.h"
#include "Tile.h"
#include "Player.h"
void RandomMapGeneration::Init()
{
	mRoot = new Node(0, 0, 150, 150);

	mCurrentNode = nullptr;

	mTileMap = new TileMap();

	s.push(mRoot);

}

void RandomMapGeneration::CreateRandomMap1()
{
	Init();
	//맵나누기 bfs
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
void RandomMapGeneration::CreateRandomMap2()
{
	//방 만들기 dfs 재귀
	mRoot->MakeRoom(mTileMap);

	//길 만들기 dfs 스택
	MakeRoad();
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
	if (!direction && node->mSizeX < 50)
	{
		direction = 1;
	}
	else if (direction && node->mSizeY < 50)
	{
		direction = 0;
	}
	if (direction == 0 && node->mSizeX > 50)//세로로짜르기
	{
		float x = 0;
		while (x < 25 || node->mSizeX - x < 25)
		{
			if (x < 25 && node->mSizeY - x < 25)
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
	else if (direction == 1 && node->mSizeY > 50)          // 가로로짜르기
	{
		float y = 0;
		while (y < 25 || node->mSizeY - y < 25)
		{
			if (y < 25 && node->mSizeY - y < 25)
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
		int x1;
		int y1;
		if (mSizeX < 30)
			x1 = 2;
		else if (mSizeX >= 30 && mSizeX < 40)
			x1 = Random::GetInstance()->RandomInt(3, 5);
		else if (mSizeX >= 40 && mSizeX < 50)
			x1 = Random::GetInstance()->RandomInt(10, 13);
		else
			x1 = Random::GetInstance()->RandomInt(15, 18);
		if (mSizeY < 30)
			y1 = 2;
		else if (mSizeY >= 30 && mSizeY < 40)
			y1 = Random::GetInstance()->RandomInt(3, 5);
		else if (mSizeY >= 40 && mSizeY < 50)
			y1 = Random::GetInstance()->RandomInt(10, 13);
		else
			y1 = Random::GetInstance()->RandomInt(15, 18);
		int x2;
		int y2;
		if (mSizeX < 30)
			x2 = 2;
		else if (mSizeX >= 30 && mSizeX < 40)
			x2 = Random::GetInstance()->RandomInt(3, 5);
		else if (mSizeX >= 40 && mSizeX < 50)
			x2 = Random::GetInstance()->RandomInt(10, 13);
		else
			x2 = Random::GetInstance()->RandomInt(15, 18);
		if (mSizeY < 30)
			y2 = 2;
		else if (mSizeY >= 30 && mSizeY < 40)
			y2 = Random::GetInstance()->RandomInt(3, 5);
		else if (mSizeY >= 40 && mSizeY < 50)
			y2 = Random::GetInstance()->RandomInt(10, 13);
		else
			y2 = Random::GetInstance()->RandomInt(15, 18);
		mSelectRoom = {
			mX + x1,
			mY + y1,
			mSizeX - (x2 + x1),
			mSizeY - (y2 + y1)
		};
		//타일깔기
		for (int y = mSelectRoom.y; y < mSelectRoom.y + mSelectRoom.sizeY; y++)
		{
			for (int x = mSelectRoom.x; x < mSelectRoom.x + mSelectRoom.sizeX; x++)
			{
				tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireFloor"));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(Random::GetInstance()->RandomInt(6));
				tilemap->GetTileList()[y][x]->SetFrameIndexY(Random::GetInstance()->RandomInt(1));
				tilemap->GetTileList()[y][x]->SetType(Type::Floor);
			}
		}
		//사방 벽 만들기.
		{
			int y = mSelectRoom.y;
			for (int x = mSelectRoom.x; x < mSelectRoom.x + mSelectRoom.sizeX; x++)
			{
				tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(1);
				tilemap->GetTileList()[y][x]->SetFrameIndexY(0);
				tilemap->GetTileList()[y][x]->SetType(Type::Wall);
			}
		}
		{
			int y = mSelectRoom.y + mSelectRoom.sizeY-1;
			for (int x = mSelectRoom.x; x < mSelectRoom.x + mSelectRoom.sizeX; x++)
			{
				tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(1);
				tilemap->GetTileList()[y][x]->SetFrameIndexY(2);
				tilemap->GetTileList()[y][x]->SetType(Type::Wall);
			}
		}
		{
			int x = mSelectRoom.x;
			for (int y = mSelectRoom.y; y < mSelectRoom.y + mSelectRoom.sizeY; y++)
			{
				tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(0);
				tilemap->GetTileList()[y][x]->SetFrameIndexY(1);
				tilemap->GetTileList()[y][x]->SetType(Type::Wall);
			}
		}
		{
			int x = mSelectRoom.x + mSelectRoom.sizeX - 1;
			for (int y = mSelectRoom.y; y < mSelectRoom.y + mSelectRoom.sizeY; y++)
			{
				tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
				tilemap->GetTileList()[y][x]->SetFrameIndexX(2);
				tilemap->GetTileList()[y][x]->SetFrameIndexY(1);
				tilemap->GetTileList()[y][x]->SetType(Type::Wall);
			}
		}
		//꼭지점 벽
		{
			int x = mSelectRoom.x;
			int y = mSelectRoom.y;
			tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
			tilemap->GetTileList()[y][x]->SetFrameIndexX(0);
			tilemap->GetTileList()[y][x]->SetFrameIndexY(0);
			tilemap->GetTileList()[y][x]->SetType(Type::Wall);
		}
		{
			int x = mSelectRoom.x;
			int y = mSelectRoom.y + mSelectRoom.sizeY -1;
			tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
			tilemap->GetTileList()[y][x]->SetFrameIndexX(0);
			tilemap->GetTileList()[y][x]->SetFrameIndexY(2);
			tilemap->GetTileList()[y][x]->SetType(Type::Wall);
		}
		{
			int x = mSelectRoom.x + mSelectRoom.sizeX -1;
			int y = mSelectRoom.y;
			tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
			tilemap->GetTileList()[y][x]->SetFrameIndexX(2);
			tilemap->GetTileList()[y][x]->SetFrameIndexY(0);
			tilemap->GetTileList()[y][x]->SetType(Type::Wall);
		}
		{
			int x = mSelectRoom.x + mSelectRoom.sizeX-1;
			int y = mSelectRoom.y + mSelectRoom.sizeY-1;
			tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
			tilemap->GetTileList()[y][x]->SetFrameIndexX(2);
			tilemap->GetTileList()[y][x]->SetFrameIndexY(2);
			tilemap->GetTileList()[y][x]->SetType(Type::Wall);
		}
		//윗벽
		{
			for (int y = mSelectRoom.y+1; y < mSelectRoom.y +4; y++)
			{
				for (int x = mSelectRoom.x+1; x < mSelectRoom.x + mSelectRoom.sizeX-1; x++)
				{
					if (((x - mSelectRoom.x) / 3) % 3 == 0)
					{
						tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireWall1"));
					}
					else if (((x - mSelectRoom.x) / 3) % 3 == 1)
					{
						tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireWall2"));
					}
					else if (((x - mSelectRoom.x) / 3) % 3 == 2)
					{
						tilemap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireWall3"));
					}
					
					tilemap->GetTileList()[y][x]->SetFrameIndexX((x - mSelectRoom.x) % 3);
					tilemap->GetTileList()[y][x]->SetFrameIndexY((y - mSelectRoom.y-1)%3);
					tilemap->GetTileList()[y][x]->SetType(Type::Wall);
				}
			}
		}
		
		
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
				int x = (nodetemp->mRightNode->mX + nodetemp->mRightNode->mX + nodetemp->mRightNode->mSizeX) / 2;
				int y = (nodetemp->mRightNode->mY + nodetemp->mRightNode->mY + nodetemp->mRightNode->mSizeY) / 2;
				float distance = 100000;

				for (int i = 0; i < nodetemp->mLeftNode->mRoomList.size(); i++)
				{
					int x2 = nodetemp->mLeftNode->mRoomList[i].centerX;
					int y2 = nodetemp->mLeftNode->mRoomList[i].centerY;
					float distance2 = Math::GetDistance(x, y, x2, y2);
					if (distance > distance2)
					{
						distance = distance2;
						nodetemp->mLeftNode->mSelectRoom = nodetemp->mLeftNode->mRoomList[i];
					}
				}


				//우측방의 셀렉트룸설정.
				x = nodetemp->mLeftNode->mSelectRoom.centerX;
				y = nodetemp->mLeftNode->mSelectRoom.centerY;
				distance = 100000;

				for (int i = 0; i < nodetemp->mRightNode->mRoomList.size(); i++)
				{
					int x2 = nodetemp->mRightNode->mRoomList[i].centerX;
					int y2 = nodetemp->mRightNode->mRoomList[i].centerY;
					float distance2 = Math::GetDistance(x, y, x2, y2);
					if (distance > distance2)
					{
						distance = distance2;
						nodetemp->mRightNode->mSelectRoom = nodetemp->mRightNode->mRoomList[i];
					}
				}

				//가로
				if (nodetemp->mLeftNode->mX == nodetemp->mRightNode->mX)
				{
					int x1, y1, x2, y2;
					x1 = (nodetemp->mRightNode->mSelectRoom.centerX + nodetemp->mLeftNode->mSelectRoom.centerX) / 2;
					x2 = x1;
					y1 = nodetemp->mRightNode->mSelectRoom.y;
					y2 = nodetemp->mLeftNode->mSelectRoom.y + nodetemp->mLeftNode->mSelectRoom.sizeY;
					Line road = { min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2) };
					mRoadList.push_back(road);

				}
				//세로로 잘랏을때
				else if (nodetemp->mLeftNode->mY == nodetemp->mRightNode->mY)
				{
					int x1, y1, x2, y2;
					x1 = nodetemp->mRightNode->mSelectRoom.x;
					x2 = nodetemp->mLeftNode->mSelectRoom.x + nodetemp->mLeftNode->mSelectRoom.sizeX;
					y1 = (nodetemp->mRightNode->mSelectRoom.centerY + nodetemp->mLeftNode->mSelectRoom.centerY)/2;
					y2 = y1;
					Line road = { min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2) };
					mRoadList.push_back(road);
				}
			}
		}
		else
		{
			

		}
	}
	if (s.empty())
	{
		
		for (int i = 0; i < mRoadList.size(); i++)
		{
			//가로로 길낼때
			if (mRoadList[i].y1 == mRoadList[i].y2)
			{
				for (int y = mRoadList[i].y1; y <= mRoadList[i].y1+2; y++)
				{
					for (int x = mRoadList[i].x1-1; x <= mRoadList[i].x2; x++)
					{
						mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireFloor"));
						mTileMap->GetTileList()[y][x]->SetFrameIndexX(Random::GetInstance()->RandomInt(6));
						mTileMap->GetTileList()[y][x]->SetFrameIndexY(Random::GetInstance()->RandomInt(1));
						mTileMap->GetTileList()[y][x]->SetType(Type::Floor);

					}
				}

				for (int y = mRoadList[i].y1-3 ; y < mRoadList[i].y1; y++)
				{
					for (int x = mRoadList[i].x1 - 1; x < mRoadList[i].x2 + 1; x++)
					{
						if (((x - mRoadList[i].x1) / 3) % 3 == 0)
						{
							mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireWall1"));
						}
						else if (((x - mRoadList[i].x1) / 3) % 3 == 1)
						{
							mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireWall2"));
						}
						else if (((x - mRoadList[i].x1) / 3) % 3 == 2)
						{
							mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireWall3"));
						}

						mTileMap->GetTileList()[y][x]->SetFrameIndexX((x - mRoadList[i].x1+1) % 3);
						mTileMap->GetTileList()[y][x]->SetFrameIndexY((y - mRoadList[i].y1+3) % 3);
						mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
					}
				}
				//상하벽
				for (int x = mRoadList[i].x1; x < mRoadList[i].x2; x++)
				{
					int y = mRoadList[i].y1-4;
					{
						mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
						mTileMap->GetTileList()[y][x]->SetFrameIndexX(1);
						mTileMap->GetTileList()[y][x]->SetFrameIndexY(0);
						mTileMap->GetTileList()[y][x]->SetType(Type::Wall);

					}
				}
				for (int x = mRoadList[i].x1; x < mRoadList[i].x2; x++)
				{
					int y = mRoadList[i].y1 + 3;
					{
						mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
						mTileMap->GetTileList()[y][x]->SetFrameIndexX(1);
						mTileMap->GetTileList()[y][x]->SetFrameIndexY(2);
						mTileMap->GetTileList()[y][x]->SetType(Type::Wall);

					}
				}
				//꼭지점 벽
				{
					int x = mRoadList[i].x1 - 1;
					int y = mRoadList[i].y1-4;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(0);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(1);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}
				{
					int x = mRoadList[i].x2;
					int y = mRoadList[i].y1-4;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(1);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(1);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}

				{
					int x = mRoadList[i].x2;
					int y = mRoadList[i].y1+3;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(1);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(0);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}
				{
					int x = mRoadList[i].x1 -1;
					int y = mRoadList[i].y1+3;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(0);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(0);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}

			}
			//세로로 길 낼때
			else if (mRoadList[i].x1 == mRoadList[i].x2)
			{
				//타일
				for (int y = mRoadList[i].y1-1; y <= mRoadList[i].y2+4; y++)
				{
					for (int x = mRoadList[i].x1 - 1; x <= mRoadList[i].x1+1; x++)
					{
						mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"FireFloor"));
						mTileMap->GetTileList()[y][x]->SetFrameIndexX(Random::GetInstance()->RandomInt(6));
						mTileMap->GetTileList()[y][x]->SetFrameIndexY(Random::GetInstance()->RandomInt(1));
						mTileMap->GetTileList()[y][x]->SetType(Type::Floor);

					}
				}
				//좌우 벽
				for (int y = mRoadList[i].y1; y < mRoadList[i].y2+1; y++)
				{
					int x = mRoadList[i].x1 - 2;
					{
						mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
						mTileMap->GetTileList()[y][x]->SetFrameIndexX(0);
						mTileMap->GetTileList()[y][x]->SetFrameIndexY(1);
						mTileMap->GetTileList()[y][x]->SetType(Type::Wall);

					}
				}
				for (int y = mRoadList[i].y1; y < mRoadList[i].y2+1; y++)
				{
					int x = mRoadList[i].x1 + 2;
					{
						mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire8Walls"));
						mTileMap->GetTileList()[y][x]->SetFrameIndexX(2);
						mTileMap->GetTileList()[y][x]->SetFrameIndexY(1);
						mTileMap->GetTileList()[y][x]->SetType(Type::Wall);

					}
				}
				//꼭지점 벽
				{
					int x = mRoadList[i].x1 - 2;
					int y = mRoadList[i].y1 - 1;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(1);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(0);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}
				{
					int x = mRoadList[i].x1 + 2;
					int y = mRoadList[i].y1 - 1;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(0);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(0);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}

				{
					int x = mRoadList[i].x1 - 2;
					int y = mRoadList[i].y2;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(1);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(1);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}
				{
					int x = mRoadList[i].x1 + 2;
					int y = mRoadList[i].y2;
					mTileMap->GetTileList()[y][x]->SetImage(ImageManager::GetInstance()->FindImage(L"Fire4Walls"));
					mTileMap->GetTileList()[y][x]->SetFrameIndexX(0);
					mTileMap->GetTileList()[y][x]->SetFrameIndexY(1);
					mTileMap->GetTileList()[y][x]->SetType(Type::Wall);
				}
				
			}
			
		}
		


	}

}

void RandomMapGeneration::RandomMonsterCreate()
{
	
	for (int i = 0; i < 8; i++)
	{
		mEnemyRoomNum.push_back(Random::GetInstance()->RandomInt(mRoot->mRoomList.size()*i /8+1, mRoot->mRoomList.size()* (i+1)/8-1));
	}
		
	for (int i = 0; i < mEnemyRoomNum.size(); i++)
	{
		float x, y;
		x = mRoot->mRoomList[mEnemyRoomNum[i]].centerX - 5;
		y = mRoot->mRoomList[mEnemyRoomNum[i]].centerY - 5;
		ParticleManager::GetInstance()->MakeEnemyCreate(x * TileSize, y * TileSize, MonsterName::Zombie, mRoot->mRoomList[mEnemyRoomNum[i]]);
		x = mRoot->mRoomList[mEnemyRoomNum[i]].centerX + 5;
		y = mRoot->mRoomList[mEnemyRoomNum[i]].centerY - 5;
		ParticleManager::GetInstance()->MakeEnemyCreate(x * TileSize, y * TileSize, MonsterName::Zombie, mRoot->mRoomList[mEnemyRoomNum[i]]);
		x = mRoot->mRoomList[mEnemyRoomNum[i]].centerX - 5;
		y = mRoot->mRoomList[mEnemyRoomNum[i]].centerY + 5;
		ParticleManager::GetInstance()->MakeEnemyCreate(x * TileSize, y * TileSize, MonsterName::Zombie, mRoot->mRoomList[mEnemyRoomNum[i]]);
		x = mRoot->mRoomList[mEnemyRoomNum[i]].centerX + 5;
		y = mRoot->mRoomList[mEnemyRoomNum[i]].centerY + 5;
		ParticleManager::GetInstance()->MakeEnemyCreate(x * TileSize, y * TileSize, MonsterName::Zombie, mRoot->mRoomList[mEnemyRoomNum[i]]);
	}

	
}

void RandomMapGeneration::RandomPlayerPosition(Player* player)
{
	
	mPlayerSpawnRoomNum = Random::GetInstance()->RandomInt(mRoot->mRoomList.size());
	player->SetX(mRoot->mRoomList[mPlayerSpawnRoomNum].centerX * TileSize);
	player->SetY(mRoot->mRoomList[mPlayerSpawnRoomNum].centerY * TileSize);
}
