#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "TowerMaker.h"

using namespace std;
using namespace algo;


//Each output link carries 576b of information
//17 towers can be fit in one link (32*17=544)
void processOutputData(hls::stream<axiword576> &link, ap_uint<576> bigdataword) {
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=9
#pragma HLS INLINE
  axiword576 r;
  r.user = 0;
  r.last = 1;
  r.data = bigdataword;
  link.write(r);
}

// Each input link carries the information of a 5x5 region
// Last 16-bits are reserved for CRC
void processInputData(hls::stream<axiword384> &link, CrystalGroup &crystalGroup) {
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
#pragma HLS PIPELINE II=6
  stitchNeighbors(0, towerLevelECALSummary[0], towerLevelECALSummary[1], etaStitchedE[0], etaStitchedE[1]);
  stitchNeighbors(0, towerLevelECALSummary[2], towerLevelECALSummary[3], etaStitchedE[2], etaStitchedE[3]);
  stitchNeighbors(0, towerLevelECALSummary[4], towerLevelECALSummary[5], etaStitchedE[4], etaStitchedE[5]);
  stitchNeighbors(0, towerLevelECALSummary[6], towerLevelECALSummary[7], etaStitchedE[6], etaStitchedE[7]);
  stitchNeighbors(0, towerLevelECALSummary[8], towerLevelECALSummary[9], etaStitchedE[8], etaStitchedE[9]);
  stitchNeighbors(0, towerLevelECALSummary[10], towerLevelECALSummary[11], etaStitchedE[10], etaStitchedE[11]);
  stitchNeighbors(0, towerLevelECALSummary[12], towerLevelECALSummary[13], etaStitchedE[12], etaStitchedE[13]);
  stitchNeighbors(0, towerLevelECALSummary[14], towerLevelECALSummary[15], etaStitchedE[14], etaStitchedE[15]);
  etaStitchedE[16] = towerLevelECALSummary[16];

  stitchNeighbors(0, towerLevelECALSummary[17], towerLevelECALSummary[18], etaStitchedE[17], etaStitchedE[18]);
  stitchNeighbors(0, towerLevelECALSummary[19], towerLevelECALSummary[20], etaStitchedE[19], etaStitchedE[20]);
  stitchNeighbors(0, towerLevelECALSummary[21], towerLevelECALSummary[22], etaStitchedE[21], etaStitchedE[22]);
  stitchNeighbors(0, towerLevelECALSummary[23], towerLevelECALSummary[24], etaStitchedE[23], etaStitchedE[24]);
  stitchNeighbors(0, towerLevelECALSummary[25], towerLevelECALSummary[26], etaStitchedE[25], etaStitchedE[26]);
  stitchNeighbors(0, towerLevelECALSummary[27], towerLevelECALSummary[28], etaStitchedE[27], etaStitchedE[28]);
  stitchNeighbors(0, towerLevelECALSummary[29], towerLevelECALSummary[30], etaStitchedE[29], etaStitchedE[30]);
  stitchNeighbors(0, towerLevelECALSummary[31], towerLevelECALSummary[32], etaStitchedE[31], etaStitchedE[32]);
  etaStitchedE[33] = towerLevelECALSummary[33];
}

