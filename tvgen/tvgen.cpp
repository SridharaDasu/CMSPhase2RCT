#include "../common/APxLinkData.hh"
#include <ap_int.h>
#include <bitset>
#include <vector>
#include <string>
#include "TFile.h"
#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

using namespace std;


#define ETA 17 // Number of Towers in iEta for RCT
#define PHI 2  // Number of Towers in iPhi for RCT

#define CETA 85 // Number of Crystals in iEta for RCT (ETA*5)
#define CPHI 10 // Number of Crystals in iPhi for RCT (PHI*5)

#define MAX_ET 100  // Maximum Et Crystal cut in RCT for writing MC Sim TV
#define SUM_ET 100 // Sum Et cut in RCT for writing MC Sim TV
#define NEVENTS -1 // Number of Events to run over for MC Sim TV
#define NTV 500 // Number of TV to generate
#define EPATTERN 0 // Set to 1 to use sample_tv_in_{ievent}_{pos/neg}{irct}, 0 for sample_tv_in_{itv}
#define GZIP 1 // GZIP files together into one archive

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
  void pack(ap_uint<64> out[6],bool verbose=false) {

    for (size_t i = 0; i < 6; i++) out[i] = 0;

    int ncrys=0;
    for(size_t i=0; i<5; i++)
      for(size_t j=0; j<5; j++){
	if(this->crystals[i][j].energy>0)
	  if (verbose) cout<<"Crys#"<<ncrys<<": ["<<i<<"]["<<j<<"]: "<<this->crystals[i][j].energy<<endl;;
	ncrys++;
      }

    out[0].range(13, 0)  = this->crystals[0][0].energy; //0 (14)
    out[0].range(27, 14) = this->crystals[0][1].energy; //1 (14)
    out[0].range(41, 28) = this->crystals[0][2].energy; //2 (14)
    out[0].range(55, 42) = this->crystals[0][3].energy; //3 (14)
    out[0].range(63, 56) = this->crystals[0][4].energy & 0xFF; //4 (8)

    out[1].range( 5,  0) = this->crystals[0][4].energy >>8 & 0x3F; //4 (6)
    out[1].range(19,  6) = this->crystals[1][0].energy; //5 (14)
    out[1].range(33, 20) = this->crystals[1][1].energy; //6 (14)
    out[1].range(47, 34) = this->crystals[1][2].energy; //7 (14)
    out[1].range(61, 48) = this->crystals[1][3].energy; //8 (14)
    out[1].range(63, 62) = this->crystals[1][4].energy & 0x3; //9 (2)

    out[2].range(11,  0) = this->crystals[1][4].energy >>2 & 0xFFF; //9 (12)
    out[2].range(25, 12) = this->crystals[2][0].energy; //10 (14)
    out[2].range(39, 26) = this->crystals[2][1].energy; //11 (14)
    out[2].range(53, 40) = this->crystals[2][2].energy; //12 (14)
    out[2].range(63, 54) = this->crystals[2][3].energy & 0x3FF; //13 (10)

    out[3].range( 3,  0) = this->crystals[2][3].energy >>10 & 0xF; //13 (4)
    out[3].range(17,  4) = this->crystals[2][4].energy; //14 (14)
    out[3].range(31, 18) = this->crystals[3][0].energy; //15 (14)
    out[3].range(45, 32) = this->crystals[3][1].energy; //16 (14)
    out[3].range(59, 46) = this->crystals[3][2].energy; //17 (14)
    out[3].range(63, 60) = this->crystals[3][3].energy & 0xF; //18 (4)

    out[4].range( 9,  0) = this->crystals[3][3].energy >>4 & 0x3FF; //18 (10)
    out[4].range(23, 10) = this->crystals[3][4].energy; //19 (14)
    out[4].range(37, 24) = this->crystals[4][0].energy; //20 (14)
    out[4].range(51, 38) = this->crystals[4][1].energy; //21 (14)
    out[4].range(63, 52) = this->crystals[4][2].energy & 0xFFF; //22 (12)

    out[5].range( 1,  0) = this->crystals[4][2].energy >> 12 & 0x3; //22 (2)
    out[5].range(15,  2) = this->crystals[4][3].energy; //23 (14)
    out[5].range(29, 16) = this->crystals[4][4].energy; //24 (14)
    out[5].range(63, 30) = 0; //EMPTY (34)

    for(size_t kk=0; kk< 6;  kk++)
      if (verbose) cout<<std::setw(20)<<out[kk]<<"   "<<std::bitset<64>(out[kk])<<std::endl;
  }

  Crystal crystals[5][5];
};

