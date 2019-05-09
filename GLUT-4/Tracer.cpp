#include "Tracer.h"

Tracer::Tracer()
{
}

Tracer::~Tracer()
{
}

void Tracer::Trace()
{
	double W, H, uc, vr;
	H = DistToScreen * tan(pi180 * AngView / 2);
	W = H * (double)width / (double)height;
	vertex d;
	color c;
	glBegin(GL_POINTS);
	for(int i(0);i<height;i++)
		for (int j(0); j < width; j++)
		{
			uc = -W + W*(2 * j) / width;
			vr = -H + H*(2 * i) / height;
			d = vertex(0);
			if (i == height / 2 -200 && j == width / 2)
				int as = 3;
			d += w * DistToScreen;
			d += u * uc;
			d += v * vr;
			curLevel = 0;
			curE = e;
			c = Trace(d, 1, 1E+7);
			glColor3ub(c.r, c.g, c.b);
			glVertex2i(j,i);
		}
	glEnd();
}

color Tracer::Trace(vertex d, double t_min, double t_max)
{
	curLevel++;
	int j = NearestCross(curE, d, t_min, t_max);
	if (j == -1)//не нашли пересечение
		return color(0, 0, 0);

	double Intensive = 0, Reflection = 0;
	vertex P;
	color c;
	color local_color, reflected_color;

	P = curE;
	P += d*t;
	switch (SceneObj[j].curType)
	{
	case sphere:
		N = P;
		N -= SceneObj[j].Position;
		break;
	case conus:
		N = vertex((P.x - SceneObj[j].Position.x) * 2, (P.y - SceneObj[j].Position.y) * 2, (P.z - SceneObj[j].Position.z - SceneObj[j].H) * -2 * (SceneObj[j].R / SceneObj[j].H)*(SceneObj[j].R / SceneObj[j].H));
		break;
	case plane:
		N = SceneObj[j].Position;
		break;
	case thetra:
		N = SceneObj[j].thetra_norm;
		break;
	default:
		break;
	}
	Intensive = CalculateLight(P, N, d*(-1), SceneObj[j].s);
	local_color = SceneObj[j].Color * Intensive;
	Reflection = SceneObj[j].refl;

	if (Reflection <= 0 || curLevel > maxLevel)
		return local_color;

	curE = P;
	d += N*((N*d)*(-2));
	reflected_color = Trace(d, 1E-1, t_max);

	c = local_color*(1 - Reflection);
	c += reflected_color*Reflection;
	return c;
}

double Tracer::CalculateLight(vertex P, vertex N, vertex V, double s)
{
	double curIntensive = 0, n_dot_l;
	for (int i(0), n(SceneLight.size()); i < n; i++)
	{
		if (SceneLight[i].type == ambient)
			curIntensive += SceneLight[i].intensity;
		else
		{
			LightVertex = SceneLight[i].direcion;
			LightVertex -= P;
			//Проверка тени
			int j = NearestCross(P, LightVertex, 1E-4, 1);
			if (j < 0 || t > 1 || t < 1E-4)//не нашли пересечения
			{
				//Диффузность
				n_dot_l = N*LightVertex;
				if (n_dot_l > 0)
					curIntensive += SceneLight[i].intensity*n_dot_l / (!N) / (!LightVertex);

				//Зеркальность
				if (s > 0)
				{
					vertex R = N*(N*LightVertex) * 2 - LightVertex;
					n_dot_l = R*V;
					if (n_dot_l > 0)
						curIntensive += SceneLight[i].intensity*pow(n_dot_l / (!R * !V), s);
				}
			}
		}
	}
	if (curIntensive > 1)
		curIntensive = 1;
	return curIntensive;
}

int Tracer::NearestCross(vertex O, vertex D, double t_min, double t_max)
{
	int j = -1;
	t = 1E+200;
	for (int i(0), n(SceneObj.size()); i < n; i++)
	{
		if (SceneObj[i].Collision(O, D, t_min, t_max))
			if (SceneObj[i].t1 < t)
			{
				t = SceneObj[i].t1;
				j = i;
			}
	}
	return j;
}
