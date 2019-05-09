#pragma once
#include <stdlib.h>
#include "glut.h"
#include <utility>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

enum shape_type { sphere, conus, thetra, plane };
enum light_type { ambient, diffusion };

//pi/180
const double pi180 = 0.01745329251994329576923690768489;
// abs(x) < eps <=> x~0
const double eps = 1E-10;
//Pi
const double Pi = 3.1415926535897932384626433832795;

struct vertex
{
	GLdouble x = 0, y = 0, z = 0;
	vertex() {};
	vertex(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {};
	vertex(double _x) :x(_x), y(_x), z(_x) {};

	vertex operator *(double a)
	{
		return vertex(x*a, y*a, z*a);
	}

	void operator *=(double a)
	{
		x *= a;
		y *= a;
		z *= a;
	}

	vertex operator -(vertex b)
	{
		return vertex(x - b.x, y - b.y, z - b.z);
	}
	
	void operator -=(vertex a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	vertex operator +(vertex b)
	{
		return vertex(x + b.x, y + b.y, z + b.z);
	}

	void operator +=(vertex a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}

	//скалярное умножение
	double operator *(vertex a)
	{
		return x*a.x + y*a.y + z*a.z;
	}

	//векторное умножение
	vertex operator /(vertex b)
	{
		return vertex(y*b.z - z*b.y, x*b.z - z*b.x, x*b.y - y*b.x);
	}

	//угол между векторами
	double operator ^(vertex a)
	{
		return acos((x*a.x + y*a.y + z*a.z) / sqrt((x*x + y*y + z*z)*(a.x*a.x + a.y*a.y + a.z*a.z)));
	}

	//норма
	double operator !()
	{
		return sqrt(x*x + y*y + z*z);
	}

	friend ifstream& operator>>(ifstream& os, vertex& v){
		os >> v.x >> v.y >> v.z;
		return os;
	};
};

struct color
{
	GLubyte r = 255, g = 255, b = 255;
	color(GLubyte _r, GLubyte _g, GLubyte _b) :r(_r), g(_g), b(_b) {};
	color() {};

	void operator +=(color a)
	{
		r += a.r; if (r > 255) r = 255;
		g += a.g; if (g > 255) g = 255;
		b += a.b; if (b > 255) b = 255;
	}

	void operator *=(double a)
	{
		r *= a;
		g *= a;
		b *= a;
	}

	color operator +(color a)
	{
		return color(r + a.r, g + a.g, b + a.b);
	}

	color operator *(double k)
	{
		return color(r*k, g*k, b*k);
	}

	void operator &=(color a)
	{
		r &= a.r;
		g &= a.g;
		b &= a.b;
	}

	//nand - !(this&a)
	void operator |=(color a)
	{
		r = ~(r&a.r);
		g = ~(g&a.g);
		b = ~(b&a.b);
	}

	friend ifstream& operator>>(ifstream& os, color& v) {
		int t;
		os >> t;
		v.r = (GLubyte)t;
		os >> t;
		v.g = (GLubyte)t;
		os >> t;
		v.b = (GLubyte)t;
		return os;
	};
};

struct Light
{
	light_type type;
	vertex direcion;
	double intensity = 0;
};