void write_tv(Tower towers[ETA][PHI],const char* fname="test_in.txt",bool verbose=false) {
  std::cout << "Writing " << fname << endl;
  ap_uint<64> packed[ETA][PHI][6];
  int nlink=0;
  for (size_t k = 0; k < PHI; k++) {
    for (size_t i = 0; i < ETA; i++) {
      if (verbose) std::cout<<"++++ LINK # "<<nlink<<"                           ------- ["<<i<<"]["<<k<<"] -------"<<endl;
      towers[i][k].pack(packed[i][k]);
      if (verbose) std::cout<<endl;
      nlink++;
    }
  }


  APxLinkData link_in(ETA*PHI);

  for (size_t i = 0; i < 6; i++) {
    for (size_t k = 0; k < ETA*PHI; k++) {
      size_t phi = k / ETA;
      size_t eta = k % ETA;
      link_in.add(i, k, {0x00, packed[eta][phi][i]});
    }
  }
  link_in.write(fname);
}

void process_card(float rct[CETA][CPHI],const char* output,int &itv) {
  Tower towers[ETA][PHI];
  // float max_crystal = 0;
  // for (int ieta = 0; ieta < CETA; ieta++)
  //   for (int iphi = 0; iphi < CPHI; iphi++)
  //     if (max_crystal < rct[ieta][iphi]) max_crystal = rct[ieta][iphi];
  // int scale = 50/max_crystal;

  float max_et = 0;
  float et_sum = 0;
  for (int ieta = 0; ieta < CETA; ieta++) {
    for (int iphi = 0; iphi < CPHI; iphi++) {
      int ceta = ieta%5; int cphi = iphi%5;
      int teta = ieta/5; int tphi = iphi/5;
      float et = rct[ieta][iphi];
      // printf("(%i,%i,%i,%i,%i,%i): %f\n",teta,tphi,ceta,cphi,ieta,iphi,et);
      if ( et  > max_et ) max_et = et;
      et_sum += et;
      towers[teta][tphi].crystals[ceta][cphi].energy = et;
    }
  }
  if ( et_sum > SUM_ET && max_et > MAX_ET ){
    write_tv(towers,output);
    itv++;
  }
}

void gzip_tv(string pattern,const char* archive) {
  if (archive == 0) return;
  printf("Compressing %s* to %s\n",pattern.c_str(),archive);
  const char* command = ("tar -czvf " + string(archive) + " " + pattern + "*").c_str();
  system(command);
}

