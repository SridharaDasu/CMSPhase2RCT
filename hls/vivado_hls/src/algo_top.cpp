#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "TowerMaker.h"

using namespace std;
using namespace algo;

// Each input link carries the information of a 5x5 region
// Last 16-bits are reserved for CRC
void processInputData(hls::stream<axiword> &link, ap_uint<64> words[N_WORDS_PER_FRAME]) {
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=6
  for (size_t i = 0; i < N_WORDS_PER_FRAME; i++) {
#ifndef __SYNTHESIS__
    // Avoid simulation warnings
    if (link.empty()) continue;
#endif
    words[i] = link.read().data;
  }
}

void processOutputData(hls::stream<axiword> &link, ap_uint<64> words[N_WORDS_PER_FRAME]) {
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=6
  for (size_t i = 0; i < N_OUTPUT_WORDS_PER_FRAME; i++) {
    axiword r;
    r.user = 0;
    if (i == (N_OUTPUT_WORDS_PER_FRAME - 1)) {
      r.last = 0;
    }
    else {
      r.last = 1;
    }
    r.data = words[i];
    link.write(r);
  }
}

void makeCrystals(ap_uint<64> words[N_WORDS_PER_FRAME], Crystal crystals[5][5]) {
#pragma HLS PIPELINE
#pragma HLS ARRAY_PARTITION variable=words
#pragma HLS ARRAY_PARTITION variable=crystals
  crystals[0][0] = Crystal(words[0].range(13,  0));
  crystals[0][1] = Crystal(words[0].range(27, 14));
  crystals[0][2] = Crystal(words[0].range(41, 28));
  crystals[0][3] = Crystal(words[0].range(55, 42));
  ap_uint<8> leftover0 = words[0].range(63, 56);
  crystals[0][4] = Crystal(words[1].range(13,  0));
  crystals[1][0] = Crystal(words[1].range(27, 14));
  crystals[1][1] = Crystal(words[1].range(41, 28));
  crystals[1][2] = Crystal(words[1].range(55, 42));
  ap_uint<8> leftover1 = words[1].range(63, 56);
  crystals[1][3] = Crystal(words[2].range(13,  0));
  crystals[1][4] = Crystal(words[2].range(27, 14));
  crystals[2][0] = Crystal(words[2].range(41, 28));
  crystals[2][1] = Crystal(words[2].range(55, 42));
  ap_uint<8> leftover2 = words[2].range(63, 56);
  crystals[2][2] = Crystal(words[3].range(13,  0));
  crystals[2][3] = Crystal(words[3].range(27, 14));
  crystals[2][4] = Crystal(words[3].range(41, 28));
  crystals[3][0] = Crystal(words[3].range(55, 42));
  ap_uint<8> leftover3 = words[3].range(63, 56);
  crystals[3][1] = Crystal(words[4].range(13,  0));
  crystals[3][2] = Crystal(words[4].range(27, 14));
  crystals[3][3] = Crystal(words[4].range(41, 28));
  crystals[3][4] = Crystal(words[4].range(55, 42));
  ap_uint<8> leftover4 = words[4].range(63, 56);
  crystals[4][0] = Crystal(words[5].range(13,  0));
  crystals[4][1] = Crystal(words[5].range(27, 14));
  crystals[4][2] = Crystal(words[5].range(41, 28));
  crystals[4][3] = Crystal(words[5].range(55, 42));
  ap_uint<8> leftover5 = words[5].range(63, 56);
  ap_uint<14> crystalData44 = (((ap_uint<14>) (leftover1.range(5, 0) & 0x3F)) << 8)  | ((ap_uint<14>) leftover0);
  crystals[4][4] = Crystal(crystalData44);
  ap_uint<32> crc = (((ap_uint<32>) leftover5) << 24) | (((ap_uint<32>) leftover4) << 16) | (((ap_uint<32>) leftover3) << 8) | ((ap_uint<32>) leftover2);
}


