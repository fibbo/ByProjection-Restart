#include <TApplication.h>
#include "Tools.h"
#include "HT.h"
#include <TGraph.h>
#include <TH1F.h>
#include <TCanvas.h>
#include "Histogram.h"
#include "HHistogram.h"
#include "HEntry.h"\

void test(HHistogram &h) {
	POINT* seed = new POINT(1,2,3);
	POINT* point= new POINT(2,3,4);
	SP t;
	t.m_point = point;
	t.m_seed = seed;

	h[0].m_bin_content = 5;
	h[0].m_source.push_back(t);
	h[1].m_bin_content = 5;
	h[1].m_source.push_back(t);
}

int main(int argc, char* argv[]) {
	TApplication theApp("App",&argc, argv);

	TTree* tree = readTree();
	std::vector<Track*> tracks = getTracks(tree);

	createSeeds(tracks);
	findSlopes(tracks);
	findClusters(tracks);

	
	std::cout << "DONE" << std::endl;
	theApp.Run();
	return 0;
}