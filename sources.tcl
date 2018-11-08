## Set the top level module
set_top algo_top
##
#### Add source code
add_files ${PROJ_DIR}/../hls_algo/src/algo_top.cpp
add_files ${PROJ_DIR}/src/algo_unpacked.cpp
add_files ${PROJ_DIR}/src/ClusterFinder.cc

### Add testbed files
add_files -tb ${PROJ_DIR}/../hls_algo/src/algo_top_tb.cpp -cflags ${CFLAGS}

### Add data files
add_files -tb ${PROJ_DIR}/data/test_tpg_inp.txt
