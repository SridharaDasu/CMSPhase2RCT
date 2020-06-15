#include "algo_top_parameters.h"
#include "TowerMaker.h"

ap_uint<3> getPeakBinOf5(ap_uint<12> et[5], ap_uint<16> etSum) {
#pragma HLS ARRAY_PARTITION variable=et
#pragma HLS PIPELINE II=6
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

void makeTower(CrystalGroup crystals, Tower &tower) {
#pragma HLS ARRAY_PARTITION variable=crystals
#pragma HLS PIPELINE II=6

  // Compute strips
  ap_uint<12> eta_strip[5];
#pragma HLS ARRAY_PARTITION variable=eta_strip
 etaStripLoop: for (size_t eta = 0; eta < 5; eta++) {
#pragma HLS UNROLL
    Crystal phiCrystal0 = crystals.crystal(eta*5+0);
    Crystal phiCrystal1 = crystals.crystal(eta*5+1);
    Crystal phiCrystal2 = crystals.crystal(eta*5+2);
    Crystal phiCrystal3 = crystals.crystal(eta*5+3);
    Crystal phiCrystal4 = crystals.crystal(eta*5+4);
    ap_uint<16> e01 = phiCrystal0.energy + phiCrystal1.energy;
    ap_uint<16> e23 = phiCrystal2.energy + phiCrystal3.energy;
    ap_uint<16> e4 = phiCrystal4.energy;
    ap_uint<16> e0123 = e01 + e23;
    eta_strip[eta] = e0123 + e4;
  }

  ap_uint<12> phi_strip[5];
#pragma HLS ARRAY_PARTITION variable=phi_strip
 phiStripLoop: for (size_t phi = 0; phi < 5; phi++) {
#pragma HLS UNROLL
    Crystal etaCrystal0 = crystals.crystal(phi + (5*0));
    Crystal etaCrystal1 = crystals.crystal(phi + (5*1));
    Crystal etaCrystal2 = crystals.crystal(phi + (5*2));
    Crystal etaCrystal3 = crystals.crystal(phi + (5*3));
    Crystal etaCrystal4 = crystals.crystal(phi + (5*4));
    ap_uint<16> e01 = etaCrystal0.energy + etaCrystal1.energy;
    ap_uint<16> e23 = etaCrystal2.energy + etaCrystal3.energy;
    ap_uint<16> e4 = etaCrystal4.energy;
    ap_uint<16> e0123 = e01 + e23;
    phi_strip[phi] = e0123 + e4;
  }

  // Compute tower energy
  ap_uint<16> e01 = eta_strip[0] + eta_strip[1];
  ap_uint<16> e23 = eta_strip[2] + eta_strip[3];
  ap_uint<16> e4 = eta_strip[4];
  ap_uint<16> e0123 = e01 + e23;
  ap_uint<16> tet = e0123 + e4;

  // Compute peak locations
  ap_uint<3> peakEta = getPeakBinOf5(eta_strip, tet);
  ap_uint<3> peakPhi = getPeakBinOf5(phi_strip, tet);

  // Small cluster ET is just the 3x5 around the peak
  uint16_t clusterEt = 0;
 clusterEtLoop: for (int dEta = -1; dEta <= 1; dEta++) {
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
  ap_uint<5> peakCrystal = peakEta + peakPhi * 5;
  if (peakCrystal < 25) {
    peakTime = crystals.crystal(peakCrystal).time;
  }
  else {
    peakTime = 7;
  }

  tower = Tower(peggedClusterEt, peggedTEt, peakPhi, peakEta, peakTime, 0);

}

ap_uint<32> makeECALSummary(Tower towerLevelECALSummary[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary complete dim=0
#pragma HLS PIPELINE II=6
  ap_uint<32> ecalSummary = 0;
 ecalSummaryLoop: for (size_t i = 0; i < N_INPUT_LINKS; i++) {
    ecalSummary += towerLevelECALSummary[i].tower_et();
  }
  return ecalSummary;
}

void stitchNeighbors(Tower Ai, Tower Bi, Tower &Ao, Tower &Bo) {
#pragma HLS PIPELINE II=6
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
