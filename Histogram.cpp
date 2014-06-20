#include "Histogram.h"


Histogram::Histogram(uint size, double min, double max) 
{
	m_hist = new uint[size];
	for (uint i = 0; i<size; i++) m_hist[i] = 0;
	m_overflow = 0;
	m_underflow = 0;
	m_entries = 0;
	m_bin_width = (uint)(max-min)/size;
	m_min = min;
	m_max = max;
	m_size = size;

}

Histogram::Histogram(double bin_width, double min, double max)
{
	m_size = (uint)ceil((max-min)/bin_width);
	m_hist = new uint[m_size];
	for (uint i = 0; i<m_size; i++) m_hist[i] = 0;
	m_overflow = 0;
	m_underflow = 0;
	m_entries = 0;
	m_min = min;
	m_max = max;
	m_bin_width = bin_width;
}


Histogram::~Histogram(void)
{
	delete m_hist;
	m_hist = NULL;
}

int Histogram::operator[](int n) const {
	return this->m_hist[n];
}

void Histogram::findBin(double value)
{
	std::cout << (uint)((value-m_min)/m_bin_width) << std::endl;
}

void Histogram::print()
{
	std::cout << m_underflow << ", ";
	for (uint i = 0; i<m_size;i++)
	{
		std::cout << m_hist[i] << ", ";
	}
	std::cout << m_overflow << std::endl;
}

void Histogram::AddToBin(int bin)
{
	if (bin >= 0 && bin < m_size) m_hist[bin] += 1;
	else if (bin < 0) m_underflow += 1;
	else m_overflow += 1;
	m_entries += 1;
}

int Histogram::AddValue(double value)
{
	int bin = (int)((value-m_min)/m_bin_width);
	if (bin >= 0 && bin < m_size) m_hist[bin] += 1;
	else if (bin < 0) m_underflow += 1;
	else m_overflow += 1;
	m_entries += 1;
	return bin;
}

uint Histogram::size()
{
	return m_size;
}

uint Histogram::getNumberOfEntries()
{
	return m_entries;
}
