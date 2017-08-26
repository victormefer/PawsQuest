#ifndef TILESET_H_
#define TILESET_H_

#include "../components/RenderComponent.h"

class TileSet{
	public:
		TileSet(int,int,std::string);
		void Render(unsigned,float,float);
		int GetTileWidth();
		int GetTileHeight();
	private:
		RenderComponent* tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};

#endif
