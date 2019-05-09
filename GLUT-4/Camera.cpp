#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::LookAt(vertex e, vertex p, vertex up)
{
	w = p - e;
	u = w / up;
	v = u / w;
	v *= 1/!v;
	w *= 1/!w;
	u *= 1/(!u);
}

