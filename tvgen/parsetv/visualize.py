import os
import sys
import numpy as np
import parseTV as parse
from ROOT import *

gROOT.SetBatch(1)
gStyle.SetOptStat(0)

def DrawInputTV(tv):
    hsname = "vis_%s"%(tv.fname.replace(".txt","").replace("../","").replace("/","_"))
    neta = parse.T_ETA*parse.C_ETA
    nphi = parse.T_PHI*parse.C_PHI
    rct = TH2I(hsname,"%s;iPhi;iEta"%hsname,nphi,0,nphi,neta,0,neta)

    for ybin in range(neta):
        if (ybin-2)%5 == 0: rct.GetYaxis().SetBinLabel(ybin+1,str((ybin-2)/5))
        else: rct.GetYaxis().SetBinLabel(ybin+1,"")

    for xbin in range(nphi):
        if (xbin-2)%5 == 0: rct.GetXaxis().SetBinLabel(xbin+1,str((xbin-2)/5))
        else: rct.GetXaxis().SetBinLabel(xbin+1,"")
        

    for tower in tv.towers:
        teta = tower.eta * parse.C_ETA
        tphi = tower.phi * parse.C_PHI

        for crystal in tower.crystals:
            if crystal.energy == 0: continue
            eta = teta + crystal.eta
            phi = tphi + crystal.phi
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
    
def DrawOutputTV(tv):
    hsname = "vis_%s"%(tv.fname.replace(".txt","").replace("../","").replace("/","_"))
    neta = parse.T_ETA*parse.C_ETA
    nphi = parse.T_PHI*parse.C_PHI
    teta = parse.T_ETA
    tphi = parse.T_PHI
    clusters = TH2I(hsname+"_clusters","%s;iPhi;iEta"%hsname,nphi,0,nphi,neta,0,neta)
    towers = TH2I(hsname+"_towers","%s;iPhi;iEta"%hsname,tphi,0,nphi,teta,0,neta)

    for ybin in range(neta):
        if (ybin-2)%5 == 0: clusters.GetYaxis().SetBinLabel(ybin+1,str((ybin-2)/5))
        else: clusters.GetYaxis().SetBinLabel(ybin+1,"")

    for xbin in range(nphi):
        if (xbin-2)%5 == 0: clusters.GetXaxis().SetBinLabel(xbin+1,str((xbin-2)/5))
        else: clusters.GetXaxis().SetBinLabel(xbin+1,"")
        

    for tower in tv.towers:
        teta = tower.eta * parse.C_ETA + 2
        tphi = tower.phi * parse.C_PHI + 2
        ceta = tower.eta * parse.C_ETA + tower.peak_eta
        cphi = tower.phi * parse.C_PHI + tower.peak_phi

        if tower.cluster_et > 0:
            clusters.Fill(cphi,ceta,tower.cluster_et)
        if tower.tower_et > 0:
            towers.Fill(tphi,teta,tower.tower_et)
    c = TCanvas(hsname,hsname,800,800)
    c.SetGrid()
    clusters.Draw("COLZ TEXT")
    towers.Draw("BOX TEXT same")
    towers.SetLineColor(kRed)
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
    
output = TFile(parse.args.write,"recreate")
for tv in parse.args.input: DrawInputTV(tv)
for tv in parse.args.output:DrawOutputTV(tv)
output.Close()
