#pragma once
#include "GemObjects.h"

class Sphere : GemObject
{
	double R;
public:
	Sphere();
	Sphere(double r, color c, vertex p);
	
	double GetR() { return R; }
	double SetR(double r) { if (r > eps)R = r; else throw exception("Invalid radius"); }

	bool Collision(vertex e, vertex d, double t_min, double t_max);
};