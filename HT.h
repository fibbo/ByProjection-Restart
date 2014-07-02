#pragma once
#include <vector>
#include "Track.h"
#include <TH1D.h>
#include "Histogram.h"
#include "HHistogram.h"
#include "SeedPS.h"


void createSeeds(std::vector<Track*> tracks);

void findSlopes(std::vector<Track*> tracks);

void findSlopes2(std::vector<Track*> tracks);

void findClusters(std::vector<Track*> tracks);

void findClusters2(std::vector<Track*> tracks);

void fillHisto(Track* track, HHistogram &h);

void fillHisto2(SeedPS seedps, Histogram &h);