void stitchInEta2(Tower etaStitchedE[N_INPUT_LINKS], Tower etaStitched[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=etaStitchedE
#pragma HLS ARRAY_PARTITION variable=etaStitched
#pragma HLS PIPELINE II=6
  etaStitched[0] = etaStitchedE[0];
  stitchNeighbors(0, etaStitchedE[1], etaStitchedE[2], etaStitched[1], etaStitched[2]);
  stitchNeighbors(0, etaStitchedE[3], etaStitchedE[4], etaStitched[3], etaStitched[4]);
  stitchNeighbors(0, etaStitchedE[5], etaStitchedE[6], etaStitched[5], etaStitched[6]);
  stitchNeighbors(0, etaStitchedE[7], etaStitchedE[8], etaStitched[7], etaStitched[8]);
  stitchNeighbors(0, etaStitchedE[9], etaStitchedE[10], etaStitched[9], etaStitched[10]);
  stitchNeighbors(0, etaStitchedE[11], etaStitchedE[12], etaStitched[11], etaStitched[12]);
  stitchNeighbors(0, etaStitchedE[13], etaStitchedE[14], etaStitched[13], etaStitched[14]);
  stitchNeighbors(0, etaStitchedE[15], etaStitchedE[16], etaStitched[15], etaStitched[16]);

  etaStitched[17] = etaStitchedE[17];
  stitchNeighbors(0, etaStitchedE[18], etaStitchedE[19], etaStitched[18], etaStitched[19]);
  stitchNeighbors(0, etaStitchedE[20], etaStitchedE[21], etaStitched[20], etaStitched[21]);
  stitchNeighbors(0, etaStitchedE[22], etaStitchedE[23], etaStitched[22], etaStitched[23]);
  stitchNeighbors(0, etaStitchedE[24], etaStitchedE[25], etaStitched[24], etaStitched[25]);
  stitchNeighbors(0, etaStitchedE[26], etaStitchedE[27], etaStitched[26], etaStitched[27]);
  stitchNeighbors(0, etaStitchedE[28], etaStitchedE[29], etaStitched[28], etaStitched[29]);
  stitchNeighbors(0, etaStitchedE[30], etaStitchedE[31], etaStitched[30], etaStitched[31]);
  stitchNeighbors(0, etaStitchedE[32], etaStitchedE[33], etaStitched[32], etaStitched[33]);
}

void stitchInPhi(Tower etaStitched[N_INPUT_LINKS], Tower stitchedTowerLevelECALSummary[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=etaStitched
#pragma HLS ARRAY_PARTITION variable=stitchedTowerLevelECALSummary
#pragma HLS PIPELINE II=6
  stitchNeighbors(1, etaStitched[0], etaStitched[17], stitchedTowerLevelECALSummary[0], stitchedTowerLevelECALSummary[17]);
  stitchNeighbors(1, etaStitched[1], etaStitched[18], stitchedTowerLevelECALSummary[1], stitchedTowerLevelECALSummary[18]);
  stitchNeighbors(1, etaStitched[2], etaStitched[19], stitchedTowerLevelECALSummary[2], stitchedTowerLevelECALSummary[19]);
  stitchNeighbors(1, etaStitched[3], etaStitched[20], stitchedTowerLevelECALSummary[3], stitchedTowerLevelECALSummary[20]);
  stitchNeighbors(1, etaStitched[4], etaStitched[21], stitchedTowerLevelECALSummary[4], stitchedTowerLevelECALSummary[21]);
  stitchNeighbors(1, etaStitched[5], etaStitched[22], stitchedTowerLevelECALSummary[5], stitchedTowerLevelECALSummary[22]);
  stitchNeighbors(1, etaStitched[6], etaStitched[23], stitchedTowerLevelECALSummary[6], stitchedTowerLevelECALSummary[23]);
  stitchNeighbors(1, etaStitched[7], etaStitched[24], stitchedTowerLevelECALSummary[7], stitchedTowerLevelECALSummary[24]);
  stitchNeighbors(1, etaStitched[8], etaStitched[25], stitchedTowerLevelECALSummary[8], stitchedTowerLevelECALSummary[25]);
  stitchNeighbors(1, etaStitched[9], etaStitched[26], stitchedTowerLevelECALSummary[9], stitchedTowerLevelECALSummary[26]);
  stitchNeighbors(1, etaStitched[10], etaStitched[27], stitchedTowerLevelECALSummary[10], stitchedTowerLevelECALSummary[27]);
  stitchNeighbors(1, etaStitched[11], etaStitched[28], stitchedTowerLevelECALSummary[11], stitchedTowerLevelECALSummary[28]);
  stitchNeighbors(1, etaStitched[12], etaStitched[29], stitchedTowerLevelECALSummary[12], stitchedTowerLevelECALSummary[29]);
  stitchNeighbors(1, etaStitched[13], etaStitched[30], stitchedTowerLevelECALSummary[13], stitchedTowerLevelECALSummary[30]);
  stitchNeighbors(1, etaStitched[14], etaStitched[31], stitchedTowerLevelECALSummary[14], stitchedTowerLevelECALSummary[31]);
  stitchNeighbors(1, etaStitched[15], etaStitched[32], stitchedTowerLevelECALSummary[15], stitchedTowerLevelECALSummary[32]);
  stitchNeighbors(1, etaStitched[16], etaStitched[33], stitchedTowerLevelECALSummary[16], stitchedTowerLevelECALSummary[33]);
}

void algo_top(hls::stream<axiword384> link_in[N_INPUT_LINKS], hls::stream<axiword576> link_out[N_OUTPUT_LINKS]) {
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
  ap_uint<576> outWord_576b;

 link0OutputLoop: for(size_t tower = 0; tower < 17; tower++) { 
#pragma HLS UNROLL
  size_t end = start + 31;
  outWord_576b.range(end, start) = stitchedTowerLevelECALSummary[tower];
  start += 32;
  }
  processOutputData(link_out[0], outWord_576b);

  start = 0;
 link1OutputLoop: for(size_t tower = 17; tower < 33; tower++) { 
#pragma HLS UNROLL
  size_t end = start + 31;
  outWord_576b.range(end, start) = stitchedTowerLevelECALSummary[tower];
  start += 32;
  }
  outWord_576b.range(575, 544) = ecalSummary;
  processOutputData(link_out[1], outWord_576b);

}
