#include "Cluster.h"


Cluster::Cluster(void)
{
	m_tx = 0.0;
	m_lsq = 0.0;
}


Cluster::~Cluster(void)
{

}


void Cluster::lsq()
{
	double r2 = 0;
	for (uint i = 0; i<m_points.size(); i++)
	{
		r2 += m_points[i]->x - m_tx*m_points[i]->z + m_seed->x;
	}
}

uint Cluster::getClusterSize()
{
	return m_points.size();
}

void Cluster::Draw()
{
	Float_t* x = new Float_t[m_points.size()+1];
	Float_t* y = new Float_t[m_points.size()+1];
	x[0] = m_seed->z;
	y[0] = m_seed->y;
	for (uint i = 1; i<m_points.size()+1; i++)
	{
		x[i]=m_points[i-1]->z;
		y[i]=m_points[i-1]->y;
	}

	TGraph* g = new TGraph(m_points.size(),x,y);
	TF1* f1 = new TF1("f1","x*[0]+[1]",400,700);
	TCanvas* c1 = new TCanvas("c1","c1",600,400);
	f1->SetParameter(0,m_tx);
	f1->SetParameter(1,m_seed->y);
	g->Draw("A*");
	f1->Draw("same");
}
