## Set the top level module
set_top algo_top

#### Add source code
add_files src/algo_top_parameters.h
add_files src/algo_top.h
add_files src/algo_top.cpp
add_files src/TowerMaker.h
add_files src/TowerMaker.cpp

### Add testbed files
add_files -tb src/algo_top_tb.cpp
add_files -tb ../../common/APxLinkData.hh
add_files -tb ../../common/APxLinkData.cpp

### Add test input files
add_files -tb data/test_in.txt
add_files -tb data/test_out_ref.txt
