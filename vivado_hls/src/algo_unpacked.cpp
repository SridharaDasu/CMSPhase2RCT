#include <stdio.h>                                                                                                                                                                   
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//#include "algo_unpacked.h"   // This is where you should have had hls_algo - if not find the header file and fix this - please do not copy this file as that defines the interface
#include "../../../../../APx_Gen0_Algo/VivadoHls/null_algo_unpacked/vivado_hls/src/algo_unpacked.h"
#include "ClusterFinder.hh"

const uint16_t NCrystalsPerLink = 11; // Bits 16-31, 32-47, ..., 176-191, keeping range(15, 0) unused
const uint16_t MaxCrystals = N_CH_IN * NCrystalsPerLink;

//#define ALGO_PASSTHROUGH


/*
 * algo_unpacked interface exposes fully unpacked input and output link data.
 * This version assumes use of 10G 8b10b links, and thus providing
 * 192  bits per BX (arranged as an arrray of 3x 64 bits)
 *
 * !!! N.B. Do NOT use the first byte (i.e. link_in/out[x].range(7,0) as this
 * portion is reserved for input/output link alignment markers.
 *
 * The remaining 184 bits (link_in/out[x].range(191,8)) are available for
 * algorithm use.
 *
 * !!! N.B. 2: make sure to assign every bit of link_out[] data. First byte should be assigned zero.
 */

