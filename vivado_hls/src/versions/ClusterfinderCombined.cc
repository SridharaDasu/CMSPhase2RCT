#include "ClusterfinderCombined.hh"
#include "ECAL_Calib_LUT.h"
#include "HCAL_Calib_LUT.h"

#include <iostream>
using namespace std;


void ECAL_bitonic32(ap_fixed<16,9> ECAL_Cluster_1_Deposits[32], uint16_t ECAL_ClusterEta[32], uint16_t ECAL_ClusterPhi[32], uint16_t ECAL_TowerEta[32], uint16_t ECAL_TowerPhi[32])
{// sorting blocks of size 32                                                                                                                                                        
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<16;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+16])
	{
	  temp=ECAL_Cluster_1_Deposits[i+16];
	  ECAL_Cluster_1_Deposits[i+16]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+16];
	  ECAL_ClusterEta[i+16]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+16];
	  ECAL_ClusterPhi[i+16]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+16];
	  ECAL_TowerEta[i+16]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+16];
	  ECAL_TowerPhi[i+16]=temp;
	}
    }

  for(int i=0;i<8;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+8])
        {
          temp=ECAL_Cluster_1_Deposits[i+8];
          ECAL_Cluster_1_Deposits[i+8]=ECAL_Cluster_1_Deposits[i];
          ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+8];
	  ECAL_ClusterEta[i+8]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+8];
	  ECAL_ClusterPhi[i+8]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+8];
	  ECAL_TowerEta[i+8]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+8];
	  ECAL_TowerPhi[i+8]=temp;
        }
    }

  for(int i=16;i<24;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+8])
	{
	  temp=ECAL_Cluster_1_Deposits[i+8];
	  ECAL_Cluster_1_Deposits[i+8]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+8];
	  ECAL_ClusterEta[i+8]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+8];
	  ECAL_ClusterPhi[i+8]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+8];
	  ECAL_TowerEta[i+8]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+8];
	  ECAL_TowerPhi[i+8]=temp;
	}
    }

  for(int i=0;i<4;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
	}
    }
  for(int i=8;i<12;i++)
    {
      #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
        {
          temp=ECAL_Cluster_1_Deposits[i+4];
          ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
          ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
        }
    }


  for(int i=16;i<20;i++)
    {
      #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
        {
          temp=ECAL_Cluster_1_Deposits[i+4];
          ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
          ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
        }
    }

  for(int i=24;i<28;i++)
    {
      #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
        {
          temp=ECAL_Cluster_1_Deposits[i+4];
          ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
          ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
        }
    }

  for(int i=0;i<29;i=i+4)
    {
            #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	   temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
      if(ECAL_Cluster_1_Deposits[i+1]<ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}
    }




  for(int i=0;i<31;i=i+2)
    {
      #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
        {
          temp=ECAL_Cluster_1_Deposits[i+1];
          ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
          ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	   temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=temp;
        }
    }

}


void ECAL_bitonic16(ap_fixed<16,9> ECAL_Cluster_1_Deposits[32], uint16_t ECAL_ClusterEta[32], uint16_t ECAL_ClusterPhi[32], uint16_t ECAL_TowerEta[32], uint16_t ECAL_TowerPhi[32])
{// sorting blocks of size 16                                                                                                                                                        
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<8;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+8])
	{
	  temp=ECAL_Cluster_1_Deposits[i+8];
	  ECAL_Cluster_1_Deposits[i+8]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+8];
	  ECAL_ClusterEta[i+8]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+8];
	  ECAL_ClusterPhi[i+8]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+8];
	  ECAL_TowerEta[i+8]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+8];
	  ECAL_TowerPhi[i+8]=temp;
	}

    }

  for(int i=16;i<24;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+8])
	{
	  temp=ECAL_Cluster_1_Deposits[i+8];
	  ECAL_Cluster_1_Deposits[i+8]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+8];
	  ECAL_ClusterEta[i+8]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+8];
	  ECAL_ClusterPhi[i+8]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+8];
	  ECAL_TowerEta[i+8]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+8];
	  ECAL_TowerPhi[i+8]=temp;
	}

    }

  for(int i=0;i<4;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
	}
    }
  for(int i=8;i<12;i++)
    {
 #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
	}
    }
  for(int i=16;i<20;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
	}
    }

  for(int i=24;i<28;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
	}
    }

  for(int i=0;i<13;i=i+4)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
      ECAL_ClusterEta[i+2]=temp;
      temp=ECAL_ClusterPhi[i];
      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
      ECAL_ClusterPhi[i+2]=temp;
      temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
      ECAL_TowerEta[i+2]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
      ECAL_TowerPhi[i+2]=temp;
	}

      if(ECAL_Cluster_1_Deposits[i+1]<ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}
    }

  for(int i=16;i<29;i=i+4)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
      ECAL_ClusterEta[i+2]=temp;
      temp=ECAL_ClusterPhi[i];
      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
      ECAL_ClusterPhi[i+2]=temp;
      temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
      ECAL_TowerEta[i+2]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
      ECAL_TowerPhi[i+2]=temp;
	}


      if(ECAL_Cluster_1_Deposits[i+1]>ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}
    }



  for(int i=0;i<15;i=i+2)
    {
#pragma HLS unroll//may be faster if split into two loops                                                                                                                          
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=temp;
	}

    }

  for(int i=16;i<31;i=i+2)
    {
#pragma HLS unroll//may be faster if split into two loops                                                                                                                          
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=temp;
	}

    }


  ECAL_bitonic32(ECAL_Cluster_1_Deposits,ECAL_ClusterEta,ECAL_ClusterPhi,ECAL_TowerEta,ECAL_TowerPhi);
}



