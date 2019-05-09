#pragma once
#include "GemObjects.h"

class Conus : GemObject
{
	double R;
	double H;
public:
	Conus();
	Conus(double r, double h, color c, vertex p);

	double GetR() { return R; }
	double SetR(double r) { if (r > eps)R = r; else throw exception("Invalid radius"); }

	double GetH() { return H; }
	double SetH(double h) { if (h > eps)H = h; else throw exception("Invalid height"); }

	bool Collision(vertex e, vertex d, double t_min, double t_max);

	friend std::ostream& operator<< (std::ostream& out, const Conus& point);
	friend std::istream& operator>> (std::istream& in, Conus& point);
}; 
