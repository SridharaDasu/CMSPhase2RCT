#include "algo_top_parameters.h"
#include "TowerMaker.h"

ap_uint<3> getPeakBinOf5(const ap_uint<12> et[5], const ap_uint<16> etSum) {
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

Tower makeTower(const Crystal crystals[5][5]) {

  ap_uint<12> phi_strip[5], eta_strip[5];

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

  Tower tower(peggedClusterEt, peggedTEt, peakPhi, peakEta, peakTime, 0);

  return tower;

}

void stitchNeigbours(Tower Ai, Tower Bi, Tower &Ao, Tower &Bo) {
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
