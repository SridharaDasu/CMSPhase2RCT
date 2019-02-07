## Set the top level module
set_top algo_unpacked

#### Add source code
add_files src/algo_unpacked.cpp
add_files src/ClusterFinder.cc

### Add testbed files
add_files -tb src/algo_unpacked_tb.cpp

### Add data files
add_files -tb data/test_ones_inp.txt
add_files -tb data/test_ones_out_ref.txt
#
add_files -tb data/test_zeros_inp.txt
add_files -tb data/test_zeros_out_ref.txt
#
add_files -tb data/test_zeros_1_inp.txt
add_files -tb data/test_zeros_1_out_ref.txt
#
add_files -tb data/test1_inp.txt
add_files -tb data/test1_out_ref.txt
#
add_files -tb data/test1_1_inp.txt
add_files -tb data/test1_1_out_ref.txt
#
add_files -tb data/test2_inp.txt
add_files -tb data/test2_out_ref.txt
#
add_files -tb data/test_random_inp.txt
add_files -tb data/test_random_out_ref.txt
