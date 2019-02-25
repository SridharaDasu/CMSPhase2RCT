#ifndef ClusterFinder_hh
#define ClusterFinder_hh

#include <stdint.h>

const uint16_t NCaloLayer1Cards = 18;

const uint16_t NCaloLayer1Eta = 5; //default: 17; CTP7: 5
const uint16_t NCaloLayer1Phi = 4;

const uint16_t NCrystalsPerEtaPhi = 5;
const uint16_t NClustersPer3x4Region = 5;

const uint16_t NClustersPerCard = 12;
const uint16_t Total_clusters = 30;

//const bool _test = true;
const uint16_t NCrystalsInPhi = (NCaloLayer1Cards * NCaloLayer1Phi * NCrystalsPerEtaPhi);
const uint16_t NCrystalsInEta = (NCaloLayer1Eta * NCrystalsPerEtaPhi);

uint16_t getPeakBinOf5(uint16_t et[NCrystalsPerEtaPhi], uint16_t etSum);

bool mergeClusters(
      uint16_t ieta1, uint16_t iphi1, uint16_t itet1, uint16_t icet1,
      uint16_t ieta2, uint16_t iphi2, uint16_t itet2, uint16_t icet2,
      uint16_t *eta1, uint16_t *phi1, uint16_t *tet1, uint16_t *cet1,
      uint16_t *eta2, uint16_t *phi2, uint16_t *tet2, uint16_t *cet2
      );

bool getClustersInTower(
      uint16_t crystals[NCrystalsPerEtaPhi][NCrystalsPerEtaPhi], 
      uint16_t *peakEta,
      uint16_t *peakPhi,
      uint16_t *towerET,
      uint16_t *clusterET
      );

bool getClustersIn3x4Region(
      uint16_t crystalsIn3x4Region[3][4][5][5],
      uint16_t clusterIn3x4Region_peakEta[12],
      uint16_t clusterIn3x4Region_peakPhi[12],
      uint16_t clusterIn3x4Region_towerEta[12],
      uint16_t clusterIn3x4Region_towerPhi[12],
      uint16_t clusterIn3x4Region_towerET[12],
      uint16_t clusterIn3x4Region_ET[12]
      );

bool getClustersInCard(
      uint16_t crystals[NCaloLayer1Eta*NCaloLayer1Phi*NCrystalsPerEtaPhi*NCrystalsPerEtaPhi],
      uint16_t SortedCluster_peakEta[12],
      uint16_t SortedCluster_peakPhi[12],
      uint16_t SortedCluster_towerEta[12],
      uint16_t SortedCluster_towerPhi[12],
      uint16_t SortedCluster_towerET[12],
      uint16_t SortedCluster_ET[12]
      );


#endif