void algo_unpacked(ap_uint<192> link_in[N_CH_IN], ap_uint<192> link_out[N_CH_OUT])
{
   //ap_uint<192> link_in[N_CH_IN];
   //ap_uint<192> link_out[N_CH_IN];
   // !!! Retain these 4 #pragma directives below in your algo_unpacked implementation !!!

#pragma HLS ARRAY_PARTITION variable=link_in complete dim=0
#pragma HLS ARRAY_PARTITION variable=link_out complete dim=0
#pragma HLS PIPELINE II=3
#pragma HLS INTERFACE ap_ctrl_hs port=return



   // null algo specific pragma: avoid fully combinatorial algo by specifying min latency
   // otherwise algorithm clock input (ap_clk) gets optimized away
#pragma HLS latency min=3

   //#pragma HLS INTERFACE ap_none port=link_out

   //#pragma HLS ARRAY_PARTITION variable=link_in_2d complete dim=0
   //#pragma HLS ARRAY_PARTITION variable=link_out_2d complete dim=0
   /*
      for (int idx = 0; idx < N_CH_IN; idx++) {
#pragma HLS UNROLL
link_in[idx].range(63, 0) = link_in_2d[idx][0];
link_in[idx].range(127, 64) = link_in_2d[idx][1];
link_in[idx].range(191, 128) = link_in_2d[idx][2];
}*/

for (int idx = 0; idx < N_CH_OUT; idx++)
{
#pragma HLS UNROLL
   /* link_in_2d[idx][0]=0;
      link_in_2d[idx][1]=0;
      link_in_2d[idx][2]=0;*/
   link_out[idx]=0;
}

#ifndef ALGO_PASSTHROUGH


static bool first = true;
// Pick the input from link_in
uint16_t crystals[NCaloLayer1Eta*NCaloLayer1Phi*NCrystalsPerEtaPhi*NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=1
crystalLoop: for(int crystalID = 0; crystalID < NCaloLayer1Eta * NCaloLayer1Phi * NCrystalsPerEtaPhi * NCrystalsPerEtaPhi; crystalID++) {
#pragma HLS UNROLL
		if(crystalID > MaxCrystals) {
		   fprintf(stderr, "Too many crystals - aborting");
		   exit(1);
		}
		int link_idx = crystalID / NCrystalsPerLink;
		int bitLo = ((crystalID - link_idx * NCrystalsPerLink) % NCrystalsPerLink + 1) * 16;
		int bitHi = bitLo + 15;
		crystals[crystalID] = link_in[link_idx].range(bitHi, bitLo);
		//printf("crystals[%d] = link_in[%d].range(%d, %d) = %d;\n", crystalID, link_idx, bitHi, bitLo, crystals[crystalID]);
		if(first && crystals[crystalID] > 0) printf("crystals[%d] = link_in[%d].range(%d, %d) = %d;\n", crystalID, link_idx, bitHi, bitLo, crystals[crystalID]);
	     }

 uint16_t sortedCluster_peakEta[12];
 uint16_t sortedCluster_peakPhi[12];
 uint16_t sortedCluster_towerEta[12];
 uint16_t sortedCluster_towerPhi[12];
 uint16_t sortedCluster_towerET[12];
 uint16_t sortedCluster_ET[12];  // Output 0-2,3-5,6-8,9-11 in four different links - ignore remaining
 
 #pragma HLS ARRAY_PARTITION variable=sortedCluster_peakEta complete dim=0
 #pragma HLS ARRAY_PARTITION variable=sortedCluster_peakPhi complete dim=0
 #pragma HLS ARRAY_PARTITION variable=sortedCluster_towerEta complete dim=0
 #pragma HLS ARRAY_PARTITION variable=sortedCluster_towerPhi complete dim=0
 #pragma HLS ARRAY_PARTITION variable=sortedCluster_towerET complete dim=0
 #pragma HLS ARRAY_PARTITION variable=sortedCluster_ET complete dim=0
 
 for(int icluster=0; icluster<12; icluster++){
 #pragma HLS UNROLL
    sortedCluster_peakEta[icluster]=0;
    sortedCluster_peakPhi[icluster]=0;
    sortedCluster_towerEta[icluster]=0;
    sortedCluster_towerPhi[icluster]=0;
    sortedCluster_towerET[icluster]=0;
    sortedCluster_ET[icluster]=0;
 }
 printf(" ............calling function ..........\n");
 bool success = getClustersInCard(crystals, 
       sortedCluster_peakEta, 
       sortedCluster_peakPhi, 
       sortedCluster_towerEta,
       sortedCluster_towerPhi,
       sortedCluster_towerET,
       sortedCluster_ET);
 
 //----
 int olink;
 for(int item=0; item < 12; item++) {
 #pragma HLS UNROLL
    olink = item / 3;
    int word = item % 3;
    int bLo1 = word * 32 + 32;
    int bHi1 = bLo1 + 2;
    for(int o=olink; o < N_CH_OUT; o+=4) {
       link_out[o].range(bHi1,bLo1) = ap_uint<3>(sortedCluster_peakEta[item]);
       //link_out[o].range(bHi1,bLo1) = 0;
    }
    if(first) printf("link_out[%d].range(%d, %d) = ap_uint<3>(sortedCluster_peakEta[%d]) = %d;\n", olink, bHi1, bLo1, item, sortedCluster_peakEta[item]);
    int bLo2 = bHi1 + 1;
    int bHi2 = bLo2 + 2;
    for(int o=olink; o < N_CH_OUT; o+=4) {
       link_out[o].range(bHi2,bLo2) = ap_uint<3>(sortedCluster_peakPhi[item]);
       //link_out[o].range(bHi2,bLo2) = 0;
    }
    if(first) printf("link_out[%d].range(%d, %d) = ap_uint<3>(sortedCluster_peakPhi[%d]) = %d;\n", olink, bHi2, bLo2, item, sortedCluster_peakPhi[item]);
    int bLo3 = bHi2 + 1;
    int bHi3 = bLo3 + 5;
    for(int o=olink; o < N_CH_OUT; o+=4) {
       link_out[o].range(bHi3,bLo3) = ap_uint<6>(sortedCluster_towerEta[item]);
       //link_out[o].range(bHi3,bLo3) = 0;
    }
//    if(first) printf("link_out[%d].range(%d, %d) = ap_uint<6>(sortedCluster_towerEta[%d]) = %d;\n", olink, bHi3, bLo3, item, sortedCluster_towerEta[item]);
    int bLo4 = bHi3 + 1;
    int bHi4 = bLo4 + 3;
    for(int o=olink; o < N_CH_OUT; o+=4) {
       link_out[o].range(bHi4,bLo4) = ap_uint<4>(sortedCluster_towerPhi[item]);
       //link_out[o].range(bHi4,bLo4) = 0;
    }
 //   if(first) printf("link_out[%d].range(%d, %d) = ap_uint<4>(sortedCluster_towerPhi[%d])=%d;\n", olink, bHi4, bLo4,item, sortedCluster_towerPhi[item]);
    int bLo5 = bHi4 + 1;
    int bHi5 = bLo5 + 15;
    for(int o=olink; o < N_CH_OUT; o+=4) {
       link_out[o].range(bHi5,bLo5) = ap_uint<16>(sortedCluster_ET[item]);
       //printf("---->> link_out[%d].range(%d, %d) = ap_uint<16>(sortedCluster_ET[%d]) = %d;\n", o, bHi5, bLo5, item, sortedCluster_ET[item]);
    }
    if(first) printf("link_out[%d].range(%d, %d) = ap_uint<16>(sortedCluster_ET[%d]) = %d;\n", olink, bHi5, bLo5, item, sortedCluster_ET[item]);
    int bLo6 = bHi5 + 1;
    for(int o=olink; o < N_CH_OUT; o+=4) {
       link_out[o].range(191,bLo6) = 0;
    }
 
 }
/*
   for (int olink = 0; olink < N_CH_OUT; olink++) 
   std::cout<< "0x" << setfill('0') << setw(16) << hex << link_out[olink].range(63,0).to_int64() << "    ";
   std::cout<<std::endl;
   for (int olink = 0; olink < N_CH_OUT; olink++) 
   std::cout<< "0x" << setfill('0') << setw(16) << hex << link_out[olink].range(127,64).to_int64() << "    ";
   std::cout<<std::endl;
   for (int olink = 0; olink < N_CH_OUT; olink++) 
   std::cout<< "0x" << setfill('0') << setw(16) << hex << link_out[olink].range(191,128).to_int64() << "    ";
   std::cout<<std::endl;

   std::cout<< endl<<setfill('.') << setw(150) << " " <<std::endl;
   */
//std::cout<<"----------------------------------------------------------------------"<<std::endl;
if(first) first = false;
#else
idxLoop: for (int idx = 0; idx < N_CH_OUT; idx++) {
	    link_out[idx] = link_in[idx];
	 }
#endif

}
