#!/bin/sh

beck=/opt/Xilinx/Vivado/2019.1/settings64.sh
uwlogin=/data/tools/Xilinx/Vivado/2018.3/settings64.sh

if [ -f "$beck" ]; then
   source $beck
elif [ if "$uwlogin" ]; then
   source $uwlogin
   source /data/setup_xilinx_lic.sh
fi