void mc_sim(vector<const char*> inputs,const char* output,const char* archive=0) {
  if ( string(output).find(".root") != string::npos ) {
    cout << output << " not valid tv file name" << endl;
    return;
  }
  // TFile* tfile = new TFile(input);
  TChain* tchain = new TChain("analyzer/tree");
  for (auto input : inputs) tchain->Add(input);
  TTreeReader reader(tchain);
  TTreeReaderValue<int> nCrystal(reader,"nCrystal");
  TTreeReaderArray<float> crystal_et(reader,"crystal_Et");
  TTreeReaderArray<int> crystal_ieta(reader,"crystal_iEta");
  TTreeReaderArray<int> crystal_iphi(reader,"crystal_iPhi");

  printf("Running %i files | %i events \noutput pattern: %s\n",inputs.size(),tchain->GetEntries(),output);
  string outname = string(output);
  outname = outname.substr(0,outname.find(".txt"));
  int itv = 0;
  for (int ievent = 0; reader.Next(); ievent++) {
    if (ievent >= NEVENTS && NEVENTS != -1) break;
    if (itv >= NTV && NTV != -1) break;
    string fname = outname;
    if (EPATTERN) fname += "_" + to_string(ievent);
    else fname += "_" + to_string(itv);
    
    float posEtaSect[CETA][360];
    float negEtaSect[CETA][360];

    float max_et = 0;
    for (int icrystal = 0; icrystal < *nCrystal; icrystal++) {
      float et = crystal_et[icrystal];
      int ieta = crystal_ieta[icrystal];
      int iphi = crystal_iphi[icrystal];

      if (et > max_et) max_et = et;

      if ( ieta < 0 )    negEtaSect[abs(ieta)-1][iphi-1] = et;
      else if (ieta > 0) posEtaSect[    ieta -1][iphi-1] = et;
    }
    if (max_et < MAX_ET) continue;
    // For pos & neg eta together
    for (int irct = 0; irct < 36; irct++) {
      float posRCT[CETA][CPHI];
      float negRCT[CETA][CPHI];
      for (int ieta = 0; ieta < CETA; ieta++) {
	for (int iphi = 0; iphi < CPHI; iphi++) {
	  int rphi = irct*CPHI + iphi;
	  posRCT[ieta][iphi] = posEtaSect[ieta][rphi];
	  negRCT[ieta][iphi] = negEtaSect[ieta][rphi];
	}
      }
      string posfname = fname;
      string negfname = fname;
      if (EPATTERN) {
	posfname += "_pos"+to_string(irct);
	negfname += "_neg"+to_string(irct);
      }
      
      process_card(posRCT,(fname+".txt").c_str(),itv);
      process_card(negRCT,(fname+".txt").c_str(),itv);
    }
  }
  printf("Finished Processesing MC: %i TV Written\n",itv);
  gzip_tv(outname,archive);
}

void test() {
  Tower towers[ETA][PHI];
  // set - 2
  towers[0][0].crystals[1][1].energy = 3;
  towers[0][0].crystals[1][3].energy = 7;
  towers[0][0].crystals[2][2].energy = 13;
  towers[0][0].crystals[2][3].energy = 26;
  towers[0][0].crystals[3][3].energy = 9;
  towers[0][1].crystals[2][4].energy = 24;
  towers[0][1].crystals[3][3].energy = 13;
  towers[0][1].crystals[3][4].energy = 43;
  towers[1][1].crystals[3][1].energy = 55;
  towers[1][1].crystals[3][2].energy = 11;
  towers[3][0].crystals[4][3].energy = 73;
  towers[4][0].crystals[3][4].energy = 16;
  towers[4][0].crystals[4][4].energy = 36;
  towers[4][1].crystals[4][0].energy = 14;
  towers[5][0].crystals[0][4].energy = 4;
  towers[5][1].crystals[3][3].energy = 11;
  towers[5][1].crystals[4][3].energy = 34;
  towers[6][1].crystals[0][3].energy = 22;
  towers[7][0].crystals[2][2].energy = 37;
  towers[9][0].crystals[4][3].energy = 18;
  towers[10][0].crystals[0][3].energy = 38;
  towers[11][1].crystals[2][1].energy = 15;
  towers[11][1].crystals[3][1].energy = 45;
  towers[12][1].crystals[4][3].energy = 27;
  towers[13][0].crystals[3][4].energy = 16;
  towers[14][0].crystals[1][4].energy = 40;
  towers[14][1].crystals[1][0].energy = 51;
  towers[15][0].crystals[4][1].energy = 32;
  towers[16][0].crystals[0][1].energy = 21;
  towers[16][1].crystals[3][4].energy = 12;
  write_tv(towers);
}

int main(int argn, char *argp[]) {
  if (argn == 1) test();
  else if (argn >= 3) {
    vector<const char*> inputs;
    const char* output=0;
    const char* archive=0;
    for (int i = 1; i < argn; i++) {
      string arg = string(argp[i]);
      if ( arg.find(".root") != string::npos ) inputs.push_back(argp[i]);
      else if ( arg.find(".txt") != string::npos ) output = argp[i];
      else if ( arg.find(".tar.gz") != string::npos ) archive = argp[i];
    }
    mc_sim(inputs,output,archive);
  }

  return 0;
}
