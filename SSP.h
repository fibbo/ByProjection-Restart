#pragma once
#include "Point.h"

/** Seed, slope and points: Each SSP corresponds to a slope between
* a fixed, predetermined seed and another point of the track
*/

struct SSP {
	Float_t tx;
	POINT* seed;
	POINT* point;
};
