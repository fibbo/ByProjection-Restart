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
	uint m_clustersize;
	POINT m_seed;
	void lsq();
};
