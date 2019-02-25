#include <stdlib.h>
#include <stdio.h>

#include "ClusterFinder.hh"
#include "bitonicSorter.hh"

#include <iostream>
using namespace std;


uint16_t getPeakBinOf5(uint16_t et[NCrystalsPerEtaPhi], uint16_t etSum) {
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=et complete dim=0
   uint16_t iEtSum = 
      (et[0] >> 1)                +  // 0.5xet[0]
      (et[1] >> 1) + et[1]        +  // 1.5xet[1]
      (et[2] >> 1) + (et[2] << 1) +  // 2.5xet[2]
      (et[3] << 2) - (et[3] >> 1) +  // 3.5xet[3]
      (et[4] << 2) + (et[4] >> 1) ;  // 4.5xet[4]
   uint16_t iAve = 0xBEEF;
   if(     iEtSum <= etSum) iAve = 0;
   else if(iEtSum <= (etSum << 1)) iAve = 1;
   else if(iEtSum <= (etSum + (etSum << 1))) iAve = 2;
   else if(iEtSum <= (etSum << 2)) iAve = 3;
   else iAve = 4;
   return iAve;
}

bool getClustersInTower(uint16_t crystals[NCrystalsPerEtaPhi][NCrystalsPerEtaPhi],
      uint16_t *peakEta,
      uint16_t *peakPhi,
      uint16_t *towerET,
      uint16_t *clusterET) {

#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0

   uint16_t phiStripSum[NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=phiStripSum complete dim=0
   for(int phi = 0; phi < NCrystalsPerEtaPhi; phi++) {
#pragma HLS UNROLL
      phiStripSum[phi] = 0;
      for(int eta = 0; eta < NCrystalsPerEtaPhi; eta++) {
#pragma HLS UNROLL
	 phiStripSum[phi] += crystals[eta][phi];
      }
   }   
   uint16_t etaStripSum[NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=etaStripSum complete dim=0
   for(int eta = 0; eta < NCrystalsPerEtaPhi; eta++) {
#pragma HLS UNROLL
      etaStripSum[eta] = 0;
      for(int phi = 0; phi < NCrystalsPerEtaPhi; phi++) {
#pragma HLS UNROLL
	 etaStripSum[eta] += crystals[eta][phi];
      }
   }   
   // Large cluster ET is the ET of the full tower
   *towerET=0;
   for(int phi = 0; phi < NCrystalsPerEtaPhi; phi++) {
#pragma HLS UNROLL
      *towerET += phiStripSum[phi];
   }  

   *peakEta = getPeakBinOf5(etaStripSum, *towerET);
   *peakPhi = getPeakBinOf5(phiStripSum, *towerET);

   // Small cluster ET is just the 3x5 around the peak
   *clusterET = 0;
   for(int dEta = -1; dEta <= 1; dEta++) {
#pragma HLS UNROLL
      int eta = *peakEta + dEta;
      if(eta >= 0 && eta < NCrystalsPerEtaPhi) {
	 *clusterET += etaStripSum[eta];
      }
   }  

   return true;
}

bool mergeClusters(
      uint16_t ieta1, uint16_t iphi1, uint16_t itet1, uint16_t icet1,
      uint16_t ieta2, uint16_t iphi2, uint16_t itet2, uint16_t icet2,
      uint16_t *eta1, uint16_t *phi1, uint16_t *tet1, uint16_t *cet1,
      uint16_t *eta2, uint16_t *phi2, uint16_t *tet2, uint16_t *cet2) {
   // Check that the clusters are neighbors in eta or phi
   if((ieta1 == ieta2) || (iphi1 == iphi2)) {
      if(icet1 > icet2) {
	 // Merge 2 in to 1, and set 2 to remnant energy centered in tower
	 *eta1 = ieta1;
	 *phi1 = iphi1;
	 *cet1 = icet1 + icet2;
	 *tet1 = itet1 + icet2;
	 *eta2 = 2;
	 *phi2 = 2;
	 *cet2 = 0;
	 *tet2 = itet2 - icet2;
      }
      else {
	 // Merge 1 in to 2, and set 1 to remnant energy centered in tower
	 *eta2 = ieta2;
	 *phi2 = iphi2;
	 *cet2 = icet2 + icet1;
	 *tet2 = itet2 + icet1;
	 *eta1 = 2;
	 *phi1 = 2;
	 *cet1 = 0;
	 *tet1 = itet1 - icet1;
      }
   }   
   else {
      *eta1 = ieta1;
      *phi1 = iphi1;
      *cet1 = icet1;
      *tet1 = itet1;
      *eta2 = ieta2;
      *phi2 = iphi2;
      *cet2 = icet2;
      *tet2 = itet2;
   }   
   return true;
}     


bool getClustersIn3x4Region(uint16_t crystalsIn3x4Region[3][4][5][5],
      uint16_t sortedClusterIn3x4_peakEta[NClustersPer3x4Region],
      uint16_t sortedClusterIn3x4_peakPhi[NClustersPer3x4Region],
      uint16_t sortedClusterIn3x4_towerEta[NClustersPer3x4Region],
      uint16_t sortedClusterIn3x4_towerPhi[NClustersPer3x4Region],
      uint16_t sortedClusterIn3x4_towerET[NClustersPer3x4Region],
      uint16_t sortedClusterIn3x4_ET[NClustersPer3x4Region]
      ){
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=crystalsIn3x4Region complete dim=0
#pragma HLS ARRAY_PARTITION variable=sortedClusterIn3x4_peakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=sortedClusterIn3x4_peakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=sortedClusterIn3x4_towerEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=sortedClusterIn3x4_towerPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=sortedClusterIn3x4_towerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=sortedClusterIn3x4_ET complete dim=0

   //Here array size is 16 instead 12(3x4) for bitonic sorting (order 2^n)
   uint16_t toSortClusterIn3x4_peakEta[16];
   uint16_t toSortClusterIn3x4_peakPhi[16];
   uint16_t toSortClusterIn3x4_towerEta[16];
   uint16_t toSortClusterIn3x4_towerPhi[16];
   uint16_t toSortClusterIn3x4_towerET[16];
   uint16_t toSortClusterIn3x4_ET[16];
#pragma HLS ARRAY_PARTITION variable=toSortClusterIn3x4_peakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSortClusterIn3x4_peakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSortClusterIn3x4_towerEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSortClusterIn3x4_towerPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSortClusterIn3x4_towerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSortClusterIn3x4_ET complete dim=0

   for(int iToSort=0; iToSort<16; iToSort++){
#pragma HLS UNROLL
      toSortClusterIn3x4_peakEta[iToSort] = 0;
      toSortClusterIn3x4_peakPhi[iToSort] = 0;
      toSortClusterIn3x4_towerEta[iToSort] = 0;
      toSortClusterIn3x4_towerPhi[iToSort] = 0;
      toSortClusterIn3x4_towerET[iToSort] = 0;
      toSortClusterIn3x4_ET[iToSort] = 0;
   }

   uint16_t crystalsInTower[NCrystalsPerEtaPhi][NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=crystalsInTower complete dim=0

   uint16_t peakEta_[3][4];
   uint16_t peakPhi_[3][4];
   uint16_t towerET_[3][4];
   uint16_t clusterET_[3][4];
#pragma HLS ARRAY_PARTITION variable=peakEta_   complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi_   complete dim=0
#pragma HLS ARRAY_PARTITION variable=towerET_   complete dim=0
#pragma HLS ARRAY_PARTITION variable=clusterET_ complete dim=0

   uint16_t mergedPeakEta_[3][4];
   uint16_t mergedPeakPhi_[3][4];
   uint16_t mergedTowerET_[3][4];
   uint16_t mergedClusterET_[3][4];
#pragma HLS ARRAY_PARTITION variable=mergedPeakEta_   complete dim=0
#pragma HLS ARRAY_PARTITION variable=mergedPeakPhi_   complete dim=0
#pragma HLS ARRAY_PARTITION variable=mergedTowerET_   complete dim=0
#pragma HLS ARRAY_PARTITION variable=mergedClusterET_ complete dim=0

   for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL
      for(int tPhi = 0; tPhi < 4; tPhi++) {
#pragma HLS UNROLL
	 peakEta_[tEta][tPhi] = 9999;
	 peakPhi_[tEta][tPhi] = 9999;
	 towerET_[tEta][tPhi] = 0;
	 clusterET_[tEta][tPhi] = 0;

	 for(int cEta=0; cEta<NCrystalsPerEtaPhi; cEta++){
#pragma HLS UNROLL
	    for(int cPhi=0; cPhi<NCrystalsPerEtaPhi; cPhi++){
#pragma HLS UNROLL
	       crystalsInTower[cEta][cPhi] = crystalsIn3x4Region[tEta][tPhi][cEta][cPhi];
	    }
	 }

	 getClustersInTower(
	       crystalsInTower, 
	       &peakEta_[tEta][tPhi],
	       &peakPhi_[tEta][tPhi],
	       &towerET_[tEta][tPhi],
	       &clusterET_[tEta][tPhi]);

	 mergedPeakEta_[tEta][tPhi]  = peakEta_[tEta][tPhi];
	 mergedPeakPhi_[tEta][tPhi]  = peakPhi_[tEta][tPhi];
	 mergedTowerET_[tEta][tPhi]  = towerET_[tEta][tPhi];
	 mergedClusterET_[tEta][tPhi]= clusterET_[tEta][tPhi];

      }
   }

   // Merge neighboring split-clusters here
   for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL    
      for(int tPhi = 0; tPhi < 4; tPhi++) {
#pragma HLS UNROLL   

	 int ntEta = -1;
	 int ntPhi = -1;
	 if(peakEta_[tEta][tPhi] == 0 && tEta != 0){
	    ntEta = tEta - 1;
	    ntPhi = tPhi;
	 }
	 if(peakEta_[tEta][tPhi] == 4 && tEta != 2){
	    ntEta = tEta + 1;
	    ntPhi = tPhi;
	 }

	 if(peakPhi_[tEta][tPhi] == 0 && tPhi != 0) {
	    ntPhi = tPhi - 1;
	    ntEta = tEta;
	 }
	 if(peakPhi_[tEta][tPhi] == 4 && tPhi != 3){
	    ntPhi = tPhi + 1;
	    ntEta = tEta;
	 }
	 if(ntEta >= 0 && ntEta < 3 && ntPhi >= 0 && ntPhi < 4){
	    if(!mergeClusters(
		     peakEta_[tEta][tPhi],
		     peakPhi_[tEta][tPhi],
		     towerET_[tEta][tPhi],
		     clusterET_[tEta][tPhi],
		     peakEta_[ntEta][ntPhi],
		     peakPhi_[ntEta][ntPhi],
		     towerET_[ntEta][ntPhi],
		     clusterET_[ntEta][ntPhi],
		     &mergedPeakEta_[tEta][tPhi],
		     &mergedPeakPhi_[tEta][tPhi],
		     &mergedTowerET_[tEta][tPhi],
		     &mergedClusterET_[tEta][tPhi],
		     &mergedPeakEta_[ntEta][ntPhi],
		     &mergedPeakPhi_[ntEta][ntPhi],
		     &mergedTowerET_[ntEta][ntPhi],
		     &mergedClusterET_[ntEta][ntPhi])
	      )
	       return false;
	 }
      }
   }


   int iCluster=0;
   for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL
      for(int tPhi = 0; tPhi < 4; tPhi++) {
#pragma HLS UNROLL
	 toSortClusterIn3x4_peakEta[iCluster]  = mergedPeakEta_[tEta][tPhi];
	 toSortClusterIn3x4_peakPhi[iCluster]  = mergedPeakPhi_[tEta][tPhi];
	 toSortClusterIn3x4_towerEta[iCluster] = tEta;
	 toSortClusterIn3x4_towerPhi[iCluster] = tPhi;
	 toSortClusterIn3x4_towerET[iCluster]  = mergedTowerET_[tEta][tPhi];
	 toSortClusterIn3x4_ET[iCluster]       = mergedClusterET_[tEta][tPhi];
	 iCluster++;
      }
   }
   uint16_t xx;

   for(int i=0;i<16;i=i+4){   
#pragma HLS unroll
      if(toSortClusterIn3x4_ET[i]<toSortClusterIn3x4_ET[i+1]){
	 xx=toSortClusterIn3x4_ET[i+1];
	 toSortClusterIn3x4_ET[i+1]=toSortClusterIn3x4_ET[i];
	 toSortClusterIn3x4_ET[i]=xx;
	 xx=toSortClusterIn3x4_peakEta[i];
	 toSortClusterIn3x4_peakEta[i]=toSortClusterIn3x4_peakEta[i+1];
	 toSortClusterIn3x4_peakEta[i+1]=xx;
	 xx=toSortClusterIn3x4_peakPhi[i];
	 toSortClusterIn3x4_peakPhi[i]=toSortClusterIn3x4_peakPhi[i+1];
	 toSortClusterIn3x4_peakPhi[i+1]=xx;
      }

      if(toSortClusterIn3x4_ET[i+2]>toSortClusterIn3x4_ET[i+3]){
	 xx=toSortClusterIn3x4_ET[i+3];
	 toSortClusterIn3x4_ET[i+3]=toSortClusterIn3x4_ET[i+2];
	 toSortClusterIn3x4_ET[i+2]=xx;
	 xx=toSortClusterIn3x4_peakEta[i+2];
	 toSortClusterIn3x4_peakEta[i+2]=toSortClusterIn3x4_peakEta[i+3];
	 toSortClusterIn3x4_peakEta[i+3]=xx;
	 xx=toSortClusterIn3x4_peakPhi[i+2];
	 toSortClusterIn3x4_peakPhi[i+2]=toSortClusterIn3x4_peakPhi[i+3];
	 toSortClusterIn3x4_peakPhi[i+3]=xx;
      }
   }

   // passing control to second level of quaternary comparators                                                                                                                     
   bitonic_1_4(toSortClusterIn3x4_ET,toSortClusterIn3x4_peakEta,toSortClusterIn3x4_peakPhi);

   for(int iSort=0; iSort<NClustersPer3x4Region; iSort++){
      sortedClusterIn3x4_ET[iSort]      =toSortClusterIn3x4_ET[iSort]; 
      sortedClusterIn3x4_peakEta[iSort] =toSortClusterIn3x4_peakEta[iSort];
      sortedClusterIn3x4_peakPhi[iSort] =toSortClusterIn3x4_peakPhi[iSort];
      sortedClusterIn3x4_towerEta[iSort]=toSortClusterIn3x4_towerEta[iSort]; // TO BE SORTED - NOT YET IN SORTER!!
      sortedClusterIn3x4_towerPhi[iSort]=toSortClusterIn3x4_towerPhi[iSort]; // TO BE SORTED
   }


   return true; 
}