void ECAL_bitonic8(ap_fixed<16,9> ECAL_Cluster_1_Deposits[32], uint16_t ECAL_ClusterEta[32], uint16_t ECAL_ClusterPhi[32],uint16_t ECAL_TowerEta[32], uint16_t ECAL_TowerPhi[32])
{// sorting blocks of size 8                                                                                                                                                         
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<4;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	  ECAL_TowerEta[i+4]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	  ECAL_TowerPhi[i+4]=temp;
	}
    } 

  for(int i=8;i<12;i++)
	{
    #pragma HLS unroll
	  if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+4])
	    {
	      temp=ECAL_Cluster_1_Deposits[i+4];
	      ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	      ECAL_Cluster_1_Deposits[i]=temp;
	      temp=ECAL_ClusterEta[i];
	      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	      ECAL_ClusterEta[i+4]=temp;
	      temp=ECAL_ClusterPhi[i];
	      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	      ECAL_ClusterPhi[i+4]=temp;
	      temp=ECAL_TowerEta[i];
	      ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
	      ECAL_TowerEta[i+4]=temp;
	      temp=ECAL_TowerPhi[i];
	      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
	      ECAL_TowerPhi[i+4]=temp;
	    }
	}


  for(int i=16;i<20;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
      ECAL_TowerEta[i+4]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
      ECAL_TowerPhi[i+4]=temp;
	}
    }
  for(int i=24;i<28;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+4];
	  ECAL_ClusterEta[i+4]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+4];
	  ECAL_ClusterPhi[i+4]=temp;
	  temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+4];
      ECAL_TowerEta[i+4]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+4];
      ECAL_TowerPhi[i+4]=temp;
	}
    }


  for(int i=0;i<5;i=i+4)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=temp;
	  temp=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=temp;
	  temp=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=temp;
	  temp=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=temp;
	}
      if(ECAL_Cluster_1_Deposits[i+1]<ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
      temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}
    }

  for(int i=8;i<13;i=i+4)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=temp;
	  temp=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=temp;
	  temp=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=temp;
	  temp=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=temp;
	}

      if(ECAL_Cluster_1_Deposits[i+1]>ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}
    }

  for(int i=16;i<21;i=i+4)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=temp;
	  temp=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=temp;
	  temp=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=temp;
	  temp=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=temp;
	}
      if(ECAL_Cluster_1_Deposits[i+1]<ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}
    }

  for(int i=24;i<29;i=i+4)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=temp;
	  temp=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=temp;
	  temp=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=temp;
	  temp=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=temp;
	}

      if(ECAL_Cluster_1_Deposits[i+1]>ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=ECAL_ClusterEta[i+3];
	  ECAL_ClusterEta[i+3]=temp;
	  temp=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=ECAL_ClusterPhi[i+3];
	  ECAL_ClusterPhi[i+3]=temp;
	  temp=ECAL_TowerEta[i+1];
	  ECAL_TowerEta[i+1]=ECAL_TowerEta[i+3];
	  ECAL_TowerEta[i+3]=temp;
	  temp=ECAL_TowerPhi[i+1];
	  ECAL_TowerPhi[i+1]=ECAL_TowerPhi[i+3];
	  ECAL_TowerPhi[i+3]=temp;
	}

    }

  for(int i=0;i<7;i=i+2)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
      temp=ECAL_ClusterEta[i];
      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
      ECAL_ClusterEta[i+1]=temp;
      temp=ECAL_ClusterPhi[i];
      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
      ECAL_ClusterPhi[i+1]=temp;
      temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
      ECAL_TowerEta[i+1]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
      ECAL_TowerPhi[i+1]=temp;
	}
    }
  for(int i=8;i<15;i=i+2)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
      temp=ECAL_ClusterEta[i];
      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
      ECAL_ClusterEta[i+1]=temp;
      temp=ECAL_ClusterPhi[i];
      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
      ECAL_ClusterPhi[i+1]=temp;
      temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
      ECAL_TowerEta[i+1]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
      ECAL_TowerPhi[i+1]=temp;
	}
    }

  for(int i=16;i<23;i=i+2)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
      temp=ECAL_ClusterEta[i];
      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
      ECAL_ClusterEta[i+1]=temp;
      temp=ECAL_ClusterPhi[i];
      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
      ECAL_ClusterPhi[i+1]=temp;
      temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
      ECAL_TowerEta[i+1]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
      ECAL_TowerPhi[i+1]=temp;
	}
    }
  for(int i=24;i<31;i=i+2)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_ClusterEta[i];
      ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
      ECAL_ClusterEta[i+1]=temp;
      temp=ECAL_ClusterPhi[i];
      ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
      ECAL_ClusterPhi[i+1]=temp;
      temp=ECAL_TowerEta[i];
      ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
      ECAL_TowerEta[i+1]=temp;
      temp=ECAL_TowerPhi[i];
      ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
      ECAL_TowerPhi[i+1]=temp;
	}
    }

  ECAL_bitonic16(ECAL_Cluster_1_Deposits,ECAL_ClusterEta,ECAL_ClusterPhi,ECAL_TowerEta,ECAL_TowerPhi);
}
void ECAL_bitonic4(ap_fixed<16,9> ECAL_Cluster_1_Deposits[32], uint16_t ECAL_ClusterEta[32], uint16_t ECAL_ClusterPhi[32],uint16_t ECAL_TowerEta[32], uint16_t ECAL_TowerPhi[32])
{
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  // comparators in blocks of 4                                                                                                                                                        
  for(int i=0;i<2;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }
  for(int i=4;i<6;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }
  for(int i=8;i<10;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }
  for(int i=12;i<14;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }
  for(int i=16;i<18;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }

  for(int i=20;i<22;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }
  for(int i=24;i<26;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }
  for(int i=28;i<30;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+2];
	  ECAL_ClusterEta[i+2]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+2];
	  ECAL_ClusterPhi[i+2]=temp;
	  temp=ECAL_TowerEta[i];
	  ECAL_TowerEta[i]=ECAL_TowerEta[i+2];
	  ECAL_TowerEta[i+2]=temp;
	  temp=ECAL_TowerPhi[i];
	  ECAL_TowerPhi[i]=ECAL_TowerPhi[i+2];
	  ECAL_TowerPhi[i+2]=temp;
	}
    }

  for(int i=0;i<3;i=i+2)
	 {
  #pragma HLS unroll
	   if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	     {temp=ECAL_Cluster_1_Deposits[i];
	       ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	       ECAL_Cluster_1_Deposits[i+1]=temp;
	       temp=ECAL_ClusterEta[i];
	       ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	       ECAL_ClusterEta[i+1]=temp;
	       temp=ECAL_ClusterPhi[i];
	       ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	       ECAL_ClusterPhi[i+1]=temp;
	       temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	     }
	 }
  for(int i=4;i<7;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
		  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
		  ECAL_Cluster_1_Deposits[i+1]=temp;
		  temp=ECAL_ClusterEta[i];
		  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
		  ECAL_ClusterEta[i+1]=temp;
		  temp=ECAL_ClusterPhi[i];
		  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
		  ECAL_ClusterPhi[i+1]=temp;
		  temp=ECAL_TowerEta[i];
		   ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
		   ECAL_TowerEta[i+1]=temp;
		   temp=ECAL_TowerPhi[i];
		   ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
		   ECAL_TowerPhi[i+1]=temp;
	}
    }


  for(int i=8;i<11;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	}
    }

  for(int i=12;i<15;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	}
    }
  for(int i=16;i<19;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	}
    }


  for(int i=20;i<23;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	}
    }



  for(int i=24;i<27;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	}
    }
  for(int i=28;i<31;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_ClusterEta[i];
	  ECAL_ClusterEta[i]=ECAL_ClusterEta[i+1];
	  ECAL_ClusterEta[i+1]=temp;
	  temp=ECAL_ClusterPhi[i];
	  ECAL_ClusterPhi[i]=ECAL_ClusterPhi[i+1];
	  ECAL_ClusterPhi[i+1]=temp;
	  temp=ECAL_TowerEta[i];
           ECAL_TowerEta[i]=ECAL_TowerEta[i+1];
           ECAL_TowerEta[i+1]=temp;
           temp=ECAL_TowerPhi[i];
           ECAL_TowerPhi[i]=ECAL_TowerPhi[i+1];
           ECAL_TowerPhi[i+1]=temp;
	}
    }

  ECAL_bitonic8(ECAL_Cluster_1_Deposits,ECAL_ClusterEta,ECAL_ClusterPhi,ECAL_TowerEta,ECAL_TowerPhi);

}

