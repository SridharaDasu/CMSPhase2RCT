#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include "bitonicSorter.hh"

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
