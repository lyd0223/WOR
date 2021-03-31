#include "pch.h"
#include "PathFinder.h"
#include "Tile.h"
#include "TileMap.h"

#define TileSize 48

int PathFinder::CalcHeuristic(int idX1, int idY1, int idX2, int idY2, int tileSize) 
{
	int dx = abs(idX1 - idX2);
	int dy = abs(idY1 - idY2);
	int diagonal = min(dx, dy);
	return (dx - diagonal + dy - diagonal) * tileSize + diagonal * tileSize* sqrtf(2);
}

vector<class Tile*> PathFinder::FindPath(class TileMap* tileList, int startIndexX, int startIndexY, int arrivalX, int arrivalY)
{
	vector<Tile*> result;

	if (startIndexX == arrivalX && startIndexY == arrivalY) return result;

	int tileCountX = tileList->GetTileList().size();
	int tileCountY = tileList->GetTileList()[0].size();

	if (startIndexX < 0 || startIndexX >= tileCountX) return result;
	if (startIndexY < 0 || startIndexY >= tileCountY) return result;
	if (arrivalX < 0 || arrivalX >= tileCountX) return result;
	if (arrivalY < 0 || arrivalY >= tileCountY) return result;

	vector<vector<DummyTile>> dummyList;

	dummyList.assign(tileCountY, vector<DummyTile>());
	for (int i = 0; i < dummyList.size(); i++) {
		dummyList[i].assign(tileCountX, DummyTile());
	}

	dummyList[startIndexY][startIndexX].IsOpen = true;
	dummyList[startIndexY][startIndexX].IsClose = true;
	dummyList[startIndexY][startIndexX].CostFromStart = 0;
	dummyList[startIndexY][startIndexX].CostToEnd = CalcHeuristic(startIndexX, startIndexY, arrivalX, arrivalY, TileSize);
	dummyList[startIndexY][startIndexX].CostTotal = dummyList[startIndexY][startIndexX].CostToEnd;

	vector<Tile*> openList;

	Tile* startTile = tileList->GetTileList(startIndexX, startIndexY);
	Tile* arrivalTile = tileList->GetTileList(arrivalX, arrivalY);
	Tile* currentTile = startTile;

	while (true) {
		if (currentTile == nullptr) return result;

		int currentIndexX = currentTile->GetX() / TileSize;
		int currentIndexY = currentTile->GetY() / TileSize;		

		bool b=0;
		for (int y = currentIndexY - 1; y <= currentIndexY + 1; y++) {

			if (y < 0 || y >= tileCountY) continue;

			for (int x = currentIndexX - 1; x <= currentIndexX + 1; x++) {
				
				if (x < 0 || x >= tileCountX) continue;

				if (x == currentIndexX && y == currentIndexY) continue;

				if (dummyList[y][x].IsClose == true) continue;

				if (tileList->GetTileList(x, y)->GetType() == Type::Wall ||
					tileList->GetTileList(x, y)->GetType() == Type::Cliff)
				{
					dummyList[y][x].IsClose = true;
					dummyList[y][x].IsOpen = true;
					b = 1;
					if (b) return result;
					continue;
				}

				if (dummyList[y][x].IsOpen == false) 
				{
					dummyList[y][x].IsOpen = true;
					dummyList[y][x].Parent = currentTile;
					dummyList[y][x].CostFromStart = dummyList[currentTile->GetY() / TileSize][currentTile->GetX() / TileSize].CostFromStart + 1;
					dummyList[y][x].CostToEnd = CalcHeuristic(x, y, arrivalX, arrivalY, TileSize);
					dummyList[y][x].CostTotal = dummyList[y][x].CostFromStart + dummyList[y][x].CostToEnd;

					openList.push_back(tileList->GetTileList(x, y));
				}
				else 
				{
					int newFromCost = dummyList[currentIndexY][currentIndexX].CostFromStart + 1;

					if (newFromCost < dummyList[y][x].CostFromStart)
					{
						dummyList[y][x].CostFromStart = newFromCost;
						dummyList[y][x].CostToEnd = dummyList[y][x].CostFromStart + dummyList[y][x].CostToEnd;
						dummyList[y][x].Parent = currentTile;
					}
				}
			}
		}

		Tile* tileMin = nullptr;

		for (int i = 0; i < openList.size(); i++) {
			if (openList[i] == currentTile) {
				openList.erase(openList.begin() + i);
				i--;
				continue;
			}

			if (tileMin == nullptr) {
				tileMin = openList[i];
				continue;
			}

			if (dummyList[openList[i]->GetY() / TileSize][openList[i]->GetX() / TileSize].CostTotal <
				dummyList[tileMin->GetY() / TileSize][tileMin->GetX() / TileSize].CostToEnd) {

				tileMin = openList[i];
			}
		}

		if (tileMin != nullptr) {
			dummyList[tileMin->GetY() / TileSize][tileMin->GetX() / TileSize].IsClose = true;
			currentTile = tileMin;
		}
		else {
			return result;
		}

		if (tileMin == arrivalTile) {
			Tile* temp = tileMin;
			result.push_back(temp);
			while (dummyList[temp->GetY() / TileSize][temp->GetX() / TileSize].Parent != nullptr) {
				temp = dummyList[temp->GetY() / TileSize][temp->GetX() / TileSize].Parent;
				result.push_back(temp);
			}

			reverse(result.begin(), result.end());

			return result;
			}

	}

	return result;
}
