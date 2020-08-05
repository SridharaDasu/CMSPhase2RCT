#include "stitchTower.h"

void stitchNeighbors(size_t stitch, Tower Ai, Tower Bi, Tower &Ao, Tower &Bo) {
#pragma HLS PIPELINE II=6

  // Check that the clusters are neigbhors in eta or phi
  bool etaStitch = (stitch == stitch_in_eta && 
                    Ai.peak_eta() == 4 && 
		    Bi.peak_eta() == 0 && 
		    Ai.peak_phi() == Bi.peak_phi());

  bool phiStitch = (stitch == stitch_in_phi && 
                    Ai.peak_phi() == 4 && 
		    Bi.peak_phi() == 0 && 
		    Ai.peak_eta() == Bi.peak_eta());

  if(etaStitch || phiStitch){
    ap_uint<12> cEtSum = Ai.cluster_et() + Bi.cluster_et();
    ap_uint<10> pegged_cEtSum = (cEtSum > 0x3FF) ? (ap_uint<10>)0x3FF : (ap_uint<10>) cEtSum;

    if(Ai.cluster_et() > Bi.cluster_et()){
      // Merge 2 in to 1, and set 2 to remnant energy centered in tower
      ap_uint<12> tEtSum = Ai.tower_et() + Bi.cluster_et();
      ap_uint<10> pegged_tEtSum = (tEtSum > 0x3FF) ? (ap_uint<10>)0x3FF : (ap_uint<10>) tEtSum;
      ap_uint<10> tEt_leftOver = Bi.tower_et() - Bi.cluster_et();

      Ao = Tower(pegged_cEtSum, pegged_tEtSum, Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
      Bo = Tower(            0,  tEt_leftOver, Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
    }
    else{
      // Merge 1 in to 2, and set 1 to remnant energy centered in tower
      ap_uint<12> tEtSum = Bi.tower_et() + Ai.cluster_et();
      ap_uint<10> pegged_tEtSum = (tEtSum > 0x3FF) ? (ap_uint<10>)0x3FF : (ap_uint<10>) tEtSum;
      ap_uint<10> tEt_leftOver = Ai.tower_et() - Ai.cluster_et();
      Ao = Tower(            0,  tEt_leftOver, Ai.peak_phi(), Ai.peak_eta(), Ai.peak_time(), Ai.hOe());
      Bo = Tower(pegged_cEtSum, pegged_tEtSum, Bi.peak_phi(), Bi.peak_eta(), Bi.peak_time(), Bi.hOe());
    }
  }
  else{
    Ao = Ai;
    Bo = Bi;
  }
}
