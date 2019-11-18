
#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "TowerMaker.h"

using namespace std;
using namespace algo;

// Each input link carries the information of a 5x5 region
// Last 16-bits are reserved for CRC
void processECALLinkData(hls::stream<axiword> &link, Crystal crystals[5][5]) {
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS INTERFACE axis port=link
#pragma HLS INLINE

  uint8_t carry = 0;

  for (size_t i = 0; i < N_WORDS_PER_FRAME; i++) {
#pragma LOOP UNROLL
#ifndef __SYNTHESIS__
    // Avoid simulation warnings
    if (link.empty()) continue;
#endif

    uint64_t data = link.read().data;

    switch (i) {
    case 0: {
      for (size_t k = 0; k < 4; k++) {
#pragma LOOP UNROLL
        crystals[0][k] = Crystal(data >> (k * 14));
      }
    } break;
    case 1: {
      crystals[0][4] = Crystal((data << 8) | carry);
      for (size_t k = 0; k < 4; k++) {
#pragma LOOP UNROLL
        crystals[1][k] = Crystal(data >> (k * 14 + 6));
      }
    } break;
    case 2: {
      crystals[1][4] = Crystal(data);
      for (size_t k = 0; k < 3; k++) {
#pragma LOOP UNROLL
        crystals[2][k] = Crystal(data >> (k * 14 + 14));
      }
    } break;
    case 3: {
      crystals[2][3] = Crystal((data << 8) | carry);
      crystals[2][4] = Crystal(data >> 6);
      for (size_t k = 0; k < 3; k++) {
#pragma LOOP UNROLL
        crystals[3][k] = Crystal(data >> (k * 14 + 20));
      }
    } break;
    case 4: {
      for (size_t k = 0; k < 2; k++) {
#pragma LOOP UNROLL
        crystals[3][k+3] = Crystal(data >> (k * 14));
      }
      for (size_t k = 0; k < 2; k++) {
#pragma LOOP UNROLL
        crystals[4][k] = Crystal(data >> (k * 14 + 28));
      }
    } break;
    case 5: {
      crystals[4][2] = Crystal((data << 8) | carry);
      for (size_t k = 0; k < 2; k++) {
#pragma LOOP UNROLL
        crystals[4][k+3] = Crystal(data >> (k * 14 + 6));
      }
    } break;
    default: break;
    }
      
    // Remaining data to be used on the next cycle
    carry = data >> 56;
  }
  
}

void stitchAllNeighbors(Tower in[N_INPUT_LINKS], Tower out[N_INPUT_LINKS]) {
#pragma HLS ARRAY_PARTITION variable=in complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0
#pragma HLS PIPELINE II=1

  Tower etaStitched[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=etaStitched complete dim=0
  for (size_t iEta = 1; iEta < TOWERS_IN_ETA; iEta+=2) {
#pragma LOOP UNROLL
    for (size_t iPhi = 0; iPhi < TOWERS_IN_PHI; iPhi++) {
#pragma LOOP UNROLL
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

  // Stitch in phi
  for (size_t iEta = 0; iEta < TOWERS_IN_ETA; iEta++) {
#pragma LOOP UNROLL
    for (size_t iPhi = 1; iPhi < TOWERS_IN_PHI; iPhi+=2) {
#pragma LOOP UNROLL
      size_t iLink1 = iPhi * TOWERS_IN_ETA  + iEta;
      size_t iLink2 = (iPhi - 1) * TOWERS_IN_ETA + iEta;
      if(iPhi > 0 && etaStitched[iLink1].peak_phi() == 0 && etaStitched[iLink2].peak_phi() == 4 )
        stitchNeigbours(etaStitched[iLink1], etaStitched[iLink2], out[iLink1], out[iLink2]);
      else {
        out[iLink1] = etaStitched[iLink1];
        out[iLink2] = etaStitched[iLink2];
      }
    }
  }

}

void algo_top(hls::stream<axiword> link_in[N_INPUT_LINKS], hls::stream<axiword> link_out[N_OUTPUT_LINKS]) {
#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME

#ifndef ALGO_PASSTHROUGH

  Tower towerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=towerLevelECALSummary complete dim=0
  // Step First: Unpack and process link/tower at a time
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
#pragma LOOP UNROLL
    Crystal crystals[5][5];
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
    processECALLinkData(link_in[i], crystals);
    towerLevelECALSummary[i] = makeTower(crystals);
  }

  ap_uint<32> ecalSummary = 0;
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
#pragma LOOP UNROLL
    ecalSummary += towerLevelECALSummary[i].tower_et();
  }

  Tower stitchedTowerLevelECALSummary[N_INPUT_LINKS];
#pragma HLS ARRAY_PARTITION variable=stitchedTowerLevelECALSummary complete dim=0
  stitchAllNeighbors(towerLevelECALSummary, stitchedTowerLevelECALSummary);
  /*
  for (size_t i = 0; i < N_INPUT_LINKS; i++) {
#pragma LOOP UNROLL
    stitchedTowerLevelECALSummary[i] = towerLevelECALSummary[i];
  }
  */

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
