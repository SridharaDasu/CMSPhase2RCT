# CMSPhase2RCT
CMS Phase2 RCT HLS Project


STEP-1 (starting from scratch):
```bash

mkdir -p /data/$USER/CMSPhase2HLS
cd /data/$USER/CMSPhase2HLS

source /data/tools/Xilinx/Vivado/2018.2/settings64.sh

git lfs install
git version
git-lfs version
git clone --recursive git@github.com:APxL1TAlgoDev/APx_Gen0_Algo.git
cd APx_Gen0_Algo
cd VivadoHls/null_algo/vivado_hls
mkdir clean
make ARGV="ones_algo"

```

STEP-2
```

source /data/tools/Xilinx/Vivado/2018.2/settings64.sh
cd /data/$USER/CMSPhase2HLS/
git clone -b setup-2018 git@github.com:SridharaDasu/CMSPhase2RCT.git
cd CMSPhase2RCT
make clean # To remove remants from the previous build 
make ARGV="<test_vector>" # i.e. make ARGV="ones_algo"

head -100 ip/algo_top_csynth.rpt

```

STEP-3
```

# Compile post-implementation checkpoint (to be integrated in final bitile)
make ARGV="<test_vector>" # i.e. make ARGV="ones_algo" dcp

```

To add a new test vector set, please make <test_vector>_inp.txt and <test_vector>_out_ref.txt  file in the data directory, and add it to the sources.tcl
