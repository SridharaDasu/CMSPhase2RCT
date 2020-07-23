# Define target output
target: bit

# Define Firmware Version Number
export PRJ_VERSION = 0x00000001

export PROJECT = apx_gen2

# Simulation configuration
export VIVADO_PROJECT_SIM = tb
export VIVADO_PROJECT_SIM_TIME = 1 us # Simulation time with unit

# Define target part
export PRJ_PART = xcvu9p-flgc2104-1-e

export PARALLEL_SYNTH = 16

# Using a non-standard target directory structure,
# which requires me to define the TOP_DIR path
export TOP_DIR = $(abspath $(PWD)/..)

# Use top level makefile
include $(TOP_DIR)/submodules/ruckus/system_vivado.mk

# Run simulation and open waveform display
xsim-gui: ../build/$(PROJECT)/$(PROJECT)_project.sim/sim_1/behav/xsim/tb_behav.wdb
	vivado -source open_sim.tcl

../build/$(PROJECT)/$(PROJECT)_project.sim/sim_1/behav/xsim/tb_behav.wdb: xsim
