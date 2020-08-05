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
const int N_WORDS_PER_FRAME = 6;
// Word has 64 bits
const int N_SHORTS_PER_WORD = 4;

/** Algorithm specific parameters **/
#define TOWERS_IN_ETA 17
#define TOWERS_IN_PHI 2

/** More common algorithm definitions, do not remove **/
// N_INPUT_LINKS and N_OUTPUT_LINKS need to be numerically specified so that wrapper generators work.
// -- N_INPUT_LINKS = TOWERS_IN_ETA*TOWERS_IN_PHI
// -- 17x2 geometry in SLR2 and SLR1
// -- ECAL(17x2x5x5x14) and HCAL(16x2x16)
#define N_INPUT_LINKS 34
// -- N_OUTPUT_LINKS 
// -- ECAL Info: 2 links (one per phi 17x2)
// -- HCAL Info: 2 links (one per phi 16x2)
#define N_OUTPUT_LINKS 2

// 16G inputs
#define N_INPUT_WORDS_PER_FRAME 6
// 25G outputs
#define N_OUTPUT_WORDS_PER_FRAME 9


#endif
 /* !__ALGO_TOP_PARAMETERS_H__ */
