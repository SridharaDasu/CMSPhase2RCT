# Load RUCKUS environment and library
source -quiet $::env(RUCKUS_DIR)/vivado_proc.tcl

# Load local source Code and constraints
loadSource      -dir "$::DIR_PATH/hdl/"
loadConstraints -dir "$::DIR_PATH/constraints/"
loadSource      -sim_only -dir "$::DIR_PATH/sim/"

# Load HLS algo via Ruckus helper script
loadRuckusTcl "$::DIR_PATH/../hls"

# Set tv.sv as the top file for simulation
set_property top {tb} [get_filesets {sim_1}]
