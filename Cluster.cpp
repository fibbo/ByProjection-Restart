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
