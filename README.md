# APx Gen2 Phase2 RCT

A refactored Phase2 RCT HLS algorithm for Gen2 hardware.

# Set up Xilinx env and licensing (uwlogin.cern.ch specific)
source /data/tools/Xilinx/Vivado/2018.2/settings64.sh
source /data/setup_xilinx_lic.sh


## Building

Running ```make``` will start the HLS compilation and export.

## Simulation

For HLS simulation:
```bash
make hls-csim tv_in=/hls/vivado_hls/data/test_in.txt tv_out=/hls/vivado_hls/data/test_out.txt
```

Firmware simulation is done as:
```bash
make xsim tv_in=/hls/vivado_hls/data/test_in.txt tv_out=/hls/vivado_hls/data/test_out.txt
```

The resulting HLS testbench can be open by doing:
```bash
cd firmware
make xsim-gui
```

## Test Vectors
A C++ library exists in ```common``` that facilitates handling of test vectors.

The Algo HLS testbench also usew this library to parse the input test vector and
write the results.

```tvgen``` shows how to use the library to create an input test vector.
Because of how AXI-stream works, there are times where writting to the stream is
not needed, this is represented by discontinuities in the cycle/clock counter
or by ```-``` in link data.

### Example of a test vector:

```
# CLK Link  0                  Link  1                  Link  2
   0  0x00 0x0000000000000000  0x00 0x0000000000000000  0x00 0x0000000000000000
   1  0x00 0x0000000000000001  0x00 0x0000000000000001  0x00 0x0000000000000001
   2  0x00 0x0000000000000002  0x00 0x0000000000000002  -    -
   6  0x00 0x0000000000000003  0x00 0x0000000000000003  0x00 0x0000000000000003
   7  0x00 0x0000000000000004  0x00 0x0000000000000004  0x00 0x0000000000000004  
   8  0x00 0x0000000000000005  0x00 0x0000000000000005  -    -
```

Between cycles 3 and 5 nothing will be added to the streams and also cycle 2
and cycle 8 will have no data being added to link 2.

Each word is composed of 8-bits of flags and 64-bits of user data.