bool getClustersInCard(
      uint16_t crystals[NCaloLayer1Eta*NCaloLayer1Phi*NCrystalsPerEtaPhi*NCrystalsPerEtaPhi],
      uint16_t SortedCluster_peakEta[NClustersPerCard],
      uint16_t SortedCluster_peakPhi[NClustersPerCard],
      uint16_t SortedCluster_towerEta[NClustersPerCard],
      uint16_t SortedCluster_towerPhi[NClustersPerCard],
      uint16_t SortedCluster_towerET[NClustersPerCard],
      uint16_t SortedCluster_ET[NClustersPerCard]
      ){
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_peakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_peakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_towerEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_towerPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_towerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_ET complete dim=0

   uint16_t crystalsET[3][4][5][5];
#pragma HLS ARRAY_PARTITION variable=crystalsET complete dim=0

   uint16_t peak_Eta[NClustersPer3x4Region];
   uint16_t peak_Phi[NClustersPer3x4Region];
   uint16_t tower_Eta[NClustersPer3x4Region];
   uint16_t tower_Phi[NClustersPer3x4Region];
   uint16_t tower_ET[NClustersPer3x4Region];
   uint16_t clusters_ET[NClustersPer3x4Region];
#pragma HLS ARRAY_PARTITION variable=peak_Eta complete dim=0
#pragma HLS ARRAY_PARTITION variable=peak_Phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=tower_Eta complete dim=0
#pragma HLS ARRAY_PARTITION variable=tower_Phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=tower_ET complete dim=0
#pragma HLS ARRAY_PARTITION variable=clusters_ET complete dim=0

   // These arrays should be of size 30 for VU9P
   // For CTP7: they are 10: 5 cluster per region
   uint16_t preMergeClusterPeakEta[10];
   uint16_t preMergeClusterPeakPhi[10];
   uint16_t preMergeClusterTowerEta[10];
   uint16_t preMergeClusterTowerPhi[10];
   uint16_t preMergeClusterTowerET[10];
   uint16_t preMergeClusterET[10];
#pragma HLS ARRAY_PARTITION variable=preMergeClusterPeakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeClusterPeakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeClusterTowerEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeClusterTowerPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeClusterTowerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeClusterET complete dim=0

   // this for-loop covers all 3x4 regions in one RCT card
   //In CTP7: Only 5x4 fit in the card= 1-3x4 + 1-2x4
   //In VU9P: 17x4: 5-3x4 + 1-2x4 (iRegion loop will change to <15)
   uint16_t region = 0;
   for(int iRegion=0; iRegion<2; iRegion+=3) {  // We are processing 5 of 17 possible etas due to CTP7 size
#pragma HLS UNROLL
      for(int iClusters=0; iClusters<NClustersPer3x4Region; iClusters++){
	 peak_Eta[iClusters]   =999;
	 peak_Phi[iClusters]   =999;
	 tower_Eta[iClusters]  =999;
	 tower_Phi[iClusters]  =999;
	 tower_ET[iClusters]   =0;
	 clusters_ET[iClusters]=0;
      }

      for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL
	 for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
	    for( int ceta =0; ceta<NCrystalsPerEtaPhi; ceta++) {
#pragma HLS UNROLL
	       for(int cphi =0; cphi<NCrystalsPerEtaPhi; cphi++) {
#pragma HLS UNROLL

		  int crystalID = (iRegion+tEta)*NCaloLayer1Phi*25+tPhi*25+ceta*5+cphi;
		  if(crystalID > 5*NCaloLayer1Phi*25) {
		     fprintf(stderr, "crystalID too large");
		     exit(1);
		  }
		  crystalsET[tEta][tPhi][ceta][cphi] = crystals[crystalID];
	       }
	    }
	 }
      }
      getClustersIn3x4Region(crystalsET, peak_Eta, peak_Phi, tower_Eta, tower_Phi, tower_ET, clusters_ET);

      for(int k=0; k<5; k++){ 
#pragma HLS UNROLL
	 preMergeClusterPeakEta[region+k]  =peak_Eta[k];
	 preMergeClusterPeakPhi[region+k]  =peak_Phi[k];
	 preMergeClusterTowerEta[region+k] =0;  // tower_Eta[k];
	 preMergeClusterTowerPhi[region+k] =0; //tower_Phi[k];
	 preMergeClusterTowerET[region+k]  =tower_ET[k];
	 preMergeClusterET[region+k]       =clusters_ET[k];

      }
      region = region + NClustersPer3x4Region; 
   }
   //Clusters in 2x4 region ---:
   //i2x4region variable is needed to get the correct tEta value for 2x4 region.
   uint16_t i2x4region;
   i2x4region = region/NClustersPer3x4Region*3;

   // Reset and initialize variables for 2x4 region
   for(int iClusters=0; iClusters<NClustersPer3x4Region; iClusters++){
#pragma HLS UNROLL
      peak_Eta[iClusters]   =999;
      peak_Phi[iClusters]   =999;
      tower_Eta[iClusters]  =999;
      tower_Phi[iClusters]  =999;
      tower_ET[iClusters]   =0;
      clusters_ET[iClusters]=0;
   }

   for(int tEta = 0; tEta < 3; tEta++) { // For 2x4 region
#pragma HLS UNROLL
      for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
	 for( int ceta =0; ceta<NCrystalsPerEtaPhi; ceta++) {
#pragma HLS UNROLL
	    for(int cphi =0; cphi<NCrystalsPerEtaPhi; cphi++) {
#pragma HLS UNROLL
	       crystalsET[tEta][tPhi][ceta][cphi] = 0;
	       if(tEta<2){ //As this section is for 2x4 region

		  int crystalID = (i2x4region+tEta)*NCaloLayer1Phi*25+tPhi*25+ceta*5+cphi;
		  if(crystalID > 5*NCaloLayer1Phi*25) {
		     fprintf(stderr, "crystalID too large");
		     exit(1);
		  }
		  crystalsET[tEta][tPhi][ceta][cphi] = crystals[crystalID];
	       }
	    }
	 }
      }
   }

   getClustersIn3x4Region(crystalsET, peak_Eta, peak_Phi, tower_Eta, tower_Phi, tower_ET, clusters_ET);

   for(int k=0; k<5; k++){ 
#pragma HLS UNROLL
      preMergeClusterPeakEta[region+k]  =peak_Eta[k];
      preMergeClusterPeakPhi[region+k]  =peak_Phi[k];
      preMergeClusterTowerEta[region+k] =0;  // tower_Eta[k];
      preMergeClusterTowerPhi[region+k] =0; //tower_Phi[k];
      preMergeClusterTowerET[region+k]  =tower_ET[k];
      preMergeClusterET[region+k]       =clusters_ET[k];

   }
   //------------



   // For CTP7: Sending only 10 clusters per card
   // Sorting final 10 clusters (this will be 30 for the VU9P case)
   //Here array size is 16 instead 12(3x4) for bitonic sorting (order 2^n)
   uint16_t toSort_peakEta[16];
   uint16_t toSort_peakPhi[16];
   uint16_t toSort_towerEta[16];
   uint16_t toSort_towerPhi[16];
   uint16_t toSort_towerET[16];
   uint16_t toSort_ET[16];
