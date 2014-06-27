#pragma once
#include "Point.h"
#include "vector"

struct SeedPS {
	POINT* seed;
	std::vector<POINT*> points;
	std::vector<Float_t> tx;

};