#include "../common/APxLinkData.hh"
#include <ap_int.h>
#include <bitset>

using namespace std;

/* ECAL crystal object definition */
struct Crystal {
	Crystal() : energy(0), timing(0), spike(false) {};

	Crystal(ap_uint<14> i) {
		this->energy = i;
		this->timing = i >> 10;
		this->spike = i >> 13;
	}

	inline operator ap_uint<14>() {
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

  // Packs a tower object into 6 64-bit words, useful for link formatting
  void pack(uint64_t out[6]) {
    for (size_t i = 0; i < 6; i++) out[i] = 0;

    for (size_t i = 0; i < 5; i++) {
      out[0] |= (uint64_t)(this->crystals[0][i].energy) << (i * 14);
    }

    out[1] |= ((uint64_t)(this->crystals[0][4].energy)) >> 8 && 0x3F;
    for (size_t i = 0; i < 4; i++) {
      out[1] |= (uint64_t)(this->crystals[1][i].energy) << (i * 14 + 6);
    }

    out[2] |= (uint64_t)(this->crystals[1][4].energy);
    for (size_t i = 0; i < 4; i++) {
      out[2] |= (uint64_t)(this->crystals[2][i].energy) << (i * 14 + 14);
    }

    out[3] |= ((uint64_t)(this->crystals[2][3].energy)) >> 8 && 0x3F;
    out[3] |= (uint64_t)(this->crystals[2][4].energy) << 6;
    for (size_t i = 0; i < 3; i++) {
      out[3] |= (uint64_t)(this->crystals[3][i].energy) << (i * 14 + 20);
    }

    for (size_t i = 0; i < 2; i++) {
      out[4] |= (uint64_t)(this->crystals[3][i+3].energy) << (i * 14);
    }
    for (size_t i = 0; i < 3; i++) {
      out[4] |= (uint64_t)(this->crystals[4][i].energy) << (i * 14 + 28);
    }

    out[5] |= ((uint64_t)(this->crystals[4][2].energy)) >> 8 && 0x3F;
    for (size_t i = 0; i < 2; i++) {
      out[5] |= (uint64_t)(this->crystals[4][i+3].energy) << (i * 14 + 6);
    }

    for(size_t kk=0; kk< 6;  kk++)
       cout<<std::setw(20)<<out[kk]<<"   "<<std::bitset<64>(out[kk])<<std::endl;
  }

	Crystal crystals[5][5];
};

#define ETA 17
#define PHI 2

int main(int argn, char *argp[]) {

  Tower towers[ETA][PHI];

//-  int counter = 0;
//-for(size_t ieta=0; ieta<5; ieta++){
//-   for(size_t iphi=0; iphi<5; iphi++){
//-      counter++;
//-      towers[0][0].crystals[ieta][iphi].energy=counter;
//-      cout<<"crystals["<<ieta<<"]["<<iphi<<"] : "<<towers[0][0].crystals[ieta][iphi].energy<<std::endl;
//-   }
//-}
//-      cout<<"----------"<<std::endl;
  
  towers[0][0].crystals[2][3].energy = 11;
  towers[0][0].crystals[2][4].energy = 22;
  towers[0][1].crystals[2][0].energy = 50;
  towers[1][0].crystals[0][3].energy = 44;
  towers[1][1].crystals[3][1].energy = 55;
  towers[2][0].crystals[4][4].energy = 66;
  towers[2][1].crystals[3][3].energy = 77;
  towers[2][1].crystals[3][4].energy = 88;
  towers[3][0].crystals[2][1].energy = 99;
  towers[4][1].crystals[3][1].energy = 95;
  towers[5][0].crystals[3][3].energy = 8;
  towers[6][1].crystals[4][0].energy = 25;
  towers[6][0].crystals[4][3].energy = 10;
  towers[6][0].crystals[4][4].energy = 36;
  towers[7][0].crystals[0][4].energy = 14;
  towers[7][1].crystals[4][3].energy = 70;
  towers[8][0].crystals[3][1].energy = 35;
  towers[8][1].crystals[2][3].energy = 26;
  towers[9][0].crystals[3][1].energy = 43;
  towers[9][0].crystals[2][2].energy = 204;
  towers[9][1].crystals[0][3].energy = 30;
  towers[12][0].crystals[1][1].energy = 170;
  towers[14][1].crystals[4][2].energy = 123;

//  towers[0][0].crystals[0][3].energy = 11;
//  towers[0][0].crystals[0][4].energy = 22;
//  towers[0][1].crystals[0][0].energy = 50;
//  towers[0][2].crystals[0][3].energy = 44;
//  towers[0][3].crystals[3][4].energy = 55;
//  towers[1][3].crystals[1][4].energy = 99;
//  towers[1][3].crystals[2][4].energy = 25;
//  towers[2][0].crystals[3][0].energy = 66;
//  towers[2][1].crystals[2][1].energy = 14;
//  towers[2][2].crystals[1][3].energy = 77;
//  towers[2][3].crystals[2][3].energy = 8;
//  towers[3][3].crystals[4][4].energy = 30;
//  towers[4][0].crystals[4][3].energy = 35;
//  towers[4][1].crystals[4][2].energy = 0x1A;
//  towers[4][2].crystals[4][1].energy = 0xCC;
//  towers[4][2].crystals[3][2].energy = 0x2B;
//  towers[4][3].crystals[0][4].energy = 70;


  uint64_t packed[ETA][PHI][6];
  for (size_t i = 0; i < ETA; i++) {
    for (size_t k = 0; k < PHI; k++) {
      std::cout<<"                                          ------- ["<<i<<"]["<<k<<"] -------"<<endl;
      towers[i][k].pack(packed[i][k]);
      std::cout<<endl;
    }
  }


  APxLinkData link_in(ETA*PHI);

  for (size_t i = 0; i < 6; i++) {
    for (size_t k = 0; k < ETA*PHI; k++) {
      size_t phi = k % PHI;
      size_t eta = k / PHI;
      link_in.add(i, k, {0x00, packed[eta][phi][i]});
    }
  }

  link_in.write("test_in.txt");

  return 0;
}
