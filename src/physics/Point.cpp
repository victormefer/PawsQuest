#include "Point.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

/*************************************************************
 *
 * getX
 *
 *************************************************************/
float Point::getX() const
{
	return x;
}

/*************************************************************
 *
 * getY
 *
 *************************************************************/
float Point::getY() const
{
	return y;
}

/*************************************************************
 *
 * setX
 *
 *************************************************************/
void Point::setX(float x)
{
	this->x = x;
}

/*************************************************************
 *
 * setY
 *
 *************************************************************/
void Point::setY(float y)
{
	this->y = y;
}

/*************************************************************
 *
 * operator+
 *
 *************************************************************/
Point Point::operator+ (const Point& p2)
{
	Point point;
	point.x = this->x + p2.x;
	point.y = this->y + p2.y;
	return point;
}

/*************************************************************
 *
 * operator-
 *
 *************************************************************/
Point Point::operator- (const Point& p2)
{
	Point point;
	point.x = this->x - p2.x;
	point.y = this->y - p2.y;
	return point;
}

/*************************************************************
 *
 * Rotate
 *
 *************************************************************/
void Point::Rotate(Point point, float module, float angle)
{
	angle = angle * PI / 180; // converter para radianos
	this->x = module * sin(angle) + point.getX();
	this->y = module * cos(angle) + point.getY();
}

/*************************************************************
 *
 * Distance
 *
 *************************************************************/
float Distance(Point p1, Point p2)
{
	return sqrt( pow ( p2.getX() - p1.getX(), 2.0 ) + pow ( p2.getY() - p1.getY(), 2.0 ) );
}

/*************************************************************
 *
 * LineInclination
 *
 *************************************************************/
float LineInclination(Point p1, Point p2)
{
	float angle = atan( (p2.getY() - p1.getY()) / (p2.getX() - p1.getX()) ) * 180 / PI;
	if (p1.getX() > p2.getX())
		return angle + 180;
	return angle;
}

/*************************************************************
 *
 * ProjectX
 *
 *************************************************************/
float ProjectX(float module, float angle)
{
	angle = angle * PI / 180;
	return cos(angle) * module;
}

/*************************************************************
 *
 * ProjectY
 *
 *************************************************************/
float ProjectY(float module, float angle)
{
	angle = angle * PI / 180;
	return sin(angle) * module;
}