void ECAL_bitonic_1_16(ap_fixed<16,9> ECAL_Cluster_1_Deposits[16], uint16_t ECAL_Cluster_1_Eta[16], uint16_t ECAL_Cluster_1_Phi[16], uint16_t ECAL_Cluster_1_towerEta[16], uint16_t ECAL_Cluster_1_towerPhi[16])
{// sorting blocks of size 16                                                                                                                                                        
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<8;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+8])
	{
	  temp=ECAL_Cluster_1_Deposits[i+8];
	  ECAL_Cluster_1_Deposits[i+8]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+8];
	  ECAL_Cluster_1_Eta[i+8]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+8];
	  ECAL_Cluster_1_Phi[i+8]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+8];
	  ECAL_Cluster_1_towerEta[i+8]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+8];
	  ECAL_Cluster_1_towerPhi[i+8]=temp;
	}

    }


  for(int i=0;i<4;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+4];
	  ECAL_Cluster_1_Eta[i+4]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+4];
	  ECAL_Cluster_1_Phi[i+4]=temp;
	   temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+4];
	  ECAL_Cluster_1_towerEta[i+4]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+4];
	  ECAL_Cluster_1_towerPhi[i+4]=temp;
	}
    }


  for(int i=8;i<12;i++)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+4];
	  ECAL_Cluster_1_Eta[i+4]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+4];
	  ECAL_Cluster_1_Phi[i+4]=temp;
	   temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+4];
	  ECAL_Cluster_1_towerEta[i+4]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+4];
	  ECAL_Cluster_1_towerPhi[i+4]=temp;
	}
    }


  for(int i=0;i<13;i=i+4)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
          ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+2];
          ECAL_Cluster_1_Eta[i+2]=temp;
          temp=ECAL_Cluster_1_Phi[i];
          ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+2];
          ECAL_Cluster_1_Phi[i+2]=temp;
          temp=ECAL_Cluster_1_towerEta[i];
          ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+2];
          ECAL_Cluster_1_towerEta[i+2]=temp;
          temp=ECAL_Cluster_1_towerPhi[i];
          ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+2];
          ECAL_Cluster_1_towerPhi[i+2]=temp;
	}

      if(ECAL_Cluster_1_Deposits[i+1]<ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=ECAL_Cluster_1_Eta[i+3];
	  ECAL_Cluster_1_Eta[i+3]=temp;
	  temp=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=ECAL_Cluster_1_Phi[i+3];
	  ECAL_Cluster_1_Phi[i+3]=temp;
	   temp=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=ECAL_Cluster_1_towerEta[i+3];
	  ECAL_Cluster_1_towerEta[i+3]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=ECAL_Cluster_1_towerPhi[i+3];
	  ECAL_Cluster_1_towerPhi[i+3]=temp;
	}
    }


  for(int i=0;i<15;i=i+2)
       {
#pragma HLS unroll//may be faster if split into two loops                                                                                                                          
	 if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	   {
	     temp=ECAL_Cluster_1_Deposits[i+1];
	     ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	     ECAL_Cluster_1_Deposits[i]=temp;
	     temp=ECAL_Cluster_1_Eta[i];
	     ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
	     ECAL_Cluster_1_Eta[i+1]=temp;
	     temp=ECAL_Cluster_1_Phi[i];
	     ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
	     ECAL_Cluster_1_Phi[i+1]=temp;
	     temp=ECAL_Cluster_1_towerEta[i];
	     ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
	     ECAL_Cluster_1_towerEta[i+1]=temp;
	     temp=ECAL_Cluster_1_towerPhi[i];
	     ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
	     ECAL_Cluster_1_towerPhi[i+1]=temp;
	   }

       }


}



void ECAL_bitonic_1_8(ap_fixed<16,9> ECAL_Cluster_1_Deposits[16], uint16_t ECAL_Cluster_1_Eta[16], uint16_t ECAL_Cluster_1_Phi[16], uint16_t ECAL_Cluster_1_towerEta[16], uint16_t ECAL_Cluster_1_towerPhi[16])
{// sorting blocks of size 8                                                                                                                                                         
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<4;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+4];
	  ECAL_Cluster_1_Eta[i+4]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+4];
	  ECAL_Cluster_1_Phi[i+4]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+4];
	  ECAL_Cluster_1_towerEta[i+4]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+4];
	  ECAL_Cluster_1_towerPhi[i+4]=temp;
	}
    }
  for(int i=8;i<12;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+4])
	{
	  temp=ECAL_Cluster_1_Deposits[i+4];
	  ECAL_Cluster_1_Deposits[i+4]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+4];
	  ECAL_Cluster_1_Eta[i+4]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+4];
	  ECAL_Cluster_1_Phi[i+4]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+4];
	  ECAL_Cluster_1_towerEta[i+4]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+4];
	  ECAL_Cluster_1_towerPhi[i+4]=temp;
	}
    }


  for(int i=0;i<5;i=i+4)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i+2];
	  ECAL_Cluster_1_Eta[i+2]=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=temp;
	  temp=ECAL_Cluster_1_Phi[i+2];
	  ECAL_Cluster_1_Phi[i+2]=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=temp;
	   temp=ECAL_Cluster_1_towerEta[i+2];
	  ECAL_Cluster_1_towerEta[i+2]=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i+2];
	  ECAL_Cluster_1_towerPhi[i+2]=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=temp;
	}
      if(ECAL_Cluster_1_Deposits[i+1]<ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
          temp=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=ECAL_Cluster_1_Eta[i+3];
	  ECAL_Cluster_1_Eta[i+3]=temp;
	  temp=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=ECAL_Cluster_1_Phi[i+3];
	  ECAL_Cluster_1_Phi[i+3]=temp;
	  temp=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=ECAL_Cluster_1_towerEta[i+3];
	  ECAL_Cluster_1_towerEta[i+3]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=ECAL_Cluster_1_towerPhi[i+3];
	  ECAL_Cluster_1_towerPhi[i+3]=temp;
	}
    }



  for(int i=8;i<13;i=i+4)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{
	  temp=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
	  temp=ECAL_Cluster_1_Eta[i+2];
	  ECAL_Cluster_1_Eta[i+2]=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=temp;
	  temp=ECAL_Cluster_1_Phi[i+2];
	  ECAL_Cluster_1_Phi[i+2]=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=temp;
	   temp=ECAL_Cluster_1_towerEta[i+2];
	  ECAL_Cluster_1_towerEta[i+2]=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i+2];
	  ECAL_Cluster_1_towerPhi[i+2]=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=temp;
	}
      if(ECAL_Cluster_1_Deposits[i+1]>ECAL_Cluster_1_Deposits[i+3])
	{
	  temp=ECAL_Cluster_1_Deposits[i+3];
	  ECAL_Cluster_1_Deposits[i+3]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=ECAL_Cluster_1_Eta[i+3];
	  ECAL_Cluster_1_Eta[i+3]=temp;
	  temp=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=ECAL_Cluster_1_Phi[i+3];
	  ECAL_Cluster_1_Phi[i+3]=temp;
	  temp=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=ECAL_Cluster_1_towerEta[i+3];
	  ECAL_Cluster_1_towerEta[i+3]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=ECAL_Cluster_1_towerPhi[i+3];
	  ECAL_Cluster_1_towerPhi[i+3]=temp;
	}
    }


  for(int i=0;i<7;i=i+2)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_Cluster_1_Eta[i];
          ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
          ECAL_Cluster_1_Eta[i+1]=temp;
          temp=ECAL_Cluster_1_Phi[i];
          ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
          ECAL_Cluster_1_Phi[i+1]=temp;
          temp=ECAL_Cluster_1_towerEta[i];
          ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
          ECAL_Cluster_1_towerEta[i+1]=temp;
          temp=ECAL_Cluster_1_towerPhi[i];
          ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
          ECAL_Cluster_1_towerPhi[i+1]=temp;
	}
    }
  for(int i=8;i<15;i=i+2)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{
	  temp=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=temp;
          temp=ECAL_Cluster_1_Eta[i];
          ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
          ECAL_Cluster_1_Eta[i+1]=temp;
          temp=ECAL_Cluster_1_Phi[i];
          ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
          ECAL_Cluster_1_Phi[i+1]=temp;
          temp=ECAL_Cluster_1_towerEta[i];
          ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
          ECAL_Cluster_1_towerEta[i+1]=temp;
          temp=ECAL_Cluster_1_towerPhi[i];
          ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
          ECAL_Cluster_1_towerPhi[i+1]=temp;
	}
    }
  ECAL_bitonic_1_16(ECAL_Cluster_1_Deposits,ECAL_Cluster_1_Eta,ECAL_Cluster_1_Phi,ECAL_Cluster_1_towerEta,ECAL_Cluster_1_towerPhi);
}




