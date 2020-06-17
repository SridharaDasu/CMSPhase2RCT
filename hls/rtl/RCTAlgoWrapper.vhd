

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use ieee.numeric_std.all;

use work.StdRtlPkg.all;
use work.AxiStreamPkg.all;

entity RCTAlgoWrapper is
  generic (
    N_INPUT_STREAMS  : integer := 34;
    N_OUTPUT_STREAMS : integer := 4
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
    axiStreamOut : out AxiStreamMasterArray(0 to N_OUTPUT_STREAMS-1)
    );
end RCTAlgoWrapper;

architecture Behavioral of RCTAlgoWrapper is


  signal axiStreamOutInt   : AxiStreamMasterArray(0 to N_OUTPUT_STREAMS-1);
  signal axiStreamOutEta   : AxiStreamMasterArray(0 to N_OUTPUT_STREAMS-1);
  signal axiStreamOutPhiS1 : AxiStreamMasterArray(0 to N_OUTPUT_STREAMS-1);
  signal axiStreamOutPhiS2 : AxiStreamMasterArray(0 to N_OUTPUT_STREAMS-1);

  signal algoRstD1, algoRstD1n : sl;

  signal algoStartD1 : sl;

  attribute max_fanout                           : integer;
  attribute max_fanout of algoRstD1, algoStartD1 : signal is 1;


  component algo_top
    port (
      ap_clk            : in  std_logic;
      ap_rst_n          : in  std_logic;
      ap_start          : in  std_logic;
      ap_done           : out std_logic;
      ap_idle           : out std_logic;
      ap_ready          : out std_logic;
      link_out_0_TREADY : in  std_logic;
      link_out_1_TREADY : in  std_logic;
      link_out_2_TREADY : in  std_logic;
      link_out_3_TREADY : in  std_logic;
      link_in_0_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_0_TVALID  : in  std_logic;
      link_in_0_TREADY  : out std_logic;
      link_in_1_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_1_TVALID  : in  std_logic;
      link_in_1_TREADY  : out std_logic;
      link_in_2_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_2_TVALID  : in  std_logic;
      link_in_2_TREADY  : out std_logic;
      link_in_3_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_3_TVALID  : in  std_logic;
      link_in_3_TREADY  : out std_logic;
      link_in_4_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_4_TVALID  : in  std_logic;
      link_in_4_TREADY  : out std_logic;
      link_in_5_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_5_TVALID  : in  std_logic;
      link_in_5_TREADY  : out std_logic;
      link_in_6_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_6_TVALID  : in  std_logic;
      link_in_6_TREADY  : out std_logic;
      link_in_7_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_7_TVALID  : in  std_logic;
      link_in_7_TREADY  : out std_logic;
      link_in_8_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_8_TVALID  : in  std_logic;
      link_in_8_TREADY  : out std_logic;
      link_in_9_TDATA   : in  std_logic_vector (383 downto 0);
      link_in_9_TVALID  : in  std_logic;
      link_in_9_TREADY  : out std_logic;
      link_in_10_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_10_TVALID : in  std_logic;
      link_in_10_TREADY : out std_logic;
      link_in_11_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_11_TVALID : in  std_logic;
      link_in_11_TREADY : out std_logic;
      link_in_12_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_12_TVALID : in  std_logic;
      link_in_12_TREADY : out std_logic;
      link_in_13_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_13_TVALID : in  std_logic;
      link_in_13_TREADY : out std_logic;
      link_in_14_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_14_TVALID : in  std_logic;
      link_in_14_TREADY : out std_logic;
      link_in_15_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_15_TVALID : in  std_logic;
      link_in_15_TREADY : out std_logic;
      link_in_16_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_16_TVALID : in  std_logic;
      link_in_16_TREADY : out std_logic;
      link_in_17_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_17_TVALID : in  std_logic;
      link_in_17_TREADY : out std_logic;
      link_in_18_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_18_TVALID : in  std_logic;
      link_in_18_TREADY : out std_logic;
      link_in_19_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_19_TVALID : in  std_logic;
      link_in_19_TREADY : out std_logic;
      link_in_20_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_20_TVALID : in  std_logic;
      link_in_20_TREADY : out std_logic;
      link_in_21_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_21_TVALID : in  std_logic;
      link_in_21_TREADY : out std_logic;
      link_in_22_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_22_TVALID : in  std_logic;
      link_in_22_TREADY : out std_logic;
      link_in_23_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_23_TVALID : in  std_logic;
      link_in_23_TREADY : out std_logic;
      link_in_24_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_24_TVALID : in  std_logic;
      link_in_24_TREADY : out std_logic;
      link_in_25_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_25_TVALID : in  std_logic;
      link_in_25_TREADY : out std_logic;
      link_in_26_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_26_TVALID : in  std_logic;
      link_in_26_TREADY : out std_logic;
      link_in_27_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_27_TVALID : in  std_logic;
      link_in_27_TREADY : out std_logic;
      link_in_28_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_28_TVALID : in  std_logic;
      link_in_28_TREADY : out std_logic;
      link_in_29_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_29_TVALID : in  std_logic;
      link_in_29_TREADY : out std_logic;
      link_in_30_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_30_TVALID : in  std_logic;
      link_in_30_TREADY : out std_logic;
      link_in_31_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_31_TVALID : in  std_logic;
      link_in_31_TREADY : out std_logic;
      link_in_32_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_32_TVALID : in  std_logic;
      link_in_32_TREADY : out std_logic;
      link_in_33_TDATA  : in  std_logic_vector (383 downto 0);
      link_in_33_TVALID : in  std_logic;
      link_in_33_TREADY : out std_logic;
      link_in_0_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_1_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_2_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_3_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_4_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_5_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_6_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_7_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_8_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_9_TUSER   : in  std_logic_vector (7 downto 0);
      link_in_10_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_11_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_12_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_13_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_14_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_15_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_16_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_17_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_18_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_19_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_20_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_21_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_22_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_23_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_24_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_25_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_26_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_27_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_28_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_29_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_30_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_31_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_32_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_33_TUSER  : in  std_logic_vector (7 downto 0);
      link_in_0_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_1_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_2_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_3_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_4_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_5_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_6_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_7_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_8_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_9_TLAST   : in  std_logic_vector (0 downto 0);
      link_in_10_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_11_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_12_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_13_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_14_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_15_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_16_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_17_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_18_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_19_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_20_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_21_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_22_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_23_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_24_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_25_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_26_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_27_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_28_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_29_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_30_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_31_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_32_TLAST  : in  std_logic_vector (0 downto 0);
      link_in_33_TLAST  : in  std_logic_vector (0 downto 0);
      link_out_0_TDATA  : out std_logic_vector (383 downto 0);
      link_out_0_TVALID : out std_logic;
      link_out_1_TDATA  : out std_logic_vector (383 downto 0);
      link_out_1_TVALID : out std_logic;
      link_out_2_TDATA  : out std_logic_vector (383 downto 0);
      link_out_2_TVALID : out std_logic;
      link_out_3_TDATA  : out std_logic_vector (383 downto 0);
      link_out_3_TVALID : out std_logic;
      link_out_0_TUSER  : out std_logic_vector (7 downto 0);
      link_out_1_TUSER  : out std_logic_vector (7 downto 0);
      link_out_2_TUSER  : out std_logic_vector (7 downto 0);
      link_out_3_TUSER  : out std_logic_vector (7 downto 0);
      link_out_0_TLAST  : out std_logic_vector (0 downto 0);
      link_out_1_TLAST  : out std_logic_vector (0 downto 0);
      link_out_2_TLAST  : out std_logic_vector (0 downto 0);
      link_out_3_TLAST  : out std_logic_vector (0 downto 0));
  end component;

  type t_cyc_6_arr is array(integer range <>) of integer range 0 to 5;
  type t_slv_384_arr is array(integer range <>) of std_logic_vector(383 downto 0);


  signal link_in  : t_slv_384_arr(N_INPUT_STREAMS-1 downto 0);
  signal link_out : t_slv_384_arr(N_OUTPUT_STREAMS-1 downto 0);

  signal link_in_reg  : t_slv_384_arr(N_INPUT_STREAMS-1 downto 0);
  signal link_out_reg : t_slv_384_arr(N_OUTPUT_STREAMS-1 downto 0);

  signal link_out_tlast         : std_logic_vector(N_OUTPUT_STREAMS-1 downto 0);
  signal link_out_tlast_latched : std_logic_vector(N_OUTPUT_STREAMS-1 downto 0);

  signal in_cyc  : t_cyc_6_arr(N_INPUT_STREAMS-1 downto 0);
  signal out_cyc : t_cyc_6_arr(N_OUTPUT_STREAMS-1 downto 0);




