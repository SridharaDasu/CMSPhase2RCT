#ifndef bitonicSorter_hh
#define bitonicSorter_hh

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <iostream>


void bitonic32(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32]);

void bitonic16(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32]);

void bitonic8(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32]);

void bitonic4(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32]);

void bitonic_1_16(uint16_t Cluster_1_Deposits[16], uint16_t Cluster_1_Eta[16], uint16_t Cluster_1_Phi[16]);

void bitonic_1_8(uint16_t Cluster_1_Deposits[16], uint16_t Cluster_1_Eta[16], uint16_t Cluster_1_Phi[16]);

void bitonic_1_4(uint16_t Cluster_1_Deposits[16], uint16_t Cluster_1_Eta[16], uint16_t Cluster_1_Phi[16]);

#endif




