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
	Float_t* x = new Float_t[m_points.size()];
	Float_t* y = new Float_t[m_points.size()];
	Float_t seedx[1];
	Float_t seedy[1];
	Float_t xmin,ymin,xmax,ymax;
	seedx[0] = m_seed->z;
	xmin = seedx[0];
	xmax = seedx[0];
	seedy[0] = m_seed->y;
	ymin = seedy[0];
	ymax = seedy[0];
	for (uint i = 0; i<m_points.size(); i++)
	{
		x[i]=m_points[i]->z;
		if (x[i] < xmin)
		{
			xmin = x[i];
		}
		if (x[i] > xmax)
		{
			xmax = x[i];
		}
		y[i]=m_points[i]->y;

	}

	TGraph* g1 = new TGraph(m_points.size(),x,y);
	TGraph* g2 = new TGraph(1,seedx,seedy);
	TCanvas* c1 = new TCanvas("c1","Seed and Points",200,10,600,400);
	g1->SetLineColor(4);

	g2->SetLineColor(2);
	g2->SetMarkerStyle(21);
	g2->Draw("ACP");
	g1->Draw("AC*");
	/*TF1* f1 = new TF1("f1","x*[0]+[1]",400,700);
	f1->SetParameter(0,m_tx);
	f1->SetParameter(1,m_seed->y);
	f1->Draw("same");*/
	
	
	
	
}

void Cluster::PrintToFile(int n)
{

}
