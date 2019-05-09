#pragma once
#include "Structs.h"
#include <fstream>
#include <string>

class GemObject
{
	double GetAng(vertex A, vertex F, vertex B);

public:
	shape_type curType;
	//если плоскость то это нормаль
	vertex Position;
	//если плоскость то это d. ax+by+cz+d=0
	double R;
	//высота конуса
	double H;
	//нормаль для тетраэдра
	vertex thetra_norm;
	//цвет
	color Color;
	//есть ли точка пересечения
	bool cross = false;
	//точки пересечения
	double t1, t2;
	//коэф зеркальности
	//-1 нету зеркальности
	double s = -1;
	//отражаемость
	double refl = 0;


	GemObject();
	GemObject(shape_type _t, vertex p, double r, color _c) :curType(_t),Position(p), R(r), Color(_c) {};
	void SetH(double h);
	void SetS(double s);
	~GemObject();

	bool Collision(vertex e, vertex d, double t_min, double t_max);
};
