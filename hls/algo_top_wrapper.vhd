library IEEE;
use IEEE.STD_LOGIC_1164.all;

use work.algo_pkg.all;

entity algo_top_wrapper is
  generic (
    N_INPUT_LINKS  : integer := 24;
    N_OUTPUT_LINKS : integer := 24
    );
  port (
    -- Algo Control/Status Signals
    ap_clk   : in  std_logic;
    ap_rst   : in  std_logic;
    ap_start : in  std_logic;
    ap_done  : out std_logic;
    ap_idle  : out std_logic;
    ap_ready : out std_logic;

    -- AXI-Stream Input Links 
    link_in_master : in  LinkMasterArrType(0 to N_INPUT_LINKS-1) := (others => LINK_MASTER_NULL_C);
    link_in_slave  : out LinkSlaveArrType(0 to N_INPUT_LINKS-1)  := (others => LINK_SLAVE_NULL_C);

    -- AXI-Stream Output Links 
    link_out_master : out LinkMasterArrType(0 to N_OUTPUT_LINKS-1) := (others => LINK_MASTER_NULL_C);
    link_out_slave  : in  LinkSlaveArrType(0 to N_OUTPUT_LINKS-1)  := (others => LINK_SLAVE_NULL_C)
    );
end algo_top_wrapper;

architecture rtl of algo_top_wrapper is
  signal ap_rst_n : std_logic;
