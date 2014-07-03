#pragma once

#include "Point.h"

class Cluster
{
public:
	Cluster(void);
	~Cluster(void);
	std::vector<POINT*> m_points;
	double m_tx;
	double m_lsq;
	POINT* m_seed;
	void lsq();
	uint getClusterSize();
};
