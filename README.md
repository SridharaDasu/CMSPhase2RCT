# APx Gen2 Phase2 RCT

Checkout existing RCT code from:
```
git clone git@github.com:SridharaDasu/CMSPhase2RCT.git
cd CMSPhase2RCT

git checkout RCT-Gen2-384-Bit 

source setEnv.sh #(uwlogin/beck independent)
```

## Simulation
For HLS simulation:
```bash
make hls-csim  tv_in=$PWD/hls/vivado_hls/data/test_in.txt tv_out=$PWD/hls/vivado_hls/data/test_out.txt
or use
./run.sh
```

## Sythesis
For HLS synthesis and exporting RTl:
```bash
cd hls/vivado_hls/
vivado_hls -f run_hls.tcl synth=1 export=1 
```

export=1 is not working as of now, Use GUI to do that.

Follow instructions at twiki: 
https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1TriggerPhase2HLSProjects
Use VNC viewer (RealVNC) instead of chicken.

## Making bit file:
```
1) ssh beck
2) git clone --recursive ssh://git@gitlab.cern.ch:7999/asvetek/phase2-rct.git
3) source /opt/Xilinx/Vivado/2019.1/settings64.sh
4) cd phase2-rct/
5) mkdir build
6) cd xla/hdl
7) Copy RTL files from impl/ip/hdl/vhdl/ here
   DO NOT remove "XtalLevelAlgoWrapper.vhd"
8) cd ../..
9) make
```
