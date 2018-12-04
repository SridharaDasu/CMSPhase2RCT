## Set the top level module
set_top algo_top

#### Add source code
add_files ${TOP_DIR}/VivadoHls/null_algo/vivado_hls/src/algo_top.cpp
add_files ${PROJ_DIR}/src/algo_unpacked.cpp
add_files ${PROJ_DIR}/src/ClusterFinder.cc

### Add testbed files
add_files -tb ${TOP_DIR}/VivadoHls/null_algo/vivado_hls/src/algo_top_tb.cpp -cflags ${CFLAGS}

### Add data files
add_files -tb ${PROJ_DIR}/data/zeros_algo_inp.txt
add_files -tb ${PROJ_DIR}/data/zeros_algo_out_ref.txt

add_files -tb ${PROJ_DIR}/data/ones_algo_inp.txt
add_files -tb ${PROJ_DIR}/data/ones_algo_out_ref.txt
