#include "Tools.h"

TTree* readTree() {
	TFile* file = new TFile("UTHits.root");
	TTree* tree = (TTree*) file->Get("UTHits/MatchedTracks");
	return tree;
}