void ECAL_bitonic_1_4(ap_fixed<16,9> ECAL_Cluster_1_Deposits[16], uint16_t ECAL_Cluster_1_Eta[16], uint16_t ECAL_Cluster_1_Phi[16],uint16_t ECAL_Cluster_1_towerEta[16], uint16_t ECAL_Cluster_1_towerPhi[16])
{
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  // comparators in blocks of 4                                                                                                                                                        
  for(int i=0;i<2;i++)
    {
    #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+2];
	  ECAL_Cluster_1_Eta[i+2]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+2];
	  ECAL_Cluster_1_Phi[i+2]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+2];
	  ECAL_Cluster_1_towerEta[i+2]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+2];
	  ECAL_Cluster_1_towerPhi[i+2]=temp;
	}
    }
  for(int i=4;i<6;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+2];
	  ECAL_Cluster_1_Eta[i+2]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+2];
	  ECAL_Cluster_1_Phi[i+2]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+2];
	  ECAL_Cluster_1_towerEta[i+2]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+2];
	  ECAL_Cluster_1_towerPhi[i+2]=temp;
	}
    }
  for(int i=8;i<10;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+2];
	  ECAL_Cluster_1_Eta[i+2]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+2];
	  ECAL_Cluster_1_Phi[i+2]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+2];
	  ECAL_Cluster_1_towerEta[i+2]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+2];
	  ECAL_Cluster_1_towerPhi[i+2]=temp;
	}
    }


  for(int i=12;i<14;i++)
    {
#pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+2])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+2];
	  ECAL_Cluster_1_Deposits[i+2]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+2];
	  ECAL_Cluster_1_Eta[i+2]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+2];
	  ECAL_Cluster_1_Phi[i+2]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+2];
	  ECAL_Cluster_1_towerEta[i+2]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+2];
	  ECAL_Cluster_1_towerPhi[i+2]=temp;
	}
    }

  for(int i=0;i<3;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=temp;
	}
    }


  for(int i=4;i<7;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=temp;
	}
    }

  for(int i=8;i<11;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]<ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=temp;
	}
    }
  for(int i=12;i<15;i=i+2)
    {
  #pragma HLS unroll
      if(ECAL_Cluster_1_Deposits[i]>ECAL_Cluster_1_Deposits[i+1])
	{temp=ECAL_Cluster_1_Deposits[i];
	  ECAL_Cluster_1_Deposits[i]=ECAL_Cluster_1_Deposits[i+1];
	  ECAL_Cluster_1_Deposits[i+1]=temp;
	  temp=ECAL_Cluster_1_Eta[i];
	  ECAL_Cluster_1_Eta[i]=ECAL_Cluster_1_Eta[i+1];
	  ECAL_Cluster_1_Eta[i+1]=temp;
	  temp=ECAL_Cluster_1_Phi[i];
	  ECAL_Cluster_1_Phi[i]=ECAL_Cluster_1_Phi[i+1];
	  ECAL_Cluster_1_Phi[i+1]=temp;
	  temp=ECAL_Cluster_1_towerEta[i];
	  ECAL_Cluster_1_towerEta[i]=ECAL_Cluster_1_towerEta[i+1];
	  ECAL_Cluster_1_towerEta[i+1]=temp;
	  temp=ECAL_Cluster_1_towerPhi[i];
	  ECAL_Cluster_1_towerPhi[i]=ECAL_Cluster_1_towerPhi[i+1];
	  ECAL_Cluster_1_towerPhi[i+1]=temp;
	}
    }

  ECAL_bitonic_1_8(ECAL_Cluster_1_Deposits,ECAL_Cluster_1_Eta,ECAL_Cluster_1_Phi,ECAL_Cluster_1_towerEta,ECAL_Cluster_1_towerPhi);

}



