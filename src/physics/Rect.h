#ifndef RECT_H_
#define RECT_H_

#include "Point.h"

class Rect
{
	public:
		Rect(): x(0), y(0), w(0), h(0) {};
		Rect(float,float,float,float);
		bool IsInside(float,float);
		float x;
		float y;
		float w;
		float h;

		// Somar retangulo com ponto para mover retangulo
		Rect operator+ (const Point&);

		Point Center();
		void Center(float* x, float* y);
};

// Distancia entre os centros dos retangulos
float Distance(Rect r1, Rect r2);

bool IsInside(Rect rect, Point point);

#endif
