import sys,os,array
if len(sys.argv)!=3:
    print ("Usage: python CombinedRootMaker.py directorypath syst_path")
    sys.exit()

from ROOT import *
gROOT.SetBatch(True)

os.system('mkdir DataCardRootFiles_sin')

path_sig='/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/20180620_monoH_v2_signal'
path_sig_2HDM ='/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/20180627_2HDMa'

fold=sys.argv[1].strip('/')
fold_syst=sys.argv[2].strip('/')
def setHistStyle(h_temp2,bins,newname):

    h_temp=h_temp2.Rebin(len(bins)-1,"h_temp",array.array('d',bins))
    h_temp.SetName(newname)
    h_temp.SetTitle(newname)
    h_temp.SetLineWidth(1)
    h_temp.SetBinContent(len(bins)-1,h_temp.GetBinContent(len(bins)-1)+h_temp.GetBinContent(len(bins))) #Add overflow bin content to last bin
    h_temp.SetBinContent(len(bins),0.)
    h_temp.GetXaxis().SetRangeUser(200,1000)
    h_temp.SetMarkerColor(kBlack);
    h_temp.SetMarkerStyle(2);
    return h_temp

CRnames=['Top','Wenu','Wmunu','Zee','Zmumu','Gamma','SR','signal']

fdict={}
# for CR in CRnames:
#     for reg in ['1b','2b']:
#         fdict[CR+"_"+reg]=TFile("DataCardRootFiles/monoH_2016_"+CR+"_"+reg+".root","RECREATE")

f=TFile("DataCardRootFiles_sin/AllMETHistos.root","RECREATE")
f.cd()

inCRfiles=[fold+"/"+i for i in os.listdir(fold) if i.endswith('hadrecoil.root')]
inSRfiles=[fold+"/"+i for i in ['met_sr1.root','met_sr2.root']]
inSystfiles=[fold_syst+"/"+i for i in os.listdir(fold_syst) if "syst" in i]

bins=[200,300,500,2000]

def getCRcat(infile):

    flnamesplit=infile.split('/')[-1].split('.')[0].split('_')
    if 'sr1' in infile:
        CR="SR"
        category='1b'
    elif 'sr2' in infile:
        CR="SR"
        category='2b'
    else:
        reg=flnamesplit[1]
        category=reg[-2:]
        if reg.startswith('1mu1e'):
            CR='Top'
        elif reg.startswith('1e'):
            CR='Wenu'
        elif reg.startswith('1mu'):
            CR='Wmunu'
        elif reg.startswith('2e'):
            CR='Zee'
        elif reg.startswith('2mu'):
            CR='Zmumu'
        elif reg.startswith('1gamma'):
            CR='Gamma'
    return CR,category

#def getSortKey(infile):
#    CR,category=getCRcat(infile)
#    newname="bbDM_2016_"+CR+"_"+sampname+"_"+category
#    flnamesplit=infile.split('/')[-1].split('.')[0].split('_')
#    if 'syst' in infile:
#        newname += "_"+flnamesplit[2]+"_"+flnamesplit[4]
#    return newname

SRCRhistos=[]

for infile in sorted(inCRfiles+inSRfiles+inSystfiles):
    fin=TFile(infile,"READ")
    #print ("So far we have choosen file", infile)

    flnamesplit=infile.split('/')[-1].split('.')[0].split('_')

    samplist=['DIBOSON','ZJets','GJets','STop','TT','WJets','DYJets','QCD']

    if 'sr' in infile or 'syst' in infile:
        samplist.append('bkgSum')
    else:
        samplist.append('data_obs')
    #try:
    # print "file",infile
    CR,category=getCRcat(infile)
    #except:
        #print infile

    h_tot=fin.Get('bkgSum')


    # print ("checking file")
    if not 'syst' in infile:
    #    print infile
        print ("Region: "+CR+category)
        try:
            tot=h_tot.Integral()
        except Exception as e:
            print (e)
            print ("WARNING1: Skipping for "+CR+category+".******************************************************************************")
            continue
        print ("Total = "+str(tot))
    else:
#        if "met" in flnamesplit[2] : continue               ####Since MET is not added yet ## TEMPORARY
        print ("Region: "+CR+category+" "+flnamesplit[2]+" "+flnamesplit[4])
        try:
            tot=h_tot.Integral()
        except Exception as e:
            print (e)
            print ("WARNING2: Skipping for "+CR+category+" "+flnamesplit[2]+" "+flnamesplit[4]+".******************************************************************************")
            continue

    for samp in samplist:
        # print ("Looking for samp:", samp)
        h_temp2=fin.Get(samp)

        if (samp=='bkgSum' or samp=='data_obs') and not 'syst' in infile:
            sampname='data_obs'
        elif samp=='bkgSum' and 'syst' in infile:
            sampname='bkgSum'
        else:
            sampname=samp
        # print ("my sampname:",sampname )

        sampname=sampname.replace("TT","Top")
        # print ("my final sampname",sampname)

        newname=CR+"_"+category+"_"+sampname

        shortname=sampname

        if 'syst' in infile:
            newname += "_"+flnamesplit[2]+"_"+flnamesplit[4]
            shortname += "_"+flnamesplit[2]+"_"+flnamesplit[4]

        h_temp=setHistStyle(h_temp2,bins,shortname)
        #if CR=="SR": h_temp.Scale(20)
        sel=h_temp.Integral()
        # fdict[CR+"_"+category].cd()
        # h_temp.Write()
        print "this is old name",newname
        if CR=="SR" and (newname.split('_')[-1]=='QCD' or newname.split('_')[-1]=='DIBOSON' or newname.split('_')[-1]=='Top' or newname.split('_')[-1]=='STop' or newname.split('_')[-1]=='WJets' or newname.split('_')[-1]=='DYJets' or newname.split('_')[-1]=='ZJets' or newname.split('_')[-1]=='GJets'):
            newname=newname.split('_')[-1]
            print "this is new name",newname
        if CR=="SR" and newname.split('_')[-1]=='obs':
            newname='data_obs'
            print "this is new name",newname

        #print "set this name",newname
        h_temp=setHistStyle(h_temp2,bins,newname)

        f.cd()
        h_temp.Write()

#        except:
#            sel=0.
#            print "Skipped "+infile+" "+samp
        if not 'syst' in infile:
            if tot!=0:
                frac=sel/tot
            else:
                frac=0.
            if samp!="data_obs" and samp!="bkgSum": print ("    Sample = " + samp+": Count = %.2f, Fraction = %.4f"%(sel,frac))
    fin.Close()

#
##Signal

CrossSec={'MH4_150':0.3217,'MH4_200':0.2453,'MH4_250':0.1758,'MH4_300':.1224,'MH4_350':0.08198,'MH4_400':0.0423,'MH4_500':0.005887}
def getCross(file):
    ma=file.split('/')[-1].strip('.root').split('_')[-4]
    XSec=CrossSec['MH4_'+str(ma)]
    return XSec,ma


monoHFiles=[path_sig+"/"+i for i in os.listdir(path_sig+"/") if i.endswith('.root')]

HDMaFiles=[path_sig_2HDM+"/"+i for i in os.listdir(path_sig_2HDM+"/") if i.endswith('.root')]
regions=['2e2b','2mu2b','1e2b','1mu2b','1mu1e2b']

lumi=35900.

MH4_150_CS=[0.05449291, 0.1904986, 0.3475371, 0.450372, 0.4496216, 0.3438409, 0.2206215, 0.2924391, 0.9575288]
sin_value=['1','2','3','4','5','6','7','8','9']
for inFile in HDMaFiles:
    fin=TFile(inFile,"READ")
    h_total=fin.Get('h_total_weight')
    tot=h_total.Integral()
    MH3='600'
    MH4=''
    MH2='600'

    MH4 = inFile.split('/')[-1].strip('.root').split('_')[-4]
    if 'MH4_150' not in inFile.split('/')[-1]: continue

    print ("Total = "+str(tot))

    for i in range(len(MH4_150_CS)):
        if '2HDMa' in inFile:
            samp='2HDMa_gg_tb_1p0_MH3_600'
        else:
            print ("Code is not reading file properly")


        h_temp2=fin.Get('h_met_sr2_')
        print ("sr2 integral", h_temp2.Integral())

        newname=samp+"_MH4_"+MH4+"_MH2_600"+"CS_"+sin_value[i]

        h_temp=setHistStyle(h_temp2,bins,newname)
        sel=h_temp.Integral()
        h_temp.Scale(lumi*(MH4_150_CS[i])/tot)
        f.cd()
        h_temp.Write()

f.Close()