uint16_t getPeakBinOf5(ap_fixed<16,9> et[5], ap_fixed<16,9> etSum) {
#pragma HLS PIPELINE II=6
#pragma HLS ARRAY_PARTITION variable=et complete dim=0
  ap_fixed<16,9> iEtSum = 
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



bool getECAL_Clustersin3x4Region(ap_fixed<16,9> crystals_tower[3][4][5][5],
			    uint16_t peakEta1[3][4],
			    uint16_t peakPhi1[3][4],
				ap_fixed<16,9> towerET1[3][4],
				ap_fixed<16,9> ECAL_ClusterET1[3][4],
				ap_fixed<16,9> SortedECAL_ClusterET[5],
				uint16_t TowerPeak_Eta[5],
				uint16_t TowerPeak_Phi[5],
			    uint16_t SortedPeakEta[5],
			    uint16_t SortedPeakPhi[5]) {
  

#pragma HLS PIPELINE II=6
#pragma HLS ARRAY_PARTITION variable=crystals_tower complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakEta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=towerET1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=ECAL_ClusterET1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedECAL_ClusterET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeakPhi complete dim=0

  uint16_t peakEta2[16];
  uint16_t peakPhi2[16];
   uint16_t towerpeakEta2[16];
  uint16_t towerpeakPhi2[16];
  ap_fixed<16,9> ECAL_ClusterET2[16];

#pragma HLS ARRAY_PARTITION variable=peakEta2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=ECAL_ClusterET2 complete dim=0

// for (int i=0;i<17;i++)
// {
//   for (int j=0;j<4;j++)
//   {
//     towerET_cal[i][j]=0;
//   }
// }
  for(int i=0;i<16;i++)
    {
#pragma HLS UNROLL      
      peakEta2[i]=0;
      peakPhi2[i]=0;
      ECAL_ClusterET2[i]=0;

    }

  int i=0;
  for(int tPhi = 0; tPhi < 4; tPhi++) {
#pragma HLS UNROLL
    for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL
      getECAL_ClustersInTower(crystals_tower[tEta][tPhi], 
			 &peakEta1[tEta][tPhi],
			 &peakPhi1[tEta][tPhi],
			 &towerET1[tEta][tPhi],
			 &ECAL_ClusterET1[tEta][tPhi]);
			 
     // std::cout<<"tower eta: " << tEta<<" tower phi: "<<tPhi<<" peakEta1: "<<peakEta1[tEta][tPhi]<<" peakPhi1: "<<peakPhi1[tEta][tPhi]<<" ECAL_ClusterET: "<<ECAL_ClusterET1[tEta][tPhi]<<std::endl;
      peakEta2[i]= peakEta1[tEta][tPhi];
      peakPhi2[i]= peakPhi1[tEta][tPhi];

      towerpeakEta2[i]= tEta;                                                                                                                                     
      towerpeakPhi2[i]= tPhi;  
      ECAL_ClusterET2[i] = ECAL_ClusterET1[tEta][tPhi];
      
      i++;
    }
  }


  
  for(int i=13;i<16;i++)
    {
#pragma HLS UNROLL
      peakEta2[i]=0;
      peakPhi2[i]=0;
      ECAL_ClusterET2[i]=0;
      towerpeakEta2[i]= 0;                                                                                                                                     
      towerpeakPhi2[i]= 0;  

    }

  
  uint16_t xx;
  
  for(int i=0;i<16;i=i+4)
    {
#pragma HLS unroll
      if(ECAL_ClusterET2[i]<ECAL_ClusterET2[i+1])
	{xx=ECAL_ClusterET2[i+1];
	  ECAL_ClusterET2[i+1]=ECAL_ClusterET2[i];
	  ECAL_ClusterET2[i]=xx;
	  xx=peakEta2[i];
	  peakEta2[i]=peakEta2[i+1];
	  peakEta2[i+1]=xx;
	  xx=peakPhi2[i];
	  peakPhi2[i]=peakPhi2[i+1];
	  peakPhi2[i+1]=xx;
	  xx=towerpeakEta2[i];
	  towerpeakEta2[i]=towerpeakEta2[i+1];
	  towerpeakEta2[i+1]=xx;
	  xx=towerpeakPhi2[i];
	  towerpeakPhi2[i]=towerpeakPhi2[i+1];
	  towerpeakPhi2[i+1]=xx;
	}

      if(ECAL_ClusterET2[i+2]>ECAL_ClusterET2[i+3])
	{xx=ECAL_ClusterET2[i+3];
	  ECAL_ClusterET2[i+3]=ECAL_ClusterET2[i+2];
	  ECAL_ClusterET2[i+2]=xx;
	  xx=peakEta2[i+2];
	  peakEta2[i+2]=peakEta2[i+3];
	  peakEta2[i+3]=xx;
	  xx=peakPhi2[i+2];
	  peakPhi2[i+2]=peakPhi2[i+3];
	  peakPhi2[i+3]=xx;
	  xx=towerpeakEta2[i+2];
	  towerpeakEta2[i+2]=towerpeakEta2[i+3];
	  towerpeakEta2[i+3]=xx;
	  xx=towerpeakPhi2[i+2];
	  towerpeakPhi2[i+2]=towerpeakPhi2[i+3];
	  towerpeakPhi2[i+3]=xx;

	}
    }


  // passing control to second level of quaternary comparators                                                                                                                     
  ECAL_bitonic_1_4(ECAL_ClusterET2,peakEta2,peakPhi2,towerpeakEta2,towerpeakPhi2);

  for(int i=0;i<5;i++)
    {
      SortedECAL_ClusterET[i] = ECAL_ClusterET2[i];
      SortedPeakEta[i]= peakEta2[i];
      SortedPeakPhi[i]= peakPhi2[i];
      TowerPeak_Eta[i]=towerpeakEta2[i];
      TowerPeak_Phi[i]=towerpeakPhi2[i];
    }
  

  

}

bool getECAL_ClustersInTower(ap_fixed<16,9> crystals[NCrystalsPerEtaPhi][NCrystalsPerEtaPhi],
                        uint16_t *peakEta,
                        uint16_t *peakPhi,
                        ap_fixed<16,9> *towerET,
                        ap_fixed<16,9> *ECAL_ClusterET) {
#pragma HLS PIPELINE II=6
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
  ap_fixed<16,9> phiStripSum[NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=phiStripSum complete dim=0
  for(int phi = 0; phi < NCrystalsPerEtaPhi; phi++) {
#pragma HLS UNROLL
    phiStripSum[phi] = 0;
    for(int eta = 0; eta < NCrystalsPerEtaPhi; eta++) {
#pragma HLS UNROLL
      phiStripSum[phi] += crystals[eta][phi];
    }
  }
  ap_fixed<16,9> etaStripSum[NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=etaStripSum complete dim=0
  for(int eta = 0; eta < NCrystalsPerEtaPhi; eta++) {
#pragma HLS UNROLL
    etaStripSum[eta] = 0;
    for(int phi = 0; phi < NCrystalsPerEtaPhi; phi++) {
#pragma HLS UNROLL
      etaStripSum[eta] += crystals[eta][phi];
     // std::cout<<"etaStripSum"<<etaStripSum[eta]<<std::endl;
    }
  }
  // Large ECAL_Cluster ET is the ET of the full tower
  *towerET = 0;
  for(int phi = 0; phi < NCrystalsPerEtaPhi; phi++) {
#pragma HLS UNROLL
    *towerET += phiStripSum[phi];
  }
  *peakEta = getPeakBinOf5(etaStripSum, *towerET);
  //std::cout<<"Peak Eta"<<*peakEta<<std::endl;
  *peakPhi = getPeakBinOf5(phiStripSum, *towerET);
  //std::cout<<"Peak Phi"<<*peakPhi<<std::endl;
  // Small ECAL_Cluster ET is just the 3x5 around the peak
  *ECAL_ClusterET = 0;
 if (*peakEta==4){
 	std::cout<<"Left 2x5"<<std::endl;
		 	for(int dEtaL = -1; dEtaL <= 0; dEtaL++) {
		#pragma HLS UNROLL
			  int eta = *peakEta + dEtaL;
			  
			    *ECAL_ClusterET += etaStripSum[eta];
			  
			}
 	if(*peakPhi==1){
		 		std::cout<<"Left 2x4"<<std::endl;
			*ECAL_ClusterET=*ECAL_ClusterET-(crystals[4][4]+crystals[3][4]);
		}
	else if(*peakPhi==0){
		 		std::cout<<"Left 2x3"<<std::endl;
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[3][3]+crystals[4][3]+crystals[4][4]+crystals[3][4]);
		}	
		else if(*peakPhi==3){
		 		std::cout<<"Left 2x4"<<std::endl;
		 	    *ECAL_ClusterET=*ECAL_ClusterET-(crystals[4][0]+crystals[3][0]);
		}
	else if(*peakPhi==4){
		 		std::cout<<"Left 2x3"<<std::endl;
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[3][0]+crystals[4][0]+crystals[4][1]+crystals[3][1]);
		}	
	
 }
	else if (*peakEta==0){
std::cout<<"Right 2x5"<<std::endl;
		 	for(int dEtaR = 0; dEtaR <= 1; dEtaR++) {
		#pragma HLS UNROLL
			  int eta = *peakEta + dEtaR;
			  
			    *ECAL_ClusterET += etaStripSum[eta];
			  
			}
		if(*peakPhi==1){
		 		std::cout<<"Right 2x4"<<std::endl;
		 	 *ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][4]+crystals[1][4]);
		}
	else if(*peakPhi==0){
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][3]+crystals[1][3]+crystals[0][4]+crystals[1][4]);
		}	
		else if(*peakPhi==3){
		 		std::cout<<"Right 2x4"<<std::endl;
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][0]+crystals[1][0]);
		}
	else if(*peakPhi==4){
		 *ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][0]+crystals[1][0]+crystals[0][1]+crystals[1][1]);
		}	
	

	}
	else
	{std::cout<<"3x5"<<std::endl;

	for(int dEta = -1; dEta <= 1; dEta++){
		#pragma HLS UNROLL
			  int eta = *peakEta + dEta;
			  
			    *ECAL_ClusterET += etaStripSum[eta];
			  
			}
			//*ECAL_ClusterET=*ECAL_ClusterET-(crystals[4][4]+crystals[3][4]);
	
 	if(*peakPhi==1){
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][4]+crystals[1][4]);
		}
	else if(*peakPhi==0){
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][3]+crystals[1][3]+crystals[0][4]+crystals[1][4]);
		}	
		else if(*peakPhi==3){
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][0]+crystals[1][0]);
		}
	else if(*peakPhi==4){
		 	*ECAL_ClusterET=*ECAL_ClusterET-(crystals[0][0]+crystals[1][0]+crystals[0][1]+crystals[1][1]);
		}	
	

	
	}
	
	//ECAL_Cluster2X5 is equal to max of 2X5L or 2X5R
	//*ECAL_Clusteret2x5 = biggerLR(ECAL_ClusterETL, ECAL_ClusterETR);
	
	return true;
}

