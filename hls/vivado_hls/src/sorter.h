#ifndef __SORTER_H__
#define __SORTER_H__

#include <cstdlib>

template <class Object>
void _sort12_odd(const Object in[12], Object out[12]) {
#pragma HLS ARRAY_PARTITION variable=in complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0
	Object tmp[12];

	for (size_t i = 0; i < 12; i+=2) {
		#pragma LOOP UNROLL
		tmp[i] = (in[i+1] > in[i])? in[i+1] : in[i];
		tmp[i+1] = (in[i+1] > in[i])? in[i] : in[i+1];
	}

	for (size_t i = 0; i < 12; i++) out[i] = tmp[i];
}

template <class Object>
void _sort12_even(const Object in[12], Object out[12]) {
#pragma HLS ARRAY_PARTITION variable=in complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0
	Object tmp[12];

	tmp[0] = in[0];
	tmp[11] = in[11];

	for (size_t i = 1; i < 11; i+=2) {
		#pragma LOOP UNROLL
		tmp[i] = (in[i+1] > in[i])? in[i+1] : in[i];
		tmp[i+1] = (in[i+1] > in[i])? in[i] : in[i+1];
	}

	for (size_t i = 0; i < 12; i++) out[i] = tmp[i];
}

template <class Object>
void sort12(const Object in[12], Object out[12]) {
#pragma HLS ARRAY_PARTITION variable=in complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0
	Object tmp[12];

	for (size_t i = 0; i < 12; i++) tmp[i] = in[i];

	for (size_t i = 0; i < 12; i++) {
		if (!(i % 2)) _sort12_odd(tmp, tmp);
		else _sort12_even(tmp, tmp);
	}

	for (size_t i = 0; i < 12; i++) out[i] = tmp[i];
}

#endif /* !__SORTER_H__*/
