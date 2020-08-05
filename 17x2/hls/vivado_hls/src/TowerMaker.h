#ifndef __TOWERMAKER_H__
#define __TOWERMAKER_H__

#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "../../../../include/objects.h"
#include "../../../../include/stitchTower.h"

using namespace std;

/* Crystal group - 25 in a tower */
class CrystalGroup {
 public:
  CrystalGroup() {;}

  CrystalGroup(ap_uint<384> data) {
#pragma HLS ARRAY_PARTITION variable=crystals complete dim=0
    for (size_t i = 0, start = 0, end = 13; i < 25; i++, start += 14, end += 14) {
#pragma LOOP UNROLL
      this->crystals[i] = Crystal(data.range(end, start));
    }
  }
  Crystal crystal(size_t i) {
    if (i < 25) {
      return crystals[i];
    }
    else {
      return Crystal();
    }
  }

#ifndef __SYNTHESIS__
  string toString() {
    string s= " ******  crystal energies ******* \n";
    for(size_t c=0; c<25; c++){
      if(this->crystals[c] > 0)
	s += to_string(c) + ": " + to_string(this->crystals[c]) + "\n";
    }
  return s;
  }
#endif

 private:
  Crystal crystals[25];
};

ap_uint<3> getPeakBinOf5(ap_uint<12> et[5], ap_uint<16> etSum);
void makeTower(CrystalGroup crystals, Tower &tower);
ap_uint<32> makeECALSummary(Tower towerLevelECALSummary[N_INPUT_LINKS]);

#endif /*!__TOWERMAKER_H__*/
