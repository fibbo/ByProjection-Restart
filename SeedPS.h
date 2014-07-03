#pragma once
#include "Point.h"
#include "vector"

struct SeedPS {
	POINT* seed;
	std::vector<POINT*> points;
	std::vector<Float_t> tx;
	Float_t min_tx, max_tx;
	SeedPS() {
		min_tx = 999;
		max_tx = -999;
	}
};