begin

  algoRstD1   <= algoRst   when rising_edge(algoClk);
  algoRstD1n  <= not algoRstD1;
  algoStartD1 <= algoStart when rising_edge(algoClk);

--  gen_Ecal : for i in 0 to N_INPUT_STREAMS-1 generate
--
--    U_ecalWrapper : entity work.ecalWrapper
--      port map(
--        algoClk   => algoClk,
--        algoRst   => algoRstD1,
--        algoStart => algoStartD1,
--        algoDone  => open,
--        algoIdle  => open,
--        algoReady => open,
--
--        -- AXI-Stream In/Out Ports
--        axiStreamIn  => axiStreamIn(i),
--        axiStreamOut => axiStreamOutInt(i)
--        );
--
--  end generate;




  gen_cyc_in : for idx in 0 to N_INPUT_STREAMS-1 generate
    process(algoClk) is
    begin
      if rising_edge(algoClk) then


        if (algoRst = '1') then
          in_cyc(idx) <= 0;
        else
          in_cyc(idx) <= in_cyc(idx) + 1;
          if (in_cyc(idx) = 5) then
            in_cyc(idx) <= 0;
          end if;
        end if;

        if (in_cyc(idx) = 0) then 
            link_in(idx)(63 downto 0)    <= axiStreamIn(idx).tdata(63 downto 0); 
        end if;

        if (in_cyc(idx) = 1) then 
            link_in(idx)(127 downto 64)  <= axiStreamIn(idx).tdata(63 downto 0); 
        end if;

        if (in_cyc(idx) = 2) then 
            link_in(idx)(191 downto 128)  <= axiStreamIn(idx).tdata(63 downto 0); 
        end if;

        if (in_cyc(idx) = 3) then 
            link_in(idx)(255 downto 192)  <= axiStreamIn(idx).tdata(63 downto 0); 
        end if;

        if (in_cyc(idx) = 4) then 
            link_in(idx)(319 downto 256)  <= axiStreamIn(idx).tdata(63 downto 0); 
        end if;

        if (in_cyc(idx) = 5) then 
            link_in_reg(idx)(63 downto 0) <= link_in(idx)(63 downto 0);
            link_in_reg(idx)(127 downto 64) <= link_in(idx)(127 downto 64);
            link_in_reg(idx)(191 downto 128) <= link_in(idx)(191 downto 128);
            link_in_reg(idx)(255 downto 192) <= link_in(idx)(255 downto 192);
            link_in_reg(idx)(319 downto 256) <= link_in(idx)(319 downto 256);
            link_in_reg(idx)(383 downto 320) <= axiStreamIn(idx).tdata(63 downto 0); 
        end if;

      end if;
    end process;
  end generate;


  gen_cyc_out : for idx in 0 to N_OUTPUT_STREAMS-1 generate
    process(algoClk) is
    begin
      if rising_edge(algoClk) then

        if (link_out_tlast(idx) = '1') then
          link_out_reg(idx) <= link_out(idx);
        end if;

   
        if (algoRstD1 = '1') then
          link_out_tlast_latched(idx) <= '0';
        elsif (link_out_tlast(idx) = '1') then
          link_out_tlast_latched(idx) <= '1';
        end if;

        if (link_out_tlast_latched(idx) = '0') then
          out_cyc(idx)                <= 0;
          axiStreamOut(idx).tvalid <= '0';
        else
          axiStreamOut(idx).tvalid <= '1';
          out_cyc(idx)                <= out_cyc(idx) + 1;
          if (out_cyc(idx) = 5) then
            out_cyc(idx) <= 0;
          end if;
        end if;

        if (out_cyc(idx) = 0) then axiStreamOut(idx).tdata(63 downto 0) <= link_out_reg(idx)(63 downto 0); end if;
        if (out_cyc(idx) = 1) then axiStreamOut(idx).tdata(63 downto 0) <= link_out_reg(idx)(127 downto 64); end if;
        if (out_cyc(idx) = 2) then axiStreamOut(idx).tdata(63 downto 0) <= link_out_reg(idx)(191 downto 128); end if;
        if (out_cyc(idx) = 3) then axiStreamOut(idx).tdata(63 downto 0) <= link_out_reg(idx)(255 downto 192); end if;
        if (out_cyc(idx) = 4) then axiStreamOut(idx).tdata(63 downto 0) <= link_out_reg(idx)(319 downto 256); end if;
        if (out_cyc(idx) = 5) then axiStreamOut(idx).tdata(63 downto 0) <= link_out_reg(idx)(383 downto 320); end if;


      end if;
    end process;
  end generate;

  i_algo_top : algo_top
    port map (
      ap_clk            => algoClk,
      ap_rst_n          => algoRstD1n,
      ap_start          => algoStartD1,
      ap_done           => algoDone,
      ap_idle           => algoIdle,
      ap_ready          => algoReady,
      link_out_0_TREADY => '1',
      link_out_1_TREADY => '1',
      link_out_2_TREADY => '1',
      link_out_3_TREADY => '1',
      
      link_out_0_TDATA  => link_out(0),
      link_out_1_TDATA  => link_out(1),
      link_out_2_TDATA  => link_out(2),
      link_out_3_TDATA  => link_out(3),
      
      link_out_0_TVALID => open,
      link_out_1_TVALID => open,
      link_out_2_TVALID => open,
      link_out_3_TVALID => open,
      
      link_out_0_TLAST(0)  => link_out_tlast(0),
      link_out_1_TLAST(0)  => link_out_tlast(1),
      link_out_2_TLAST(0)  => link_out_tlast(2),
      link_out_3_TLAST(0)  => link_out_tlast(3),
      
      link_out_0_TUSER => open,
      link_out_1_TUSER => open,
      link_out_2_TUSER => open,
      link_out_3_TUSER => open,


      link_in_0_TREADY  => open,
      link_in_1_TREADY  => open,
      link_in_2_TREADY  => open,
      link_in_3_TREADY  => open,
      link_in_4_TREADY  => open,
      link_in_5_TREADY  => open,
      link_in_6_TREADY  => open,
      link_in_7_TREADY  => open,
      link_in_8_TREADY  => open,
      link_in_9_TREADY  => open,
      link_in_10_TREADY => open,
      link_in_11_TREADY => open,
      link_in_12_TREADY => open,
      link_in_13_TREADY => open,
      link_in_14_TREADY => open,
      link_in_15_TREADY => open,
      link_in_16_TREADY => open,
      link_in_17_TREADY => open,
      link_in_18_TREADY => open,
      link_in_19_TREADY => open,
      link_in_20_TREADY => open,
      link_in_21_TREADY => open,
      link_in_22_TREADY => open,
      link_in_23_TREADY => open,
      link_in_24_TREADY => open,
      link_in_25_TREADY => open,
      link_in_26_TREADY => open,
      link_in_27_TREADY => open,
      link_in_28_TREADY => open,
      link_in_29_TREADY => open,
      link_in_30_TREADY => open,
      link_in_31_TREADY => open,
      link_in_32_TREADY => open,
      link_in_33_TREADY => open,

      link_in_0_TDATA  => link_in_reg(0),
      link_in_1_TDATA  => link_in_reg(1),
      link_in_2_TDATA  => link_in_reg(2),
      link_in_3_TDATA  => link_in_reg(3),
      link_in_4_TDATA  => link_in_reg(4),
      link_in_5_TDATA  => link_in_reg(5),
      link_in_6_TDATA  => link_in_reg(6),
      link_in_7_TDATA  => link_in_reg(7),
      link_in_8_TDATA  => link_in_reg(8),
      link_in_9_TDATA  => link_in_reg(9),
      link_in_10_TDATA => link_in_reg(10),
      link_in_11_TDATA => link_in_reg(11),
      link_in_12_TDATA => link_in_reg(12),
      link_in_13_TDATA => link_in_reg(13),
      link_in_14_TDATA => link_in_reg(14),
      link_in_15_TDATA => link_in_reg(15),
      link_in_16_TDATA => link_in_reg(16),
      link_in_17_TDATA => link_in_reg(17),
      link_in_18_TDATA => link_in_reg(18),
      link_in_19_TDATA => link_in_reg(19),
      link_in_20_TDATA => link_in_reg(20),
      link_in_21_TDATA => link_in_reg(21),
      link_in_22_TDATA => link_in_reg(22),
      link_in_23_TDATA => link_in_reg(23),
      link_in_24_TDATA => link_in_reg(24),
      link_in_25_TDATA => link_in_reg(25),
      link_in_26_TDATA => link_in_reg(26),
      link_in_27_TDATA => link_in_reg(27),
      link_in_28_TDATA => link_in_reg(28),
      link_in_29_TDATA => link_in_reg(29),
      link_in_30_TDATA => link_in_reg(30),
      link_in_31_TDATA => link_in_reg(31),
      link_in_32_TDATA => link_in_reg(32),
      link_in_33_TDATA => link_in_reg(33),

      link_in_0_TVALID  => '1',
      link_in_1_TVALID  => '1',
      link_in_2_TVALID  => '1',
      link_in_3_TVALID  => '1',
      link_in_4_TVALID  => '1',
      link_in_5_TVALID  => '1',
      link_in_6_TVALID  => '1',
      link_in_7_TVALID  => '1',
      link_in_8_TVALID  => '1',
      link_in_9_TVALID  => '1',
      link_in_10_TVALID => '1',
      link_in_11_TVALID => '1',
      link_in_12_TVALID => '1',
      link_in_13_TVALID => '1',
      link_in_14_TVALID => '1',
      link_in_15_TVALID => '1',
      link_in_16_TVALID => '1',
      link_in_17_TVALID => '1',
      link_in_18_TVALID => '1',
      link_in_19_TVALID => '1',
      link_in_20_TVALID => '1',
      link_in_21_TVALID => '1',
      link_in_22_TVALID => '1',
      link_in_23_TVALID => '1',
      link_in_24_TVALID => '1',
      link_in_25_TVALID => '1',
      link_in_26_TVALID => '1',
      link_in_27_TVALID => '1',
      link_in_28_TVALID => '1',
      link_in_29_TVALID => '1',
      link_in_30_TVALID => '1',
      link_in_31_TVALID => '1',
      link_in_32_TVALID => '1',
      link_in_33_TVALID => '1',

      link_in_0_TLAST  => "0", 
      link_in_1_TLAST  => "0", 
      link_in_2_TLAST  => "0", 
      link_in_3_TLAST  => "0", 
      link_in_4_TLAST  => "0", 
      link_in_5_TLAST  => "0", 
      link_in_6_TLAST  => "0", 
      link_in_7_TLAST  => "0", 
      link_in_8_TLAST  => "0", 
      link_in_9_TLAST  => "0", 
      link_in_10_TLAST => "0", 
      link_in_11_TLAST => "0", 
      link_in_12_TLAST => "0", 
      link_in_13_TLAST => "0", 
      link_in_14_TLAST => "0", 
      link_in_15_TLAST => "0", 
      link_in_16_TLAST => "0", 
      link_in_17_TLAST => "0", 
      link_in_18_TLAST => "0", 
      link_in_19_TLAST => "0", 
      link_in_20_TLAST => "0", 
      link_in_21_TLAST => "0", 
      link_in_22_TLAST => "0", 
      link_in_23_TLAST => "0", 
      link_in_24_TLAST => "0", 
      link_in_25_TLAST => "0", 
      link_in_26_TLAST => "0", 
      link_in_27_TLAST => "0", 
      link_in_28_TLAST => "0", 
      link_in_29_TLAST => "0", 
      link_in_30_TLAST => "0", 
      link_in_31_TLAST => "0", 
      link_in_32_TLAST => "0", 
      link_in_33_TLAST => "0",
      
      
      link_in_0_TUSER => x"00",
      link_in_1_TUSER => x"00",
      link_in_2_TUSER => x"00",
      link_in_3_TUSER => x"00",
      link_in_4_TUSER => x"00",
      link_in_5_TUSER => x"00",
      link_in_6_TUSER => x"00",
      link_in_7_TUSER => x"00",
      link_in_8_TUSER => x"00",
      link_in_9_TUSER => x"00",
      link_in_10_TUSER => x"00",
      link_in_11_TUSER => x"00",
      link_in_12_TUSER => x"00",
      link_in_13_TUSER => x"00",
      link_in_14_TUSER => x"00",
      link_in_15_TUSER => x"00",
      link_in_16_TUSER => x"00",
      link_in_17_TUSER => x"00",
      link_in_18_TUSER => x"00",
      link_in_19_TUSER => x"00",
      link_in_20_TUSER => x"00",
      link_in_21_TUSER => x"00",
      link_in_22_TUSER => x"00",
      link_in_23_TUSER => x"00",
      link_in_24_TUSER => x"00",
      link_in_25_TUSER => x"00",
      link_in_26_TUSER => x"00",
      link_in_27_TUSER => x"00",
      link_in_28_TUSER => x"00",
      link_in_29_TUSER => x"00",
      link_in_30_TUSER => x"00",
      link_in_31_TUSER => x"00",
      link_in_32_TUSER => x"00",
      link_in_33_TUSER => x"00"
      );
end Behavioral;
