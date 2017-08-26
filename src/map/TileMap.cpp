#include "TileMap.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>

std::vector<int> TileMap::tileMatrix;
std::vector<Entity*> TileMap::colliderMatrix;
int TileMap::mapWidth = 0;
int TileMap::mapHeight = 0;
int TileMap::mapDepth = 0;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
TileMap::TileMap(std::string file, TileSet* tileSet)
{
	// std::cout << "OI" << std::endl;
	tileMatrix.clear();
	colliderMatrix.clear();
	// std::cout << "TCHAU" << std::endl;

	Load(file);
	this->tileSet = tileSet;

	for(int i=0; i<mapHeight*mapWidth*mapDepth; i++)
	{
		// std::cout << i << std::endl;
		colliderMatrix.push_back(NULL);
	}
}

/*************************************************************
 *
 * Load
 *
 *************************************************************/
void TileMap::Load(std::string file)
{
	std::ifstream fin;
	fin.open(file, std::ios::in);
	char comma;

	fin >> mapHeight;
	fin >> comma;
	fin >> mapWidth;
	fin >> comma;
	fin >> mapDepth;
	fin >> comma;

	for(int i=0; i<mapHeight*mapWidth*mapDepth; i++)
	{
		int aux;
		fin >> aux;
		//cout << aux;
		tileMatrix.push_back(aux-1);
		fin >> comma;
		//cout << comma;
	}

	Camera::SetMaxWidth(mapHeight * 64);
	Camera::SetMaxHeight(mapWidth * 64);
}

/*************************************************************
 *
 * SetTileSet
 *
 *************************************************************/
void TileMap::SetTileSet(TileSet* tileSet)
{
	this->tileSet = tileSet;
}

/*************************************************************
 *
 * At
 *
 *************************************************************/
int& TileMap::At(int x, int y, int z)
{
	return tileMatrix[(x+(y*mapHeight)+(z*mapWidth*mapHeight))];
}

/*************************************************************
 *
 * At
 *
 *************************************************************/
void TileMap::SetEntity(Entity* entity, int x, int y, int z)
{
	colliderMatrix[(x+(y*mapHeight)+(z*mapWidth*mapHeight))] = entity;
}

/*************************************************************
 *
 * At
 *
 *************************************************************/
Entity* TileMap::AtEntity(int x, int y, int z)
{
	return colliderMatrix[(x+(y*mapHeight)+(z*mapWidth*mapHeight))];
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void TileMap::Render(int cameraX, int cameraY)
{
	for(int i=0; i<mapDepth; i++)
	{
		RenderLayer(i,cameraX,cameraY);
	}
}

/*************************************************************
 *
 * RenderLayer
 *
 *************************************************************/
void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
	for( int x =  (cameraX / 64 - 2 < 0) ? 0 : (cameraX / 64 - 2) ;
		x < (cameraX + 1024) / 64 + 2 && x < mapHeight;
		x++)
		for( int y = (cameraY / 64 - 2 < 0) ? 0 : (cameraY / 64 - 2) ;
			y < (cameraY + 600) / 64 + 2 && y < mapWidth;
			y++)
		{
			switch(layer)
			{
			case 0:
				this->tileSet->Render(At(x,y,layer),
						x*tileSet->GetTileWidth(),
						y*tileSet->GetTileHeight());
				break;
			case 1:
				this->tileSet->Render(At(x,y,layer),
						x*tileSet->GetTileWidth(),
						y*tileSet->GetTileHeight());
				break;
			default:
				break;
			}
		}
}

/*************************************************************
 *
 * GetWidth
 *
 *************************************************************/
int TileMap::GetWidth()
{
	return mapWidth;
}

/*************************************************************
 *
 * GetHeight
 *
 *************************************************************/
int TileMap::GetHeight()
{
	return mapHeight;
}

/*************************************************************
 *
 * GetDepth
 *
 *************************************************************/
int TileMap::GetDepth()
{
	return mapDepth;
}
