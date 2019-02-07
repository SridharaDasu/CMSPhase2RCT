#include <stdlib.h>
#include <stdio.h>

#include "ClusterFinder.hh"

#include <iostream>
using namespace std;


void bitonic32(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32])
{// sorting blocks of size 32                                                                                                                                                        
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<16;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+16])
	{
	  temp=ClusterDeposits[i+16];
	  ClusterDeposits[i+16]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+16];
	  ClusterEta[i+16]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+16];
	  ClusterPhi[i+16]=temp;
	}
    }

  for(int i=0;i<8;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+8])
        {
          temp=ClusterDeposits[i+8];
          ClusterDeposits[i+8]=ClusterDeposits[i];
          ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+8];
	  ClusterEta[i+8]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+8];
	  ClusterPhi[i+8]=temp;
        }
    }

  for(int i=16;i<24;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+8])
	{
	  temp=ClusterDeposits[i+8];
	  ClusterDeposits[i+8]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+8];
	  ClusterEta[i+8]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+8];
	  ClusterPhi[i+8]=temp;
	}
    }

  for(int i=0;i<4;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }
  for(int i=8;i<12;i++)
    {
      #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
        {
          temp=ClusterDeposits[i+4];
          ClusterDeposits[i+4]=ClusterDeposits[i];
          ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
        }
    }


  for(int i=16;i<20;i++)
    {
      #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
        {
          temp=ClusterDeposits[i+4];
          ClusterDeposits[i+4]=ClusterDeposits[i];
          ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
        }
    }

  for(int i=24;i<28;i++)
    {
      #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
        {
          temp=ClusterDeposits[i+4];
          ClusterDeposits[i+4]=ClusterDeposits[i];
          ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
        }
    }

  for(int i=0;i<29;i=i+4)
    {
            #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
      if(ClusterDeposits[i+1]<ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}
    }




  for(int i=0;i<31;i=i+2)
    {
      #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
        {
          temp=ClusterDeposits[i+1];
          ClusterDeposits[i+1]=ClusterDeposits[i];
          ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
        }
    }

}


void bitonic16(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32])
{// sorting blocks of size 16                                                                                                                                                        
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<8;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+8])
	{
	  temp=ClusterDeposits[i+8];
	  ClusterDeposits[i+8]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+8];
	  ClusterEta[i+8]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+8];
	  ClusterPhi[i+8]=temp;
	}

    }

  for(int i=16;i<24;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+8])
	{
	  temp=ClusterDeposits[i+8];
	  ClusterDeposits[i+8]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+8];
	  ClusterEta[i+8]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+8];
	  ClusterPhi[i+8]=temp;
	}

    }

  for(int i=0;i<4;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }
  for(int i=8;i<12;i++)
    {
 #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }
  for(int i=16;i<20;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }

  for(int i=24;i<28;i++)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }

  for(int i=0;i<13;i=i+4)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
          ClusterEta[i]=ClusterEta[i+2];
          ClusterEta[i+2]=temp;
          temp=ClusterPhi[i];
          ClusterPhi[i]=ClusterPhi[i+2];
          ClusterPhi[i+2]=temp;
	}

      if(ClusterDeposits[i+1]<ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}
    }

  for(int i=16;i<29;i=i+4)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
          ClusterEta[i]=ClusterEta[i+2];
          ClusterEta[i+2]=temp;
          temp=ClusterPhi[i];
          ClusterPhi[i]=ClusterPhi[i+2];
          ClusterPhi[i+2]=temp;
	}


      if(ClusterDeposits[i+1]>ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}
    }



  for(int i=0;i<15;i=i+2)
    {
#pragma HLS unroll//may be faster if split into two loops                                                                                                                          
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
	{
	  temp=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}

    }

  for(int i=16;i<31;i=i+2)
    {
#pragma HLS unroll//may be faster if split into two loops                                                                                                                          
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{
	  temp=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}

    }


  bitonic32(ClusterDeposits,ClusterEta,ClusterPhi);
}



