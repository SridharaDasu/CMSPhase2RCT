library ieee;
use ieee.std_logic_1164.all;

package algo_pkg is

  type LinkMasterType is record
    tValid : std_logic;
    tData  : std_logic_vector(63 downto 0);
    tUser  : std_logic_vector(7 downto 0);
    tLast  : std_logic;
  end record LinkMasterType;
  
  type LinkSlaveType is record
    tReady : std_logic;
  end record LinkSlaveType;

  constant LINK_MASTER_NULL_C : LinkMasterType := (
    tValid => '0',
    tData  => (others => '0'),
    tUser  => (others => '0'),
    tLast  => '0'
    );

  constant LINK_SLAVE_NULL_C : LinkSlaveType := (
    tReady => '0'
    );

  type LinkMasterArrType is array (natural range<>) of LinkMasterType;
  type LinkSlaveArrType is array (natural range<>) of LinkSlaveType;

end package;
