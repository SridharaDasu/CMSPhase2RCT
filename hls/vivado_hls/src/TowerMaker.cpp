#include "algo_top_parameters.h"
#include "TowerMaker.h"

ap_uint<3> getPeakBinOf5(ap_uint<13> et[5], ap_uint<16> etSum) {
#pragma HLS ARRAY_PARTITION variable=et
#pragma HLS PIPELINE II=6
  ap_uint<16> iEtSum12 =
    (et[0] >> 1)                +  // 0.5xet[0]
    (et[1] >> 1) + et[1]        +  // 1.5xet[1]
    (et[2] >> 1) + (et[2] << 1) +  // 2.5xet[2]
    (et[3] << 2) - (et[3] >> 1) +  // 3.5xet[3]
    (et[4] << 2) + (et[4] >> 1) ;  // 4.5xet[4]
  ap_uint<16> iEtSum = 0;
  if(iEtSum12 > 0xFFFF) {
    iEtSum = 0xFFFF;
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

ap_uint<16> getSum(ap_uint<16> e0, ap_uint<16> e1, ap_uint<16> e2, ap_uint<16> e3, ap_uint<16> e4) {
#pragma HLS PIPELINE II=6
  ap_uint<16> e01 = e0 + e1;
  ap_uint<16> e23 = e2 + e3;
  ap_uint<16> e0123 = e01 + e23;
  ap_uint<16> e = e0123 + e4;
  return e;
}

void makeEtaStrip(CrystalGroup crystals, ap_uint<13> eta_strip[5]) {
#pragma HLS PIPELINE II=6
#pragma HLS ARRAY_PARTITION variable=crystals
#pragma HLS ARRAY_PARTITION variable=eta_strip
 etaStripLoop: for (size_t eta = 0; eta < 5; eta++) {
#pragma HLS UNROLL
    Crystal phiCrystal0 = crystals.crystal(eta*5+0);
    Crystal phiCrystal1 = crystals.crystal(eta*5+1);
    Crystal phiCrystal2 = crystals.crystal(eta*5+2);
    Crystal phiCrystal3 = crystals.crystal(eta*5+3);
    Crystal phiCrystal4 = crystals.crystal(eta*5+4);
    eta_strip[eta] = getSum(phiCrystal0.energy, phiCrystal1.energy, phiCrystal2.energy, phiCrystal3.energy, phiCrystal4.energy);
  }
}


void makePhiStrip(CrystalGroup crystals, ap_uint<13> phi_strip[5]) {
#pragma HLS PIPELINE II=6
#pragma HLS ARRAY_PARTITION variable=crystals
#pragma HLS ARRAY_PARTITION variable=phi_strip
 phiStripLoop: for (size_t phi = 0; phi < 5; phi++) {
#pragma HLS UNROLL
    Crystal etaCrystal0 = crystals.crystal(phi + (5*0));
    Crystal etaCrystal1 = crystals.crystal(phi + (5*1));
    Crystal etaCrystal2 = crystals.crystal(phi + (5*2));
    Crystal etaCrystal3 = crystals.crystal(phi + (5*3));
    Crystal etaCrystal4 = crystals.crystal(phi + (5*4));
    phi_strip[phi] = getSum(etaCrystal0.energy, etaCrystal1.energy, etaCrystal2.energy, etaCrystal3.energy, etaCrystal4.energy);
  }
}

void makeTower(CrystalGroup crystals, Tower &tower) {
#pragma HLS ARRAY_PARTITION variable=crystals
#pragma HLS PIPELINE II=6

  // Compute strips
  ap_uint<13> eta_strip[5];
#pragma HLS ARRAY_PARTITION variable=eta_strip
  makeEtaStrip(crystals, eta_strip);

  ap_uint<13> phi_strip[5];
#pragma HLS ARRAY_PARTITION variable=phi_strip
  makePhiStrip(crystals, phi_strip);

  // Compute tower energy
  ap_uint<16> tet = getSum(eta_strip[0], eta_strip[1], eta_strip[2], eta_strip[3], eta_strip[4]);

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

void stitchNeighbors(bool stitch, Tower Ai, Tower Bi, Tower &Ao, Tower &Bo) {
#pragma HLS PIPELINE II=6
   // Check that the clusters are neigbhors in eta or phi
   bool etaStitch = (stitch == 0 && Ai.peak_eta() == 4 && Bi.peak_eta() == 0 && Ai.peak_phi() == Bi.peak_phi());
   bool phiStitch = (stitch == 1 && Ai.peak_phi() == 4 && Bi.peak_phi() == 0 && Ai.peak_eta() == Bi.peak_eta());

   if(etaStitch || phiStitch){
      ap_uint<12> cEtSum = Ai.cluster_et() + Bi.cluster_et();
      ap_uint<10> pegged_cEtSum = (cEtSum > 0x3FF) ? (ap_uint<10>)0x3FF : (ap_uint<10>) cEtSum;

      ap_uint<12> tEtSum = Ai.tower_et() + Bi.tower_et();
      ap_uint<10> pegged_tEtSum = (tEtSum > 0x3FF) ? (ap_uint<10>)0x3FF : (ap_uint<10>) tEtSum;

      if(Ai.cluster_et() > Bi.cluster_et()){
	 // Merge 2 in to 1, and set 2 to remnant energy centered in tower
	 ap_uint<10> tEt_leftOver = Ai.tower_et() - Bi.tower_et();
	 Ao = Tower(pegged_cEtSum, pegged_tEtSum, Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
	 Bo = Tower(            0,  tEt_leftOver, Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
      }
      else{
	 // Merge 1 in to 2, and set 1 to remnant energy centered in tower
	 ap_uint<10> tEt_leftOver = Bi.tower_et() - Ai.tower_et();
	 Ao = Tower(            0,  tEt_leftOver, Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
	 Bo = Tower(pegged_cEtSum, pegged_tEtSum, Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
      }
   }
   else{
      Ao = Ai;
      Bo = Bi;
   }
}
