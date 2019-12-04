#include "algo_top_parameters.h"
#include "TowerMaker.h"

ap_uint<3> getPeakBinOf5(const ap_uint<12> et[5], const ap_uint<16> etSum) {
#pragma HLS PIPELINE
#pragma HLS ARRAY_PARTITION variable=et
  ap_uint<12> iEtSum12 =
    (et[0] >> 1)                +  // 0.5xet[0]
    (et[1] >> 1) + et[1]        +  // 1.5xet[1]
    (et[2] >> 1) + (et[2] << 1) +  // 2.5xet[2]
    (et[3] << 2) - (et[3] >> 1) +  // 3.5xet[3]
    (et[4] << 2) + (et[4] >> 1) ;  // 4.5xet[4]
  ap_uint<10> iEtSum = 0;
  if(iEtSum12 > 0x3FF) {
    iEtSum = 0x3FF;
  }
  else {
    iEtSum = iEtSum12;
  }
  ap_uint<3> iAve;
  if(     iEtSum <= etSum) iAve = 0;
  else if(iEtSum <= (etSum << 1)) iAve = 1;
  else if(iEtSum <= (etSum + (etSum << 1))) iAve = 2;
  else if(iEtSum <= (etSum << 2)) iAve = 3;
  else iAve = 4;
  return iAve;
}

void makeTower(const Crystal crystals[5][5], Tower &tower) {
#pragma HLS PIPELINE
#pragma HLS ARRAY_PARTITION variable=crystals
  ap_uint<12> phi_strip[5], eta_strip[5];
#pragma HLS ARRAY_PARTITION variable=phi_strip
#pragma HLS ARRAY_PARTITION variable=eta_strip

  // Compute strips
  for (size_t eta = 0; eta < 5; eta++) {
    eta_strip[eta] = 0;
    for (size_t phi = 0; phi < 5; phi++) {
      eta_strip[eta] += crystals[eta][phi].energy;
    }
  }

  for (size_t phi = 0; phi < 5; phi++) {
    phi_strip[phi] = 0;
    for (size_t eta = 0; eta < 5; eta++) {
      phi_strip[phi] += crystals[eta][phi].energy;
    }
  }

  // Compute tower energy
  ap_uint<16> tet = 0;
  for (size_t eta = 0; eta < 5; eta++) {
    tet += eta_strip[eta];
  }

  // Compute peak locations
  ap_uint<3> peakEta = getPeakBinOf5(eta_strip, tet);
  ap_uint<3> peakPhi = getPeakBinOf5(phi_strip, tet);

  // Small cluster ET is just the 3x5 around the peak
  uint16_t clusterEt = 0;
  for (int dEta = -1; dEta <= 1; dEta++) {
    int eta = peakEta + dEta;
    if (eta >= 0 && eta < 5) {
      clusterEt += eta_strip[eta];
    }
    else{
      clusterEt = clusterEt;
    }
  }

  ap_uint<10> peggedClusterEt;
  if(clusterEt > 0x3FF) {
    peggedClusterEt = 0x3FF;
  }
  else {
    peggedClusterEt = clusterEt;
  }
  ap_uint<10> peggedTEt;
  if(tet > 0x3FF) {
    peggedTEt = 0x3FF;
  }
  else {
    peggedTEt = tet;
  }
  ap_uint<3> peakTime;
  if (peakEta < 5 && peakPhi < 5) {
    peakTime = crystals[peakEta][peakPhi].time;
  }
  else {
    peakTime = 7;
  }

  tower = Tower(peggedClusterEt, peggedTEt, peakPhi, peakEta, peakTime, 0);

}

ap_uint<32> makeECALSummary(Tower towerLevelECALSummary[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary complete dim=0
#pragma HLS latency max=6
#pragma HLS PIPELINE
  ap_uint<32> ecalSummary = 0;
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
    ecalSummary += towerLevelECALSummary[i].tower_et();
  }
  return ecalSummary;
}

