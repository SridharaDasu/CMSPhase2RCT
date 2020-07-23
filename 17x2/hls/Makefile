all: synth export

.PHONY: check-env clean gui csim cosim synth export

check-env:
ifndef XILINX_VIVADO
	$(error XILINX_VIVADO is not sourced!)
endif

csim: check-env
ifndef tv_in
	$(error tv_in needs to be defined!)
endif
ifndef tv_out
	tv_out=0
endif
ifndef tv_ref
	tv_ref=0
endif
	(cd vivado_hls; vivado_hls run_hls.tcl csim=1 tv_in=$(tv_in) tv_out=$(tv_out) tv_ref=$(tv_ref))

cosim: check-env synth
ifndef tv_in
	$(error tv_in needs to be defined!)
endif
ifndef tv_out
	tv_out=0
endif
ifndef tv_ref
	tv_ref=0
endif
	(cd vivado_hls; vivado_hls run_hls.tcl cosim=1 tv_in=$(tv_in) tv_out=$(tv_out) tv_ref=$(tv_ref))

synth: check-env vivado_hls/proj/solution1/impl/vhdl/

export: check-env vivado_hls/proj/solution1/impl/ip/hdl/vhdl/

vivado_hls/proj/solution1/impl/vhdl/:
	(cd vivado_hls; vivado_hls -f run_hls.tcl synth=1)

vivado_hls/proj/solution1/impl/ip/hdl/vhdl/:
	(cd vivado_hls; vivado_hls -f run_hls.tcl export=1)

gui: check-env
	(cd vivado_hls; vivado_hls -p proj)

clean:
	rm -r vivado_hls/proj
