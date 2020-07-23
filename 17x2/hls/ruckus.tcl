# Load RUCKUS library
source -quiet $::env(RUCKUS_DIR)/vivado_proc.tcl

# # Load Source Code
loadSource -path "$::DIR_PATH/rtl/RCTAlgoWrapper.vhd"
loadSource -path "$::DIR_PATH/rtl/algoTopWrapper.vhd"

loadSource -dir "$::DIR_PATH/vivado_hls/proj/solution1/impl/ip/hdl/vhdl/"
