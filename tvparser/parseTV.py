import os
from argparse import ArgumentParser
import math

T_ETA,T_PHI = 17,2
C_ETA,C_PHI = 5,5
class Crystal:
    def __init__(self,binary,eta=None,phi=None):
        # self.binary = binary
        self.energy = int( binary[4:14],2 )
        self.timing = int( binary[1:4],2 )
        self.spike = int( binary[:1] )
        self.eta = eta
        self.phi = phi
    def __str__(self): return "({energy},{timing},{spike},{eta},{phi})".format(**vars(self))
    def binary(self): return "{0:01b}".format(self.spike)+"{0:03b}".format(self.timing)+"{0:010b}".format(self.energy)
class Tower:
    def __init__(self,word):
        self.words = []
        self.add(word)
    def add(self,word): self.words.append("{0:064b}".format(int(word,16)))
    def process(self,eta=0,phi=0):
        self.eta = eta
        self.phi = phi
        
        self.crystals = []
        # some crystals are split between words, merge words together to recover
        binary = ""
        for word in self.words: binary = word + binary
        # only 25 clusters are kept in a link, last 34 bits are empty
        binary = binary[34:]
        nbits = len(binary)
        ncrystals = nbits/14
        for i in range(ncrystals):
            lo = nbits - 14*i
            hi = nbits - 14*(i+1)
            phi = i%5
            eta = i/5
            crystal = Crystal(binary[hi:lo],eta,phi)
            self.crystals.append(crystal)
    def unwrap(self): return self.crystals
    def __str__(self):
        return "Tower: ({eta},{phi})\n".format(**vars(self)) + "\n".join( "\tCrystal: %s"%crystal for crystal in self.crystals if crystal.energy > 0) + '\n'
    def link(self):
        words = []
        binary = ""
        for crystal in self.crystals:
            binary = crystal.binary() + binary

        add_word = lambda word : words.append("0x"+"{0:016x}".format(int(word,2)))
        word = ""
        for bit in reversed(binary):
            if len(word) < 64: word = bit + word
            else:
                add_word(word)
                word = ""
        while len(words) < 6: add_word("0")
        return words
class InputTV:
    def __init__(self,fname):
        self.fname = fname
        with open(fname,"r") as f: rawinput = [line.strip() for line in f.readlines() if "#" not in line and any(line.strip())]

        self.towers = []
        for iline,line in enumerate(rawinput):
            data = line.split(" 0x00 ")[1:]
            if iline == 0:
                self.ntowers = len(data)
                for tower in data: self.towers.append( Tower(tower) )
            else:
                for itower,tower in enumerate(data): self.towers[itower].add(tower)
        for i,tower in enumerate(self.towers):
            phi = (i/T_ETA)
            eta = (i%T_ETA)
            tower.process(eta,phi)
    def __str__(self):
        return '**************\n'.join([str(tower) for tower in self.towers])
    def unwrap(self):
        unwrapped = []
        for tower in self.towers: unwrapped += tower.unwrap()
        return unwrapped
    def write(self,fname):
        print "Writing TV to",fname
        with open(fname,"w") as tv:
            tv.write("# Automatically generated\n\n")
            tv.write("# CLK " + "                  ".join("Link {0:>2}".format(str(i)) for i in range(len(self.towers)))+"\n")
            links = [ tower.link() for tower in self.towers ]
            links.insert(0,
                         ["{0:>4}".format(i) for i in range(len(links[0]))]
            )
            for i in range(len(links[0])):
                tv.write('  0x00 '.join([ link[i] for link in links ])+'\n')

parser = ArgumentParser()
parser.add_argument("-i","--input",type=InputTV,nargs="*")
args = parser.parse_args()

if __name__ == "__main__":
    intv = args.input[0]
    intv.write("remade_tv.txt")
    # crystals = intv.unwrap()
    # for tower in intv.towers: print tower
    # print "nTowers:",len(intv.towers)
    # print "nCrystals:",len(crystals)
