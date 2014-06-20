#include <TApplication.h>
#include "Tools.h"
#include "HT.h"
#include <TGraph.h>
#include <TH1F.h>
#include <TCanvas.h>
#include "Histogram.h"

int main(int argc, char* argv[]) {
	TApplication theApp("App",&argc, argv);

	TTree* tree = readTree();
	std::vector<Track*> tracks = getTracks(tree);

	//std::cout << tracks.size() << std::endl;
	createSeeds(tracks);
	findSlopes(tracks);
	findClusters(tracks);

	//std::vector<Track*>::iterator it;

	//std::vector<TH1*> histos;

	//uint k = 0;
	//for (it = tracks.begin(); it!=tracks.end(); it++) {

	//	TH1C* h1 = new TH1C(Form("h%u",k),"title",100, (*it)->min_tx - 0.05*fabs((*it)->min_tx), (*it)->max_tx + 0.05*fabs((*it)->max_tx));
	//	for (uint i = 0; i<(*it)->tx.size(); i++) {
	//		h1->Fill((*it)->tx[i].tx);
	//	}
	//	histos.push_back(h1);
	//	++k;
	//}

	std::cout << "DONE" << std::endl;
	theApp.Run();
	return 0;
}