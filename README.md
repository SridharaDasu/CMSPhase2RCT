# APx Gen2 Phase2 RCT

# Set up Xilinx env and licensing (uwlogin.cern.ch specific)
```
source /data/tools/Xilinx/Vivado/2018.2/settings64.sh
source /data/setup_xilinx_lic.sh
```

Checkout existing RCT code from:
```
git clone -b RCT-Gen2 git@github.com:SridharaDasu/CMSPhase2RCT.git
cd CMSPhase2RCT
```

## Simulation
For HLS simulation:
```bash
make hls-csim  tv_in=$PWD/hls/vivado_hls/data/test_in.txt tv_out=$PWD/hls/vivado_hls/data/test_out.txt
or use
./run.sh
```

## Sythesis
For HLS synthesis:
```bash
cd hls/vivado_hls/
vivado_hls -f run_hls.tcl synth=1 
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
