# CMSPhase2RCT
CMS Phase2 RCT HLS Project

This project uses CTP7-HLS from Ales Svetek

The setup instructions are:

```bash

mkdir -p /data/$USER/CMSPhase2HLS
cd /data/$USER/CMSPhase2HLS

source /data/tools/Xilinx/Vivado/2018.2/settings64.sh

git clone git@github.com:uwcms/CTP7-HLS.git
cd CTP7-HLS/
mkdir build
git checkout io_links
git submodule init; git submodule update
cd hls_algo
make

cd ../

git clone git@github.com:SridharaDasu/CMSPhase2RCT.git
cd CMSPhase2RCT
export CTP7_HLS_RUN_LABEL=test_tpg # Test input file is take from this label - default is test_data
make clean # To remove remants from the previous build 
make

head -100 ip/algo_top_csynth.rpt

```

To add a new test input file, please make <label>_inp.txt file in the data directory, and add it to the sources.tcl
To use a different input file, export CTP7_HLS_RUN_LABEL=<label>