// uint16_t biggerLR(ap_fixed<16,9> ECAL_ClusterETL, ap_fixed<16,9> ECAL_ClusterETR){


// //
// #pragma HLS PIPELINE II=6

//   uint16_t ECAL_Clusterf = 0;
  
//   if(ECAL_ClusterETL>ECAL_ClusterETR)
//     ECAL_Clusterf = ECAL_ClusterETL;
  
//   else
//     ECAL_Clusterf = ECAL_ClusterETR;
  
//   return ECAL_Clusterf;
// }




bool mergeECAL_Clusters(uint16_t ieta1, uint16_t iphi1, ap_fixed<16,9> itet1, ap_fixed<16,9> icet1,
                   uint16_t ieta2, uint16_t iphi2, ap_fixed<16,9> itet2, ap_fixed<16,9> icet2,
                   uint16_t *eta1, uint16_t *phi1, ap_fixed<16,9> *tet1, ap_fixed<16,9> *cet1,
                   uint16_t *eta2, uint16_t *phi2, ap_fixed<16,9> *tet2, ap_fixed<16,9> *cet2) {
  // Check that the ECAL_Clusters are neighbors in eta or phi
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

bool getECAL_ClustersInCard(ap_fixed<16,9> uncal_crystals[NCaloLayer1Eta][NCaloLayer1Phi][NCrystalsPerEtaPhi][NCrystalsPerEtaPhi],
                       uint16_t peakEta[NCaloLayer1Eta][NCaloLayer1Phi],
                       uint16_t peakPhi[NCaloLayer1Eta][NCaloLayer1Phi],
                       ap_fixed<16,9> towerET[NCaloLayer1Eta][NCaloLayer1Phi],
                       ap_fixed<16,9> ECAL_ClusterET[NCaloLayer1Eta][NCaloLayer1Phi],
		       ap_fixed<16,9> SortedECAL_Cluster_ET[30],
		       uint16_t SortedPeak_Eta[30],
		        uint16_t TowerPeak_Eta[30],
                uint16_t TowerPeak_Phi[30],
		       ap_fixed<16,9> HCAL_towerET_uncal[17][4],
		       uint16_t SortedPeak_Phi[30]) {
#pragma HLS PIPELINE II=6
#pragma HLS ARRAY_PARTITION variable=uncal_crystals complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=towerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=ECAL_ClusterET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedECAL_Cluster_ET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Eta complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=TowerPeak_Eta complete dim=0
#pragma HLS ARRAY_PARTITION variable=TowerPeak_Phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=HCAL_towerET_uncal complete dim=0
ap_fixed<16,9> crystals[NCaloLayer1Eta][NCaloLayer1Phi][NCrystalsPerEtaPhi][NCrystalsPerEtaPhi];
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
for (int i=0;i<17;i++)
{
  for (int j=0;j<4;j++)
  {
  	for (int k=0;k<5;k++)
  	{
  		for(int l=0;l<5;l++)
  		{
  			crystals[i][j][k][l]=0;
  		}
  	}
    
  }
}
//ECAL_Calibration
// ap_fixed<16,9>   towerET_cal [17][4];

// #pragma HLS ARRAY_PARTITION variable=towerET complete dim=0
// for (int i=0;i<17;i++)
// {
//   #pragma HLS UNROLL
//   for (int j=0;j<4;j++)
//   {
//     #pragma HLS UNROLL
//     towerET_cal[i][j]=0;
//   }
// }
// for (int i=0;i<17;i++)
// {
//   #pragma HLS UNROLL
//   for (int j=0;j<4;j++)
//   {
//     #pragma HLS UNROLL
//     for (int k=0;k<5;k++)
//     {
//       #pragma HLS UNROLL
//       for(int l=0;l<5;l++)
//       {
//         #pragma HLS UNROLL
//         towerET_cal[i][j]=towerET_cal[i][j]+uncal_crystals[i][j][k][l];
//       }
//     }
//    // towerET_cal[i][j]=towerET_cal[i][j]+HCAL_towerET_uncal[i][j];
//   }
// }
//  for (int j=0;j<17;j++)
//   {
//   #pragma HLS UNROLL
//       for (int k=0;k<4;k++)
//       {
//       #pragma HLS UNROLL
//         if(towerET_cal[j][k]<ECAL_Calib_ET_Bins[0])
//          {
//           towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[0][j];
          
//          }
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[0])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[1]))
//          {
//               towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[1][j];

//          } 
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[1])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[2]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[2][j];
//          }
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[2])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[3]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[3][j];
//          } 
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[3])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[4]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[4][j];
//          }
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[4])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[5]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[5][j];
//          } 
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[5])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[6]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[6][j];
//          }
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[6])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[7]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[7][j];
//          } 
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[7])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[8]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[8][j];
//          }
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[8])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[9]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[9][j];
//          } 
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[9])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[10]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[10][j];
//          }
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[10])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[11]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[11][j];
//          } 
//         else if ((towerET_cal[j][k]>ECAL_Calib_ET_Bins[11])&&(towerET_cal[j][k]<ECAL_Calib_ET_Bins[12]))
//          {
//         	towerET_cal[j][k]=towerET_cal[j][k]*ECAL_Calib_LUT[12][j];
//          }

//       }
//   }

  uint16_t preMergePeakEta[NCaloLayer1Eta][NCaloLayer1Phi];
  uint16_t preMergePeakPhi[NCaloLayer1Eta][NCaloLayer1Phi];
  ap_fixed<16,9> preMergeTowerET[NCaloLayer1Eta][NCaloLayer1Phi];
  ap_fixed<16,9> preMergeECAL_ClusterET[NCaloLayer1Eta][NCaloLayer1Phi];
  ap_fixed<16,9> crystals_tower[3][4][5][5];
#pragma HLS ARRAY_PARTITION variable=crystals_tower complete dim=0
  ap_fixed<16,9> sortedECAL_Clusteret[5];

#pragma HLS ARRAY_PARTITION variable=sortedECAL_Clusteret complete dim=0
  uint16_t sortedpeaketa[5];
#pragma HLS ARRAY_PARTITION variable=sortedpeaketa complete dim=0
  uint16_t sortedpeakphi[5];
#pragma HLS ARRAY_PARTITION variable=sortedpeakphi complete dim=0
   uint16_t towerpeaketa[5];
#pragma HLS ARRAY_PARTITION variable=towerpeaketa complete dim=0
  uint16_t towerpeakphi[5];