void algo_top(hls::stream<axiword> link_in[N_INPUT_LINKS], hls::stream<axiword> link_out[N_OUTPUT_LINKS]) {
#pragma HLS PIPELINE
#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out

  // Step First: Unpack
  ap_uint<64> input[N_INPUT_LINKS][N_WORDS_PER_FRAME];
#pragma HLS ARRAY_PARTITION variable=input
  processInputData(link_in[0], input[0]);
  processInputData(link_in[1], input[1]);
  processInputData(link_in[2], input[2]);
  processInputData(link_in[3], input[3]);
  processInputData(link_in[4], input[4]);
  processInputData(link_in[5], input[5]);
  processInputData(link_in[6], input[6]);
  processInputData(link_in[7], input[7]);
  processInputData(link_in[8], input[8]);
  processInputData(link_in[9], input[9]);
  processInputData(link_in[10], input[10]);
  processInputData(link_in[11], input[11]);
  processInputData(link_in[12], input[12]);
  processInputData(link_in[13], input[13]);
  processInputData(link_in[14], input[14]);
  processInputData(link_in[15], input[15]);
  processInputData(link_in[16], input[16]);
  processInputData(link_in[17], input[17]);
  processInputData(link_in[18], input[18]);
  processInputData(link_in[19], input[19]);
  processInputData(link_in[20], input[20]);
  processInputData(link_in[21], input[21]);
  processInputData(link_in[22], input[22]);
  processInputData(link_in[23], input[23]);
  processInputData(link_in[24], input[24]);
  processInputData(link_in[25], input[25]);
  processInputData(link_in[26], input[26]);
  processInputData(link_in[27], input[27]);
  processInputData(link_in[28], input[28]);
  processInputData(link_in[29], input[29]);
  processInputData(link_in[30], input[30]);
  processInputData(link_in[31], input[31]);
  processInputData(link_in[32], input[32]);
  processInputData(link_in[33], input[33]);

  // Make crystals
  Crystal crystals0[5][5];
  Crystal crystals1[5][5];
  Crystal crystals2[5][5];
  Crystal crystals3[5][5];
  Crystal crystals4[5][5];
  Crystal crystals5[5][5];
  Crystal crystals6[5][5];
  Crystal crystals7[5][5];
  Crystal crystals8[5][5];
  Crystal crystals9[5][5];
  Crystal crystals10[5][5];
  Crystal crystals11[5][5];
  Crystal crystals12[5][5];
  Crystal crystals13[5][5];
  Crystal crystals14[5][5];
  Crystal crystals15[5][5];
  Crystal crystals16[5][5];
  Crystal crystals17[5][5];
  Crystal crystals18[5][5];
  Crystal crystals19[5][5];
  Crystal crystals20[5][5];
  Crystal crystals21[5][5];
  Crystal crystals22[5][5];
  Crystal crystals23[5][5];
  Crystal crystals24[5][5];
  Crystal crystals25[5][5];
  Crystal crystals26[5][5];
  Crystal crystals27[5][5];
  Crystal crystals28[5][5];
  Crystal crystals29[5][5];
  Crystal crystals30[5][5];
  Crystal crystals31[5][5];
  Crystal crystals32[5][5];
  Crystal crystals33[5][5];
#pragma HLS ARRAY_PARTITION variable=crystals0
#pragma HLS ARRAY_PARTITION variable=crystals1
#pragma HLS ARRAY_PARTITION variable=crystals2
#pragma HLS ARRAY_PARTITION variable=crystals3
#pragma HLS ARRAY_PARTITION variable=crystals4
#pragma HLS ARRAY_PARTITION variable=crystals5
#pragma HLS ARRAY_PARTITION variable=crystals6
#pragma HLS ARRAY_PARTITION variable=crystals7
#pragma HLS ARRAY_PARTITION variable=crystals8
#pragma HLS ARRAY_PARTITION variable=crystals9
#pragma HLS ARRAY_PARTITION variable=crystals10
#pragma HLS ARRAY_PARTITION variable=crystals11
#pragma HLS ARRAY_PARTITION variable=crystals12
#pragma HLS ARRAY_PARTITION variable=crystals13
#pragma HLS ARRAY_PARTITION variable=crystals14
#pragma HLS ARRAY_PARTITION variable=crystals15
#pragma HLS ARRAY_PARTITION variable=crystals16
#pragma HLS ARRAY_PARTITION variable=crystals17
#pragma HLS ARRAY_PARTITION variable=crystals18
#pragma HLS ARRAY_PARTITION variable=crystals19
#pragma HLS ARRAY_PARTITION variable=crystals20
#pragma HLS ARRAY_PARTITION variable=crystals21
#pragma HLS ARRAY_PARTITION variable=crystals22
#pragma HLS ARRAY_PARTITION variable=crystals23
#pragma HLS ARRAY_PARTITION variable=crystals24
#pragma HLS ARRAY_PARTITION variable=crystals25
#pragma HLS ARRAY_PARTITION variable=crystals26
#pragma HLS ARRAY_PARTITION variable=crystals27
#pragma HLS ARRAY_PARTITION variable=crystals28
#pragma HLS ARRAY_PARTITION variable=crystals29
#pragma HLS ARRAY_PARTITION variable=crystals30
#pragma HLS ARRAY_PARTITION variable=crystals31
#pragma HLS ARRAY_PARTITION variable=crystals32
#pragma HLS ARRAY_PARTITION variable=crystals33
  makeCrystals(input[0], crystals0);
  makeCrystals(input[1], crystals1);
  makeCrystals(input[2], crystals2);
  makeCrystals(input[3], crystals3);
  makeCrystals(input[4], crystals4);
  makeCrystals(input[5], crystals5);
  makeCrystals(input[6], crystals6);
  makeCrystals(input[7], crystals7);
  makeCrystals(input[8], crystals8);
  makeCrystals(input[9], crystals9);
  makeCrystals(input[10], crystals10);
  makeCrystals(input[11], crystals11);
  makeCrystals(input[12], crystals12);
  makeCrystals(input[13], crystals13);
  makeCrystals(input[14], crystals14);
  makeCrystals(input[15], crystals15);
  makeCrystals(input[16], crystals16);
  makeCrystals(input[17], crystals17);
  makeCrystals(input[18], crystals18);
  makeCrystals(input[19], crystals19);
  makeCrystals(input[20], crystals20);
  makeCrystals(input[21], crystals21);
  makeCrystals(input[22], crystals22);
  makeCrystals(input[23], crystals23);
  makeCrystals(input[24], crystals24);
  makeCrystals(input[25], crystals25);
  makeCrystals(input[26], crystals26);
  makeCrystals(input[27], crystals27);
  makeCrystals(input[28], crystals28);
  makeCrystals(input[29], crystals29);
  makeCrystals(input[30], crystals30);
  makeCrystals(input[31], crystals31);
  makeCrystals(input[32], crystals32);
  makeCrystals(input[33], crystals33);

  // Make towers - operations not using tower pairs
  Tower towerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary
  makeTower(crystals0, towerLevelECALSummary[0]);
  makeTower(crystals1, towerLevelECALSummary[1]);
  makeTower(crystals2, towerLevelECALSummary[2]);
  makeTower(crystals3, towerLevelECALSummary[3]);
  makeTower(crystals4, towerLevelECALSummary[4]);
  makeTower(crystals5, towerLevelECALSummary[5]);
  makeTower(crystals6, towerLevelECALSummary[6]);
  makeTower(crystals7, towerLevelECALSummary[7]);
  makeTower(crystals8, towerLevelECALSummary[8]);
  makeTower(crystals9, towerLevelECALSummary[9]);
  makeTower(crystals10, towerLevelECALSummary[10]);
  makeTower(crystals11, towerLevelECALSummary[11]);
  makeTower(crystals12, towerLevelECALSummary[12]);
  makeTower(crystals13, towerLevelECALSummary[13]);
  makeTower(crystals14, towerLevelECALSummary[14]);
  makeTower(crystals15, towerLevelECALSummary[15]);
  makeTower(crystals16, towerLevelECALSummary[16]);
  makeTower(crystals17, towerLevelECALSummary[17]);
  makeTower(crystals18, towerLevelECALSummary[18]);
  makeTower(crystals19, towerLevelECALSummary[19]);
  makeTower(crystals20, towerLevelECALSummary[20]);
  makeTower(crystals21, towerLevelECALSummary[21]);
  makeTower(crystals22, towerLevelECALSummary[22]);
  makeTower(crystals23, towerLevelECALSummary[23]);
  makeTower(crystals24, towerLevelECALSummary[24]);
  makeTower(crystals25, towerLevelECALSummary[25]);
  makeTower(crystals26, towerLevelECALSummary[26]);
  makeTower(crystals27, towerLevelECALSummary[27]);
  makeTower(crystals28, towerLevelECALSummary[28]);
  makeTower(crystals29, towerLevelECALSummary[29]);
  makeTower(crystals30, towerLevelECALSummary[30]);
  makeTower(crystals31, towerLevelECALSummary[31]);
  makeTower(crystals32, towerLevelECALSummary[32]);
  makeTower(crystals33, towerLevelECALSummary[33]);

  // Compute total ECAL ET

  ap_uint<32> ecalSummary = makeECALSummary(towerLevelECALSummary);

  // Stitch neighboring towers
  
  Tower etaStitchedE[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitchedE
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

  Tower etaStitched[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched
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

  Tower stitchedTowerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=stitchedTowerLevelECALSummary

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

  // Pack the outputs

  ap_uint<64> output[N_OUTPUT_LINKS][N_WORDS_PER_FRAME];
#pragma HLS ARRAY_PARTITION variable=output
  output[0][0] = (ap_uint<64>) stitchedTowerLevelECALSummary[0] | (ap_uint<64>) stitchedTowerLevelECALSummary[1] << 32;
  output[0][1] = (ap_uint<64>) stitchedTowerLevelECALSummary[2] | (ap_uint<64>) stitchedTowerLevelECALSummary[3] << 32;
  output[0][2] = (ap_uint<64>) stitchedTowerLevelECALSummary[4] | (ap_uint<64>) stitchedTowerLevelECALSummary[5] << 32;
  output[0][3] = (ap_uint<64>) stitchedTowerLevelECALSummary[6] | (ap_uint<64>) stitchedTowerLevelECALSummary[7] << 32;
  output[0][4] = (ap_uint<64>) stitchedTowerLevelECALSummary[8] | (ap_uint<64>) stitchedTowerLevelECALSummary[9] << 32;
  output[0][5] = (ap_uint<64>) stitchedTowerLevelECALSummary[10] | (ap_uint<64>) stitchedTowerLevelECALSummary[11] << 32;
  output[1][0] = (ap_uint<64>) stitchedTowerLevelECALSummary[12] | (ap_uint<64>) stitchedTowerLevelECALSummary[13] << 32;
  output[1][1] = (ap_uint<64>) stitchedTowerLevelECALSummary[14] | (ap_uint<64>) stitchedTowerLevelECALSummary[15] << 32;
  output[1][2] = (ap_uint<64>) stitchedTowerLevelECALSummary[16] | (ap_uint<64>) stitchedTowerLevelECALSummary[17] << 32;
  output[1][3] = (ap_uint<64>) stitchedTowerLevelECALSummary[18] | (ap_uint<64>) stitchedTowerLevelECALSummary[19] << 32;
  output[1][4] = (ap_uint<64>) stitchedTowerLevelECALSummary[20] | (ap_uint<64>) stitchedTowerLevelECALSummary[21] << 32;
  output[1][5] = (ap_uint<64>) stitchedTowerLevelECALSummary[22] | (ap_uint<64>) stitchedTowerLevelECALSummary[23] << 32;
  output[2][0] = (ap_uint<64>) stitchedTowerLevelECALSummary[24] | (ap_uint<64>) stitchedTowerLevelECALSummary[25] << 32;
  output[2][1] = (ap_uint<64>) stitchedTowerLevelECALSummary[26] | (ap_uint<64>) stitchedTowerLevelECALSummary[27] << 32;
  output[2][2] = (ap_uint<64>) stitchedTowerLevelECALSummary[28] | (ap_uint<64>) stitchedTowerLevelECALSummary[29] << 32;
  output[2][3] = (ap_uint<64>) stitchedTowerLevelECALSummary[30] | (ap_uint<64>) stitchedTowerLevelECALSummary[31] << 32;
  output[2][4] = (ap_uint<64>) stitchedTowerLevelECALSummary[32] | (ap_uint<64>) stitchedTowerLevelECALSummary[33] << 32;
  output[2][5] = (ap_uint<64>) ecalSummary;
  output[3][0] = (ap_uint<64>) ecalSummary;
  output[3][1] = (ap_uint<64>) ecalSummary;
  output[3][2] = (ap_uint<64>) ecalSummary;
  output[3][3] = (ap_uint<64>) ecalSummary;
  output[3][4] = (ap_uint<64>) ecalSummary;
  output[3][5] = (ap_uint<64>) ecalSummary;

  // Step Last: Write the output

  processOutputData(link_out[0], output[0]);
  processOutputData(link_out[1], output[1]);
  processOutputData(link_out[2], output[2]);
  processOutputData(link_out[3], output[3]);

}
