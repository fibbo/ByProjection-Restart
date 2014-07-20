#include "Track.h"


bool isGood(const Track &track) {
	return (track.reconstructible_asLong  // long track
		&& track.true_p > 3000            //     # min momentum
		&& track.true_pt > 500           //       # min transverse momentum (momentum perpendicular to the beam pipe - aka physics happened)
		&& track.true_eta > 2             //       # pseudorapidity (spatial coordinate describing the angle of a particle relative to the beam axis) range 
		&& track.true_eta < 5            //        # 
		&& abs(track.pid) != 22           //      # not an electron/positron
		&& track.fromB);
}



void copyPointsToVector(Track* t, Float_t velo_x_hit[], Float_t velo_y_hit[], Float_t velo_z_hit[]) {

	for (uint i = 0; i<(uint)t->vplen;i++) {
		POINT p(velo_x_hit[i],velo_y_hit[i],velo_z_hit[i]);
		t->m_velo_points.push_back(p);
	}
}

std::vector<Track*> getTracks(TTree* tree) {
	std::vector<Track*> tracks;
	static Track t;
	Float_t velo_x_hit[VPLEN_MAX];
	Float_t velo_y_hit[VPLEN_MAX];
	Float_t velo_z_hit[VPLEN_MAX];
	tree->SetBranchAddress("reconstructible_asLong",&t.reconstructible_asLong);
	tree->SetBranchAddress("reconstructible_asUpstream",&t.reconstructible_asUpstream);
	tree->SetBranchAddress("fromB",&t.fromB);
	tree->SetBranchAddress("pid",&t.pid);
	tree->SetBranchAddress("true_p",&t.true_p);
	tree->SetBranchAddress("true_px",&t.true_px);
	tree->SetBranchAddress("true_py",&t.true_py);
	tree->SetBranchAddress("true_pt",&t.true_pt);
	tree->SetBranchAddress("true_eta",&t.true_eta);
	tree->SetBranchAddress("true_threeCharge",&t.true_threeCharge);
	tree->SetBranchAddress("nHits",&t.nHits);
	tree->SetBranchAddress("len",&t.len);
	tree->SetBranchAddress("x_hit",&t.x_hit);
	tree->SetBranchAddress("y_min_hit",&t.y_min_hit);
	tree->SetBranchAddress("y_max_hit",&t.y_max_hit);
	tree->SetBranchAddress("z_hit",&t.z_hit);
	tree->SetBranchAddress("planeCode",&t.planeCode);
	/*tree->SetBranchAddress("x_UT",&t.x_UT);*/ //buggy in UTHits_100.root
	tree->SetBranchAddress("x_velo",&t.x_velo);
	tree->SetBranchAddress("y_velo",&t.y_velo);
	tree->SetBranchAddress("z_velo",&t.z_velo);
	tree->SetBranchAddress("tx_velo",&t.tx_velo);
	tree->SetBranchAddress("ty_velo",&t.ty_velo);
	tree->SetBranchAddress("hasVelo",&t.hasVelo);
	tree->SetBranchAddress("vplen",&t.vplen);
	tree->SetBranchAddress("velo_x_hit",velo_x_hit);
	tree->SetBranchAddress("velo_y_hit",velo_y_hit);
	tree->SetBranchAddress("velo_z_hit",velo_z_hit);
	for (unsigned long i=0; i<tree->GetEntries(); i++) {
		tree->GetEntry(i);

		if (1)
		{
			Track* tt = new Track();
			*tt = t;
			copyPointsToVector(tt,velo_x_hit, velo_y_hit,velo_z_hit);
			tracks.push_back(tt);
		}

	}
	return tracks;
}



void Track::sortVeloByZ() {
	m_velo_points = QuickSortZ(m_velo_points);
}

void Track::PrintToFile(int n)
{
	std::ofstream file;
	std::ostringstream fname;
	fname << "data/track_" << n << ".txt";
	file.open(fname.str().c_str());
	for (uint i = 0; i<m_velo_points.size(); i++)
	{
		file << m_velo_points[i].m_z << "\t" << m_velo_points[i].m_y << std::endl;
	}

	file.close();
}

std::vector<POINT> QuickSortZ(std::vector<POINT> S) 
{
	if (S.size() <= 1) return S;
	Float_t p = S.back().m_z;
	std::vector<POINT> L(0), E(0), G(0);
	while (!S.empty()) 
	{
		if (S.back().m_z < p) L.push_back(eraseBack(S));
		else if (S.back().m_z == p) E.push_back(eraseBack(S));
		else G.push_back(eraseBack(S));
	}
	L = QuickSortZ(L);
	G = QuickSortZ(G);
	while (!L.empty())
	{
		S.push_back(eraseFront(L));
	}
	while (!E.empty()) 
	{
		S.push_back(eraseFront(E));
	}
	while (!G.empty()) 
	{
		S.push_back(eraseFront(G));
	}
	return S;
}

std::vector<SSP> QuickSortSSP(std::vector<SSP> S) 
{
	if (S.size() <= 1) return S;
	Float_t p = S.back().tx;
	std::vector<SSP> L(0), E(0), G(0);
	while (!S.empty()) 
	{
		if (S.back().tx < p) L.push_back(eraseBack(S));
		else if (S.back().tx == p) E.push_back(eraseBack(S));
		else G.push_back(eraseBack(S));
	}
	L = QuickSortSSP(L);
	G = QuickSortSSP(G);
	while (!L.empty())
	{
		S.push_back(eraseFront(L));
	}
	while (!E.empty())
	{
		S.push_back(eraseFront(E));
	}

	while (!G.empty())
	{ 
		S.push_back(eraseFront(G));
	}

	return S;
}