#pragma HLS ARRAY_PARTITION variable=toSort_peakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSort_peakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSort_towerEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSort_towerPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSort_towerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=toSort_ET complete dim=0

   for(int iToSort=0; iToSort<16; iToSort++){
#pragma HLS UNROLL
      toSort_peakEta[iToSort] = 0;
      toSort_peakPhi[iToSort] = 0;
      toSort_towerEta[iToSort] = 0;
      toSort_towerPhi[iToSort] = 0;
      toSort_towerET[iToSort] = 0;
      toSort_ET[iToSort] = 0;
      if(iToSort < 10){
	 toSort_peakEta[iToSort] = preMergeClusterPeakEta[iToSort];
	 toSort_peakPhi[iToSort] = preMergeClusterPeakPhi[iToSort];
	 toSort_towerEta[iToSort] = preMergeClusterTowerEta[iToSort];
	 toSort_towerPhi[iToSort] = preMergeClusterTowerPhi[iToSort];
	 toSort_towerET[iToSort] = preMergeClusterTowerET[iToSort];
	 toSort_ET[iToSort] = preMergeClusterET[iToSort];
      }
   }

   uint16_t xx;
   for(int ii=0; ii<16; ii=ii+4){
#pragma HLS unroll 
      if(toSort_ET[ii] < toSort_ET[ii+1]){
	 xx=toSort_ET[ii+1];
	 toSort_ET[ii+1]=toSort_ET[ii];
	 toSort_ET[ii]=xx;
	 xx=toSort_peakEta[ii];
	 toSort_peakEta[ii]=toSort_peakEta[ii+1];
	 toSort_peakEta[ii+1]=xx;
	 xx=toSort_peakPhi[ii];
	 toSort_peakPhi[ii]=toSort_peakPhi[ii+1];
	 toSort_peakPhi[ii+1]=xx;
      }

      if(toSort_ET[ii+2]>toSort_ET[ii+3])
      {xx=toSort_ET[ii+3];
	 toSort_ET[ii+3]=toSort_ET[ii+2];
	 toSort_ET[ii+2]=xx;
	 xx=toSort_peakEta[ii+2];
	 toSort_peakEta[ii+2]=toSort_peakEta[ii+3];
	 toSort_peakEta[ii+3]=xx;
	 xx=toSort_peakPhi[ii+2];
	 toSort_peakPhi[ii+2]=toSort_peakPhi[ii+3];
	 toSort_peakPhi[ii+3]=xx;
      }    
   }        
   // passing control to second level of quaternary comparators
   bitonic_1_4(toSort_ET,toSort_peakEta,toSort_peakPhi);
   //Sorting ends, assigning sorted clusters to final set of variables.


   for(int kk=0; kk<10; kk++){ // kk<NClustersPerCard : For now sending 10 only
#pragma HLS UNROLL
      SortedCluster_peakEta[kk]  = toSort_peakEta[kk];
      SortedCluster_peakPhi[kk]  = toSort_peakPhi[kk];
      SortedCluster_towerEta[kk] = 0; //preMergeClusterTowerEta[kk];
      SortedCluster_towerPhi[kk] = 0; //preMergeClusterTowerPhi[kk];
      SortedCluster_towerET[kk]  = 0; //preMergeClusterTowerET[kk];
      SortedCluster_ET[kk]       = toSort_ET[kk];
   }

   return true;
}
