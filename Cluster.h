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
	Float_t m_tx;
	Float_t m_lsq;
	POINT* m_seed;
	void lsq();
	uint getClusterSize();
	void Draw();
	void PrintToFile(int n);
};
