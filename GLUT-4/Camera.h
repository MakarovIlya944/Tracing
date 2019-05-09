#pragma once
#include "Structs.h"
class Camera
{
public:
	Camera();
	~Camera();

	//z
	vertex v;
	//y
	vertex w;
	//x
	vertex u;
	//eye
	vertex e;

	void LookAt(vertex e, vertex p, vertex up);
};

