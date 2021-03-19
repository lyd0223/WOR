#include "pch.h"

#include "MonsterObject.h"
#include "TileMap.h"
#include "Tile.h"
#include "Player.h"

MonsterObject::MonsterObject(const string & name)
	: MovingObject(name) {}