void bitonic8(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32])
{// sorting blocks of size 8                                                                                                                                                         
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<4;i++)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    } 

  for(int i=8;i<12;i++)
	{
    #pragma HLS unroll
	  if(ClusterDeposits[i]>ClusterDeposits[i+4])
	    {
	      temp=ClusterDeposits[i+4];
	      ClusterDeposits[i+4]=ClusterDeposits[i];
	      ClusterDeposits[i]=temp;
	      temp=ClusterEta[i];
	      ClusterEta[i]=ClusterEta[i+4];
	      ClusterEta[i+4]=temp;
	      temp=ClusterPhi[i];
	      ClusterPhi[i]=ClusterPhi[i+4];
	      ClusterPhi[i+4]=temp;
	    }
	}


  for(int i=16;i<20;i++)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }
  for(int i=24;i<28;i++)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+4])
	{
	  temp=ClusterDeposits[i+4];
	  ClusterDeposits[i+4]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+4];
	  ClusterEta[i+4]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+4];
	  ClusterPhi[i+4]=temp;
	}
    }


  for(int i=0;i<5;i=i+4)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i+2];
	  ClusterEta[i+2]=ClusterEta[i];
	  ClusterEta[i]=temp;
	  temp=ClusterPhi[i+2];
	  ClusterPhi[i+2]=ClusterPhi[i];
	  ClusterPhi[i]=temp;
	}
      if(ClusterDeposits[i+1]<ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
          temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}
    }

  for(int i=8;i<13;i=i+4)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i+2];
	  ClusterEta[i+2]=ClusterEta[i];
	  ClusterEta[i]=temp;
	  temp=ClusterPhi[i+2];
	  ClusterPhi[i+2]=ClusterPhi[i];
	  ClusterPhi[i]=temp;
	}

      if(ClusterDeposits[i+1]>ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}
    }

  for(int i=16;i<21;i=i+4)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i+2];
	  ClusterEta[i+2]=ClusterEta[i];
	  ClusterEta[i]=temp;
	  temp=ClusterPhi[i+2];
	  ClusterPhi[i+2]=ClusterPhi[i];
	  ClusterPhi[i]=temp;
	}
      if(ClusterDeposits[i+1]<ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}
    }

  for(int i=24;i<29;i=i+4)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{
	  temp=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i+2];
	  ClusterEta[i+2]=ClusterEta[i];
	  ClusterEta[i]=temp;
	  temp=ClusterPhi[i+2];
	  ClusterPhi[i+2]=ClusterPhi[i];
	  ClusterPhi[i]=temp;
	}

      if(ClusterDeposits[i+1]>ClusterDeposits[i+3])
	{
	  temp=ClusterDeposits[i+3];
	  ClusterDeposits[i+3]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i+1];
	  ClusterEta[i+1]=ClusterEta[i+3];
	  ClusterEta[i+3]=temp;
	  temp=ClusterPhi[i+1];
	  ClusterPhi[i+1]=ClusterPhi[i+3];
	  ClusterPhi[i+3]=temp;
	}

    }

  for(int i=0;i<7;i=i+2)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
	{
	  temp=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
          ClusterEta[i]=ClusterEta[i+1];
          ClusterEta[i+1]=temp;
          temp=ClusterPhi[i];
          ClusterPhi[i]=ClusterPhi[i+1];
          ClusterPhi[i+1]=temp;
	}
    }
  for(int i=8;i<15;i=i+2)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{
	  temp=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
          ClusterEta[i]=ClusterEta[i+1];
          ClusterEta[i+1]=temp;
          temp=ClusterPhi[i];
          ClusterPhi[i]=ClusterPhi[i+1];
          ClusterPhi[i+1]=temp;
	}
    }

  for(int i=16;i<23;i=i+2)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
	{
	  temp=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
          temp=ClusterEta[i];
          ClusterEta[i]=ClusterEta[i+1];
          ClusterEta[i+1]=temp;
          temp=ClusterPhi[i];
          ClusterPhi[i]=ClusterPhi[i+1];
          ClusterPhi[i+1]=temp;
	}
    }
  for(int i=24;i<31;i=i+2)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{
	  temp=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=ClusterDeposits[i];
	  ClusterDeposits[i]=temp;
	  temp=ClusterEta[i];
          ClusterEta[i]=ClusterEta[i+1];
          ClusterEta[i+1]=temp;
          temp=ClusterPhi[i];
          ClusterPhi[i]=ClusterPhi[i+1];
          ClusterPhi[i+1]=temp;
	}
    }

  bitonic16(ClusterDeposits,ClusterEta,ClusterPhi);
}
void bitonic4(uint16_t ClusterDeposits[32], uint16_t ClusterEta[32], uint16_t ClusterPhi[32])
{
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  // comparators in blocks of 4                                                                                                                                                        
  for(int i=0;i<2;i++)
    {
    #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }
  for(int i=4;i<6;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }
  for(int i=8;i<10;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }
  for(int i=12;i<14;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }
  for(int i=16;i<18;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }

  for(int i=20;i<22;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }
  for(int i=24;i<26;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }
  for(int i=28;i<30;i++)
    {
#pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+2])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+2];
	  ClusterDeposits[i+2]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+2];
	  ClusterEta[i+2]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+2];
	  ClusterPhi[i+2]=temp;
	}
    }

  for(int i=0;i<3;i=i+2)
	 {
  #pragma HLS unroll
	   if(ClusterDeposits[i]<ClusterDeposits[i+1])
	     {temp=ClusterDeposits[i];
	       ClusterDeposits[i]=ClusterDeposits[i+1];
	       ClusterDeposits[i+1]=temp;
	       temp=ClusterEta[i];
	       ClusterEta[i]=ClusterEta[i+1];
	       ClusterEta[i+1]=temp;
	       temp=ClusterPhi[i];
	       ClusterPhi[i]=ClusterPhi[i+1];
	       ClusterPhi[i+1]=temp;
	     }
	 }
  for(int i=4;i<7;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }


  for(int i=8;i<11;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }

  for(int i=12;i<15;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }
  for(int i=16;i<19;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }


  for(int i=20;i<23;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }



  for(int i=24;i<27;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]<ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }
  for(int i=28;i<31;i=i+2)
    {
  #pragma HLS unroll
      if(ClusterDeposits[i]>ClusterDeposits[i+1])
	{temp=ClusterDeposits[i];
	  ClusterDeposits[i]=ClusterDeposits[i+1];
	  ClusterDeposits[i+1]=temp;
	  temp=ClusterEta[i];
	  ClusterEta[i]=ClusterEta[i+1];
	  ClusterEta[i+1]=temp;
	  temp=ClusterPhi[i];
	  ClusterPhi[i]=ClusterPhi[i+1];
	  ClusterPhi[i+1]=temp;
	}
    }

  bitonic8(ClusterDeposits,ClusterEta,ClusterPhi);

}