void stitchNeigbours(Tower Ai, Tower Bi, Tower &Ao, Tower &Bo) {
#pragma HLS PIPELINE
  // Check that the clusters are neigbhors in eta or phi
  ap_uint<12> cluster_et = Ai.cluster_et() + Bi.cluster_et();
  if(Ai.cluster_et() > Bi.cluster_et()){
    // Merge 2 in to 1
    if (cluster_et > 0x3FF) {
      Ao = Tower(0x3FF, Ai.tower_et(), Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
    }
    else {
      Ao = Tower(cluster_et, Ai.tower_et(), Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
    }
    Bo = Tower(0, Bi.tower_et(), Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
  }
  else{
    // Merge 1 in to 2, and set 1 to remnant energy centered in tower
    Ao = Tower(0, Ai.tower_et(), Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
    if (cluster_et > 0x3FF) {
      Bo = Tower(0x3FF, Bi.tower_et(), Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
    }
    else {
      Bo = Tower(cluster_et, Bi.tower_et(), Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
    }
  }
}

void stitchAllNeighbors(Tower in[N_INPUT_LINKS], Tower out[N_INPUT_LINKS]) {
#pragma HLS PIPELINE
#pragma HLS ARRAY_PARTITION variable=in
#pragma HLS ARRAY_PARTITION variable=out

  // Stitch (0,1), (2,3), ...
  Tower etaStitched[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched
  for (size_t iEta = 1; iEta < TOWERS_IN_ETA; iEta+=2) {
#pragma HLS UNROLL
    for (size_t iPhi = 0; iPhi < TOWERS_IN_PHI; iPhi++) {
#pragma HLS UNROLL
      size_t iLink1 = iPhi * TOWERS_IN_ETA  + iEta;
      size_t iLink2 = iLink1 - 1;
      if(iEta > 0 && in[iLink1].peak_eta() == 0 && in[iLink2].peak_eta() == 4 )
	stitchNeigbours(in[iLink1], in[iLink2], etaStitched[iLink1], etaStitched[iLink2]);
      else {
	etaStitched[iLink1] = in[iLink1];
	etaStitched[iLink2] = in[iLink2];
      }
    }
  }

  // (1,2), (3,4), ...
  Tower etaStitched2[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched2
  for (size_t iEta = 2; iEta < TOWERS_IN_ETA; iEta+=2) {
#pragma HLS UNROLL
    for (size_t iPhi = 0; iPhi < TOWERS_IN_PHI; iPhi++) {
#pragma HLS UNROLL
      size_t iLink1 = iPhi * TOWERS_IN_ETA  + iEta;
      size_t iLink2 = iLink1 - 1;
      if(iEta > 0 && etaStitched[iLink1].peak_eta() == 0 && etaStitched[iLink2].peak_eta() == 4 )
	stitchNeigbours(etaStitched[iLink1], etaStitched[iLink2], etaStitched2[iLink1], etaStitched2[iLink2]);
      else {
	etaStitched2[iLink1] = etaStitched[iLink1];
	etaStitched2[iLink2] = etaStitched[iLink2];
      }
    }
  }
  
  // Stitch in phi
  for (size_t iEta = 0; iEta < TOWERS_IN_ETA; iEta++) {
#pragma HLS UNROLL
    for (size_t iPhi = 1; iPhi < TOWERS_IN_PHI; iPhi+=2) {
#pragma HLS UNROLL
      size_t iLink1 = iPhi * TOWERS_IN_ETA  + iEta;
      size_t iLink2 = (iPhi - 1) * TOWERS_IN_ETA + iEta;
      if(iPhi > 0 && etaStitched2[iLink1].peak_phi() == 0 && etaStitched2[iLink2].peak_phi() == 4 )
	stitchNeigbours(etaStitched2[iLink1], etaStitched2[iLink2], out[iLink1], out[iLink2]);
      else {
	out[iLink1] = etaStitched2[iLink1];
	out[iLink2] = etaStitched2[iLink2];
      }
    }
  }
}
