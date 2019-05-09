#pragma once
#include "GemObjects.h"

class Plane : GemObject
{
	double R;
public:
	Plane();
	Plane(double r, color c, vertex p);

	double GetR() { return R; }
	double SetR(double r) { if (r > eps)R = r; else throw exception("Invalid d"); }

	bool Collision(vertex e, vertex d, double t_min, double t_max);
};
