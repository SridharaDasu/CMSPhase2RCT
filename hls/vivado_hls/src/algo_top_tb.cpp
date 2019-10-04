#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <argp.h>

#include "algo_top_parameters.h"
#include "algo_top.h"

#include "../../../common/APxLinkData.hh"

using namespace std;
using namespace algo;

/* argp declarations */
const char *algo_top_tb_version = "algo_top_tb 1.0";
const char *algo_top_tb_bug_address = "<marcelo.vicente@cern.ch>";

static char doc[] =
    "APx HLS Algo C/RTL simulation";

static struct argp_option options[] = {
    {"read", 'r', "FILE", 0, "Reads target file and writes contexts to AXI streams", 0},
    {"write", 'w', "FILE", 0, "Writes algorithm results to target file", 0},
	{"compare", 'c', "FILE", 0, "Compare the algorithm output to target file", 0},
    {"verbose", 'v', 0, 0, "Produce verbose output", 0},
    {0},
};

struct arguments {
    char *readfile;
    char *writefile;
    char *cmpfile;
    bool verbose;
};

struct arguments arguments = {0};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = (struct arguments *)state->input;

    switch (key) {
    case 'r': arguments->readfile = arg; break;
    case 'w': arguments->writefile = arg; break;
    case 'c': arguments->cmpfile = arg; break;
    case 'v': arguments->verbose = true; break;
    default: return ARGP_ERR_UNKNOWN; break;
    }

    return 0;
}

static struct argp argp = { options, parse_opt, NULL, doc };

int main(int argc, char **argv) {

	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	hls::stream<axiword> link_in[N_INPUT_LINKS];
	hls::stream<axiword> link_out[N_OUTPUT_LINKS];
	size_t loop_count = 1;

	if (arguments.readfile) {
		APxLinkData datafile_in(N_INPUT_LINKS);

		datafile_in.read(arguments.readfile);

		// Copy the file data to the stream
		for (size_t i = 0; i < datafile_in.getCycles(); i++) {
			for (size_t k = 0; k < N_INPUT_LINKS; k++) {
				APxLinkData::LinkValue v;
				if (datafile_in.get(i, k, v)) {
					link_in[k].write({v.data, v.user, 0});
				}
			}
		}

		if (arguments.verbose) {
			cout << "Input data:" << endl;
			datafile_in.print();
		}

		// Calculate how many times the algorithm will have to run
		loop_count = datafile_in.getCycles() / N_WORDS_PER_FRAME;
		if (datafile_in.getCycles() % N_WORDS_PER_FRAME) loop_count++;
	}

	// Run the algorithm
	for (size_t i = 0; i < loop_count; i++) {
		algo_top(link_in, link_out);
	}

	APxLinkData datafile_out(N_OUTPUT_LINKS);

	for (size_t i = 0; i < N_OUTPUT_WORDS_PER_FRAME * loop_count; i++) {
		for (size_t k = 0; k < N_OUTPUT_LINKS; k++) {
			if (!link_out[k].empty()) {
				axiword r = link_out[k].read();
				datafile_out.add(i, k, {r.user, r.data});
			}
		}
	}

	if (arguments.verbose) {
		cout << "Output data:" << endl;
		datafile_out.print();
	}

	if (arguments.writefile) {
		datafile_out.write(arguments.writefile);
	}

	if (arguments.cmpfile) {
		APxLinkData datafile_cmp(N_OUTPUT_LINKS);
		datafile_cmp.read(arguments.cmpfile);

		if (datafile_cmp != datafile_out) {
			cout << "HLS output DOES NOT match!" << endl;
			return -1;
		} else {
			cout << "HLS output matches!" << endl;
		}
	}

	return 0;
}

