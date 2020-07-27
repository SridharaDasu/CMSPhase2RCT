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

For HLS simulation of first-stage SLR processing of 17x2 trigger towers:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x2/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

For HLS simulation of second-stage SLR processing of 17x4 trigger towers:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x4/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

## Sythesis

For HLS synthesis and exporting RTL of first-stage SLR processing of 17x2 trigger towers:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x2/hls/vivado_hls/
vivado_hls -f run_hls.tcl synth=1 export=1 
```
For HLS synthesis and exporting RTL of second-stage SLR processing of 17x4 trigger towers:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x4/hls/vivado_hls/
vivado_hls -f run_hls.tcl synth=1 export=1 
```

## Test Vectors

To make test vectors (see tvgen/README.md for more details - first stage):
```bash
cd $AP_FW_BASE_DIR/17x2/tvgen
cmsenv
make
./tvgen output*.root test_tv_in.txt
```
To make test vectors (see tvgen/README.md for more details - second stage):
```bash
cd $AP_FW_BASE_DIR/17x4/tvgen
cmsenv
make
./tvgen output*.root test_tv_in.txt
```

## The whole enchilada

Simulation, Synthesis, Verification and RTL generation in Vivado HLS (takes 2 hours) - first stage:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x2/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 synth=1 cosim=1 export=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```
Simulation, Synthesis, Verification and RTL generation in Vivado HLS (takes 2 hours) - second stage:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x4/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 synth=1 cosim=1 export=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

## The nightcap

Checkout APx Core Firmware connector and Make a bit file for APd (takes hours) - presently it only has two copies of 17x2 with 384b IO. Eventually, it should take 2 copies of 17x2 with 384b input, and one copy of 17x4 to output at 576b from APd2:
```
cd $AP_FW_BASE_DIR/
git clone --recursive ssh://git@gitlab.cern.ch:7999/asvetek/phase2-rct.git -b 384b
cd $AP_FW_BASE_DIR/phase2-rct/
mkdir build
make
```

## GUI access

For g25n01.hep.wisc.edu: 

1) Activate your WiscVPN - Download from : https://it.wisc.edu/services/wiscvpn/
2) Use ssh to connect to g25n01.hep.wisc.edu
3) Check if you have a VNC serrver running:  vncserver -list
4) If it is running note the window <:n> where n is the window number
5) If it is NOT running, start one, vncserver -geometry 1440x900
6) Use VNC Viewer client on your laptop to connect to g25n01.hep.wisc.edu<:n> - where n is the window number.
6) Once connected open a Terminal using the linux gui
7) Navigate to $AP_FW_BASE_DIR and cmsenv
8) cd $AP_FW_BASE_DIR/CMSPhase2RCT/17x2/hls/vivado_hls/
9) vivado_hls
10) In the GUI open the directory $AP_FW_BASE_DIR/CMSPhase2RCT/17x2/hls/vivado_hls/proj

Click away to use the vivado_HLS

Similar method can be used for Vivado itself, if necessary to inspect the bitfile production stage fully from phase2-rct directory.

Try to avoid over using the GUI as it is resource intensive. Secondly, do not run multiple copies of vncserver. "vncserver -list" shows you the versions that are rrunning.  You can kill them, if they are unuseable using "vncserver -kill".

