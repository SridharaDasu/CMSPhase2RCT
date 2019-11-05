#ifndef __CLUSTERFINDER_H__
#define __CLUSTERFINDER_H__

#include "algo_top_parameters.h"
//#include <algorithm>
//#include <utility>

using namespace std;


/* ECAL crystal object definition */
struct Crystal {
   Crystal() : energy(0), timing(0), spike(false) {};

   Crystal(ap_uint<14> i) {
      this->energy = i;
      this->timing = i >> 10;
      this->spike = i >> 13;
   }

   Crystal& operator=(const Crystal& rhs) {
      energy = rhs.energy;
      timing = rhs.timing;
      spike  = rhs.spike;
      return *this;
   }

   inline operator uint16_t() {
      return  ((uint16_t)(this->spike) << 13) |
	 ((uint16_t)(this->timing) << 10) |
	 this->energy;
   }

#ifndef __SYNTHESIS__
   string toString() {
      return "energy = " + to_string(this->energy) + ", timing = " + to_string(this->timing) + ", spike = " + to_string(this->spike);
   }
#endif

   ap_uint<10> energy;
   ap_uint<3> timing;
   bool spike;
};

/* ECAL cluster object definition */
struct Cluster {
   Cluster() : et(0), tower_phi(0), tower_eta(0), peak_phi(0), peak_eta(0) {};

   // Even thought it is practical, this kind of initialization should be avoided to prevent mistakes.
   //	Cluster(uint16_t et, ap_uint<4> tower_phi, ap_uint<6> tower_eta, ap_uint<3> peak_phi, ap_uint<3> peak_eta) :
   //		et(et), tower_phi(tower_phi), tower_eta(tower_eta), peak_phi(peak_phi), peak_eta(peak_eta) {};

   Cluster(uint32_t i) {
      this->et = i;
      this->tower_phi = i >> 16;
      this->tower_eta = i >> 20;
      this->peak_phi = i >> 26;
      this->peak_eta = i >> 29;
   }

   Cluster& operator=(const Cluster& rhs) {
      et        = rhs.et;
      tower_phi = rhs.tower_phi;
      tower_eta = rhs.tower_eta;
      peak_phi  = rhs.peak_phi;
      peak_eta  = rhs.peak_eta;

      return *this;
   }

   inline friend bool operator >(const Cluster& c1, const Cluster& c2) {
      if (c1.et > c2.et) return true;
      else return false;
   }

   inline operator uint32_t() {
#pragma HLS INLINE
      return  ((uint32_t)(this->peak_eta) << 29) |
	 ((uint32_t)(this->peak_phi) << 26) |
	 ((uint32_t)(this->tower_eta) << 20) |
	 ((uint32_t)(this->tower_phi) << 16) |
	 (uint32_t)this->et;
   }

   static void stitchNeigbours(const Cluster Ai, const Cluster Bi, Cluster &Ao, Cluster &B);

   template <size_t ETA, size_t PHI>
      static void stitchRegion(const Cluster in[ETA][PHI], Cluster out[ETA][PHI]);

#ifndef __SYNTHESIS__
   string toString() const {
      return "Cluster [" + to_string(this->tower_eta) + "(" + to_string(this->peak_eta) + ")," + to_string(this->tower_phi) + "(" + to_string(this->peak_phi) + ")]: " + to_string(this->et);
   }
#endif

   uint16_t et;
   ap_uint<4> tower_phi;
   ap_uint<6> tower_eta;
   ap_uint<3> peak_phi;
   ap_uint<3> peak_eta;
};

void Cluster::stitchNeigbours(const Cluster Ai, const Cluster Bi, Cluster &Ao, Cluster &Bo) {
   // For some reason if this pragma is set then the code doesn't synthetize properly...
   //#pragma HLS INLINE
   // Check that the clusters are neigbhors in eta or phi
   if (Ai.tower_eta == Bi.tower_eta || Ai.tower_phi == Bi.tower_phi ) {
      if(Ai.et > Bi.et){
	 // Merge 2 in to 1, and set 2 to remnant energy centered in tower
	 Ao.et = Ai.et + Bi.et;
	 Ao.peak_eta = Ai.peak_eta;
	 Ao.peak_phi = Ai.peak_phi;
	 Bo.et = 0 ;
	 Bo.peak_eta = 2 ;
	 Bo.peak_phi = 2 ;
      }
      else{
	 // Merge 1 in to 2, and set 1 to remnant energy centered in tower
	 Ao.et = 0;
	 Ao.peak_eta = 2;
	 Ao.peak_phi = 2;
	 Bo.et = Ai.et + Bi.et ;
	 Bo.peak_eta = Bi.peak_eta ;
	 Bo.peak_phi = Bi.peak_phi ;
      }

#ifndef __SYNTHESIS__
      cout << "Stitching cluster cluster [" + to_string(Ai.tower_eta) + "," + to_string(Ai.tower_phi) + "]:"<<to_string(Ai.et)<<" with [" <<
	 to_string(Bi.tower_eta) + "," + to_string(Bi.tower_phi) + "]:"<<to_string(Bi.et) << endl;
#endif

   } else {
      Ao = Ai;
      Bo = Bi;
   }
}

