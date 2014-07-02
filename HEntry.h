#pragma once
#include "Tools.h"
#include "Point.h"

struct SP 
{
	POINT* m_seed;
	POINT* m_point;
	SP() {

	}

	~SP() {

	}
};

struct HEntry
{
	uint m_bin_content;
	std::vector<SP> m_source;
};

struct HHEntry
{
	uint m_bin_content;
	std::vector<POINT*> m_points;
};
