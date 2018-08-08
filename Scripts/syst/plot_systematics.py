#!/usr/bin/env python
import ROOT as ROOT
import os
import random
import sys, optparse
from array import array
import math
from ROOT import *
import getpass
import socket
import json

def SetCanvas():

    # CMS inputs
    # -------------
    H_ref = 1000;
    W_ref = 1000;
    W = W_ref
    H  = H_ref

    T = 0.08*H_ref
    B = 0.21*H_ref
    L = 0.12*W_ref
    R = 0.08*W_ref
    # --------------

    c1 = TCanvas("c2","c2",0,0,1500,1500)
    c1.SetFillColor(0)
    c1.SetBorderMode(0)
    c1.SetFrameFillStyle(0)
    c1.SetFrameBorderMode(0)
    c1.SetLeftMargin( L/W )
    c1.SetRightMargin( R/W )
    c1.SetTopMargin( T/H )
    c1.SetBottomMargin( B/H )
    c1.SetTickx(0)
    c1.SetTicky(0)
    c1.SetTickx(1)
    c1.SetTicky(1)
    c1.SetGridy()
    c1.SetGridx()
    return c1

def SetTpad():
    # CMS inputs
    # -------------
    H_ref = 1000;
    W_ref = 1000;
    W = W_ref
    H  = H_ref

    L = 0.12*W_ref
    R = 0.08*W_ref
    # --------------

    c1_1 = ROOT.TPad("c1_1", "newpad",0,0.0,1,0.2)
    c1_1.Draw()
    c1_1.cd()
#    c1_1.Range(-7.862408,-629.6193,53.07125,486.5489)
    c1_1.SetFillColor(0)
    c1_1.SetTicky(1)
    c1_1.SetLeftMargin( L/W )
    c1_1.SetRightMargin( R/W )
    c1_1.SetTopMargin(0.0)
    c1_1.SetBottomMargin(0.3)
    c1_1.SetTickx(1)
    c1_1.SetTicky(1)
    c1_1.SetGridy(1)
    c1_1.SetGridx(1)
    c1_1.SetFrameFillStyle(0)
    c1_1.SetFrameBorderMode(0)
    c1_1.SetFrameFillStyle(0)
    c1_1.SetFrameBorderMode(0)
    c1_1.SetLogy(0)
    return c1_1


def CreateLegend(x1, y1, x2, y2, header):

    leg = ROOT.TLegend(x1, x2, y1, y2)
    leg.SetFillColor(0)
    leg.SetFillStyle(3002)
    leg.SetBorderSize(0)
    leg.SetHeader(header)
    return leg

def CustomiseHistogram(h, titleX, titleY, color, lineStyle,title):
    '''
    '''
    h.SetMarkerColor(color)
    h.SetMarkerSize(1.0)

    h.SetLineColor(color)
    h.SetLineWidth(2)
    h.SetLineStyle(lineStyle)
    h.GetXaxis().SetLabelSize(0)
    h.GetYaxis().SetTitle(titleY)

    h.GetYaxis().SetTitleOffset(1.4)
    h.GetXaxis().SetTitleOffset(1.2)
    h.SetTitle(title)

    return

def CustomiseRatio(h1,h2,h3,titleX):
    h1.SetMarkerSize(0.7)
    h1.SetMarkerStyle(20)
    h1.SetMarkerColor(kRed)
    h1.SetLineColor(kRed)
    h2.SetMarkerSize(0.7)
    h2.SetMarkerStyle(20)
    h2.SetMarkerColor(kBlue)
    h2.SetLineColor(kBlue)
    h3.SetMarkerSize(0.7)
    h3.SetMarkerStyle(20)
    h3.SetMarkerColor(kBlack)
    h3.SetLineColor(kBlack)
    h1.GetYaxis().SetLabelSize(.1)
    h1.GetXaxis().SetLabelSize(.1)
    h1.Draw("P e1")
    h2.Draw("P e1 same")
    h3.Draw("P e1 same")
    h1.SetMinimum(0.5)
    h1.SetMaximum(1.5)
    h1.GetXaxis().SetNdivisions(508)
    h1.GetYaxis().SetNdivisions(505)
    h1.GetXaxis().SetTitle(titleX)
    h1.GetXaxis().SetTitleOffset(0.75)
    h1.GetXaxis().SetTitleSize(.15)
    return

