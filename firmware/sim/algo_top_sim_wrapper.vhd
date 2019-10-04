library IEEE;
use IEEE.STD_LOGIC_1164.all;
use work.algo_pkg.all;

entity algo_top_sim_wrapper is
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

    link_in_master_0_tvalid : in std_logic;
    link_in_master_0_tdata : in std_logic_vector (63 downto 0);
    link_in_master_0_tuser : in std_logic_vector (7 downto 0);
    link_in_master_0_tlast : in std_logic;
    link_in_slave_0_tready : out std_logic;

    link_in_master_1_tvalid : in std_logic;
    link_in_master_1_tdata : in std_logic_vector (63 downto 0);
    link_in_master_1_tuser : in std_logic_vector (7 downto 0);
    link_in_master_1_tlast : in std_logic;
    link_in_slave_1_tready : out std_logic;

    link_in_master_2_tvalid : in std_logic;
    link_in_master_2_tdata : in std_logic_vector (63 downto 0);
    link_in_master_2_tuser : in std_logic_vector (7 downto 0);
    link_in_master_2_tlast : in std_logic;
    link_in_slave_2_tready : out std_logic;

    link_in_master_3_tvalid : in std_logic;
    link_in_master_3_tdata : in std_logic_vector (63 downto 0);
    link_in_master_3_tuser : in std_logic_vector (7 downto 0);
    link_in_master_3_tlast : in std_logic;
    link_in_slave_3_tready : out std_logic;

    link_in_master_4_tvalid : in std_logic;
    link_in_master_4_tdata : in std_logic_vector (63 downto 0);
    link_in_master_4_tuser : in std_logic_vector (7 downto 0);
    link_in_master_4_tlast : in std_logic;
    link_in_slave_4_tready : out std_logic;

    link_in_master_5_tvalid : in std_logic;
    link_in_master_5_tdata : in std_logic_vector (63 downto 0);
    link_in_master_5_tuser : in std_logic_vector (7 downto 0);
    link_in_master_5_tlast : in std_logic;
    link_in_slave_5_tready : out std_logic;

    link_in_master_6_tvalid : in std_logic;
    link_in_master_6_tdata : in std_logic_vector (63 downto 0);
    link_in_master_6_tuser : in std_logic_vector (7 downto 0);
    link_in_master_6_tlast : in std_logic;
    link_in_slave_6_tready : out std_logic;

    link_in_master_7_tvalid : in std_logic;
    link_in_master_7_tdata : in std_logic_vector (63 downto 0);
    link_in_master_7_tuser : in std_logic_vector (7 downto 0);
    link_in_master_7_tlast : in std_logic;
    link_in_slave_7_tready : out std_logic;

    link_in_master_8_tvalid : in std_logic;
    link_in_master_8_tdata : in std_logic_vector (63 downto 0);
    link_in_master_8_tuser : in std_logic_vector (7 downto 0);
    link_in_master_8_tlast : in std_logic;
    link_in_slave_8_tready : out std_logic;

    link_in_master_9_tvalid : in std_logic;
    link_in_master_9_tdata : in std_logic_vector (63 downto 0);
    link_in_master_9_tuser : in std_logic_vector (7 downto 0);
    link_in_master_9_tlast : in std_logic;
    link_in_slave_9_tready : out std_logic;

    link_in_master_10_tvalid : in std_logic;
    link_in_master_10_tdata : in std_logic_vector (63 downto 0);
    link_in_master_10_tuser : in std_logic_vector (7 downto 0);
    link_in_master_10_tlast : in std_logic;
    link_in_slave_10_tready : out std_logic;

    link_in_master_11_tvalid : in std_logic;
    link_in_master_11_tdata : in std_logic_vector (63 downto 0);
    link_in_master_11_tuser : in std_logic_vector (7 downto 0);
    link_in_master_11_tlast : in std_logic;
    link_in_slave_11_tready : out std_logic;

    link_in_master_12_tvalid : in std_logic;
    link_in_master_12_tdata : in std_logic_vector (63 downto 0);
    link_in_master_12_tuser : in std_logic_vector (7 downto 0);
    link_in_master_12_tlast : in std_logic;
    link_in_slave_12_tready : out std_logic;

    link_in_master_13_tvalid : in std_logic;
    link_in_master_13_tdata : in std_logic_vector (63 downto 0);
    link_in_master_13_tuser : in std_logic_vector (7 downto 0);
    link_in_master_13_tlast : in std_logic;
    link_in_slave_13_tready : out std_logic;

    link_in_master_14_tvalid : in std_logic;
    link_in_master_14_tdata : in std_logic_vector (63 downto 0);
    link_in_master_14_tuser : in std_logic_vector (7 downto 0);
    link_in_master_14_tlast : in std_logic;
    link_in_slave_14_tready : out std_logic;

    link_in_master_15_tvalid : in std_logic;
    link_in_master_15_tdata : in std_logic_vector (63 downto 0);
    link_in_master_15_tuser : in std_logic_vector (7 downto 0);
    link_in_master_15_tlast : in std_logic;
    link_in_slave_15_tready : out std_logic;

    link_in_master_16_tvalid : in std_logic;
    link_in_master_16_tdata : in std_logic_vector (63 downto 0);
    link_in_master_16_tuser : in std_logic_vector (7 downto 0);
    link_in_master_16_tlast : in std_logic;
    link_in_slave_16_tready : out std_logic;

    link_in_master_17_tvalid : in std_logic;
    link_in_master_17_tdata : in std_logic_vector (63 downto 0);
    link_in_master_17_tuser : in std_logic_vector (7 downto 0);
    link_in_master_17_tlast : in std_logic;
    link_in_slave_17_tready : out std_logic;

    link_in_master_18_tvalid : in std_logic;
    link_in_master_18_tdata : in std_logic_vector (63 downto 0);
    link_in_master_18_tuser : in std_logic_vector (7 downto 0);
    link_in_master_18_tlast : in std_logic;
    link_in_slave_18_tready : out std_logic;

    link_in_master_19_tvalid : in std_logic;
    link_in_master_19_tdata : in std_logic_vector (63 downto 0);
    link_in_master_19_tuser : in std_logic_vector (7 downto 0);
    link_in_master_19_tlast : in std_logic;
    link_in_slave_19_tready : out std_logic;

    link_in_master_20_tvalid : in std_logic;
    link_in_master_20_tdata : in std_logic_vector (63 downto 0);
    link_in_master_20_tuser : in std_logic_vector (7 downto 0);
    link_in_master_20_tlast : in std_logic;
    link_in_slave_20_tready : out std_logic;

    link_in_master_21_tvalid : in std_logic;
    link_in_master_21_tdata : in std_logic_vector (63 downto 0);
    link_in_master_21_tuser : in std_logic_vector (7 downto 0);
    link_in_master_21_tlast : in std_logic;
    link_in_slave_21_tready : out std_logic;

    link_in_master_22_tvalid : in std_logic;
    link_in_master_22_tdata : in std_logic_vector (63 downto 0);
    link_in_master_22_tuser : in std_logic_vector (7 downto 0);
    link_in_master_22_tlast : in std_logic;
    link_in_slave_22_tready : out std_logic;

    link_in_master_23_tvalid : in std_logic;
    link_in_master_23_tdata : in std_logic_vector (63 downto 0);
    link_in_master_23_tuser : in std_logic_vector (7 downto 0);
    link_in_master_23_tlast : in std_logic;
    link_in_slave_23_tready : out std_logic;

    link_out_master_0_tvalid : out std_logic;
    link_out_master_0_tdata : out std_logic_vector (63 downto 0);
    link_out_master_0_tuser : out std_logic_vector (7 downto 0);
    link_out_master_0_tlast : out std_logic;
    link_out_slave_0_tready : in std_logic;

    link_out_master_1_tvalid : out std_logic;
    link_out_master_1_tdata : out std_logic_vector (63 downto 0);
    link_out_master_1_tuser : out std_logic_vector (7 downto 0);
    link_out_master_1_tlast : out std_logic;
    link_out_slave_1_tready : in std_logic;

    link_out_master_2_tvalid : out std_logic;
    link_out_master_2_tdata : out std_logic_vector (63 downto 0);
    link_out_master_2_tuser : out std_logic_vector (7 downto 0);
    link_out_master_2_tlast : out std_logic;
    link_out_slave_2_tready : in std_logic;

    link_out_master_3_tvalid : out std_logic;
    link_out_master_3_tdata : out std_logic_vector (63 downto 0);
    link_out_master_3_tuser : out std_logic_vector (7 downto 0);
    link_out_master_3_tlast : out std_logic;
    link_out_slave_3_tready : in std_logic;

    link_out_master_4_tvalid : out std_logic;
    link_out_master_4_tdata : out std_logic_vector (63 downto 0);
    link_out_master_4_tuser : out std_logic_vector (7 downto 0);
    link_out_master_4_tlast : out std_logic;
    link_out_slave_4_tready : in std_logic;

    link_out_master_5_tvalid : out std_logic;
    link_out_master_5_tdata : out std_logic_vector (63 downto 0);
    link_out_master_5_tuser : out std_logic_vector (7 downto 0);
    link_out_master_5_tlast : out std_logic;
    link_out_slave_5_tready : in std_logic;

    link_out_master_6_tvalid : out std_logic;
    link_out_master_6_tdata : out std_logic_vector (63 downto 0);
    link_out_master_6_tuser : out std_logic_vector (7 downto 0);
    link_out_master_6_tlast : out std_logic;
    link_out_slave_6_tready : in std_logic;

    link_out_master_7_tvalid : out std_logic;
    link_out_master_7_tdata : out std_logic_vector (63 downto 0);
    link_out_master_7_tuser : out std_logic_vector (7 downto 0);
    link_out_master_7_tlast : out std_logic;
    link_out_slave_7_tready : in std_logic;

    link_out_master_8_tvalid : out std_logic;
    link_out_master_8_tdata : out std_logic_vector (63 downto 0);
    link_out_master_8_tuser : out std_logic_vector (7 downto 0);
    link_out_master_8_tlast : out std_logic;
    link_out_slave_8_tready : in std_logic;

    link_out_master_9_tvalid : out std_logic;
    link_out_master_9_tdata : out std_logic_vector (63 downto 0);
    link_out_master_9_tuser : out std_logic_vector (7 downto 0);
    link_out_master_9_tlast : out std_logic;
    link_out_slave_9_tready : in std_logic;

    link_out_master_10_tvalid : out std_logic;
    link_out_master_10_tdata : out std_logic_vector (63 downto 0);
    link_out_master_10_tuser : out std_logic_vector (7 downto 0);
    link_out_master_10_tlast : out std_logic;
    link_out_slave_10_tready : in std_logic;

    link_out_master_11_tvalid : out std_logic;
    link_out_master_11_tdata : out std_logic_vector (63 downto 0);
    link_out_master_11_tuser : out std_logic_vector (7 downto 0);
    link_out_master_11_tlast : out std_logic;
    link_out_slave_11_tready : in std_logic;

    link_out_master_12_tvalid : out std_logic;
    link_out_master_12_tdata : out std_logic_vector (63 downto 0);
    link_out_master_12_tuser : out std_logic_vector (7 downto 0);
    link_out_master_12_tlast : out std_logic;
    link_out_slave_12_tready : in std_logic;

    link_out_master_13_tvalid : out std_logic;
    link_out_master_13_tdata : out std_logic_vector (63 downto 0);
    link_out_master_13_tuser : out std_logic_vector (7 downto 0);
    link_out_master_13_tlast : out std_logic;
    link_out_slave_13_tready : in std_logic;

    link_out_master_14_tvalid : out std_logic;
    link_out_master_14_tdata : out std_logic_vector (63 downto 0);
    link_out_master_14_tuser : out std_logic_vector (7 downto 0);
    link_out_master_14_tlast : out std_logic;
    link_out_slave_14_tready : in std_logic;

    link_out_master_15_tvalid : out std_logic;
    link_out_master_15_tdata : out std_logic_vector (63 downto 0);
    link_out_master_15_tuser : out std_logic_vector (7 downto 0);
    link_out_master_15_tlast : out std_logic;
    link_out_slave_15_tready : in std_logic;

    link_out_master_16_tvalid : out std_logic;
    link_out_master_16_tdata : out std_logic_vector (63 downto 0);
    link_out_master_16_tuser : out std_logic_vector (7 downto 0);
    link_out_master_16_tlast : out std_logic;
    link_out_slave_16_tready : in std_logic;

    link_out_master_17_tvalid : out std_logic;
    link_out_master_17_tdata : out std_logic_vector (63 downto 0);
    link_out_master_17_tuser : out std_logic_vector (7 downto 0);
    link_out_master_17_tlast : out std_logic;
    link_out_slave_17_tready : in std_logic;

    link_out_master_18_tvalid : out std_logic;
    link_out_master_18_tdata : out std_logic_vector (63 downto 0);
    link_out_master_18_tuser : out std_logic_vector (7 downto 0);
    link_out_master_18_tlast : out std_logic;
    link_out_slave_18_tready : in std_logic;

    link_out_master_19_tvalid : out std_logic;
    link_out_master_19_tdata : out std_logic_vector (63 downto 0);
    link_out_master_19_tuser : out std_logic_vector (7 downto 0);
    link_out_master_19_tlast : out std_logic;
    link_out_slave_19_tready : in std_logic;

    link_out_master_20_tvalid : out std_logic;
    link_out_master_20_tdata : out std_logic_vector (63 downto 0);
    link_out_master_20_tuser : out std_logic_vector (7 downto 0);
    link_out_master_20_tlast : out std_logic;
    link_out_slave_20_tready : in std_logic;

    link_out_master_21_tvalid : out std_logic;
    link_out_master_21_tdata : out std_logic_vector (63 downto 0);
    link_out_master_21_tuser : out std_logic_vector (7 downto 0);
    link_out_master_21_tlast : out std_logic;
    link_out_slave_21_tready : in std_logic;

    link_out_master_22_tvalid : out std_logic;
    link_out_master_22_tdata : out std_logic_vector (63 downto 0);
    link_out_master_22_tuser : out std_logic_vector (7 downto 0);
    link_out_master_22_tlast : out std_logic;
    link_out_slave_22_tready : in std_logic;

    link_out_master_23_tvalid : out std_logic;
    link_out_master_23_tdata : out std_logic_vector (63 downto 0);
    link_out_master_23_tuser : out std_logic_vector (7 downto 0);
    link_out_master_23_tlast : out std_logic;
    link_out_slave_23_tready : in std_logic

  );

