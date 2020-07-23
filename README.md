# APx Gen2 Phase2 RCT

Checkout existing RCT code on uwlogin.cern.ch:/data/$USER/ or g25n01.hep.wisc.edu:/nfs_scratch/$USER/:
```
cmsrel CMSSW_10_2_10
cd CMSSW_10_2_10/src
git clone git@github.com:SridharaDasu/CMSPhase2RCT.git
cd CMSPhase2RCT
source setEnv.sh  #(uwlogin.cern.ch or g25n01.hep.wisc.edu independent)
```

## Simulation

For HLS simulation:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

## Sythesis

For HLS synthesis and exporting RTl:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/hls/vivado_hls/
vivado_hls -f run_hls.tcl synth=1 export=1 
```

## Test Vectors

To make test vectors (see tvgen/README.md for more details):
```bash
cd $AP_FW_BASE_DIR/tvgen
cmsenv
make
./tvgen output*.root test_tv_in.txt
```

## The whole enchilada

Simulation, Synthesis, Verification and RTL generation in Vivado HLS (takes 2 hours):
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 synth=1 cosim=1 export=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

## The nightcap

Checkout APx Core Firmware connector and Make a bit file for APd (takes hours):
```
cd $AP_FW_BASE_DIR/
git clone --recursive ssh://git@gitlab.cern.ch:7999/asvetek/phase2-rct.git -b 384b
cd $AP_FW_BASE_DIR/phase2-rct/
mkdir build
make
```

## GUI access

Follow instructions at twiki - adapt suitably for usage on g25n01.hep.wisc.edu: 
https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1TriggerPhase2HLSProjects

