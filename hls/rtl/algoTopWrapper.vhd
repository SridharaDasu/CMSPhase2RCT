library IEEE;
use IEEE.STD_LOGIC_1164.all;
use ieee.numeric_std.all;

use work.StdRtlPkg.all;
use work.AxiStreamPkg.all;

entity algoTopWrapper is
  generic (
    N_INPUT_STREAMS  : integer := 96;
    N_OUTPUT_STREAMS : integer := 96
    );
  port (
    -- Algo Control/Status Signals
    algoClk   : in  sl;
    algoRst   : in  sl;
    algoStart : in  sl;
    algoDone  : out sl := '0';
    algoIdle  : out sl := '0';
    algoReady : out sl := '0';

    -- AXI-Stream In/Out Ports
    axiStreamIn  : in  AxiStreamMasterArray(0 to N_INPUT_STREAMS-1);
    axiStreamOut : out AxiStreamMasterArray(0 to N_OUTPUT_STREAMS-1) := (others => AXI_STREAM_MASTER_INIT_C)
    );
end algoTopWrapper;

architecture rtl of algoTopWrapper is

  constant N_INPUT_STREAMS_XLA  : integer := 34;
  constant N_OUTPUT_STREAMS_XLA : integer := 4;

  signal axiStreamInXLA0  : AxiStreamMasterArray(0 to N_INPUT_STREAMS_XLA-1);
  signal axiStreamOutXLA0 : AxiStreamMasterArray(0 to N_OUTPUT_STREAMS_XLA-1);

  signal axiStreamInXLA1  : AxiStreamMasterArray(0 to N_INPUT_STREAMS_XLA-1);
  signal axiStreamOutXLA1 : AxiStreamMasterArray(0 to N_OUTPUT_STREAMS_XLA-1);

  signal algoRstD1   : sl;
  signal algoStartD1 : sl;

  constant XLA0_INPUT_MAP_C : IntegerArray(0 to N_INPUT_STREAMS_XLA-1) := (
    0  => 28,
    1  => 29,
    2  => 30,
    3  => 31,
    4  => 32,
    5  => 33,
    6  => 34,
    7  => 35,
    8  => 36,
    9  => 37,
    10 => 38,
    11 => 39,
    12 => 40,
    13 => 41,
    14 => 42,
    15 => 43,
    16 => 44,
    17 => 45,
    18 => 46,
    19 => 47,
    20 => 76,
    21 => 77,
    22 => 78,
    23 => 79,
    24 => 80,
    25 => 81,
    26 => 82,
    27 => 83,
    28 => 84,
    29 => 85,
    30 => 86,
    31 => 87,
    32 => 88,
    33 => 89
    );

  constant XLA0_OUTPUT_MAP_C : IntegerArray(0 to N_OUTPUT_STREAMS_XLA-1) := (
    0  => 28,
    1  => 29,
    2  => 30,
    3  => 31
    );

  constant XLA1_INPUT_MAP_C : IntegerArray(0 to N_INPUT_STREAMS_XLA-1) := (
    0  => 12,
    1  => 13,
    2  => 14,
    3  => 15,
    4  => 16,
    5  => 17,
    6  => 18,
    7  => 19,
    8  => 20,
    9  => 21,
    10 => 22,
    11 => 23,
    12 => 24,
    13 => 25,
    14 => 26,
    15 => 27,
    16 => 56,
    17 => 57,
    18 => 58,
    19 => 59,
    20 => 60,
    21 => 61,
    22 => 62,
    23 => 63,
    24 => 64,
    25 => 65,
    26 => 66,
    27 => 67,
    28 => 68,
    29 => 69,
    30 => 70,
    31 => 71,
    32 => 72,
    33 => 73
    );

  constant XLA1_OUTPUT_MAP_C : IntegerArray(0 to N_OUTPUT_STREAMS_XLA-1) := (
    0  => 12,
    1  => 13,
    2  => 14,
    3  => 15
    );

begin

  algoRstD1   <= algoRst   when rising_edge(algoClk);
  algoStartD1 <= algoStart when rising_edge(algoClk);

  gen_XlaInputMapping : for i in 0 to N_INPUT_STREAMS_XLA-1 generate
    axiStreamInXLA0(i) <= axiStreamIn(XLA0_INPUT_MAP_C(i));
    axiStreamInXLA1(i) <= axiStreamIn(XLA1_INPUT_MAP_C(i));
  end generate;


  gen_XlaOutputMapping : for i in 0 to N_OUTPUT_STREAMS_XLA-1 generate
    axiStreamOut(XLA0_OUTPUT_MAP_C(i)) <= axiStreamOutXLA0(i);
    axiStreamOut(XLA1_OUTPUT_MAP_C(i)) <= axiStreamOutXLA1(i);
  end generate;

  U_RCTAlgoWrapper_0 : entity work.RCTAlgoWrapper
    generic map(
      N_INPUT_STREAMS  => N_INPUT_STREAMS_XLA,
      N_OUTPUT_STREAMS => N_OUTPUT_STREAMS_XLA
      )
    port map (
      -- Algo Control/Status Signals
      algoClk   => algoClk,
      algoRst   => algoRstD1,
      algoStart => algoStartD1,
      algoDone  => open,
      algoIdle  => open,
      algoReady => open,

      axiStreamIn  => axiStreamInXLA0,
      axiStreamOut => axiStreamOutXLA0
      );

  U_RCTAlgoWrapper_1 : entity work.RCTAlgoWrapper
    generic map(
      N_INPUT_STREAMS  => N_INPUT_STREAMS_XLA,
      N_OUTPUT_STREAMS => N_OUTPUT_STREAMS_XLA
      )
    port map (
      -- Algo Control/Status Signals
      algoClk   => algoClk,
      algoRst   => algoRstD1,
      algoStart => algoStartD1,
      algoDone  => open,
      algoIdle  => open,
      algoReady => open,

      axiStreamIn  => axiStreamInXLA1,
      axiStreamOut => axiStreamOutXLA1
      );

end rtl;
