#pragma once
#include "Tools.h"
#include "HEntry.h"

class HHistogram
{
public:
	HHistogram(uint size, double min, double max);
	HHistogram(double bin_width, double min, double max);
	virtual ~HHistogram(void);
	HEntry& operator[](int n);
	void findBin(double value);
	void print();
	void AddToBin(int bin);
	int AddValue(double value);
	uint size();
	uint getNumberOfEntries();
	HEntry* m_hist;


private:
	double m_bin_width;
	uint m_size;
	uint m_overflow;
	uint m_underflow;
	uint m_entries;
	double m_min;
	double m_max;
};