void bitonic_1_16(uint16_t Cluster_1_Deposits[16], uint16_t Cluster_1_Eta[16], uint16_t Cluster_1_Phi[16])
{// sorting blocks of size 16                                                                                                                                                        
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<8;i++)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+8])
	{
	  temp=Cluster_1_Deposits[i+8];
	  Cluster_1_Deposits[i+8]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+8];
	  Cluster_1_Eta[i+8]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+8];
	  Cluster_1_Phi[i+8]=temp;
	}

    }


  for(int i=0;i<4;i++)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+4])
	{
	  temp=Cluster_1_Deposits[i+4];
	  Cluster_1_Deposits[i+4]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+4];
	  Cluster_1_Eta[i+4]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+4];
	  Cluster_1_Phi[i+4]=temp;
	}
    }


  for(int i=8;i<12;i++)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+4])
	{
	  temp=Cluster_1_Deposits[i+4];
	  Cluster_1_Deposits[i+4]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+4];
	  Cluster_1_Eta[i+4]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+4];
	  Cluster_1_Phi[i+4]=temp;
	}
    }


  for(int i=0;i<13;i=i+4)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+2])
	{
	  temp=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i];
          Cluster_1_Eta[i]=Cluster_1_Eta[i+2];
          Cluster_1_Eta[i+2]=temp;
          temp=Cluster_1_Phi[i];
          Cluster_1_Phi[i]=Cluster_1_Phi[i+2];
          Cluster_1_Phi[i+2]=temp;
	}

      if(Cluster_1_Deposits[i+1]<Cluster_1_Deposits[i+3])
	{
	  temp=Cluster_1_Deposits[i+3];
	  Cluster_1_Deposits[i+3]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
	  temp=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=Cluster_1_Eta[i+3];
	  Cluster_1_Eta[i+3]=temp;
	  temp=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=Cluster_1_Phi[i+3];
	  Cluster_1_Phi[i+3]=temp;
	}
    }


  for(int i=0;i<15;i=i+2)
       {
#pragma HLS unroll//may be faster if split into two loops                                                                                                                          
	 if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+1])
	   {
	     temp=Cluster_1_Deposits[i+1];
	     Cluster_1_Deposits[i+1]=Cluster_1_Deposits[i];
	     Cluster_1_Deposits[i]=temp;
	     temp=Cluster_1_Eta[i];
	     Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
	     Cluster_1_Eta[i+1]=temp;
	     temp=Cluster_1_Phi[i];
	     Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
	     Cluster_1_Phi[i+1]=temp;
	   }

       }


}



