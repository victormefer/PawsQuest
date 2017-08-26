#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "TileSet.h"
#include "../Camera.h"
#include "../entities/Entity.h"

#include <vector>

class TileMap
{
public:
	TileMap(std::string,TileSet*);
	void Load(std::string);
	void SetTileSet(TileSet*);
	static int& At(int,int,int);
	static void SetEntity(Entity*, int,int,int);
	static Entity* AtEntity(int,int,int);
	void Render(int,int);
	void RenderLayer(int,int,int);
	int GetWidth();
	int GetHeight();
	int GetDepth();

	static std::vector<int> tileMatrix;
	static std::vector<Entity*> colliderMatrix;
	static int mapWidth;
	static int mapHeight;
	static int mapDepth;
private:
	TileSet* tileSet;
};

#endif
