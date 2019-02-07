#ifndef ClusterfinderCombined_hh
#define ClusterfinderCombined_hh

#include <stdint.h>
#include <ap_fixed.h>

const uint16_t NCaloLayer1Cards = 18;

const uint16_t NCaloLayer1Eta = 17;
const uint16_t NCaloLayer1Phi = 4;

const uint16_t NCrystalsPerEtaPhi = 5;

const uint16_t NCrystalsInPhi = (NCaloLayer1Cards * NCaloLayer1Phi * NCrystalsPerEtaPhi);
const uint16_t NCrystalsInEta = (NCaloLayer1Eta * NCrystalsPerEtaPhi);

uint16_t getPeakBinOf5(ap_fixed<16,9> et[NCrystalsPerEtaPhi], ap_fixed<16,9> etSum);

bool getECAL_ClustersInTower(ap_fixed<16,9> crystals[NCrystalsPerEtaPhi][NCrystalsPerEtaPhi],
      uint16_t *peakEta,
      uint16_t *peakPhi,
	  ap_fixed<16,9> *largeECAL_ClusterET,
	  ap_fixed<16,9> *smallECAL_ClusterET);

bool mergeECAL_Clusters(uint16_t ieta1, uint16_t iphi1, uint16_t itet1, uint16_t icet1,
       uint16_t ieta2, uint16_t iphi2, uint16_t itet2, uint16_t icet2,
       uint16_t *eta1, uint16_t *phi1, uint16_t *tet1, uint16_t *cet1,
       uint16_t *eta2, uint16_t *phi2, uint16_t *tet2, uint16_t *cet2);

bool getECAL_ClustersInCard(ap_fixed<16,9> crystals[NCaloLayer1Eta][NCaloLayer1Phi][NCrystalsPerEtaPhi][NCrystalsPerEtaPhi],
           uint16_t peakEta[NCaloLayer1Eta][NCaloLayer1Phi],
           uint16_t peakPhi[NCaloLayer1Eta][NCaloLayer1Phi],
		   ap_fixed<16,9> largeECAL_ClusterET[NCaloLayer1Eta][NCaloLayer1Phi],
		   ap_fixed<16,9> smallECAL_ClusterET[NCaloLayer1Eta][NCaloLayer1Phi],
		   ap_fixed<16,9>SortedECAL_Cluster_ET[30],
                       uint16_t SortedPeak_Eta[30],
                       uint16_t TowerPeak_Eta[30],
                       uint16_t TowerPeak_Phi[30],
                       ap_fixed<16,9> HCAL_towerET_uncal[17][4],
                       uint16_t SortedPeak_Phi[30]);

//uint16_t biggerLR(uint16_t ECAL_ClusterETL, uint16_t ECAL_ClusterETR);

//void HCAL_TowerPeaks(ap_fixed<16,9> HCAL_towerET[17][4], uint16_t HCAL_TowerPhi[30], uint16_t HCAL_TowerEta[30]);  


#endif