void bitonic_1_8(uint16_t Cluster_1_Deposits[16], uint16_t Cluster_1_Eta[16], uint16_t Cluster_1_Phi[16])
{// sorting blocks of size 8                                                                                                                                                         
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  for(int i=0;i<4;i++)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+4])
	{
	  temp=Cluster_1_Deposits[i+4];
	  Cluster_1_Deposits[i+4]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+4];
	  Cluster_1_Eta[i+4]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+4];
	  Cluster_1_Phi[i+4]=temp;
	}
    }
  for(int i=8;i<12;i++)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+4])
	{
	  temp=Cluster_1_Deposits[i+4];
	  Cluster_1_Deposits[i+4]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+4];
	  Cluster_1_Eta[i+4]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+4];
	  Cluster_1_Phi[i+4]=temp;
	}
    }


  for(int i=0;i<5;i=i+4)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+2])
	{
	  temp=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i+2];
	  Cluster_1_Eta[i+2]=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=temp;
	  temp=Cluster_1_Phi[i+2];
	  Cluster_1_Phi[i+2]=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=temp;
	}
      if(Cluster_1_Deposits[i+1]<Cluster_1_Deposits[i+3])
	{
	  temp=Cluster_1_Deposits[i+3];
	  Cluster_1_Deposits[i+3]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
          temp=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=Cluster_1_Eta[i+3];
	  Cluster_1_Eta[i+3]=temp;
	  temp=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=Cluster_1_Phi[i+3];
	  Cluster_1_Phi[i+3]=temp;
	}
    }



  for(int i=8;i<13;i=i+4)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+2])
	{
	  temp=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
	  temp=Cluster_1_Eta[i+2];
	  Cluster_1_Eta[i+2]=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=temp;
	  temp=Cluster_1_Phi[i+2];
	  Cluster_1_Phi[i+2]=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=temp;
	}
      if(Cluster_1_Deposits[i+1]>Cluster_1_Deposits[i+3])
	{
	  temp=Cluster_1_Deposits[i+3];
	  Cluster_1_Deposits[i+3]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
	  temp=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=Cluster_1_Eta[i+3];
	  Cluster_1_Eta[i+3]=temp;
	  temp=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=Cluster_1_Phi[i+3];
	  Cluster_1_Phi[i+3]=temp;
	}
    }


  for(int i=0;i<7;i=i+2)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+1])
	{
	  temp=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
          temp=Cluster_1_Eta[i];
          Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
          Cluster_1_Eta[i+1]=temp;
          temp=Cluster_1_Phi[i];
          Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
          Cluster_1_Phi[i+1]=temp;
	}
    }
  for(int i=8;i<15;i=i+2)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+1])
	{
	  temp=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=temp;
          temp=Cluster_1_Eta[i];
          Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
          Cluster_1_Eta[i+1]=temp;
          temp=Cluster_1_Phi[i];
          Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
          Cluster_1_Phi[i+1]=temp;
	}
    }
  bitonic_1_16(Cluster_1_Deposits,Cluster_1_Eta,Cluster_1_Phi);
}




