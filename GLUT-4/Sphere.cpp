#include "Sphere.h"

Sphere::Sphere()
{
	R = 1;
	Position = vertex(0, 0, 0);
	Color = color(255, 255, 255);
}

Sphere::Sphere(double r = 1, color c = color(255,255,255), vertex p = vertex(0,0,0))
{
	Position = p;
	R = r;
	Color = c;
}

bool Sphere::Collision(vertex e, vertex d, double t_min, double t_max)
{
	double a, b, c, D;
	//приводим к каноничному виду
	e -= Position;
	e *= 1 / R;

	cross = false;
	a = d * d; b = e * d; c = e * e - 1;
	D = b * b - a * c;
	if (D < 0)
		return false;
	if (D < eps)
	{
		t1 = -b / a * R;
		cross = t1 > t_min;
	}
	else
	{
		t2 = (-b + sqrt(D)) / a * R;
		t1 = (-b - sqrt(D)) / a * R;
		cross = t1 > t_min;
		if (!cross && t2 > t_min)
		{
			t1 = t2;
			cross = true;
		}
	}
	return cross;
}
