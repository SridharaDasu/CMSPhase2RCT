# CMSPhase2RCT
CMS Phase2 RCT HLS Project

This project uses CTP7-HLS from Ales Svetek

The setup instructions are:

'''bash

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
export CTP7_HLS_RUN_LABEL=test_tpg
make

head -100 ip/algo_top_csynth.rpt

'''
