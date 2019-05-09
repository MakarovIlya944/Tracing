#include "GemObjects.h"

void GemObject::SetH(double h)
{
	H = h;
}

void GemObject::SetS(double _s)
{
	if (_s < 0)
		s = -1;
	else
		s = _s;
}

///
bool GemObject::Collision(vertex e, vertex d, double t_min, double t_max)
{
	double a, b, c, tmp, D;
	vertex A[4], N[4], v1,v2;
	double n[4];
	switch (curType)
	{
	case sphere:
		//приводим к каноничному виду
		e -= Position;
		e *= 1 / R;

		cross = false;
		a = d*d; b = e*d; c = e*e - 1;
		D = b*b - a*c;
		if (D < 0)
			return false;
		if (D < eps)
		{
			t1 = -b / a *R;
			cross = t1 > t_min;
		}
		else
		{
			t2 = (-b + sqrt(D)) / a*R;
			t1 = (-b - sqrt(D)) / a*R;
			cross = t1 > t_min;
			if (!cross && t2 >t_min)
			{
				t1 = t2;
				cross = true;
			}
		}
		return cross;
		break;
	case conus:
		//приводим к виду x*x+y*y-((z-h)*R/H)^2 = 0
		e -= Position;
		
		tmp = R * R / H / H;
		a = d.z*d.z*tmp - d.x*d.x - d.y*d.y;
		b = d.z*(e.z - H)*tmp - e.x*d.x - e.y*d.y;
		c = (e.z - H)*(e.z - H)*tmp - e.x*e.x - e.y*e.y;

		D = b*b - a*c;
		e += Position;
		if (D < 0)
			return false;
		if (D < eps)
		{
			t1 = -b / a;
			if ((e + d*t1).z < 0 || (e + d*t1).z > H)
				return false;
			cross = t1 > 1;
		}
		else
		{
			t1 = (-b - sqrt(D)) / a;
			tmp = (e + d*t1).z;
			cross = tmp < H && tmp > 0 && t1 > 1;

			t2 = (-b + sqrt(D)) / a;
			tmp = (e + d*t2).z;

			if (!cross)//если первый не подошел
			{
				cross = tmp < H && tmp > 0 && t2 > 1;
				if (cross)
					t1 = t2;
				else
					return false;
			}
			else//если первый подошел, проверим какой ближе t1 или t2
			{
				if (tmp < H && tmp > 0 && t2 > 1 && t2 < t1)
					t1 = t2;
			}
		}
		return true;
		break;
	case thetra:
		e -= Position;
		//основание
		A[0] = vertex(1,0,0);
		A[1] = vertex(-0.5,0.87,0);
		A[2] = vertex(-0.5,-0.87,0);
		A[3] = vertex(0,0,1.41);

		//ABC
		N[0] = vertex(0, 0, -1);
		n[0] = 0;
		//CBE
		N[1] = vertex(1.22, 2.12, 0.87);
		n[1] = -1.22;
		//AEC
		N[2] = vertex(1.22,-2.12,0.87);
		n[2] = -1.22;
		//ABE
		N[3] = vertex(-2.45, 0, 0.87);
		n[3] = -1.22;

		/*
		N ABC, CBE, AEC, ABE
		ABCE
		C-0
		B-1
		A-2
		E-3
		0,1,2 CBA
		0,1,3 CBE
		0,2,3 CAE
		1,2,3 BAE
		i/3 | i/2 + 1 | (i+2)/3+2
		*/
		t1 = 1E+100;
		cross = false;

		for (int i(0); i < 4; i++)
		{
			D = d*N[i];
			if (abs(D) > eps)//если есть пересечение
			{
				t2 = -((e*N[i]) + n[i]) / D;
				if (t2 > t_max || t2 < t_min)
					continue;
				//проверим на попадание в треугольник
				a = 0;
				v1 = e + d*t2;
				a += GetAng(A[i / 3], v1, A[(i + 2) / 3 + 2]);
				a += GetAng(A[i / 3], v1, A[i / 2 + 1]);
				a += GetAng(A[i / 2 + 1], v1, A[(i + 2) / 3 + 2]);

				if (abs(a - 2*Pi) < 1E-3)//есть попадание
					if (t2 < t1)//она ближе
					{
						t1 = t2;
						cross = true;
						thetra_norm = N[i];
					}
			}
		}
		return cross;
		break;
	case plane:
		D = d*Position;
		if (abs(D) < eps)
			return false;
		else
		{
			t1 = -((e*Position) + R) / D;
			cross = t1 > 1;
			return cross;
		}
		break;
	default:
		break;
	}
	return false;
}

double GemObject::GetAng(vertex A, vertex F, vertex B)
{
	vertex v1 = A - F;
	vertex v2 = B - F;
	return v1^v2;
}

GemObject::GemObject()
{
}

GemObject::~GemObject()
{
}