end algo_top_sim_wrapper;

architecture rtl of algo_top_sim_wrapper is
  signal link_in_master : LinkMasterArrType(0 to N_INPUT_LINKS-1) := (others => LINK_MASTER_NULL_C);
  signal link_in_slave : LinkSlaveArrType(0 to N_INPUT_LINKS-1) := (others => LINK_SLAVE_NULL_C);
  signal link_out_master : LinkMasterArrType(0 to N_OUTPUT_LINKS-1) := (others => LINK_MASTER_NULL_C);
  signal link_out_slave : LinkSlaveArrType(0 to N_OUTPUT_LINKS-1) := (others => LINK_SLAVE_NULL_C);
begin

  u0_algo_top : entity work.algo_top_wrapper
  GENERIC MAP (
    N_INPUT_LINKS => N_INPUT_LINKS,
    N_OUTPUT_LINKS => N_OUTPUT_LINKS
  )
  PORT MAP (
    ap_clk => ap_clk,
    ap_rst => ap_rst,
    ap_start => ap_start,
    ap_done => ap_done,
    ap_idle => ap_idle,
    ap_ready => ap_ready,

    link_in_master => link_in_master,
    link_in_slave => link_in_slave,
    link_out_master => link_out_master,
    link_out_slave => link_out_slave
  );

  link_in_master(0).tValid <= link_in_master_0_tvalid;
  link_in_master(0).tData <= link_in_master_0_tdata;
  link_in_master(0).tUser <= link_in_master_0_tuser;
  link_in_master(0).tLast <= link_in_master_0_tlast;
  link_in_slave_0_tready <= link_in_slave(0).tReady;

  link_in_master(1).tValid <= link_in_master_1_tvalid;
  link_in_master(1).tData <= link_in_master_1_tdata;
  link_in_master(1).tUser <= link_in_master_1_tuser;
  link_in_master(1).tLast <= link_in_master_1_tlast;
  link_in_slave_1_tready <= link_in_slave(1).tReady;

  link_in_master(2).tValid <= link_in_master_2_tvalid;
  link_in_master(2).tData <= link_in_master_2_tdata;
  link_in_master(2).tUser <= link_in_master_2_tuser;
  link_in_master(2).tLast <= link_in_master_2_tlast;
  link_in_slave_2_tready <= link_in_slave(2).tReady;

  link_in_master(3).tValid <= link_in_master_3_tvalid;
  link_in_master(3).tData <= link_in_master_3_tdata;
  link_in_master(3).tUser <= link_in_master_3_tuser;
  link_in_master(3).tLast <= link_in_master_3_tlast;
  link_in_slave_3_tready <= link_in_slave(3).tReady;

  link_in_master(4).tValid <= link_in_master_4_tvalid;
  link_in_master(4).tData <= link_in_master_4_tdata;
  link_in_master(4).tUser <= link_in_master_4_tuser;
  link_in_master(4).tLast <= link_in_master_4_tlast;
  link_in_slave_4_tready <= link_in_slave(4).tReady;

  link_in_master(5).tValid <= link_in_master_5_tvalid;
  link_in_master(5).tData <= link_in_master_5_tdata;
  link_in_master(5).tUser <= link_in_master_5_tuser;
  link_in_master(5).tLast <= link_in_master_5_tlast;
  link_in_slave_5_tready <= link_in_slave(5).tReady;

  link_in_master(6).tValid <= link_in_master_6_tvalid;
  link_in_master(6).tData <= link_in_master_6_tdata;
  link_in_master(6).tUser <= link_in_master_6_tuser;
  link_in_master(6).tLast <= link_in_master_6_tlast;
  link_in_slave_6_tready <= link_in_slave(6).tReady;

  link_in_master(7).tValid <= link_in_master_7_tvalid;
  link_in_master(7).tData <= link_in_master_7_tdata;
  link_in_master(7).tUser <= link_in_master_7_tuser;
  link_in_master(7).tLast <= link_in_master_7_tlast;
  link_in_slave_7_tready <= link_in_slave(7).tReady;

  link_in_master(8).tValid <= link_in_master_8_tvalid;
  link_in_master(8).tData <= link_in_master_8_tdata;
  link_in_master(8).tUser <= link_in_master_8_tuser;
  link_in_master(8).tLast <= link_in_master_8_tlast;
  link_in_slave_8_tready <= link_in_slave(8).tReady;

  link_in_master(9).tValid <= link_in_master_9_tvalid;
  link_in_master(9).tData <= link_in_master_9_tdata;
  link_in_master(9).tUser <= link_in_master_9_tuser;
  link_in_master(9).tLast <= link_in_master_9_tlast;
  link_in_slave_9_tready <= link_in_slave(9).tReady;

  link_in_master(10).tValid <= link_in_master_10_tvalid;
  link_in_master(10).tData <= link_in_master_10_tdata;
  link_in_master(10).tUser <= link_in_master_10_tuser;
  link_in_master(10).tLast <= link_in_master_10_tlast;
  link_in_slave_10_tready <= link_in_slave(10).tReady;

  link_in_master(11).tValid <= link_in_master_11_tvalid;
  link_in_master(11).tData <= link_in_master_11_tdata;
  link_in_master(11).tUser <= link_in_master_11_tuser;
  link_in_master(11).tLast <= link_in_master_11_tlast;
  link_in_slave_11_tready <= link_in_slave(11).tReady;

  link_in_master(12).tValid <= link_in_master_12_tvalid;
  link_in_master(12).tData <= link_in_master_12_tdata;
  link_in_master(12).tUser <= link_in_master_12_tuser;
  link_in_master(12).tLast <= link_in_master_12_tlast;
  link_in_slave_12_tready <= link_in_slave(12).tReady;

  link_in_master(13).tValid <= link_in_master_13_tvalid;
  link_in_master(13).tData <= link_in_master_13_tdata;
  link_in_master(13).tUser <= link_in_master_13_tuser;
  link_in_master(13).tLast <= link_in_master_13_tlast;
  link_in_slave_13_tready <= link_in_slave(13).tReady;

  link_in_master(14).tValid <= link_in_master_14_tvalid;
  link_in_master(14).tData <= link_in_master_14_tdata;
  link_in_master(14).tUser <= link_in_master_14_tuser;
  link_in_master(14).tLast <= link_in_master_14_tlast;
  link_in_slave_14_tready <= link_in_slave(14).tReady;

  link_in_master(15).tValid <= link_in_master_15_tvalid;
  link_in_master(15).tData <= link_in_master_15_tdata;
  link_in_master(15).tUser <= link_in_master_15_tuser;
  link_in_master(15).tLast <= link_in_master_15_tlast;
  link_in_slave_15_tready <= link_in_slave(15).tReady;

  link_in_master(16).tValid <= link_in_master_16_tvalid;
  link_in_master(16).tData <= link_in_master_16_tdata;
  link_in_master(16).tUser <= link_in_master_16_tuser;
  link_in_master(16).tLast <= link_in_master_16_tlast;
  link_in_slave_16_tready <= link_in_slave(16).tReady;

  link_in_master(17).tValid <= link_in_master_17_tvalid;
  link_in_master(17).tData <= link_in_master_17_tdata;
  link_in_master(17).tUser <= link_in_master_17_tuser;
  link_in_master(17).tLast <= link_in_master_17_tlast;
  link_in_slave_17_tready <= link_in_slave(17).tReady;

  link_in_master(18).tValid <= link_in_master_18_tvalid;
  link_in_master(18).tData <= link_in_master_18_tdata;
  link_in_master(18).tUser <= link_in_master_18_tuser;
  link_in_master(18).tLast <= link_in_master_18_tlast;
  link_in_slave_18_tready <= link_in_slave(18).tReady;

  link_in_master(19).tValid <= link_in_master_19_tvalid;
  link_in_master(19).tData <= link_in_master_19_tdata;
  link_in_master(19).tUser <= link_in_master_19_tuser;
  link_in_master(19).tLast <= link_in_master_19_tlast;
  link_in_slave_19_tready <= link_in_slave(19).tReady;

  link_in_master(20).tValid <= link_in_master_20_tvalid;
  link_in_master(20).tData <= link_in_master_20_tdata;
  link_in_master(20).tUser <= link_in_master_20_tuser;
  link_in_master(20).tLast <= link_in_master_20_tlast;
  link_in_slave_20_tready <= link_in_slave(20).tReady;

  link_in_master(21).tValid <= link_in_master_21_tvalid;
  link_in_master(21).tData <= link_in_master_21_tdata;
  link_in_master(21).tUser <= link_in_master_21_tuser;
  link_in_master(21).tLast <= link_in_master_21_tlast;
  link_in_slave_21_tready <= link_in_slave(21).tReady;

  link_in_master(22).tValid <= link_in_master_22_tvalid;
  link_in_master(22).tData <= link_in_master_22_tdata;
  link_in_master(22).tUser <= link_in_master_22_tuser;
  link_in_master(22).tLast <= link_in_master_22_tlast;
  link_in_slave_22_tready <= link_in_slave(22).tReady;

  link_in_master(23).tValid <= link_in_master_23_tvalid;
  link_in_master(23).tData <= link_in_master_23_tdata;
  link_in_master(23).tUser <= link_in_master_23_tuser;
  link_in_master(23).tLast <= link_in_master_23_tlast;
  link_in_slave_23_tready <= link_in_slave(23).tReady;

  link_out_master_0_tvalid <= link_out_master(0).tValid;
  link_out_master_0_tdata <= link_out_master(0).tData;
  link_out_master_0_tuser <= link_out_master(0).tUser;
  link_out_master_0_tlast <= link_out_master(0).tLast;
  link_out_slave(0).tReady <= link_out_slave_0_tready;

  link_out_master_1_tvalid <= link_out_master(1).tValid;
  link_out_master_1_tdata <= link_out_master(1).tData;
  link_out_master_1_tuser <= link_out_master(1).tUser;
  link_out_master_1_tlast <= link_out_master(1).tLast;
  link_out_slave(1).tReady <= link_out_slave_1_tready;

  link_out_master_2_tvalid <= link_out_master(2).tValid;
  link_out_master_2_tdata <= link_out_master(2).tData;
  link_out_master_2_tuser <= link_out_master(2).tUser;
  link_out_master_2_tlast <= link_out_master(2).tLast;
  link_out_slave(2).tReady <= link_out_slave_2_tready;

  link_out_master_3_tvalid <= link_out_master(3).tValid;
  link_out_master_3_tdata <= link_out_master(3).tData;
  link_out_master_3_tuser <= link_out_master(3).tUser;
  link_out_master_3_tlast <= link_out_master(3).tLast;
  link_out_slave(3).tReady <= link_out_slave_3_tready;

  link_out_master_4_tvalid <= link_out_master(4).tValid;
  link_out_master_4_tdata <= link_out_master(4).tData;
  link_out_master_4_tuser <= link_out_master(4).tUser;
  link_out_master_4_tlast <= link_out_master(4).tLast;
  link_out_slave(4).tReady <= link_out_slave_4_tready;

  link_out_master_5_tvalid <= link_out_master(5).tValid;
  link_out_master_5_tdata <= link_out_master(5).tData;
  link_out_master_5_tuser <= link_out_master(5).tUser;
  link_out_master_5_tlast <= link_out_master(5).tLast;
  link_out_slave(5).tReady <= link_out_slave_5_tready;

  link_out_master_6_tvalid <= link_out_master(6).tValid;
  link_out_master_6_tdata <= link_out_master(6).tData;
  link_out_master_6_tuser <= link_out_master(6).tUser;
  link_out_master_6_tlast <= link_out_master(6).tLast;
  link_out_slave(6).tReady <= link_out_slave_6_tready;

  link_out_master_7_tvalid <= link_out_master(7).tValid;
  link_out_master_7_tdata <= link_out_master(7).tData;
  link_out_master_7_tuser <= link_out_master(7).tUser;
  link_out_master_7_tlast <= link_out_master(7).tLast;
  link_out_slave(7).tReady <= link_out_slave_7_tready;

  link_out_master_8_tvalid <= link_out_master(8).tValid;
  link_out_master_8_tdata <= link_out_master(8).tData;
  link_out_master_8_tuser <= link_out_master(8).tUser;
  link_out_master_8_tlast <= link_out_master(8).tLast;
  link_out_slave(8).tReady <= link_out_slave_8_tready;

  link_out_master_9_tvalid <= link_out_master(9).tValid;
  link_out_master_9_tdata <= link_out_master(9).tData;
  link_out_master_9_tuser <= link_out_master(9).tUser;
  link_out_master_9_tlast <= link_out_master(9).tLast;
  link_out_slave(9).tReady <= link_out_slave_9_tready;

  link_out_master_10_tvalid <= link_out_master(10).tValid;
  link_out_master_10_tdata <= link_out_master(10).tData;
  link_out_master_10_tuser <= link_out_master(10).tUser;
  link_out_master_10_tlast <= link_out_master(10).tLast;
  link_out_slave(10).tReady <= link_out_slave_10_tready;

  link_out_master_11_tvalid <= link_out_master(11).tValid;
  link_out_master_11_tdata <= link_out_master(11).tData;
  link_out_master_11_tuser <= link_out_master(11).tUser;
  link_out_master_11_tlast <= link_out_master(11).tLast;
  link_out_slave(11).tReady <= link_out_slave_11_tready;

  link_out_master_12_tvalid <= link_out_master(12).tValid;
  link_out_master_12_tdata <= link_out_master(12).tData;
  link_out_master_12_tuser <= link_out_master(12).tUser;
  link_out_master_12_tlast <= link_out_master(12).tLast;
  link_out_slave(12).tReady <= link_out_slave_12_tready;

  link_out_master_13_tvalid <= link_out_master(13).tValid;
  link_out_master_13_tdata <= link_out_master(13).tData;
  link_out_master_13_tuser <= link_out_master(13).tUser;
  link_out_master_13_tlast <= link_out_master(13).tLast;
  link_out_slave(13).tReady <= link_out_slave_13_tready;

  link_out_master_14_tvalid <= link_out_master(14).tValid;
  link_out_master_14_tdata <= link_out_master(14).tData;
  link_out_master_14_tuser <= link_out_master(14).tUser;
  link_out_master_14_tlast <= link_out_master(14).tLast;
  link_out_slave(14).tReady <= link_out_slave_14_tready;

  link_out_master_15_tvalid <= link_out_master(15).tValid;
  link_out_master_15_tdata <= link_out_master(15).tData;
  link_out_master_15_tuser <= link_out_master(15).tUser;
  link_out_master_15_tlast <= link_out_master(15).tLast;
  link_out_slave(15).tReady <= link_out_slave_15_tready;

  link_out_master_16_tvalid <= link_out_master(16).tValid;
  link_out_master_16_tdata <= link_out_master(16).tData;
  link_out_master_16_tuser <= link_out_master(16).tUser;
  link_out_master_16_tlast <= link_out_master(16).tLast;
  link_out_slave(16).tReady <= link_out_slave_16_tready;

  link_out_master_17_tvalid <= link_out_master(17).tValid;
  link_out_master_17_tdata <= link_out_master(17).tData;
  link_out_master_17_tuser <= link_out_master(17).tUser;
  link_out_master_17_tlast <= link_out_master(17).tLast;
  link_out_slave(17).tReady <= link_out_slave_17_tready;

  link_out_master_18_tvalid <= link_out_master(18).tValid;
  link_out_master_18_tdata <= link_out_master(18).tData;
  link_out_master_18_tuser <= link_out_master(18).tUser;
  link_out_master_18_tlast <= link_out_master(18).tLast;
  link_out_slave(18).tReady <= link_out_slave_18_tready;

  link_out_master_19_tvalid <= link_out_master(19).tValid;
  link_out_master_19_tdata <= link_out_master(19).tData;
  link_out_master_19_tuser <= link_out_master(19).tUser;
  link_out_master_19_tlast <= link_out_master(19).tLast;
  link_out_slave(19).tReady <= link_out_slave_19_tready;

  link_out_master_20_tvalid <= link_out_master(20).tValid;
  link_out_master_20_tdata <= link_out_master(20).tData;
  link_out_master_20_tuser <= link_out_master(20).tUser;
  link_out_master_20_tlast <= link_out_master(20).tLast;
  link_out_slave(20).tReady <= link_out_slave_20_tready;

  link_out_master_21_tvalid <= link_out_master(21).tValid;
  link_out_master_21_tdata <= link_out_master(21).tData;
  link_out_master_21_tuser <= link_out_master(21).tUser;
  link_out_master_21_tlast <= link_out_master(21).tLast;
  link_out_slave(21).tReady <= link_out_slave_21_tready;

  link_out_master_22_tvalid <= link_out_master(22).tValid;
  link_out_master_22_tdata <= link_out_master(22).tData;
  link_out_master_22_tuser <= link_out_master(22).tUser;
  link_out_master_22_tlast <= link_out_master(22).tLast;
  link_out_slave(22).tReady <= link_out_slave_22_tready;

  link_out_master_23_tvalid <= link_out_master(23).tValid;
  link_out_master_23_tdata <= link_out_master(23).tData;
  link_out_master_23_tuser <= link_out_master(23).tUser;
  link_out_master_23_tlast <= link_out_master(23).tLast;
  link_out_slave(23).tReady <= link_out_slave_23_tready;


end rtl;