begin

  ap_rst_n <= not ap_rst;

  algo_top : entity work.algo_top
  PORT MAP (
    ap_clk => ap_clk,
    ap_rst_n => ap_rst_n,
    ap_start => ap_start,
    ap_done => ap_done,
    ap_idle => ap_idle,
    ap_ready => ap_ready,

    link_in_0_TUSER => link_in_master(0).tUser,
    link_in_0_TDATA => link_in_master(0).tData,
    link_in_0_TVALID => link_in_master(0).tValid,
    link_in_0_TLAST(0) => link_in_master(0).tLast,
    link_in_0_TREADY => link_in_slave(0).tReady,
    link_in_1_TUSER => link_in_master(1).tUser,
    link_in_1_TDATA => link_in_master(1).tData,
    link_in_1_TVALID => link_in_master(1).tValid,
    link_in_1_TLAST(0) => link_in_master(1).tLast,
    link_in_1_TREADY => link_in_slave(1).tReady,
    link_in_2_TUSER => link_in_master(2).tUser,
    link_in_2_TDATA => link_in_master(2).tData,
    link_in_2_TVALID => link_in_master(2).tValid,
    link_in_2_TLAST(0) => link_in_master(2).tLast,
    link_in_2_TREADY => link_in_slave(2).tReady,
    link_in_3_TUSER => link_in_master(3).tUser,
    link_in_3_TDATA => link_in_master(3).tData,
    link_in_3_TVALID => link_in_master(3).tValid,
    link_in_3_TLAST(0) => link_in_master(3).tLast,
    link_in_3_TREADY => link_in_slave(3).tReady,
    link_in_4_TUSER => link_in_master(4).tUser,
    link_in_4_TDATA => link_in_master(4).tData,
    link_in_4_TVALID => link_in_master(4).tValid,
    link_in_4_TLAST(0) => link_in_master(4).tLast,
    link_in_4_TREADY => link_in_slave(4).tReady,
    link_in_5_TUSER => link_in_master(5).tUser,
    link_in_5_TDATA => link_in_master(5).tData,
    link_in_5_TVALID => link_in_master(5).tValid,
    link_in_5_TLAST(0) => link_in_master(5).tLast,
    link_in_5_TREADY => link_in_slave(5).tReady,
    link_in_6_TUSER => link_in_master(6).tUser,
    link_in_6_TDATA => link_in_master(6).tData,
    link_in_6_TVALID => link_in_master(6).tValid,
    link_in_6_TLAST(0) => link_in_master(6).tLast,
    link_in_6_TREADY => link_in_slave(6).tReady,
    link_in_7_TUSER => link_in_master(7).tUser,
    link_in_7_TDATA => link_in_master(7).tData,
    link_in_7_TVALID => link_in_master(7).tValid,
    link_in_7_TLAST(0) => link_in_master(7).tLast,
    link_in_7_TREADY => link_in_slave(7).tReady,
    link_in_8_TUSER => link_in_master(8).tUser,
    link_in_8_TDATA => link_in_master(8).tData,
    link_in_8_TVALID => link_in_master(8).tValid,
    link_in_8_TLAST(0) => link_in_master(8).tLast,
    link_in_8_TREADY => link_in_slave(8).tReady,
    link_in_9_TUSER => link_in_master(9).tUser,
    link_in_9_TDATA => link_in_master(9).tData,
    link_in_9_TVALID => link_in_master(9).tValid,
    link_in_9_TLAST(0) => link_in_master(9).tLast,
    link_in_9_TREADY => link_in_slave(9).tReady,
    link_in_10_TUSER => link_in_master(10).tUser,
    link_in_10_TDATA => link_in_master(10).tData,
    link_in_10_TVALID => link_in_master(10).tValid,
    link_in_10_TLAST(0) => link_in_master(10).tLast,
    link_in_10_TREADY => link_in_slave(10).tReady,
    link_in_11_TUSER => link_in_master(11).tUser,
    link_in_11_TDATA => link_in_master(11).tData,
    link_in_11_TVALID => link_in_master(11).tValid,
    link_in_11_TLAST(0) => link_in_master(11).tLast,
    link_in_11_TREADY => link_in_slave(11).tReady,
    link_in_12_TUSER => link_in_master(12).tUser,
    link_in_12_TDATA => link_in_master(12).tData,
    link_in_12_TVALID => link_in_master(12).tValid,
    link_in_12_TLAST(0) => link_in_master(12).tLast,
    link_in_12_TREADY => link_in_slave(12).tReady,
    link_in_13_TUSER => link_in_master(13).tUser,
    link_in_13_TDATA => link_in_master(13).tData,
    link_in_13_TVALID => link_in_master(13).tValid,
    link_in_13_TLAST(0) => link_in_master(13).tLast,
    link_in_13_TREADY => link_in_slave(13).tReady,
    link_in_14_TUSER => link_in_master(14).tUser,
    link_in_14_TDATA => link_in_master(14).tData,
    link_in_14_TVALID => link_in_master(14).tValid,
    link_in_14_TLAST(0) => link_in_master(14).tLast,
    link_in_14_TREADY => link_in_slave(14).tReady,
    link_in_15_TUSER => link_in_master(15).tUser,
    link_in_15_TDATA => link_in_master(15).tData,
    link_in_15_TVALID => link_in_master(15).tValid,
    link_in_15_TLAST(0) => link_in_master(15).tLast,
    link_in_15_TREADY => link_in_slave(15).tReady,
    link_in_16_TUSER => link_in_master(16).tUser,
    link_in_16_TDATA => link_in_master(16).tData,
    link_in_16_TVALID => link_in_master(16).tValid,
    link_in_16_TLAST(0) => link_in_master(16).tLast,
    link_in_16_TREADY => link_in_slave(16).tReady,
    link_in_17_TUSER => link_in_master(17).tUser,
    link_in_17_TDATA => link_in_master(17).tData,
    link_in_17_TVALID => link_in_master(17).tValid,
    link_in_17_TLAST(0) => link_in_master(17).tLast,
    link_in_17_TREADY => link_in_slave(17).tReady,
    link_in_18_TUSER => link_in_master(18).tUser,
    link_in_18_TDATA => link_in_master(18).tData,
    link_in_18_TVALID => link_in_master(18).tValid,
    link_in_18_TLAST(0) => link_in_master(18).tLast,
    link_in_18_TREADY => link_in_slave(18).tReady,
    link_in_19_TUSER => link_in_master(19).tUser,
    link_in_19_TDATA => link_in_master(19).tData,
    link_in_19_TVALID => link_in_master(19).tValid,
    link_in_19_TLAST(0) => link_in_master(19).tLast,
    link_in_19_TREADY => link_in_slave(19).tReady,
    link_in_20_TUSER => link_in_master(20).tUser,
    link_in_20_TDATA => link_in_master(20).tData,
    link_in_20_TVALID => link_in_master(20).tValid,
    link_in_20_TLAST(0) => link_in_master(20).tLast,
    link_in_20_TREADY => link_in_slave(20).tReady,
    link_in_21_TUSER => link_in_master(21).tUser,
    link_in_21_TDATA => link_in_master(21).tData,
    link_in_21_TVALID => link_in_master(21).tValid,
    link_in_21_TLAST(0) => link_in_master(21).tLast,
    link_in_21_TREADY => link_in_slave(21).tReady,
    link_in_22_TUSER => link_in_master(22).tUser,
    link_in_22_TDATA => link_in_master(22).tData,
    link_in_22_TVALID => link_in_master(22).tValid,
    link_in_22_TLAST(0) => link_in_master(22).tLast,
    link_in_22_TREADY => link_in_slave(22).tReady,
    link_in_23_TUSER => link_in_master(23).tUser,
    link_in_23_TDATA => link_in_master(23).tData,
    link_in_23_TVALID => link_in_master(23).tValid,
    link_in_23_TLAST(0) => link_in_master(23).tLast,
    link_in_23_TREADY => link_in_slave(23).tReady,
    link_out_0_TUSER => link_out_master(0).tUser,
    link_out_0_TDATA => link_out_master(0).tData,
    link_out_0_TVALID => link_out_master(0).tValid,
    link_out_0_TLAST(0) => link_out_master(0).tLast,
    link_out_0_TREADY => link_out_slave(0).tReady
  );

end rtl;
