#pragma once
#include <vector>
#include "Track.h"
#include <TH1D.h>
#include "Histogram.h"


void createSeeds(std::vector<Track*> tracks);

void findSlopes(std::vector<Track*> tracks);

void findClusters(std::vector<Track*> tracks);

void fillHisto(Track* track, Histogram &h);