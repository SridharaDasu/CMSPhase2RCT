current_fileset
open_wave_database ../build/apx_gen2/apx_gen2_project.sim/sim_1/behav/xsim/tb_behav.wdb

# From Vivado's generated tb.tcl script
set curr_wave [current_wave_config]
if { [string length $curr_wave] == 0 } {
 if { [llength [get_objects]] > 0} {
   add_wave /
   set_property needs_save false [current_wave_config]
 } else {
    send_msg_id Add_Wave-1 WARNING "No top level signals found. Simulator will start without a wave window. If you want to open a wave window go to 'File->New Waveform Configuration' or type 'create_wave_config' in the TCL console."
 }
}

# add_wave {{/tb}}
