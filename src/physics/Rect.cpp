#include "Rect.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Rect::Rect(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

/*************************************************************
 *
 * IsInside
 *
 *************************************************************/
bool Rect::IsInside(float mouseX, float mouseY)
{
	return (mouseX>x && mouseX<x+w) && (mouseY>y && mouseY<y+h);
}

/*************************************************************
 *
 * Center
 *
 *************************************************************/
Point Rect::Center()
{
	return Point ( this->x + this->w / 2, this->y + this->h / 2 );
}

/*************************************************************
 *
 * Center
 *
 *************************************************************/
void Rect::Center(float* x, float* y)
{
	*x = this->x + this->w / 2;
	*y = this->y + this->h / 2;
}

/*************************************************************
 *
 * operator+
 *
 *************************************************************/
Rect Rect::operator+ (const Point& point)
{
	Rect rect;
	rect.x = this->x + point.getX();
	rect.y = this->y + point.getY();
	rect.w = this->w;
	rect.h = this->h;
	return rect;
}

/*************************************************************
 *
 * Distance
 *
 *************************************************************/
float Distance(Rect r1, Rect r2)
{
	return Distance( r1.Center(), r2.Center() );
}

/*************************************************************
 *
 * IsInside
 *
 *************************************************************/
bool IsInside(Rect rect, Point point)
{
	return (point.x > rect.x && point.x < rect.x + rect.w) && (point.y > rect.y && point.y < rect.y + rect.h);
}
