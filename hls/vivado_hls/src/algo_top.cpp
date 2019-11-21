#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "TowerMaker.h"

using namespace std;
using namespace algo;

// Each input link carries the information of a 5x5 region
// Last 16-bits are reserved for CRC
void processECALLinkData(hls::stream<axiword> &link, ap_uint<64> words[N_WORDS_PER_FRAME]) {
#pragma HLS INLINE
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=words complete dim=0

  for (size_t i = 0; i < N_WORDS_PER_FRAME; i++) {
#pragma LOOP UNROLL
#ifndef __SYNTHESIS__
    // Avoid simulation warnings
    if (link.empty()) continue;
#endif
#pragma HLS latency min=1 max=1
    words[i] = link.read().data;

  }
  
}

void makeCrystals(ap_uint<64> words[N_WORDS_PER_FRAME], Crystal crystals[5][5]) {
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=words complete dim=0
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
#pragma HLS latency min=1 max=6
  crystals[0][0] = Crystal(words[0].range( 0, 13));
  crystals[0][1] = Crystal(words[0].range(14, 27));
  crystals[0][2] = Crystal(words[0].range(28, 41));
  crystals[0][3] = Crystal(words[0].range(42, 55));
  ap_uint<8> leftover0 = words[0].range(56, 63);
  crystals[0][4] = Crystal(words[1].range( 0, 13));
  crystals[1][0] = Crystal(words[1].range(14, 27));
  crystals[1][1] = Crystal(words[1].range(28, 41));
  crystals[1][2] = Crystal(words[1].range(42, 55));
  ap_uint<8> leftover1 = words[1].range(56, 63);
  crystals[1][3] = Crystal(words[2].range( 0, 13));
  crystals[1][4] = Crystal(words[2].range(14, 27));
  crystals[2][0] = Crystal(words[2].range(28, 41));
  crystals[2][1] = Crystal(words[2].range(42, 55));
  ap_uint<8> leftover2 = words[2].range(56, 63);
  crystals[2][2] = Crystal(words[3].range( 0, 13));
  crystals[2][3] = Crystal(words[3].range(14, 27));
  crystals[2][4] = Crystal(words[3].range(28, 41));
  crystals[3][0] = Crystal(words[3].range(42, 55));
  ap_uint<8> leftover3 = words[3].range(56, 63);
  crystals[3][1] = Crystal(words[4].range( 0, 13));
  crystals[3][2] = Crystal(words[4].range(14, 27));
  crystals[3][3] = Crystal(words[4].range(28, 41));
  crystals[3][4] = Crystal(words[4].range(42, 55));
  ap_uint<8> leftover4 = words[4].range(56, 63);
  crystals[4][0] = Crystal(words[5].range( 0, 13));
  crystals[4][1] = Crystal(words[5].range(14, 27));
  crystals[4][2] = Crystal(words[5].range(28, 41));
  crystals[4][3] = Crystal(words[5].range(42, 55));
  ap_uint<8> leftover5 = words[5].range(56, 63);
  ap_uint<14> crystalData44 = (((ap_uint<14>) (leftover1.range(0, 5) & 0x3F)) << 8)  | ((ap_uint<14>) leftover0);
  crystals[4][4] = Crystal(crystalData44);
  ap_uint<32> crc = (((ap_uint<32>) leftover5) << 24) | (((ap_uint<32>) leftover4) << 16) | (((ap_uint<32>) leftover3) << 8) | ((ap_uint<32>) leftover2);
}

