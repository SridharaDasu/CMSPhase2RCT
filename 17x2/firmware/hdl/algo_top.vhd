library IEEE;
use IEEE.STD_LOGIC_1164.all;
use ieee.numeric_std.all;

use work.algo_pkg.all;

entity algo_top is
  port (
    ap_clk   : in  std_logic;
    ap_rst   : in  std_logic;
    ap_start : in  std_logic;
    ap_done  : out std_logic;
    ap_idle  : out std_logic;
    ap_ready : out std_logic;

    -- Input Links 
    link_in_master : in  LinkMasterArrType(0 to 23);
    --link_in_slave  : out LinkSlaveArrType(0 downto 0);

    -- Output Links 
    link_out_master : out LinkMasterArrType(0 to 23)
   -- link_out_slave  : in  LinkSlaveArrType(0 downto 0)
    );

end algo_top;

architecture rtl of algo_top is

begin
    link_out_master(0) <= link_in_master(0);
    --link_in_slave(0) <= link_out_slave(0);

end architecture rtl;