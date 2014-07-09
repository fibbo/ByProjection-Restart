#pragma once

#include "Point.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "fstream"
#include "sstream"

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
	void Draw();
	void PrintToFile(int n);
};