#pragma HLS ARRAY_PARTITION variable=towerpeakphi complete dim=0
  ap_fixed<16,9> SortedECAL_Cluster_ET1[30];
  uint16_t SortedPeak_Eta1[30];
  uint16_t SortedPeak_Phi1[30];
  uint16_t TowerPeak_Eta1[30];
  uint16_t TowerPeak_Phi1[30];


#pragma HLS ARRAY_PARTITION variable=preMergePeakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergePeakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeTowerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeECAL_ClusterET complete dim=0




#pragma HLS ARRAY_PARTITION variable=SortedECAL_Cluster_ET1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Eta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Phi1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=TowerPeak_Eta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=TowerPeak_Phi1 complete dim=0

  for(int i=0; i<5; i++)
    {
      sortedECAL_Clusteret[i]=0;
      sortedpeaketa[i]=0;
      sortedpeakphi[i]=0;
      towerpeaketa[i]=0;
      towerpeakphi[i]=0;
    }


  for(int i=0; i<30; i++)
    {
      SortedECAL_Cluster_ET1[i]=0;
      SortedPeak_Eta1[i]=0;
      SortedPeak_Phi1[i]=0;
      TowerPeak_Eta1[i]=0;
      TowerPeak_Phi1[i]=0;
    }


  for(int i=0; i<30; i++)
    {
      SortedECAL_Cluster_ET[i]=0;
      SortedPeak_Eta[i]=0;
      SortedPeak_Phi[i]=0;
      TowerPeak_Eta[i]=0;
      TowerPeak_Phi[i]=0;
      
    }
  

  int a=0;
  for(int i =0; i<15; i+=3) {
#pragma HLS UNROLL
    for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL
      for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
	preMergePeakEta[tEta][tPhi] = 999;
	preMergePeakPhi[tEta][tPhi] = 999;
	preMergeTowerET[tEta][tPhi] = 0;
	preMergeECAL_ClusterET[tEta][tPhi] = 0;
	for( int ceta =0; ceta<5; ceta++) {
#pragma HLS UNROLL
	  for( int cphi =0; cphi<5; cphi++) {
#pragma HLS UNROLL
	crystals_tower[tEta][tPhi][ceta][cphi] = uncal_crystals[i+tEta][tPhi][ceta][cphi];
	  }
	  
	}
      }
    }
    getECAL_Clustersin3x4Region(crystals_tower, preMergePeakEta,
			   preMergePeakPhi,
			   preMergeTowerET,
			   preMergeECAL_ClusterET,
			   sortedECAL_Clusteret,
			   towerpeaketa,
			   towerpeakphi,
			   sortedpeaketa,
			   sortedpeakphi);
    

    SortedECAL_Cluster_ET1[a+0] = sortedECAL_Clusteret[0];
    SortedECAL_Cluster_ET1[a+1] = sortedECAL_Clusteret[1];
    SortedECAL_Cluster_ET1[a+2] = sortedECAL_Clusteret[2];
    SortedECAL_Cluster_ET1[a+3] = sortedECAL_Clusteret[3];
    SortedECAL_Cluster_ET1[a+4] = sortedECAL_Clusteret[4];

    
    SortedPeak_Eta1[a+0] = sortedpeaketa[0];
    SortedPeak_Eta1[a+1] = sortedpeaketa[1];
    SortedPeak_Eta1[a+2] = sortedpeaketa[2];
    SortedPeak_Eta1[a+3] = sortedpeaketa[3];
    SortedPeak_Eta1[a+4] = sortedpeaketa[4];
    
    
    SortedPeak_Phi1[a+0] = sortedpeakphi[0];
    SortedPeak_Phi1[a+1] = sortedpeakphi[1];
    SortedPeak_Phi1[a+2] = sortedpeakphi[2];
    SortedPeak_Phi1[a+3] = sortedpeakphi[3];
    SortedPeak_Phi1[a+4] = sortedpeakphi[4];

    TowerPeak_Eta1[a+0] = towerpeaketa[0];
    TowerPeak_Eta1[a+1] = towerpeaketa[1];
    TowerPeak_Eta1[a+2] = towerpeaketa[2];
    TowerPeak_Eta1[a+3] = towerpeaketa[3];
    TowerPeak_Eta1[a+4] = towerpeaketa[4];
    
    
    TowerPeak_Phi1[a+0] = towerpeakphi[0];
    TowerPeak_Phi1[a+1] = towerpeakphi[1];
    TowerPeak_Phi1[a+2] = towerpeakphi[2];
    TowerPeak_Phi1[a+3] = towerpeakphi[3];
    TowerPeak_Phi1[a+4] = towerpeakphi[4];

    //    for(int i=0;i<5; i++)
    //{std::cout<<"a: "<<a<<"i: "<<i<<"SortedPeak_Eta[a+0]: "<<SortedPeak_Eta[a+i]<<"SortedPeak_Phi[a+0]: "<<SortedPeak_Phi[a+i]<<"peak eta: "<<preMergePeakEta[SortedPeak_Eta[a+i]][SortedPeak_Phi[a+i]]<<"Sorted_et: "<<SortedECAL_Cluster_ET[a+i]<<"Using clsuter et: "<<preMergeECAL_ClusterET[SortedPeak_Eta[a+i]][SortedPeak_Phi[a+i]]<<std::endl;}


    a= a+5;

          
  }
  
  for(int tEta = 0; tEta < 2; tEta++) {
#pragma HLS UNROLL
    for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
      for( int ceta =0; ceta<5; ceta++) {
#pragma HLS UNROLL
	for( int cphi =0; cphi<5; cphi++) {
#pragma HLS UNROLL
	  crystals_tower[tEta][tPhi][ceta][cphi] = uncal_crystals[tEta+15][tPhi][ceta][cphi];
	}

      }
    }
  }
  getECAL_Clustersin3x4Region(crystals_tower, preMergePeakEta,
			 preMergePeakPhi,
			 preMergeTowerET,
			 preMergeECAL_ClusterET,
			 sortedECAL_Clusteret,
			 towerpeaketa,
			   towerpeakphi,
			 sortedpeaketa,
			 sortedpeakphi);


  SortedECAL_Cluster_ET1[25+0] = sortedECAL_Clusteret[0];
  SortedECAL_Cluster_ET1[25+1] = sortedECAL_Clusteret[1];
  SortedECAL_Cluster_ET1[25+2] = sortedECAL_Clusteret[2];
  SortedECAL_Cluster_ET1[25+3] = sortedECAL_Clusteret[3];
  SortedECAL_Cluster_ET1[25+4] = sortedECAL_Clusteret[4];


  SortedPeak_Eta1[25+0] = sortedpeaketa[0];
  SortedPeak_Eta1[25+1] = sortedpeaketa[1];
  SortedPeak_Eta1[25+2] = sortedpeaketa[2];
  SortedPeak_Eta1[25+3] = sortedpeaketa[3];
  SortedPeak_Eta1[25+4] = sortedpeaketa[4];


  SortedPeak_Phi1[25+0] = sortedpeakphi[0];
  SortedPeak_Phi1[25+1] = sortedpeakphi[1];
  SortedPeak_Phi1[25+2] = sortedpeakphi[2];
  SortedPeak_Phi1[25+3] = sortedpeakphi[3];
  SortedPeak_Phi1[25+4] = sortedpeakphi[4];

  TowerPeak_Eta1[25+0] = towerpeaketa[0];
  TowerPeak_Eta1[25+1] = towerpeaketa[1];
  TowerPeak_Eta1[25+2] = towerpeaketa[2];
  TowerPeak_Eta1[25+3] = towerpeaketa[3];
  TowerPeak_Eta1[25+4] = towerpeaketa[4];


  TowerPeak_Phi1[25+0] = towerpeakphi[0];
  TowerPeak_Phi1[25+1] = towerpeakphi[1];
  TowerPeak_Phi1[25+2] = towerpeakphi[2];
  TowerPeak_Phi1[25+3] = towerpeakphi[3];
  TowerPeak_Phi1[25+4] = towerpeakphi[4];
  
  uint16_t TowerpeakEta3[32];
  uint16_t TowerpeakPhi3[32];
  uint16_t peakEta3[32];
  uint16_t peakPhi3[32];
  ap_fixed<16,9> ECAL_ClusterET3[32];

