#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "../../../../include/objects.h"
#include "../../../../include/stitchTower.h"

using namespace std;
using namespace algo;

void unpackInput(hls::stream<axiword576> &link, Tower tower[TOWERS_IN_ETA]) {
#pragma HLS INTERFACE axis port=link
#pragma HLS PIPELINE II=9
#pragma HLS INLINE
#ifndef __SYNTHESIS__
  // Avoid simulation warnings
  if (link.empty()) return;
#endif
  ap_uint<576> word_576b_;
            
  word_576b_ = link.read().data;
            
  tower[0]  = Tower(word_576b_( 31,   0));
  tower[1]  = Tower(word_576b_( 63,  32));
  tower[2]  = Tower(word_576b_( 95,  64));
  tower[3]  = Tower(word_576b_(127,  96));
  tower[4]  = Tower(word_576b_(159, 128));
  tower[5]  = Tower(word_576b_(191, 160));
  tower[6]  = Tower(word_576b_(223, 192));
  tower[7]  = Tower(word_576b_(255, 224));
  tower[8]  = Tower(word_576b_(287, 256));
  tower[9]  = Tower(word_576b_(319, 288));
  tower[10] = Tower(word_576b_(351, 320));
  tower[11] = Tower(word_576b_(383, 352));
  tower[12] = Tower(word_576b_(415, 384));
  tower[13] = Tower(word_576b_(447, 416));
  tower[14] = Tower(word_576b_(479, 448));
  tower[15] = Tower(word_576b_(511, 480));
  tower[16] = Tower(word_576b_(543, 512));
  
  return;
}

bool packOutput(Tower tower[TOWERS_IN_ETA], hls::stream<algo::axiword576> &olink){
#pragma HLS PIPELINE II=N_OUTPUT_WORDS_PER_FRAME
#pragma HLS INTERFACE axis port=link
#pragma HLS INLINE   
             
  ap_uint<576> word_576b_;   
             
  word_576b_( 31,   0) = (ap_uint<32>) tower[0].data;
  word_576b_( 63,  32) = (ap_uint<32>) tower[1].data;
  word_576b_( 95,  64) = (ap_uint<32>) tower[2].data;
  word_576b_(127,  96) = (ap_uint<32>) tower[3].data;
  word_576b_(159, 128) = (ap_uint<32>) tower[4].data;
  word_576b_(191, 160) = (ap_uint<32>) tower[5].data;
  word_576b_(223, 192) = (ap_uint<32>) tower[6].data;
  word_576b_(255, 224) = (ap_uint<32>) tower[7].data;
  word_576b_(287, 256) = (ap_uint<32>) tower[8].data;
  word_576b_(319, 288) = (ap_uint<32>) tower[9].data;
  word_576b_(351, 320) = (ap_uint<32>) tower[10].data;
  word_576b_(383, 352) = (ap_uint<32>) tower[11].data;
  word_576b_(415, 384) = (ap_uint<32>) tower[12].data;
  word_576b_(447, 416) = (ap_uint<32>) tower[13].data;
  word_576b_(479, 448) = (ap_uint<32>) tower[14].data;
  word_576b_(511, 480) = (ap_uint<32>) tower[15].data;
  word_576b_(543, 512) = (ap_uint<32>) tower[16].data;
  word_576b_(575, 544) = (ap_uint<32>) 0;
             
  axiword576 r; r.last = 0; r.user = 0;
  r.data = word_576b_;
  olink.write(r);
             
  return true;
}

void stitchInPhi(Tower stitchedTwr[TOWERS_IN_PHI][TOWERS_IN_ETA], Tower leftTwr[2][TOWERS_IN_ETA], Tower rightTwr[2][TOWERS_IN_ETA]){
#pragma HLS ARRAY_PARTITION variable=stitchedTwr
#pragma HLS ARRAY_PARTITION variable=leftTwr
#pragma HLS ARRAY_PARTITION variable=rightTwr
#pragma HLS PIPELINE II=9

  for(size_t eta=0; eta<TOWERS_IN_ETA; eta++){
#pragma HLS UNROLL
    //stitchNeighbors(stitch_in_phi, stitchedTwr[1][eta], stitchedTwr[2][eta], leftTwr[1][eta], rightTwr[0][eta]);
    stitchNeighbors(1, stitchedTwr[1][eta], stitchedTwr[2][eta], leftTwr[1][eta], rightTwr[0][eta]);
    stitchedTwr[0][eta] = leftTwr[0][eta];
    stitchedTwr[3][eta] = rightTwr[1][eta];
  }

  return;
}

void algo_top(hls::stream<axiword576> link_in[N_INPUT_LINKS], hls::stream<axiword576> link_out[N_OUTPUT_LINKS]) {
#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out
#pragma HLS PIPELINE II=9

  // Step First: Unpack to make
  Tower towers17x2Left[2][TOWERS_IN_ETA];
  Tower towers17x2Right[2][TOWERS_IN_ETA];

#pragma HLS ARRAY_PARTITION variable=towers17x2Left
#pragma HLS ARRAY_PARTITION variable=towers17x2Right

unpackLoop: for (size_t iLink = 0; iLink < N_INPUT_LINKS/2; iLink++) {
#pragma HLS UNROLL
    unpackInput(link_in[iLink],   towers17x2Left[iLink]);
    unpackInput(link_in[iLink+2], towers17x2Right[iLink+2]);
  }

  // Compute total ECAL ET
//  ap_uint<32> ecalSummary = makeECALSummary(towerLevelECALSummary);

  // Stitch neighboring towers
  Tower stitchedTower[TOWERS_IN_PHI][TOWERS_IN_ETA];
#pragma HLS ARRAY_PARTITION variable=stitchedTower

  stitchInPhi(stitchedTower, towers17x2Left, towers17x2Right);

  // Step Last: Pack and write the output
  for (size_t i = 0; i < N_OUTPUT_LINKS; i++) {
#pragma LOOP UNROLL
    packOutput(stitchedTower[i], link_out[i]);
  }

}
