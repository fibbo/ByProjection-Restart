#pragma once
#include <vector>
#include <iostream>
/* Define _USE_MATH_DEFINES before including math.h to expose these macro
* definitions for common math constants.  These are placed under an #ifdef
* since these commonly-defined names are not part of the C/C++ standards.
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include <TFile.h>
#include <TTree.h>

typedef unsigned int uint;


TTree* readTree();

template<typename T>
T round(T d)
{
	return floor(d + 0.5);
}

template<typename T>
T get_minimum(std::vector<T> x) {
	T min = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] < min) min = x[i];
	}
	return min;
}

template<typename T>
T get_maximum(std::vector<T> x) {
	T max = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] > max) max = x[i];
	}
	return max;
}

static void PressEnterToContinue() {
	int c;
	printf( "Press ENTER to continue... " );
	fflush( stdout );
	do c = getchar(); while ((c != '\n') && (c != EOF));
}
