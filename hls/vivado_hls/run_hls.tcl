# Using part of the build script for HLS4ML project authored by Vladimir Loncar (vloncar)
# https://github.com/hls-fpga-machine-learning/hls4ml

array set opt {
    csim   0
    synth  0
    cosim  0
    export 0
    tv_in  "data/test_in.txt"
    tv_out "data/test_out.txt"
    tv_ref "data/test_out_ref.txt"
}

foreach arg $::argv {
    foreach o [lsort [array names opt]] {
         regexp "$o\=(.*)" $arg unused opt($o)
    }
}

proc report_time { op_name time_start time_end  } {
    set time_taken [expr $time_end - $time_start]
    set time_s [expr ($time_taken / 1000) % 60]
    set time_m [expr ($time_taken / (1000*60)) % 60]
    set time_h [expr ($time_taken / (1000*60*60)) % 24]
    puts "***** ${op_name} COMPLETED IN ${time_h}h${time_m}m${time_s}s *****"
}

# open the project
open_project proj

# Add sources and specify top function
source "./sources.tcl"

# Open the solution
open_solution "solution1"

# Specify FPGA and clock constraints
source "./solution.tcl"

# Add Vivado HLS project directives
source "./directives.tcl"

if {$opt(csim)} {
  puts "***** C SIMULATION *****"
  set time_start [clock clicks -milliseconds]
  set args "-r $opt(tv_in) -v"
  if {[string compare $opt(tv_out) ""]} {set args [append args " -w $opt(tv_out)"]}
  if {[string compare $opt(tv_ref) ""]} {set args [append args " -c $opt(tv_ref)"]}
  puts "Executing: csim_design -argv \"$args\""
  csim_design -argv "$args"
  set time_end [clock clicks -milliseconds]
  report_time "C SIMULATION" $time_start $time_end
}

if {$opt(synth)} {
  puts "***** C/RTL SYNTHESIS *****"
  set time_start [clock clicks -milliseconds]
  csynth_design
  set time_end [clock clicks -milliseconds]
  report_time "C/RTL SYNTHESIS" $time_start $time_end
}

if {$opt(cosim)} {
  puts "***** C/RTL SIMULATION *****"
  set time_start [clock clicks -milliseconds]
  set args "-r $opt(tv_in) -v"
  if {[string compare $opt(tv_out) ""]} {set args [append args " -w $opt(tv_out)"]}
  if {[string compare $opt(tv_ref) ""]} {set args [append args " -c $opt(tv_ref)"]}
  puts "Executing: cosim_design -argv \"$args\" -trace_level all"
  cosim_design -argv "$args" -trace_level all
  set time_end [clock clicks -milliseconds]
  report_time "C/RTL SIMULATION" $time_start $time_end
}

if {$opt(export)} {
  puts "***** EXPORT IP *****"
  set time_start [clock clicks -milliseconds]
  export_design -format ip_catalog
  set time_end [clock clicks -milliseconds]
  report_time "EXPORT IP" $time_start $time_end

  puts "***** GENERATING WRAPPERS *****"
  puts [exec python ../wrapper_generator.py src/algo_top_parameters.h --wrapper ../rtl/algo_top_wrapper.vhd]
}

exit
