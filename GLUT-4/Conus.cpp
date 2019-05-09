#include "Conus.h"

Conus::Conus()
{
}

Conus::Conus(double r, double h, color c, vertex p)
{
	R = r;
	H = h;
	Color = c;
	Position = p;
}

bool Conus::Collision(vertex e, vertex d, double t_min, double t_max)
{
	double tmp, a, b, c, D;
	//приводим к виду x*x+y*y-((z-h)*R/H)^2 = 0
	e -= Position;

	tmp = R * R / H / H;
	a = d.z * d.z * tmp - d.x * d.x - d.y * d.y;
	b = d.z * (e.z - H) * tmp - e.x * d.x - e.y * d.y;
	c = (e.z - H) * (e.z - H) * tmp - e.x * e.x - e.y * e.y;

	D = b * b - a * c;
	e += Position;
	if (D < 0)
		return false;
	if (D < eps)
	{
		t1 = -b / a;
		if ((e + d * t1).z < 0 || (e + d * t1).z > H)
			return false;
		cross = t1 > 1;
	}
	else
	{
		t1 = (-b - sqrt(D)) / a;
		tmp = (e + d * t1).z;
		cross = tmp < H && tmp > 0 && t1 > 1;

		t2 = (-b + sqrt(D)) / a;
		tmp = (e + d * t2).z;

		if (!cross)//если первый не подошел
		{
			cross = tmp < H && tmp > 0 && t2 > 1;
			if (cross)
				t1 = t2;
			else
				return false;
		}
		else//если первый подошел, проверим какой ближе t1 или t2
			if (tmp < H && tmp > 0 && t2 > 1 && t2 < t1)
				t1 = t2;
	}
	return true;
}

std::ostream& operator<<(std::ostream& out, const Conus& point)
{

}

std::istream& operator>>(std::istream& in, Conus& point)
{
	int type;
	in >> type;
}