def AddText(txt):
    texcms = ROOT.TLatex(-20.0, 50.0, txt)
    texcms.SetNDC()
    texcms.SetTextAlign(12)
    texcms.SetX(0.15)
    texcms.SetY(0.94)
    texcms.SetTextSize(0.02)
    texcms.SetTextSizePixels(22)
    return texcms

def AddTextCat(cat):
    texCat = ROOT.TLatex(-20.0, 50.0, cat)
    texCat.SetNDC()
    texCat.SetTextAlign(12)
    texCat.SetX(0.80)
    texCat.SetY(0.94)
    texCat.SetTextFont(40)
    texCat.SetTextSize(0.02)
    texCat.SetTextSizePixels(22)
    return texCat

ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
gROOT.SetBatch(True)
uncertfile=open("uncert.txt","w")
binuncertfile=open("binuncert.txt","w")
for loc in ['bbMETSystPdf','bbMETSystPng']:
    for jetprop in ['btag','lep','ewkZ','ewkW','ewkTop','met','jec','jer']:
        for reg in ['sr','Zcr','Wcr','TOPcr','Gamma']:
            os.system("mkdir -p "+loc+"/"+jetprop+"/"+reg )
for jetprop in ['btag','lep','ewkZ','ewkW','ewkTop','met','jec','jer']:
    for reg in ['sr1','sr2','2e1b','2mu1b','2e2b','2mu2b','1e1b','1mu1b','1e2b','1mu2b','1mu1e1b','1mu1e2b','1gamma1b','1gamma2b']:
        try:
            for syst in ['up','down']:
                exec("systematics_"+reg+"_"+jetprop+"_"+syst+"_file = TFile('ROOTFiles/reg_"+reg+"_"+jetprop+"_syst_"+syst+".root')")
                exec("central_"+reg+"_"+jetprop+"_file = TFile('ROOTFiles/reg_"+reg+"_hadrecoil.root')")
                exec(jetprop+"_syst_"+reg+"_"+syst+" = systematics_"+reg+"_"+jetprop+"_"+syst+"_file.Get('bkgSum')")
                exec(jetprop+"_syst_"+reg+"_central = central_"+reg+"_"+jetprop+"_file.Get('bkgSum')")

            colors = {
                    "up"     : ROOT.kRed,
                    "down"     : ROOT.kBlue,
                    "central" : ROOT.kBlack,
                    }
            titleX = "E_{T}^{miss} (GeV)"
            titleY = ""

            # Set Canvas
            c1 = SetCanvas()
            exec("CustomiseHistogram("+jetprop+"_syst_"+reg+"_up, titleX, titleY, colors['up'], 1,'Up')")
            exec("CustomiseHistogram("+jetprop+"_syst_"+reg+"_down, titleX, titleY, colors['down'], 1,'Down')")
            exec("CustomiseHistogram("+jetprop+"_syst_"+reg+"_central, titleX, titleY, colors['central'], 1,'Central')")

            exec("bins = "+jetprop+"_syst_"+reg+"_central.GetSize()")
            exec("upUnc = "+jetprop+"_syst_"+reg+"_up.Integral(2,8)")
            exec("downUnc = "+jetprop+"_syst_"+reg+"_down.Integral(2,8)")
            exec("centralUnc = "+jetprop+"_syst_"+reg+"_central.Integral(2,8)")

            #print btag_syst_sr1_central.GetBinContent(6)



            uncertfile.write(jetprop+"_syst_"+reg+": ")
            uncertfile.write(str((max(abs(upUnc-centralUnc),abs(centralUnc-downUnc))/centralUnc)*100)+"\n")

            binuncertfile.write(jetprop+"_syst_"+reg+": \n \n")


            exec(jetprop+"_syst_"+reg+"_up.Rebin(4)")
            exec(jetprop+"_syst_"+reg+"_down.Rebin(4)")
            exec(jetprop+"_syst_"+reg+"_central.Rebin(4)")
            exec("bins = "+jetprop+"_syst_"+reg+"_central.GetSize()")

            for i in range(1,bins-1):
                #print('enter')
                exec("binupUnc = "+jetprop+"_syst_"+reg+"_up.GetBinContent(i)")
                exec("bindownUnc = "+jetprop+"_syst_"+reg+"_down.GetBinContent(i)")
                exec("bincentralUnc = "+jetprop+"_syst_"+reg+"_central.GetBinContent(i)")
                #print bincentralUnc
                if bincentralUnc==0: continue
                binuncertfile.write("bin "+str(i)+": ")
                binuncertfile.write(str((max(abs(binupUnc-bincentralUnc),abs(bincentralUnc-bindownUnc))/bincentralUnc)*100)+", ")
                #print('exit')
            binuncertfile.write("\n \n \n")

            exec(jetprop+"_syst_"+reg+"_up.Draw()")
            exec(jetprop+"_syst_"+reg+"_down.Draw('same')")
            exec(jetprop+"_syst_"+reg+"_central.Draw('same')")

            #c1.BuildLegend()

            leg = CreateLegend(0.7, 0.9, 0.7, 0.9, "")
            exec("leg.AddEntry("+jetprop+"_syst_"+reg+"_up, 'Up' , 'l')")
            exec("leg.AddEntry("+jetprop+"_syst_"+reg+"_central, 'Central' , 'l')")
            exec("leg.AddEntry("+jetprop+"_syst_"+reg+"_down, 'Down' , 'l')")
            leg.Draw("same")


            if reg in ['sr1','2e1b','2mu1b','1e1b','1mu1b','1mu1e1b','1gamma1b']:
                textcat = '1 btag category'
            if reg in ['sr2','2e2b','2mu2b','1e2b','1mu2b','1mu1e2b','1gamma2b']:
                textcat = '2 btag category'
            txt = 'DM + Heavy Flavor'

            texcms = AddText(txt)
            texCat= AddTextCat(textcat)

            texcms.Draw("same")
            texCat.Draw("same")


            exec(jetprop+"_syst_"+reg+"_up.GetXaxis().SetRangeUser(200, 1000)")
            exec(jetprop+"_syst_"+reg+"_down.GetXaxis().SetRangeUser(200, 1000)")
            exec(jetprop+"_syst_"+reg+"_central.GetXaxis().SetRangeUser(200, 1000)")

            exec("ratioUp = "+jetprop+"_syst_"+reg+"_up.Clone()")
            exec("ratioDown = "+jetprop+"_syst_"+reg+"_down.Clone()")
            exec("ratioCentral = "+jetprop+"_syst_"+reg+"_central.Clone()")

            exec("ratioUp.Divide("+jetprop+"_syst_"+reg+"_central)")
            exec("ratioCentral.Divide("+jetprop+"_syst_"+reg+"_central)")
            exec("ratioDown.Divide("+jetprop+"_syst_"+reg+"_central)")



            c1_1 = SetTpad()
            exec("CustomiseRatio(ratioUp,ratioDown,ratioCentral, titleX)")
            c1_1.Update()
            c1.SetLogy()
            c1.Update()

            if reg=='sr1' or reg=='sr2':
                exec("c1.SaveAs('bbMETSystPdf/"+jetprop+"/sr/"+jetprop+"_syst_"+reg+".pdf')")
                exec("c1.SaveAs('bbMETSystPng/"+jetprop+"/sr/"+jetprop+"_syst_"+reg+".png')")
            if reg=="2mu1b" or reg=="2e1b" or reg=="2mu2b" or reg=="2e2b":
                exec("c1.SaveAs('bbMETSystPdf/"+jetprop+"/Zcr/"+jetprop+"_syst_"+reg+".pdf')")
                exec("c1.SaveAs('bbMETSystPng/"+jetprop+"/Zcr/"+jetprop+"_syst_"+reg+".png')")
            if reg=="1mu1b" or reg=="1e1b" or reg=="1mu2b" or reg=="1e2b" :
                exec("c1.SaveAs('bbMETSystPdf/"+jetprop+"/Wcr/"+jetprop+"_syst_"+reg+".pdf')")
                exec("c1.SaveAs('bbMETSystPng/"+jetprop+"/Wcr/"+jetprop+"_syst_"+reg+".png')")
            if reg =='1mu1e1b' or reg == '1mu1e2b' :
                exec("c1.SaveAs('bbMETSystPdf/"+jetprop+"/TOPcr/"+jetprop+"_syst_"+reg+".pdf')")
                exec("c1.SaveAs('bbMETSystPng/"+jetprop+"/TOPcr/"+jetprop+"_syst_"+reg+".png')")

            c1.Close()
            exec("print ('Done "+jetprop+"_syst_"+reg+"')")
        except:
            pass
