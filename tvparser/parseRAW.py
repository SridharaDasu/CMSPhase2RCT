import os
from sys import argv

def RCTwriteLINK(output,links):
    """
    Write RCT link to file
    """
    with open(output,'w') as f:
        f.write("=====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================\n")
        f.write("WordCnt             LINK_00               LINK_01               LINK_02               LINK_03               LINK_04               LINK_05               LINK_06               LINK_07               LINK_08               LINK_09               LINK_10               LINK_11               LINK_12               LINK_13               LINK_14               LINK_15               LINK_16               LINK_17               LINK_18               LINK_19               LINK_20               LINK_21               LINK_22               LINK_23               LINK_24               LINK_25               LINK_26               LINK_27               LINK_28               LINK_29               LINK_30               LINK_31               LINK_32               LINK_33               LINK_34               LINK_35               LINK_36               LINK_37               LINK_38               LINK_39               LINK_40               LINK_41               LINK_42               LINK_43               LINK_44               LINK_45               LINK_46               LINK_47\n")
        f.write("#BeginData\n")
        for i in range(3):
            line = '0x'+str(hex(i))[2:].zfill(4)+"   "
            for link in links:
                line += link[i]+"    "
            f.write(line+"\n")
####################################################
def RCTparseRAW(input):
    """
    Parse out raw RCT input into link form
            
            <02><01><00><  >
    Link -> <06><05><04><03>
            <10><09><08><07>
    """
    output = 'data/'+input.split("/")[-1].replace('_raw','')
    with open(input,'r') as f: text = f.readlines()
    text.reverse()
    grid = [line.split() for line in text]
    crystals = []
    bunch = [0]
    for tEta in range(5):
        for tPhi in range(4):
            for pEta in range(5):
                for pPhi in range(5):
                    x = pPhi + tPhi*5
                    y = pEta + tEta*5
                    bunch.append(int(grid[y][x]))
                    if len(bunch) == 12:
                        crystals.append(bunch)
                        bunch = [0]
    ##########################################
    while len(crystals) != 48: crystals.append([0]*12)
    links = []
    for bunch in crystals:
        links.append([])
        for r in ((0,4),(4,8),(8,12)):
            entry = ''
            for et in bunch[r[0]:r[1]]:
                val = str(hex(et))[2:].zfill(4)
                entry = val + entry
            entry = entry.zfill(16)
            links[-1].append('0x'+entry)
            
    RCTwriteLINK(output,links)

################################################################

for input in argv[1:]: RCTparseRAW(input)
