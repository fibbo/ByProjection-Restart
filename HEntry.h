#pragma once
#include "Tools.h"
#include "Point.h"

struct SP 
{
	POINT* m_seed;
	POINT* m_point;
	~SP() {
		delete m_seed;
		delete m_point;
		m_seed = nullptr;
		m_point = nullptr;
	}
};

struct HEntry
{
	uint m_entries;
	std::vector<SP> m_source;
};