void bitonic_1_4(uint16_t Cluster_1_Deposits[16], uint16_t Cluster_1_Eta[16], uint16_t Cluster_1_Phi[16])
{
  int temp;
  // #pragma HLS dataflow                                                                                                                                                              
  // comparators in blocks of 4                                                                                                                                                        
  for(int i=0;i<2;i++)
    {
    #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+2])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+2];
	  Cluster_1_Eta[i+2]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+2];
	  Cluster_1_Phi[i+2]=temp;
	}
    }
  for(int i=4;i<6;i++)
    {
#pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+2])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+2];
	  Cluster_1_Eta[i+2]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+2];
	  Cluster_1_Phi[i+2]=temp;
	}
    }
  for(int i=8;i<10;i++)
    {
#pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+2])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+2];
	  Cluster_1_Eta[i+2]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+2];
	  Cluster_1_Phi[i+2]=temp;
	}
    }


  for(int i=12;i<14;i++)
    {
#pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+2])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+2];
	  Cluster_1_Deposits[i+2]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+2];
	  Cluster_1_Eta[i+2]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+2];
	  Cluster_1_Phi[i+2]=temp;
	}
    }

  for(int i=0;i<3;i=i+2)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+1])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=temp;
	}
    }


  for(int i=4;i<7;i=i+2)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+1])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=temp;
	}
    }

  for(int i=8;i<11;i=i+2)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]<Cluster_1_Deposits[i+1])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=temp;
	}
    }
  for(int i=12;i<15;i=i+2)
    {
  #pragma HLS unroll
      if(Cluster_1_Deposits[i]>Cluster_1_Deposits[i+1])
	{temp=Cluster_1_Deposits[i];
	  Cluster_1_Deposits[i]=Cluster_1_Deposits[i+1];
	  Cluster_1_Deposits[i+1]=temp;
	  temp=Cluster_1_Eta[i];
	  Cluster_1_Eta[i]=Cluster_1_Eta[i+1];
	  Cluster_1_Eta[i+1]=temp;
	  temp=Cluster_1_Phi[i];
	  Cluster_1_Phi[i]=Cluster_1_Phi[i+1];
	  Cluster_1_Phi[i+1]=temp;
	}
    }

  bitonic_1_8(Cluster_1_Deposits,Cluster_1_Eta,Cluster_1_Phi);

}



