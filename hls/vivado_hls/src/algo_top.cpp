
#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "TowerMaker.h"

using namespace std;
using namespace algo;

void processOutputData(hls::stream<axiword> &link, ap_uint<384> bigdataword) {
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=6
#pragma HLS INLINE
  axiword r;
  r.user = 0;
  r.last = 1;
  r.data = bigdataword;
  link.write(r);
}

// Each input link carries the information of a 5x5 region
// Last 16-bits are reserved for CRC
void processInputData(hls::stream<axiword> &link, CrystalGroup &crystalGroup) {
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=6
#pragma HLS INLINE
#ifndef __SYNTHESIS__
  // Avoid simulation warnings
  if (link.empty()) return;
#endif
  ap_uint<384> bigdataword = link.read().data;
  crystalGroup = CrystalGroup(bigdataword);
  return;
}


void stitchInEta1(Tower towerLevelECALSummary[N_INPUT_LINKS], Tower etaStitchedE[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary
#pragma HLS ARRAY_PARTITION variable=etaStitched
#pragma HLS PIPELINE
  stitchNeighbors(towerLevelECALSummary[0], towerLevelECALSummary[1], etaStitchedE[0], etaStitchedE[1]);
  stitchNeighbors(towerLevelECALSummary[2], towerLevelECALSummary[3], etaStitchedE[2], etaStitchedE[3]);
  stitchNeighbors(towerLevelECALSummary[4], towerLevelECALSummary[5], etaStitchedE[4], etaStitchedE[5]);
  stitchNeighbors(towerLevelECALSummary[6], towerLevelECALSummary[7], etaStitchedE[6], etaStitchedE[7]);
  stitchNeighbors(towerLevelECALSummary[8], towerLevelECALSummary[9], etaStitchedE[8], etaStitchedE[9]);
  stitchNeighbors(towerLevelECALSummary[10], towerLevelECALSummary[11], etaStitchedE[10], etaStitchedE[11]);
  stitchNeighbors(towerLevelECALSummary[12], towerLevelECALSummary[13], etaStitchedE[12], etaStitchedE[13]);
  stitchNeighbors(towerLevelECALSummary[14], towerLevelECALSummary[15], etaStitchedE[14], etaStitchedE[15]);
  stitchNeighbors(towerLevelECALSummary[16], towerLevelECALSummary[17], etaStitchedE[16], etaStitchedE[17]);
  stitchNeighbors(towerLevelECALSummary[18], towerLevelECALSummary[19], etaStitchedE[18], etaStitchedE[19]);
  stitchNeighbors(towerLevelECALSummary[20], towerLevelECALSummary[21], etaStitchedE[20], etaStitchedE[21]);
  stitchNeighbors(towerLevelECALSummary[22], towerLevelECALSummary[23], etaStitchedE[22], etaStitchedE[23]);
  stitchNeighbors(towerLevelECALSummary[24], towerLevelECALSummary[25], etaStitchedE[24], etaStitchedE[25]);
  stitchNeighbors(towerLevelECALSummary[26], towerLevelECALSummary[27], etaStitchedE[26], etaStitchedE[27]);
  stitchNeighbors(towerLevelECALSummary[28], towerLevelECALSummary[29], etaStitchedE[28], etaStitchedE[29]);
  stitchNeighbors(towerLevelECALSummary[30], towerLevelECALSummary[31], etaStitchedE[30], etaStitchedE[31]);
  stitchNeighbors(towerLevelECALSummary[32], towerLevelECALSummary[33], etaStitchedE[32], etaStitchedE[33]);
}

void stitchInEta2(Tower etaStitchedE[N_INPUT_LINKS], Tower etaStitched[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=etaStitchedE
#pragma HLS ARRAY_PARTITION variable=etaStitched
#pragma HLS PIPELINE
  etaStitched[0] = etaStitchedE[0];
  stitchNeighbors(etaStitchedE[1], etaStitchedE[2], etaStitched[1], etaStitched[2]);
  stitchNeighbors(etaStitchedE[3], etaStitchedE[4], etaStitched[3], etaStitched[4]);
  stitchNeighbors(etaStitchedE[5], etaStitchedE[6], etaStitched[5], etaStitched[6]);
  stitchNeighbors(etaStitchedE[7], etaStitchedE[8], etaStitched[7], etaStitched[8]);
  stitchNeighbors(etaStitchedE[9], etaStitchedE[10], etaStitched[9], etaStitched[10]);
  stitchNeighbors(etaStitchedE[11], etaStitchedE[12], etaStitched[11], etaStitched[12]);
  stitchNeighbors(etaStitchedE[13], etaStitchedE[14], etaStitched[13], etaStitched[14]);
  stitchNeighbors(etaStitchedE[15], etaStitchedE[16], etaStitched[15], etaStitched[16]);
  stitchNeighbors(etaStitchedE[17], etaStitchedE[18], etaStitched[17], etaStitched[18]);
  stitchNeighbors(etaStitchedE[19], etaStitchedE[20], etaStitched[19], etaStitched[20]);
  stitchNeighbors(etaStitchedE[21], etaStitchedE[22], etaStitched[21], etaStitched[22]);
  stitchNeighbors(etaStitchedE[23], etaStitchedE[24], etaStitched[23], etaStitched[24]);
  stitchNeighbors(etaStitchedE[25], etaStitchedE[26], etaStitched[25], etaStitched[26]);
  stitchNeighbors(etaStitchedE[27], etaStitchedE[28], etaStitched[27], etaStitched[28]);
  stitchNeighbors(etaStitchedE[29], etaStitchedE[30], etaStitched[29], etaStitched[30]);
  stitchNeighbors(etaStitchedE[31], etaStitchedE[32], etaStitched[31], etaStitched[32]);
  etaStitched[33] = etaStitchedE[33];
}

void stitchInPhi(Tower etaStitched[N_INPUT_LINKS], Tower stitchedTowerLevelECALSummary[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=etaStitched
#pragma HLS ARRAY_PARTITION variable=stitchedTowerLevelECALSummary
#pragma HLS PIPELINE
  stitchNeighbors(etaStitched[0], etaStitched[17], stitchedTowerLevelECALSummary[0], stitchedTowerLevelECALSummary[17]);
  stitchNeighbors(etaStitched[1], etaStitched[18], stitchedTowerLevelECALSummary[1], stitchedTowerLevelECALSummary[18]);
  stitchNeighbors(etaStitched[2], etaStitched[19], stitchedTowerLevelECALSummary[2], stitchedTowerLevelECALSummary[19]);
  stitchNeighbors(etaStitched[3], etaStitched[20], stitchedTowerLevelECALSummary[3], stitchedTowerLevelECALSummary[20]);
  stitchNeighbors(etaStitched[4], etaStitched[21], stitchedTowerLevelECALSummary[4], stitchedTowerLevelECALSummary[21]);
  stitchNeighbors(etaStitched[5], etaStitched[22], stitchedTowerLevelECALSummary[5], stitchedTowerLevelECALSummary[22]);
  stitchNeighbors(etaStitched[6], etaStitched[23], stitchedTowerLevelECALSummary[6], stitchedTowerLevelECALSummary[23]);
  stitchNeighbors(etaStitched[7], etaStitched[24], stitchedTowerLevelECALSummary[7], stitchedTowerLevelECALSummary[24]);
  stitchNeighbors(etaStitched[8], etaStitched[25], stitchedTowerLevelECALSummary[8], stitchedTowerLevelECALSummary[25]);
  stitchNeighbors(etaStitched[9], etaStitched[26], stitchedTowerLevelECALSummary[9], stitchedTowerLevelECALSummary[26]);
  stitchNeighbors(etaStitched[10], etaStitched[27], stitchedTowerLevelECALSummary[10], stitchedTowerLevelECALSummary[27]);
  stitchNeighbors(etaStitched[11], etaStitched[28], stitchedTowerLevelECALSummary[11], stitchedTowerLevelECALSummary[28]);
  stitchNeighbors(etaStitched[12], etaStitched[29], stitchedTowerLevelECALSummary[12], stitchedTowerLevelECALSummary[29]);
  stitchNeighbors(etaStitched[13], etaStitched[30], stitchedTowerLevelECALSummary[13], stitchedTowerLevelECALSummary[30]);
  stitchNeighbors(etaStitched[14], etaStitched[31], stitchedTowerLevelECALSummary[14], stitchedTowerLevelECALSummary[31]);
  stitchNeighbors(etaStitched[15], etaStitched[32], stitchedTowerLevelECALSummary[15], stitchedTowerLevelECALSummary[32]);
  stitchNeighbors(etaStitched[16], etaStitched[33], stitchedTowerLevelECALSummary[16], stitchedTowerLevelECALSummary[33]);
}

void algo_top(hls::stream<axiword> link_in[N_INPUT_LINKS], hls::stream<axiword> link_out[N_OUTPUT_LINKS]) {
#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out
#pragma HLS PIPELINE II=6

  // Step First: Unpack to make crystals
  CrystalGroup crystals[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=crystals
 makeCrystalsLoop: for (size_t iLink = 0; iLink < N_INPUT_LINKS; iLink++) {
#pragma HLS UNROLL
    processInputData(link_in[iLink], crystals[iLink]);
  }

  // Make towers - operations not using tower pairs
  Tower towerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary
 makeTowersLoop: for (size_t iLink = 0; iLink < N_INPUT_LINKS; iLink++) {
#pragma HLS UNROLL
    makeTower(crystals[iLink], towerLevelECALSummary[iLink]);
  }

  // Compute total ECAL ET

  ap_uint<32> ecalSummary = makeECALSummary(towerLevelECALSummary);

  // Stitch neighboring towers
  
  Tower etaStitchedE[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitchedE
  
  stitchInEta1(towerLevelECALSummary, etaStitchedE);

  Tower etaStitched[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched

  stitchInEta2(etaStitchedE, etaStitched);

  Tower stitchedTowerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=stitchedTowerLevelECALSummary

  stitchInPhi(etaStitched, stitchedTowerLevelECALSummary);

  // Step Last: Pack and write the output

  size_t start = 0;
  ap_uint<384> bigdataword;
 link0OutputLoop: for (size_t tower = 0; tower < 12; tower++) {
#pragma HLS UNROLL
    size_t end = start + 31;
    bigdataword.range(end, start) = stitchedTowerLevelECALSummary[tower];
    start += 32;
  }
  processOutputData(link_out[0], bigdataword);
  start = 0;
 link1OutputLoop: for (size_t tower = 12; tower < 24; tower++) {
#pragma HLS UNROLL
    size_t end = start + 31;
    bigdataword.range(end, start) = stitchedTowerLevelECALSummary[tower];
    start += 32;
  }
  processOutputData(link_out[1], bigdataword);
  start = 0;
 link2OutputLoop: for (size_t tower = 24; tower < 34; tower++) {
#pragma HLS UNROLL
    size_t end = start + 31;
    bigdataword.range(end, start) = stitchedTowerLevelECALSummary[tower];
    start += 32;
  }
  bigdataword.range(383, start) = 0;
  processOutputData(link_out[2], bigdataword);
  start = 0;
 link3OutputLoop: for (size_t tower = 0; tower < 12; tower++) {
#pragma HLS UNROLL
    size_t end = start + 31;
    bigdataword.range(end, start) = ecalSummary;
  }
  processOutputData(link_out[3], bigdataword);

}
