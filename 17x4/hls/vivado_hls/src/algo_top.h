#ifndef __ALGO_TOP_H__
#define __ALGO_TOP_H__

#include <stdint.h>
#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>

#include "algo_top_parameters.h"

template<int D, int U>
struct ap_axiu <D, U, 0, 0>{
	ap_uint<D>       data;
	ap_uint<U>       user;
	ap_uint<1>       last;
};

namespace algo {
	typedef ap_axiu<32, 8, 0, 0> axiword32;
	typedef ap_axiu<64, 8, 0, 0> axiword64;
	typedef ap_axiu<256, 8, 0, 0> axiword256;
	typedef ap_axiu<320, 8, 0, 0> axiword320;
	typedef ap_axiu<384, 8, 0, 0> axiword384;
	typedef ap_axiu<448, 8, 0, 0> axiword448;
	typedef ap_axiu<512, 8, 0, 0> axiword512;
	typedef ap_axiu<576, 8, 0, 0> axiword576;
}

void algo_top(
	hls::stream<algo::axiword576> link_in[N_INPUT_LINKS],
	hls::stream<algo::axiword576> link_out[N_OUTPUT_LINKS]
);

#endif /* !__ALGO_TOP_H__ */
