#include "TileSet.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
TileSet::TileSet(int tileWidth, int tileHeight, std::string file): tileSet(new RenderComponent(file))
{
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->rows = tileSet->GetHeight()/tileHeight;
	this->columns = tileSet->GetWidth()/tileWidth;
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void TileSet::Render(unsigned index, float x, float y)
{
	int auxY;
	int auxX;
	//std::cout<<(int)index;
	if (index < unsigned(rows*columns))
	{
		//auxY = (int)index/(columns+1);
		//auxX = (int)index-(columns*auxX-1);
		auxX = index%columns;
		auxY = index/columns;
		//std::cout<<'[' + auxY + ']';
		//std::cout<<'[' + auxX + ']';
		tileSet->SetClip(tileWidth*auxX,tileHeight*auxY,tileWidth,tileHeight);
		tileSet->Render(new TransformComponent(Rect(x, y, 0, 0), 0, Point(1,1)));
	}
}

/*************************************************************
 *
 * GetTileWidth
 *
 *************************************************************/
int TileSet::GetTileWidth()
{
	return tileWidth;
}

/*************************************************************
 *
 * GetTileHeight
 *
 *************************************************************/
int TileSet::GetTileHeight()
{
	return tileHeight;
}






