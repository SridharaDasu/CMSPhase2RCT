#define default target (synthesis without co-simulation)
target: csyn_nocosim

export TOP_DIR = $(abspath $(PWD)/..)

#
## # Set ARGV, CFLAGs, LDFLAGs
export ARGV    = 
export CFLAGS  = 
export LDFLAGS = 
#
## # Set TOP_DIR to be the base directory for which the build directory resides
export PROJ_DIR = $(abspath $(PWD))
export BASE_DIR = $(abspath $(PWD)/..)
export TOP_DIR  = $(abspath $(PWD)/..)
#
export HLS_SIM_TOOL = xsim

# # Use top level makefile
include $(TOP_DIR)/submodules/ruckus/system_vivado_hls.mk
