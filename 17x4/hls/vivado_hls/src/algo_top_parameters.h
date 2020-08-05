/**
 * algo_top_parameters.h
 *
 * Defines the algorithm related configuration parameters.
 */

#ifndef __ALGO_TOP_PARAMETERS_H__
#define __ALGO_TOP_PARAMETERS_H__

/** Common algorithm definitions, do not remove **/
// Un-comment to have algo as a passthrough for testing purposes
//#define ALGO_PASSTHROUGH

// Number of data words per processing cycle/frame
// Word has 64 bits
const int N_WORDS_PER_FRAME = 9;
// 576b inputs
#define N_INPUT_WORDS_PER_FRAME 9
// 576b outputs
#define N_OUTPUT_WORDS_PER_FRAME 9


/** Algorithm specific parameters **/
#define TOWERS_IN_ETA 17
#define TOWERS_IN_PHI 4

/** More common algorithm definitions, do not remove **/
// N_INPUT_LINKS and N_OUTPUT_LINKS need to be numerically specified so that wrapper generators work.
// -- N_INPUT_LINKS
#define N_INPUT_LINKS  4 
// -- N_OUTPUT_LINKS
#define N_OUTPUT_LINKS	4

#endif
 /* !__ALGO_TOP_PARAMETERS_H__ */
