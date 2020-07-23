all: hls xsim

.PHONY: hls hls-sim hls-gui xsim clean help

help:
	@echo "With no arguments it will compile, export and simulate the HLS code in firmware."
	@echo "When using hls-csim or xsim the following arguments can be used:"
	@echo " tv_in: test vector input file"
	@echo " tv_out: test vector output file"
	@echo " tv_ref: test vector reference file (not implemented)"
	@echo "Example: make xsim tv_in=$(pwd)/hls/vivado_hls/data/test_in.txt tv_out=$(pwd)/hls/vivado_hls/data/test_out.txt"

hls:
	(cd hls; make)

hls-csim:
	(cd hls; make csim)

hls-gui:
	(cd hls; make gui)

xsim: hls
ifndef tv_in
	$(error tv_in needs to be defined!)
endif
	$(eval PARAMS := tv_in=$(tv_in))
ifdef tv_out
	$(eval PARAMS := $(PARAMS) tv_out=$(tv_out))
endif
ifdef tv_ref
	$(eval PARAMS := $(PARAMS) tv_ref=$(tv_ref))
endif
	(cd firmware; make xsim SIM_PARAMETERS="$(PARAMS)")

clean:
	(cd firmware; make clean)
	(cd hls; make clean)
