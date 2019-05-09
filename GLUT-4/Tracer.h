#pragma once
#include "GemObjects.h"
#include "Conus.h"
#include "Plane.h"
#include "Sphere.h"
#include <fstream>

class Tracer
{
	vertex N, LightVertex;
	double t;
	
	vertex e, curE;
	vertex u, w, v;
	double AngView;
	double DistToScreen;

	int curLevel;

public:

	std::vector<GemObject> SceneObj;
	std::vector<Light> SceneLight;

	int maxLevel = 1;
	int width;
	int height;

	Tracer();
	//t AngView
	Tracer(vertex _e, vertex _u, vertex _w, vertex _v, int W, int h, double _t, double _n) 
	:e(_e),u(_u), w(_w), v(_v), width(W), height(h), AngView(_t),DistToScreen(_n) {};
	~Tracer();

	void Init(vertex _e, vertex _u, vertex _w, vertex _v, int W, int h, double _t, double _n)
	{
		e = _e; u = _u; w = _w; v = _v; width = W; height = h; AngView = _t; DistToScreen = _n;
	}

	void Trace();
	color Trace(vertex d, double t_min, double t_max);

	double CalculateLight(vertex P, vertex N, vertex V, double s);
	int NearestCross(vertex O, vertex D, double t_min, double t_max);
};

