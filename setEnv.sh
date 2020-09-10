#!/bin/sh

export AP_FW_BASE_DIR=`dirname $PWD`

g25n01=/opt/Xilinx/Vivado/2020.1/settings64.sh
uwlogin=/data/tools/Xilinx/Vivado/2019.1/settings64.sh

if [ -f "$g25n01" ]; then
   source $g25n01
elif [ -f "$uwlogin" ]; then
   source $uwlogin
   source /data/setup_xilinx_lic.sh
fi
