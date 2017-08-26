#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#define PI 3.14159265359

class Point
{
public:
	Point(): x(0), y(0) {};
	Point(float,float);
	float getX() const;
	float getY() const;
	void setX(float);
	void setY(float);
	Point operator+ (const Point&);
	Point operator- (const Point&);
	// Rotacionar em relacao a outro ponto, a partir de uma distancia e angulo, sentido horario
	void Rotate(Point point, float module, float angle);
	float x;
	float y;
};

float Distance(Point p1, Point p2);

// Inclinação da reta formada por dois pontos
float LineInclination(Point p1, Point p2);

// Projecao em X e Y de um vetor
float ProjectX(float module, float angle);
float ProjectY(float module, float angle);

#endif
