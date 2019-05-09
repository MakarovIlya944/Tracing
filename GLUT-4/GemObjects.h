#pragma once
#include "Structs.h"
#include <fstream>
#include <string>

class GemObject
{
	double GetAng(vertex A, vertex F, vertex B);

public:
	shape_type curType;
	//���� ��������� �� ��� �������
	vertex Position;
	//���� ��������� �� ��� d. ax+by+cz+d=0
	double R;
	//������ ������
	double H;
	//������� ��� ���������
	vertex thetra_norm;
	//����
	color Color;
	//���� �� ����� �����������
	bool cross = false;
	//����� �����������
	double t1, t2;
	//���� ������������
	//-1 ���� ������������
	double s = -1;
	//������������
	double refl = 0;


	GemObject();
	GemObject(shape_type _t, vertex p, double r, color _c) :curType(_t),Position(p), R(r), Color(_c) {};
	void SetH(double h);
	void SetS(double s);
	~GemObject();

	bool Collision(vertex e, vertex d, double t_min, double t_max);
};