#pragma HLS ARRAY_PARTITION variable=peakEta3 complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi3 complete dim=0
#pragma HLS ARRAY_PARTITION variable=TowerpeakEta3 complete dim=0
#pragma HLS ARRAY_PARTITION variable=TowerpeakPhi3 complete dim=0
#pragma HLS ARRAY_PARTITION variable=ECAL_ClusterET3 complete dim=0
  
  for(int i=0;i<32;i++)
    {
#pragma HLS UNROLL
      peakEta3[i]=0;
      peakPhi3[i]=0;
      ECAL_ClusterET3[i]=0;

    }


  for(int i=0;i<30;i++)
    {
      ECAL_ClusterET3[i]= SortedECAL_Cluster_ET1[i];
      peakEta3[i]= SortedPeak_Eta1[i];
      peakPhi3[i]= SortedPeak_Phi1[i];
      TowerpeakEta3[i]= TowerPeak_Eta1[i];
      TowerpeakPhi3[i]= TowerPeak_Phi1[i];

    }


  int xx=0;
  //first level of binary comparators                                                                                                                                                  
  for(int i=0;i<32;i=i+4)
    {
#pragma HLS unroll
      if(ECAL_ClusterET3[i]>ECAL_ClusterET3[i+1])
	{xx=ECAL_ClusterET3[i+1];
	  ECAL_ClusterET3[i+1]=ECAL_ClusterET3[i];
	  ECAL_ClusterET3[i]=xx;
	  xx=peakEta3[i];
	  peakEta3[i]=peakEta3[i+1];
	  peakEta3[i+1]=xx;
	  xx=peakPhi3[i];
	  peakPhi3[i]=peakPhi3[i+1];
	  peakPhi3[i+1]=xx;
	
	xx=TowerpeakEta3[i];
      TowerpeakEta3[i]=TowerpeakEta3[i+1];
      TowerpeakEta3[i+1]=xx;
      xx=TowerpeakPhi3[i];
      TowerpeakPhi3[i]=TowerpeakPhi3[i+1];
      TowerpeakPhi3[i+1]=xx;

}
      if(ECAL_ClusterET3[i+2]<ECAL_ClusterET3[i+3])
	{xx=ECAL_ClusterET3[i+3];
	  ECAL_ClusterET3[i+3]=ECAL_ClusterET3[i+2];
	  ECAL_ClusterET3[i+2]=xx;
	  xx=peakEta3[i+2];
	  peakEta3[i+2]=peakEta3[i+3];
	  peakEta3[i+3]=xx;
	  xx=peakPhi3[i+2];
	  peakPhi3[i+2]=peakPhi3[i+3];
	  peakPhi3[i+3]=xx;
	  xx=TowerpeakEta3[i+2];
      TowerpeakEta3[i+2]=TowerpeakEta3[i+3];
      TowerpeakEta3[i+3]=xx;
      xx=TowerpeakPhi3[i+2];
      TowerpeakPhi3[i+2]=TowerpeakPhi3[i+3];
      TowerpeakPhi3[i+3]=xx;

	}
    }


  ECAL_bitonic4(ECAL_ClusterET3,peakEta3,peakPhi3,TowerpeakEta3,TowerpeakPhi3);


  for(int i=0;i<30;i++)
    {
      //SortedECAL_Cluster_ET[i] = ECAL_ClusterET3[i];
      SortedPeak_Eta[i]= peakEta3[i];
      SortedPeak_Phi[i]= peakPhi3[i];
	TowerPeak_Eta[i]=TowerpeakEta3[i];
      TowerPeak_Phi[i]=TowerpeakPhi3[i];
      SortedECAL_Cluster_ET[i] = ECAL_ClusterET3[i]+HCAL_towerET_uncal[TowerpeakEta3[i]][TowerpeakPhi3[i]];
      //std::cout<<"i: "<<i<<" SortedPeak_Eta[i] "<<SortedPeak_Eta[i]<<" SortedPeak_Phi[i]"<<SortedPeak_Phi[i]<<"  SortedECAL_Cluster_ET[i]"<< SortedECAL_Cluster_ET[i]<<std::endl;
    }

  
  // Merge neighboring split-ECAL_Clusters here
  for(int tEta = 0; tEta < NCaloLayer1Eta; tEta++) {
#pragma HLS UNROLL
    for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
      peakEta[tEta][tPhi] = preMergePeakEta[tEta][tPhi];
      peakPhi[tEta][tPhi] = preMergePeakPhi[tEta][tPhi];
      towerET[tEta][tPhi] = preMergeTowerET[tEta][tPhi];
      ECAL_ClusterET[tEta][tPhi] = preMergeECAL_ClusterET[tEta][tPhi];
      int nEta = -1;
      int nPhi = -1;
      if(preMergePeakEta[tEta][tPhi] == 0 && tEta != 0) nEta = tEta - 1;
      if(preMergePeakEta[tEta][tPhi] == NCaloLayer1Phi && tEta != 16) nEta = tEta + 1;
      if(preMergePeakPhi[tEta][tPhi] == 0 && tPhi != 0) nPhi = tPhi - 1;
      if(preMergePeakPhi[tEta][tPhi] == NCaloLayer1Phi && tPhi != 3) nPhi = tPhi + 1;
      //std::cout<<"Before merging tEta/tPhi/peakEta/peakPhi/"<<tEta<<"/"<<tPhi<<"/"<<peakEta[tEta][tPhi]<<"/"<<peakPhi[tEta][tPhi]<<endl;
      if(nEta >= 0 && nEta < NCaloLayer1Eta && nPhi >= 0 && nPhi < NCaloLayer1Phi) {
	if(!mergeECAL_Clusters(preMergePeakEta[tEta][tPhi],
			  preMergePeakPhi[tEta][tPhi],
			  preMergeTowerET[tEta][tPhi],
			  preMergeECAL_ClusterET[tEta][tPhi],
			  preMergePeakEta[nEta][nPhi],
			  preMergePeakPhi[nEta][nPhi],
			  preMergeTowerET[nEta][nPhi],
			  preMergeECAL_ClusterET[nEta][nPhi],
			  &peakEta[tEta][tPhi],
			  &peakPhi[tEta][tPhi],
			  &towerET[tEta][tPhi],
			  &ECAL_ClusterET[tEta][tPhi],
			  &peakEta[nEta][nPhi],
			  &peakPhi[nEta][nPhi],
			  &towerET[nEta][nPhi],
			  &ECAL_ClusterET[nEta][nPhi]))
			  return false;
	
      }
      
            
	
    }
  }
  
  
  return true;
}
