#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(double r, color c, vertex p)
{
	R = r;
	Color = c;
	Position = p;
}

bool Plane::Collision(vertex e, vertex d, double t_min, double t_max)
{
	double D;
	D = d * Position;
	if (abs(D) < eps)
		return false;
	else
	{
		t1 = -((e * Position) + R) / D;
		cross = t1 > 1;
		return cross;
	}
}