template <size_t ETA, size_t PHI>
void Cluster::stitchRegion(const Cluster in[ETA][PHI], Cluster out[ETA][PHI]) {
#pragma HLS ARRAY_PARTITION variable=in complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0

   Cluster stitch_eta[ETA][PHI];
   Cluster stitch_phi[ETA][PHI];
#pragma HLS ARRAY_PARTITION variable=stitch_eta complete dim=0
#pragma HLS ARRAY_PARTITION variable=stitch_phi complete dim=0


   for (size_t teta = 0; teta < ETA; teta++) {
#pragma LOOP UNROLL
      for (size_t tphi = 0; tphi < PHI; tphi++) {
#pragma LOOP UNROLL
	 stitch_eta[teta][tphi] = in[teta][tphi];
      }
   }

   // Stitch in eta
   for (size_t teta = 1; teta < ETA; teta++) {
#pragma LOOP UNROLL
      for (size_t tphi = 0; tphi < PHI; tphi++) {
#pragma LOOP UNROLL
	 if(in[teta][tphi].peak_eta == 0 && in[teta-1][tphi].peak_eta == 4 )
	    Cluster::stitchNeigbours(in[teta][tphi], in[teta-1][tphi], stitch_eta[teta][tphi], stitch_eta[teta-1][tphi]);
      }
   }

   for (size_t teta = 0; teta < ETA; teta++) {
#pragma LOOP UNROLL
      for (size_t tphi = 0; tphi < PHI; tphi++) {
#pragma LOOP UNROLL
	 stitch_phi[teta][tphi] = stitch_eta[teta][tphi];
	 out[teta][tphi]    = stitch_eta[teta][tphi];
      }
   }

   // Stitch in phi
   for (size_t teta = 0; teta < ETA; teta++) {
#pragma LOOP UNROLL
      for (size_t tphi = 1; tphi < PHI; tphi++) {
#pragma LOOP UNROLL
	 
	 if(stitch_phi[teta][tphi].peak_phi == 0 && stitch_phi[teta][tphi-1].peak_phi == 4 )
	    Cluster::stitchNeigbours(stitch_phi[teta][tphi], stitch_phi[teta][tphi-1], out[teta][tphi], out[teta][tphi-1]);
      }
   }

}

/* Tower object definition */
struct Tower {
   Tower() {
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
      for (size_t i = 0; i < 5; i++) {
#pragma LOOP UNROLL
	 for (size_t j = 0; j < 5; j++) {
#pragma LOOP UNROLL
	    this->crystals[i][j] = Crystal();
	 }
      }
   }

   Tower& operator=(const Tower& rhs) {
      for (size_t i = 0; i < 5; i++) {
#pragma LOOP UNROLL
	 for (size_t j = 0; j < 5; j++) {
#pragma LOOP UNROLL
	    crystals[i][j] = rhs.crystals[i][j];
	 }
      }
      return *this;
   }


   Cluster computeCluster(const ap_uint<6> towerEta, const ap_uint<4> towerPhi, uint16_t &towerEt);

#ifndef __SYNTHESIS__
   string toString() {
      ostringstream str;
      for (size_t i = 0; i < 5; i++) {
	 for (size_t k = 0; k < 5; k++) {
	    str << setfill('0') << setw(4) << hex << this->crystals[i][k].energy << " ";
	 }
	 str << endl;
      }

      return str.str();
   }
#endif

   Crystal crystals[5][5];

   protected:
   inline uint16_t getPeakBinOf5(const uint16_t et[5], const uint16_t etSum);
};


Cluster Tower::computeCluster(const ap_uint<6> towerEta, const ap_uint<4> towerPhi, uint16_t &towerEt) {
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0

   uint16_t phi_strip[5], eta_strip[5];
#pragma HLS ARRAY_PARTITION variable=phi_strip complete dim=0
#pragma HLS ARRAY_PARTITION variable=eta_strip complete dim=0

   // Compute strips
   for (size_t eta = 0; eta < 5; eta++) {
#pragma LOOP UNROLL
      eta_strip[eta] = 0;
      for (size_t phi = 0; phi < 5; phi++) {
#pragma LOOP UNROLL
	 eta_strip[eta] += this->crystals[eta][phi].energy;
      }
   }

   for (size_t phi = 0; phi < 5; phi++) {
#pragma LOOP UNROLL
      phi_strip[phi] = 0;
      for (size_t eta = 0; eta < 5; eta++) {
#pragma LOOP UNROLL
	 phi_strip[phi] += this->crystals[eta][phi].energy;
      }
   }

   // Compute tower energy
   uint16_t tet = 0;
   for (size_t eta = 0; eta < 5; eta++) {
#pragma LOOP UNROLL
      tet += eta_strip[eta];
   }
   towerEt = tet;

   // Compute peak locations
   ap_uint<3> peakEta = getPeakBinOf5(eta_strip, tet);
   ap_uint<3> peakPhi = getPeakBinOf5(phi_strip, tet);

   // Small cluster ET is just the 3x5 around the peak
   uint16_t clusterEt = 0;
   for (int dEta = -1; dEta <= 1; dEta++) {
#pragma LOOP UNROLL
      int eta = peakEta + dEta;
      clusterEt = (eta >= 0 && eta < 5)? clusterEt + eta_strip[eta] : clusterEt;
   }

   Cluster cluster;
   cluster.et = clusterEt;
   cluster.tower_eta = towerEta;
   cluster.tower_phi = towerPhi;
   cluster.peak_eta = peakEta;
   cluster.peak_phi = peakPhi;

   return cluster;
}


inline uint16_t Tower::getPeakBinOf5(const uint16_t et[5], const uint16_t etSum) {
#pragma HLS ARRAY_PARTITION variable=et complete dim=0
#pragma HLS INLINE
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


#endif /*!__CLUSTERFINDER_H__*/
