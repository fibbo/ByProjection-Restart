#pragma once
#include "Tools.h"

struct POINT {
	POINT(Float_t xx=0, Float_t yy=0, Float_t zz=0):x(xx),y(yy),z(zz){ }
	Float_t x,y,z;
	void print() {
		printf("POINT: (%.3f,%.3f,%.3f)\n",x,y,z);
	}
};