uint16_t getPeakBinOf5(uint16_t et[5], uint16_t etSum) {
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



bool getClustersin3x4Region(uint16_t crystals_tower[3][4][5][5],
			    uint16_t peakEta1[3][4],
			    uint16_t peakPhi1[3][4],
			    uint16_t towerET1[3][4],
			    uint16_t clusterET1[3][4],
			    uint16_t SortedClusterET[5],
			    uint16_t SortedPeakEta[5],
			    uint16_t SortedPeakPhi[5]) {
  

#pragma HLS PIPELINE II=1

#pragma HLS ARRAY_PARTITION variable=crystals_tower complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakEta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=towerET1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=clusterET1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedClusterET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeakPhi complete dim=0

  uint16_t peakEta2[16];
  uint16_t peakPhi2[16];
  uint16_t clusterET2[16];

#pragma HLS ARRAY_PARTITION variable=peakEta2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=clusterET2 complete dim=0


  for(int i=0;i<16;i++)
    {
#pragma HLS UNROLL      
      peakEta2[i]=0;
      peakPhi2[i]=0;
      clusterET2[i]=0;

    }

  int i=0;
  for(int tPhi = 0; tPhi < 4; tPhi++) {
#pragma HLS UNROLL
    for(int tEta = 0; tEta < 3; tEta++) {
#pragma HLS UNROLL
      getClustersInTower(crystals_tower[tEta][tPhi], 
			 &peakEta1[tEta][tPhi],
			 &peakPhi1[tEta][tPhi],
			 &towerET1[tEta][tPhi],
			 &clusterET1[tEta][tPhi]);
			 
      if(clusterET1[tEta][tPhi] > 0) 
	std::cout<<"tower eta: " << tEta<<" tower phi: "<<tPhi<<" peakEta1: "<<peakEta1[tEta][tPhi]<<" peakPhi1: "<<peakPhi1[tEta][tPhi]<<" clusterET: "<<clusterET1[tEta][tPhi]<<std::endl;
      peakEta2[i]= peakEta1[tEta][tPhi];
      peakPhi2[i]= peakPhi1[tEta][tPhi];

      //peakEta2[i]= tEta;                                                                                                                                     
      //peakPhi2[i]= tPhi;  
      clusterET2[i] = clusterET1[tEta][tPhi];
      
      i++;
    }
  }


  
  for(int i=13;i<16;i++)
    {
#pragma HLS UNROLL
      peakEta2[i]=0;
      peakPhi2[i]=0;
      clusterET2[i]=0;

    }

  
  uint16_t xx;
  
  for(int i=0;i<16;i=i+4)
    {
#pragma HLS unroll
      if(clusterET2[i]<clusterET2[i+1])
	{xx=clusterET2[i+1];
	  clusterET2[i+1]=clusterET2[i];
	  clusterET2[i]=xx;
	  xx=peakEta2[i];
	  peakEta2[i]=peakEta2[i+1];
	  peakEta2[i+1]=xx;
	  xx=peakPhi2[i];
	  peakPhi2[i]=peakPhi2[i+1];
	  peakPhi2[i+1]=xx;
	}

      if(clusterET2[i+2]>clusterET2[i+3])
	{xx=clusterET2[i+3];
	  clusterET2[i+3]=clusterET2[i+2];
	  clusterET2[i+2]=xx;
	  xx=peakEta2[i+2];
	  peakEta2[i+2]=peakEta2[i+3];
	  peakEta2[i+3]=xx;
	  xx=peakPhi2[i+2];
	  peakPhi2[i+2]=peakPhi2[i+3];
	  peakPhi2[i+3]=xx;

	}
    }


  // passing control to second level of quaternary comparators                                                                                                                     
  bitonic_1_4(clusterET2,peakEta2,peakPhi2);

  for(int i=0;i<5;i++)
    {
      SortedClusterET[i] = clusterET2[i];
      SortedPeakEta[i]= peakEta2[i];
      SortedPeakPhi[i]= peakPhi2[i];
    }
  

  return true; 

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
  *towerET = 0;
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
////subCluster 2X5L
//  uint16_t clusterETL ;
//  clusterETL =0;
//	for(int dEtaL = -1; dEtaL <= 0; dEtaL++) {
//#pragma HLS UNROLL
//	  int eta = *peakEta + dEtaL;
//	  if(eta >= 0 && eta < NCrystalsPerEtaPhi){
//	    clusterETL += etaStripSum[eta];
//	  }
//	}
//	//subCluster 2X5R
//	uint16_t clusterETR ;
//	clusterETR =0;
//	for(int dEtaR = 0; dEtaR <= 1; dEtaR++) {
//#pragma HLS UNROLL
//	  int eta = *peakEta + dEtaR;
//	  if(eta >= 0 && eta < NCrystalsPerEtaPhi){
//	    clusterETR += etaStripSum[eta];
//	  }
//	}
//	//cluster2X5 is equal to max of 2X5L or 2X5R
//	*clusteret2x5 = biggerLR(clusterETL, clusterETR);
//	
	return true;
}

uint16_t biggerLR(uint16_t clusterETL, uint16_t clusterETR){


//
#pragma HLS PIPELINE II=1

  uint16_t clusterf = 0;
  
  if(clusterETL>clusterETR)
    clusterf = clusterETL;
  
  else
    clusterf = clusterETR;
  
  return clusterf;
}




bool mergeClusters(uint16_t ieta1, uint16_t iphi1, uint16_t itet1, uint16_t icet1,
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

bool getClustersInCard(uint16_t crystals[NCaloLayer1Eta*NCaloLayer1Phi*NCrystalsPerEtaPhi*NCrystalsPerEtaPhi],
                       uint16_t peakEta[NCaloLayer1Eta][NCaloLayer1Phi],
                       uint16_t peakPhi[NCaloLayer1Eta][NCaloLayer1Phi],
                       uint16_t towerET[NCaloLayer1Eta][NCaloLayer1Phi],
                       uint16_t clusterET[NCaloLayer1Eta][NCaloLayer1Phi],
					   uint16_t SortedCluster_ET[30],
					   uint16_t SortedPeak_Eta[30],
					   uint16_t SortedPeak_Phi[30]) {

#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=towerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=clusterET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedCluster_ET complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Eta complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Phi complete dim=0


  uint16_t preMergePeakEta[NCaloLayer1Eta][NCaloLayer1Phi];
  uint16_t preMergePeakPhi[NCaloLayer1Eta][NCaloLayer1Phi];
  uint16_t preMergeTowerET[NCaloLayer1Eta][NCaloLayer1Phi];
  uint16_t preMergeClusterET[NCaloLayer1Eta][NCaloLayer1Phi];
  uint16_t crystals_tower[3][4][5][5];
#pragma HLS ARRAY_PARTITION variable=crystals_tower complete dim=0
  uint16_t sortedclusteret[5];

#pragma HLS ARRAY_PARTITION variable=sortedclusteret complete dim=0
  uint16_t sortedpeaketa[5];
#pragma HLS ARRAY_PARTITION variable=sortedpeaketa complete dim=0
  uint16_t sortedpeakphi[5];
#pragma HLS ARRAY_PARTITION variable=sortedpeakphi complete dim=0
  uint16_t SortedCluster_ET1[30];
  uint16_t SortedPeak_Eta1[30];
  uint16_t SortedPeak_Phi1[30];


#pragma HLS ARRAY_PARTITION variable=preMergePeakEta complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergePeakPhi complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeTowerET complete dim=0
#pragma HLS ARRAY_PARTITION variable=preMergeClusterET complete dim=0

#pragma HLS ARRAY_PARTITION variable=SortedCluster_ET1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Eta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=SortedPeak_Phi1 complete dim=0

  for(int i=0; i<5; i++)
    {
      sortedclusteret[i]=0;
      sortedpeaketa[i]=0;
      sortedpeakphi[i]=0;
      
    }


  for(int i=0; i<30; i++)
    {
      SortedCluster_ET1[i]=0;
      SortedPeak_Eta1[i]=0;
      SortedPeak_Phi1[i]=0;
      
    }


  for(int i=0; i<30; i++)
    {
      SortedCluster_ET[i]=0;
      SortedPeak_Eta[i]=0;
      SortedPeak_Phi[i]=0;
      
    }
  

  int a=0;
  for(int i =0; i<2; i+=3) {  // We are processing 5 of 17 possible etas due to CTP7 size
#pragma HLS UNROLL
    for(int tEta = 0; tEta < 3; tEta++) {
      if(i == 1 && tEta == 2) continue; // i=0 uses 3, i=1 2
#pragma HLS UNROLL
      for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
	preMergePeakEta[tEta][tPhi] = 999;
	preMergePeakPhi[tEta][tPhi] = 999;
	preMergeTowerET[tEta][tPhi] = 0;
	preMergeClusterET[tEta][tPhi] = 0;
	for( int ceta =0; ceta<5; ceta++) {
#pragma HLS UNROLL
	  for( int cphi =0; cphi<5; cphi++) {
#pragma HLS UNROLL
	    int crystalID = (i+tEta)*NCaloLayer1Phi*25+tPhi*25+ceta*5+cphi;
	    if(crystalID > 5*NCaloLayer1Phi*25) {
	      fprintf(stderr, "crystalID too large");
	      exit(1);
	    }
	    crystals_tower[tEta][tPhi][ceta][cphi] = crystals[crystalID];
	  }
	  
	}
      }
    }
    getClustersin3x4Region(crystals_tower, preMergePeakEta,
			   preMergePeakPhi,
			   preMergeTowerET,
			   preMergeClusterET,
			   sortedclusteret,
			   sortedpeaketa,
			   sortedpeakphi);
    

    SortedCluster_ET1[a+0] = sortedclusteret[0];
    SortedCluster_ET1[a+1] = sortedclusteret[1];
    SortedCluster_ET1[a+2] = sortedclusteret[2];
    SortedCluster_ET1[a+3] = sortedclusteret[3];
    SortedCluster_ET1[a+4] = sortedclusteret[4];

    
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

    //    for(int i=0;i<5; i++)
    //{std::cout<<"a: "<<a<<"i: "<<i<<"SortedPeak_Eta[a+0]: "<<SortedPeak_Eta[a+i]<<"SortedPeak_Phi[a+0]: "<<SortedPeak_Phi[a+i]<<"peak eta: "<<preMergePeakEta[SortedPeak_Eta[a+i]][SortedPeak_Phi[a+i]]<<"Sorted_et: "<<SortedCluster_ET[a+i]<<"Using clsuter et: "<<preMergeClusterET[SortedPeak_Eta[a+i]][SortedPeak_Phi[a+i]]<<std::endl;}


    a= a+5;

          
  }
  



  uint16_t peakEta3[32];
  uint16_t peakPhi3[32];
  uint16_t clusterET3[32];

#pragma HLS ARRAY_PARTITION variable=peakEta3 complete dim=0
#pragma HLS ARRAY_PARTITION variable=peakPhi3 complete dim=0
#pragma HLS ARRAY_PARTITION variable=clusterET3 complete dim=0
  
  for(int i=0;i<32;i++)
    {
#pragma HLS UNROLL
      peakEta3[i]=0;
      peakPhi3[i]=0;
      clusterET3[i]=0;

    }


  for(int i=0;i<30;i++)
    {
      clusterET3[i]= SortedCluster_ET1[i];
      peakEta3[i]= SortedPeak_Eta1[i];
      peakPhi3[i]= SortedPeak_Phi1[i];
    }


  int xx=0;
  //first level of binary comparators                                                                                                                                                  
  for(int i=0;i<32;i=i+4)
    {
#pragma HLS unroll
      if(clusterET3[i]>clusterET3[i+1])
	{xx=clusterET3[i+1];
	  clusterET3[i+1]=clusterET3[i];
	  clusterET3[i]=xx;
	  xx=peakEta3[i];
	  peakEta3[i]=peakEta3[i+1];
	  peakEta3[i+1]=xx;
	  xx=peakPhi3[i];
	  peakPhi3[i]=peakPhi3[i+1];
	  peakPhi3[i+1]=xx;
	}


      if(clusterET3[i+2]<clusterET3[i+3])
	{xx=clusterET3[i+3];
	  clusterET3[i+3]=clusterET3[i+2];
	  clusterET3[i+2]=xx;
	  xx=peakEta3[i+2];
	  peakEta3[i+2]=peakEta3[i+3];
	  peakEta3[i+3]=xx;
	  xx=peakPhi3[i+2];
	  peakPhi3[i+2]=peakPhi3[i+3];
	  peakPhi3[i+3]=xx;

	}
    }


  bitonic4(clusterET3,peakEta3,peakPhi3);


  for(int i=0;i<30;i++)
    {
      SortedCluster_ET[i] = clusterET3[i];
      SortedPeak_Eta[i]= peakEta3[i];
      SortedPeak_Phi[i]= peakPhi3[i];

      if(SortedCluster_ET[i] > 0) 
	std::cout<<"i: "<<i<<" SortedPeak_Eta[i] "<<SortedPeak_Eta[i]<<" SortedPeak_Phi[i]"<<SortedPeak_Phi[i]<<"  SortedCluster_ET[i]"<< SortedCluster_ET[i]<<std::endl;
    }

  
  // Merge neighboring split-clusters here
  for(int tEta = 0; tEta < NCaloLayer1Eta; tEta++) {
#pragma HLS UNROLL
    for(int tPhi = 0; tPhi < NCaloLayer1Phi; tPhi++) {
#pragma HLS UNROLL
      peakEta[tEta][tPhi] = preMergePeakEta[tEta][tPhi];
      peakPhi[tEta][tPhi] = preMergePeakPhi[tEta][tPhi];
      towerET[tEta][tPhi] = preMergeTowerET[tEta][tPhi];
      clusterET[tEta][tPhi] = preMergeClusterET[tEta][tPhi];
      int nEta = -1;
      int nPhi = -1;
      if(preMergePeakEta[tEta][tPhi] == 0 && tEta != 0) nEta = tEta - 1;
      if(preMergePeakEta[tEta][tPhi] == NCaloLayer1Phi && tEta != 16) nEta = tEta + 1;
      if(preMergePeakPhi[tEta][tPhi] == 0 && tPhi != 0) nPhi = tPhi - 1;
      if(preMergePeakPhi[tEta][tPhi] == NCaloLayer1Phi && tPhi != 3) nPhi = tPhi + 1;
      //std::cout<<"Before merging tEta/tPhi/peakEta/peakPhi/"<<tEta<<"/"<<tPhi<<"/"<<peakEta[tEta][tPhi]<<"/"<<peakPhi[tEta][tPhi]<<endl;
      if(nEta >= 0 && nEta < NCaloLayer1Eta && nPhi >= 0 && nPhi < NCaloLayer1Phi) {
	if(!mergeClusters(preMergePeakEta[tEta][tPhi],
			  preMergePeakPhi[tEta][tPhi],
			  preMergeTowerET[tEta][tPhi],
			  preMergeClusterET[tEta][tPhi],
			  preMergePeakEta[nEta][nPhi],
			  preMergePeakPhi[nEta][nPhi],
			  preMergeTowerET[nEta][nPhi],
			  preMergeClusterET[nEta][nPhi],
			  &peakEta[tEta][tPhi],
			  &peakPhi[tEta][tPhi],
			  &towerET[tEta][tPhi],
			  &clusterET[tEta][tPhi],
			  &peakEta[nEta][nPhi],
			  &peakPhi[nEta][nPhi],
			  &towerET[nEta][nPhi],
			  &clusterET[nEta][nPhi]))
			  return false;
	
      }
      
            
	
    }
  }
  
  
  return true;
}