/*
ap_uint<32> makeECALSummary(Tower towerLevelECALSummary[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary complete dim=0
#pragma HLS latency max=6
#pragma HLS PIPELINE II=1
  ap_uint<32> ecalSummary = 0;
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
    ecalSummary += towerLevelECALSummary[i].tower_et();
  }
  return ecalSummary;
}

void stitchAllNeighbors(Tower in[N_INPUT_LINKS], Tower out[N_INPUT_LINKS]) {
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=in complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  Tower etaStitched1[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched1 complete dim=0
  for (size_t iEta = 1; iEta < TOWERS_IN_ETA; iEta+=2) {
#pragma LOOP UNROLL
    for (size_t iPhi = 0; iPhi < TOWERS_IN_PHI; iPhi++) {
#pragma LOOP UNROLL
      size_t iLink1 = iPhi * TOWERS_IN_ETA  + iEta;
      size_t iLink2 = iLink1 - 1;
      if(in[iLink1].peak_eta() == 0 && in[iLink2].peak_eta() == 4 &&
	 in[iLink1].peak_phi() == in[iLink2].peak_phi())
        stitchNeigbours(in[iLink1], in[iLink2], etaStitched1[iLink1], etaStitched1[iLink2]);
      else {
        etaStitched1[iLink1] = in[iLink1];
        etaStitched1[iLink2] = in[iLink2];
      }
    }
  }
  etaStitched1[16] = in[16];
  etaStitched1[33] = in[33];

  Tower etaStitched2[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched2 complete dim=0
  for (size_t iEta = 2; iEta < TOWERS_IN_ETA; iEta+=2) {
#pragma LOOP UNROLL
    for (size_t iPhi = 0; iPhi < TOWERS_IN_PHI; iPhi++) {
#pragma LOOP UNROLL
      size_t iLink1 = iPhi * TOWERS_IN_ETA  + iEta;
      size_t iLink2 = iLink1 - 1;
      if(etaStitched1[iLink1].peak_eta() == 0 && etaStitched1[iLink2].peak_eta() == 4 &&
	 etaStitched1[iLink1].peak_phi() ==etaStitched1[iLink2].peak_phi())
        stitchNeigbours(etaStitched1[iLink1], etaStitched1[iLink2], etaStitched2[iLink1], etaStitched2[iLink2]);
      else {
        etaStitched2[iLink1] = etaStitched1[iLink1];
        etaStitched2[iLink2] = etaStitched1[iLink2];
      }
    }
  }
  etaStitched2[0] = etaStitched1[0];
  etaStitched2[17] = etaStitched1[17];

  // Stitch in phi (there is only one needed as TOWERS_IN_PHI == 2
  for (size_t iEta = 0; iEta < TOWERS_IN_ETA; iEta++) {
#pragma LOOP UNROLL
    size_t iLink1 = TOWERS_IN_ETA  + iEta;
    size_t iLink2 = iEta;
    if(etaStitched2[iLink1].peak_phi() == 0 && etaStitched2[iLink2].peak_phi() == 4 &&
       etaStitched2[iLink1].peak_eta() == etaStitched2[iLink2].peak_eta())
      stitchNeigbours(etaStitched2[iLink1], etaStitched2[iLink2], out[iLink1], out[iLink2]);
    else {
      out[iLink1] = etaStitched2[iLink1];
      out[iLink2] = etaStitched2[iLink2];
    }
  }

}
*/

void algo_top(hls::stream<axiword> link_in[N_INPUT_LINKS], hls::stream<axiword> link_out[N_OUTPUT_LINKS]) {
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out

#ifndef ALGO_PASSTHROUGH

  // Step First: Unpack
  ap_uint<64> words[N_INPUT_LINKS][N_WORDS_PER_FRAME];
#pragma HLS ARRAY_PARTITION variable=words complete dim=0
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
#pragma LOOP UNROLL
    //#pragma HLS latency min=6 max=6
    processECALLinkData(link_in[i], words[i]);
  }

  // Tower loop - operations not using tower pairs
  Tower towerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary complete dim=0
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
#pragma LOOP UNROLL
    Crystal crystals[5][5];
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
    // Make crystals
    //#pragma HLS DEPENDENCE variable=words inter RAW distance=6 true
    makeCrystals(words[i], crystals);
    // Make towers
    towerLevelECALSummary[i] = makeTower(crystals);
  }

  // Compute total ECAL ET

  //#pragma HLS DEPENDENCE variable=towerLevelECALSummary inter RAW distance=1 true
  ap_uint<32> ecalSummary = towerLevelECALSummary[0].tower_et(); // makeECALSummary(towerLevelECALSummary);

  // Stitch neighboring towers

  Tower stitchedTowerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=stitchedTowerLevelECALSummary complete dim=0
  // stitchAllNeighbors(towerLevelECALSummary, stitchedTowerLevelECALSummary);
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
#pragma LOOP UNROLL
    stitchedTowerLevelECALSummary[i] = towerLevelECALSummary[i];
  }

  // Step Last: Pack the outputs
  ap_uint<64> ecalData = ecalSummary + (ecalSummary << 32);
  size_t l = 0;
  for (size_t j = 0; j < N_OUTPUT_WORDS_PER_FRAME; j++) {
#pragma LOOP UNROLL
    for (size_t i = 0; i < N_OUTPUT_LINKS; i++) {
#pragma LOOP UNROLL

      axiword r;
      r.user = 0;
      if (j == (N_OUTPUT_WORDS_PER_FRAME - 1)) {
        r.last = 0;
      }
      else {
        r.last = 1;
      }
      if (l <= N_INPUT_LINKS - 2) {
        ap_uint<64> towerData1 = uint32_t(stitchedTowerLevelECALSummary[l]);
        ap_uint<64> towerData2 = uint32_t(stitchedTowerLevelECALSummary[l+1]);
        ap_uint<64> towerData = towerData1 | (towerData2 << 32);
        r.data = towerData;
        l += 2;
      }
      else {
        r.data = ecalData;
      }
          
      link_out[i].write(r);

    }

  }

#else
  // Algo passthrough (for testing)
  for (size_t i = 0; i < N_WORDS_PER_FRAME; i++) {
    axiword r[N_INPUT_LINKS];

    // Read all inputs
    for (size_t l = 0; l < N_INPUT_LINKS; l++)
      r[l] = link_in[l].read();

    // Write inputs to outputs
    for (size_t l = 0; l < N_OUTPUT_LINKS; l++) {
      if (l >= N_INPUT_LINKS) {
        link_out[l].write(r[N_INPUT_LINKS-1]);
      } else {
        link_out[l].write(r[l]);
      }
    }
  }


#endif /* !ALGO_PASSTHROUGH */

}

