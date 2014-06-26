#include "HHistogram.h"


HHistogram::HHistogram(uint size, double min, double max) 
{
	m_hist = new HEntry[size];
	for (uint i = 0; i<size; i++) { m_hist[i].m_bin_content = 0; }
	m_overflow = 0;
	m_underflow = 0;
	m_entries = 0;
	m_bin_width = (uint)(max-min)/size;
	m_min = min;
	m_max = max;
	m_size = size;

}

HHistogram::HHistogram(double bin_width, double min, double max)
{
	m_size = (uint)ceil((max-min)/bin_width);
	m_hist = new HEntry[m_size];
	for (uint i = 0; i<m_size; i++) { m_hist[i].m_bin_content = 0; }
	m_overflow = 0;
	m_underflow = 0;
	m_entries = 0;
	m_min = min;
	m_max = max;
	m_bin_width = bin_width;
}


HHistogram::~HHistogram(void)
{
	delete[] m_hist;
}

HEntry& HHistogram::operator[](int n) {
	return this->m_hist[n];
}

void HHistogram::findBin(double value)
{
	std::cout << (uint)((value-m_min)/m_bin_width) << std::endl;
}

void HHistogram::print()
{
	std::cout << m_underflow << ", ";
	for (uint i = 0; i<m_size;i++)
	{
		std::cout << m_hist[i].m_bin_content << ", ";
	}
	std::cout << m_overflow << std::endl;
}

void HHistogram::AddToBin(int bin)
{
	if (bin >= 0 && bin < m_size) { m_hist[bin].m_bin_content += 1; }
	else if (bin < 0){ m_underflow += 1; }
	else { m_overflow += 1; }
	m_entries += 1;
}

int HHistogram::AddValue(double value)
{
	int bin = (int)((value-m_min)/m_bin_width);
	if (bin >= 0 && bin < m_size) { m_hist[bin].m_bin_content += 1; }
	else if (bin < 0) { m_underflow += 1; }
	else m_overflow += 1;
	m_entries += 1;
	return bin;
}

uint HHistogram::size()
{
	return m_size;
}

uint HHistogram::getNumberOfEntries()
{
	return m_entries;
}
