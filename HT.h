#pragma once
#include <vector>
#include "Track.h"
#include <TH1D.h>
#include "HHistogram.h"


void createSeeds(std::vector<Track*> tracks);

void findSlopes(std::vector<Track*> tracks);

void findClusters(std::vector<Track*> tracks);

void fillHisto(Track* track, HHistogram &h);