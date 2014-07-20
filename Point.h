#pragma once
#include "Tools.h"

struct POINT {
	POINT(Float_t xx=0, Float_t yy=0, Float_t zz=0):m_x(xx),m_y(yy),m_z(zz){ }
	Float_t m_x,m_y,m_z;

	void print() {
		printf("POINT: (%.3f,%.3f,%.3f)\n",m_x,m_y,m_z);
	}
	POINT& operator= (const POINT &other) {
		if (this != &other)
		{
			this->m_x = other.m_x;
			this->m_y = other.m_y;
			this->m_z = other.m_z;
		}
		return *this;
	}
};
