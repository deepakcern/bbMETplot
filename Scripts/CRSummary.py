import matplotlib.pyplot as plt
from ROOT import *

regnames=['1#mu2b','1e2b','2#mu2b','2e2b','1#mu1e2b']
bkgsum=[970,619,63,41,110]
data=[766,537,74,45,79]
n=len(regnames)
#ypos=range(n)

#plt.bar(ypos,bkgsum)
#plt.scatter(ypos,data)
#plt.xticks(ypos,regnames)
#plt.yscale('log')
#plt.ylabel("Events")
#plt.show()

c=TCanvas('c','c',1000,800)
c.SetWindowSize(1000,800)
c.SetLogy()

h=TH1F("h","Control Region Summary",n,0,n)
for i in range(n):
    h.SetBinContent(i+1,bkgsum[i])
    h.GetXaxis().SetBinLabel(i+1,regnames[i])
h.SetStats(0)
h.GetYaxis().SetTitle("Events")
h.GetYaxis().SetTitleOffset(1.4)
h.GetYaxis().SetMoreLogLabels()
h.SetFillColor(kBlue-10)
h.Draw('hist e')

hd=TH1F("hd","Control Region Summary",n,0,n)
for i in range(n):
    hd.SetBinContent(i+1,data[i])
#    hd.SetBinError(i+1,0.)
hd.SetStats(0)
hd.SetLineColor(1)
hd.SetMarkerColor(kBlack)
hd.SetMarkerStyle(20)
hd.SetMarkerSize(1.5)
hd.Draw('same p e1')

c.SaveAs('CRsummary.png')
c.SaveAs('CRsummary.pdf')
