/************************************************************************/
/* Track.h: Track struct with the leaves from the ROOT-tree plus custom member 
variables:
- velo_points: vector of single velo-coordinates consolidated in a point struct
- seeds: first x elements of velo_points are taken as seed and moved to this vector
- ssp: vector of all the possible slopes between points and seeds of a track
- min_tx, max_tx: smallest and biggest measured slope (need for creating appropriate sized histograms
+ sortByVeloZ(): to make sure the elements of velo_points are ordered by increasing z.
/************************************************************************/

#pragma once
#include <vector>
#include <list>
#include <limits>
#include <TTree.h>
#include <iostream>
#include "Tools.h"
#include "Point.h"
#include "SSP.h"
#include "Cluster.h"
#include "SeedPS.h"
#define VPLEN_MAX 25

struct Track {
	Track() {min_tx = 999.; max_tx = -999.;	}
	//Track& operator=(const Track &other);

	bool reconstructible_asLong;
	bool reconstructible_asUpstream;
	bool fromB;
	Int_t pid;
	Double_t true_p;
	Double_t true_px;
	Double_t true_py;
	Double_t true_pt;
	Double_t true_eta;
	Int_t true_threeCharge;
	Int_t nHits;
	Int_t len;
	Float_t x_hit;
	Float_t y_min_hit;
	Float_t y_max_hit;
	Float_t z_hit;
	Float_t planeCode;
	Float_t x_UT;
	Double_t x_velo;
	Double_t y_velo;
	Double_t z_velo;
	Double_t tx_velo;
	Double_t ty_velo;
	bool hasVelo;
	Int_t vplen;
	std::vector<POINT> m_velo_points;
	std::vector<POINT> m_seeds;
	std::vector<SSP> m_ssp;
	std::vector<SeedPS> m_seedPS;
	std::vector<Cluster> m_cluster;
	Float_t min_tx, max_tx;
	Float_t Max_tx() const { return max_tx; }
	void Max_tx(Float_t val) { max_tx = val; }
	Float_t Min_tx() const { return min_tx; }
	void Min_tx(Float_t val) { min_tx = val; }
	void sortVeloByZ();
	void PrintToFile(int n);

};


bool isGood(const Track &track);
std::vector<Track*> getTracks(TTree* tree);
void copyPointsToVector(Track &t);
std::vector<POINT> QuickSortZ(std::vector<POINT> S);
std::vector<SSP> QuickSortSSP(std::vector<SSP> S);

template<typename T>
std::list<T> QuickSort(std::list<T> S) {
	if (S.size() <= 1) return S;
	T p = S.back();
	std::list<T> L(0), E(0), G(0);
	while (!S.empty()) {
		if (S.back() < p) L.push_back(eraseBack(S));
		else if (S.back() == p) E.push_back(eraseBack(S));
		else G.push_back(eraseBack(S));
	}
	L = QuickSort(L);
	G = QuickSort(G);
	while (!L.empty()) S.push_back(eraseFront(L));
	while (!E.empty()) S.push_back(eraseFront(E));
	while (!G.empty()) S.push_back(eraseFront(G));
	return S;
}

template<typename T>
std::vector<T> QuickSort(std::vector<T> S) {
	if (S.size() <= 1) return S;
	T p = S.back();
	std::vector<T> L(0), E(0), G(0);
	while (!S.empty()) {
		if (S.back() < p) L.push_back(eraseBack(S));
		else if (S.back() == p) E.push_back(eraseBack(S));
		else G.push_back(eraseBack(S));
	}
	L = QuickSort(L);
	G = QuickSort(G);
	while (!L.empty()) S.push_back(eraseFront(L));
	while (!E.empty()) S.push_back(eraseFront(E));
	while (!G.empty()) S.push_back(eraseFront(G));
	return S;
}


template<typename T> T eraseBack(std::list<T> &list) {
	T p = list.back();
	list.pop_back();
	return p;
}

template<typename T> T eraseFront(std::list<T> &list) {
	T p = list.front();
	list.pop_front();
	return p;
}

template<typename T> T eraseBack(std::vector<T> &v) {
	T p = v.back();
	v.pop_back();
	return p;
}


template<typename T> T eraseFront(std::vector<T> &v) {
	try {
		if (!v.empty()) {
			T front = v[0];
			typename std::vector<T>::iterator it = v.begin();
			v.erase(it);
			return front;
		}
		else throw;
	}
	catch (...) {
		std::cout << "Could not erase front of vector because vector is empty" << std::endl;
	}
}
