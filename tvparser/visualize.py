import os
import sys
import numpy as np
import parseTV as parse
from ROOT import *

gROOT.SetBatch(1)
gStyle.SetOptStat(0)

def DrawTV(tv):
    hsname = "vis_%s"%(tv.fname.replace(".txt","").replace("../",""))
    neta = parse.T_ETA*parse.C_ETA
    nphi = parse.T_PHI*parse.C_PHI
    rct = TH2I(hsname,"%s;eta;phi"%hsname,nphi,0,nphi,neta,0,neta)

    for ybin in range(neta):
        if (ybin-2)%5 == 0: rct.GetYaxis().SetBinLabel(ybin+1,str((ybin-2)/5))
        else: rct.GetYaxis().SetBinLabel(ybin+1,"")

    for xbin in range(nphi):
        if (xbin-2)%5 == 0: rct.GetXaxis().SetBinLabel(xbin+1,str((xbin-2)/5))
        else: rct.GetXaxis().SetBinLabel(xbin+1,"")
        

    for tower in tv.towers:
        teta = tower.eta
        tphi = tower.phi

        for crystal in tower.crystals:
            if crystal.energy == 0: continue
            eta = parse.C_ETA*teta + crystal.eta
            phi = parse.C_PHI*tphi + crystal.phi
            rct.Fill(phi,eta,crystal.energy)

    c = TCanvas(hsname,hsname,800,800)
    c.SetGrid()
    rct.Draw("COLZ TEXT")
    lines = []
    for y in range(1,parse.T_ETA):
        line = TLine(0,5*y,nphi,5*y)
        line.SetLineWidth(2)
        line.Draw()
        lines.append(line)
    for x in range(1,parse.T_PHI):
        line = TLine(5*x,0,5*x,neta)
        line.SetLineWidth(2)
        line.Draw()
        lines.append(line)
    c.Write()
    
output = TFile("tv_plots.root","recreate")
for tv in parse.args.input: DrawTV(tv)
output.Close()
