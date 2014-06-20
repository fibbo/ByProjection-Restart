#include "HT.h"


#define NO_OF_SEEDS 1
#define BIN_WIDTH 0.00015
void createSeeds(std::vector<Track*> tracks) {

	for (uint i = 0; i<tracks.size(); i++) {
		tracks[i]->sortVeloByZ();
		if (tracks[i]->velo_points.size() > 2) {
			for (uint j = 0; j<NO_OF_SEEDS; j++) {
				tracks[i]->seeds.push_back(eraseFront(tracks[i]->velo_points));
			}
		}
		else {
			tracks[i]->seeds.push_back(eraseFront(tracks[i]->velo_points));
		}
	}

}

void findSlopes(std::vector<Track*> tracks) {
	for (uint i = 0; i<tracks.size(); i++) {
		std::vector<POINT>::iterator it;
		SSP t;
		for (it = tracks[i]->seeds.begin(); it != tracks[i]->seeds.end(); it++) {
			Float_t x0 = (*it).y;
			Float_t z0 = (*it).z;
			std::vector<POINT>::iterator jt;
			for (jt = tracks[i]->velo_points.begin(); jt!=tracks[i]->velo_points.end(); jt++) {
				Float_t tx = atan(((*jt).y - x0)/((*jt).z - z0));
				t.tx = tx;
				/* for book keeping */
				if (tx < tracks[i]->min_tx) tracks[i]->min_tx = tx;
				if (tx > tracks[i]->max_tx) tracks[i]->max_tx = tx;
				t.point = &(*jt);
				t.seed  = &(*it);
				tracks[i]->ssp.push_back(t);
				/* end of book keeping*/
			}	
		}
		tracks[i]->ssp = QuickSortSSP(tracks[i]->ssp);

	}


}

void findClusters(std::vector<Track*> tracks) {
	for (uint i = 0; i < tracks.size(); i++)
	{
		int k;
		HHistogram h(BIN_WIDTH,tracks[i]->min_tx-2*BIN_WIDTH, tracks[i]->max_tx+2*BIN_WIDTH);
		fillHisto(tracks[i], h);
		h.print();
		for (uint j = 0; j<h.size();)
		{
			double sum = 0, coc = 0; uint entries = 0;
			if (h[j].m_bin_content > 0)
			{
				k=j+1; 
				while ((k<h.size()) && (h[k].m_bin_content > 0)) k++;
				for (uint t=j; t<=k; t++)
				{
					sum += h[t].m_bin_content*t;
					entries += h[t].m_bin_content;
				}
				coc = sum/entries; j = ++k;
			}
			else ++j;
		}
	}
}

void fillHisto(Track* track, HHistogram &h)
{

	for (uint j = 0; j < track->ssp.size(); j++)
	{
		int bin = h.AddValue(track->ssp[j].tx);
		SP t;
		t.m_seed = track->ssp[j].seed;
		t.m_point = track->ssp[j].point;
		h[bin].m_source.push_back(t);
	}
}
