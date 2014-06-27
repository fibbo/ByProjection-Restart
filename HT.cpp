#include "HT.h"


#define NO_OF_SEEDS 1
#define BIN_WIDTH 0.00015
void createSeeds(std::vector<Track*> tracks) {

	for (uint i = 0; i<tracks.size(); i++) {
		tracks[i]->sortVeloByZ();
		if (tracks[i]->m_velo_points.size() > 2) {
			for (uint j = 0; j<NO_OF_SEEDS; j++) {
				tracks[i]->m_seeds.push_back(eraseFront(tracks[i]->m_velo_points));
			}
		}
		else {
			tracks[i]->m_seeds.push_back(eraseFront(tracks[i]->m_velo_points));
		}
	}

}

void findSlopes(std::vector<Track*> tracks) {
	for (uint i = 0; i<tracks.size(); i++) {
		std::vector<POINT>::iterator it;
		SSP t;
		for (it = tracks[i]->m_seeds.begin(); it != tracks[i]->m_seeds.end(); it++) {
			Float_t x0 = (*it).y;
			Float_t z0 = (*it).z;
			std::vector<POINT>::iterator jt;
			for (jt = tracks[i]->m_velo_points.begin(); jt!=tracks[i]->m_velo_points.end(); jt++) {
				Float_t tx = atan(((*jt).y - x0)/((*jt).z - z0));
				t.tx = tx;
				/* for book keeping */
				if (tx < tracks[i]->min_tx) tracks[i]->min_tx = tx;
				if (tx > tracks[i]->max_tx) tracks[i]->max_tx = tx;
				t.point = &(*jt);
				t.seed  = &(*it);
				tracks[i]->m_ssp.push_back(t);
				/* end of book keeping*/
			}	
		}
		tracks[i]->m_ssp = QuickSortSSP(tracks[i]->m_ssp);
	}
}


void findSlopes2(std::vector<Track*> tracks)
{
	for (uint i = 0; i<tracks.size(); i++)
	{
		std::vector<POINT>::iterator it;
		for (it = tracks[i]->m_seeds.begin(); it!= tracks[i]->m_seeds.end(); it++)
		{
			SeedPS ps;
			ps.seed = &(*it);
			Float_t x0 = (*it).y;
			Float_t z0 = (*it).z;
			std::vector<POINT>::iterator jt;
			for (jt = tracks[i]->m_velo_points.begin(); jt!=tracks[i]->m_velo_points.end(); jt++)
			{
				Float_t tx = atan(((*jt).y - x0)/ ((*jt).z - z0));
				ps.points.push_back(&(*jt));
				ps.tx.push_back(tx);
			}
			tracks[i]->m_seedPS.push_back(ps);
		}
	}
}


void findClusters(std::vector<Track*> tracks) {
	for (uint i = 0; i < tracks.size(); i++)
	{

		HHistogram h(BIN_WIDTH,tracks[i]->min_tx-2*BIN_WIDTH, tracks[i]->max_tx+2*BIN_WIDTH);
		fillHisto(tracks[i], h);
		h.print();
		for (uint j = 0; j<h.size();)
		{
			int k = 0, start_bin, end_bin;
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

void findClusters2(std::vector<Track*> tracks) {
	
}

void fillHisto(Track* track, HHistogram &h)
{

	for (uint j = 0; j < track->m_ssp.size(); j++)
	{
		SP t;
		t.m_point = track->m_ssp[j].point;
		t.m_seed = track->m_ssp[j].seed;
		int bin = h.AddValue(track->m_ssp[j].tx);
		h[bin].m_source.push_back(t);
	}
}

