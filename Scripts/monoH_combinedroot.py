import sys,os,array
if len(sys.argv)!=3:
    print ("Usage: python CombinedRootMaker.py directorypath syst_path")
    sys.exit()

from ROOT import *
gROOT.SetBatch(True)

Xsec_MZp=[]
Mass_MZp=[]
Eff_MZp=[]

os.system('rm -rf DataCardRootFiles')
os.system('mkdir DataCardRootFiles')

path_sig='/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/monoH_signal_ZpBaryonic_v3'
path_sig_2HDM ='/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/monoH_signal_2HDMa_v3'

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


def setHistStyle_(h_temp2,bins,newname):

    h_temp=h_temp2.Rebin(6)
    h_temp.SetName(newname)
    h_temp.SetTitle(newname)
    h_temp.SetLineWidth(1)
    #h_temp.SetBinContent(len(bins)-1,h_temp.GetBinContent(len(bins)-1)+h_temp.GetBinContent(len(bins))) #Add overflow bin content to last bin
    #h_temp.SetBinContent(len(bins),0.)
    h_temp.GetXaxis().SetRangeUser(0,250)
    h_temp.SetMarkerColor(kBlack);
    h_temp.SetMarkerStyle(2);
    return h_temp

CRnames=['Top','Wenu','Wmunu','Zee','Zmumu','Gamma','SR','signal']

Hists=['h_met_sr2_','h_bb_Mass_sr2_']#,'h_MT_sr2_']

fdict={}

for CR in CRnames:
    # for reg in ['1b','2b']:
    #fdict[CR+"_"+reg]=TFile("DataCardRootFiles/monoH_2016_"+CR+"_"+reg+".root","RECREATE")
    fdict[CR+"_"+"2b"]=TFile("DataCardRootFiles/monoH_2016_"+CR+".root","RECREATE")

f=TFile("DataCardRootFiles/AllMETHistos.root","RECREATE")
f.cd()

inCRfiles=[fold+"/"+i for i in os.listdir(fold) if i.endswith('hadrecoil.root')]
inSRfiles=[fold+"/"+i for i in ['met_sr2.root','bb_Mass_sr2.root']]
inSystfiles=[fold_syst+"/"+i for i in os.listdir(fold_syst) if "syst" in i]

#bins=[200.0,270.0,345.0,480.0,1000.0]
#bins=[200,275,400,1000]
#bins=[200.0,300.0,400.0,500.0,1000.0]
bins=[200.0,270.0,350.0,480.0,1000.0]

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
    print ("So far we have choosen file", infile)

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
		print ("Looking for samp:", samp)
		h_temp2=fin.Get(samp)
		print "Integral: ",h_temp2.Integral()

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
		#if 'met' in infile:
		#	h_temp=setHistStyle(h_temp2,bins,shortname)
		#else:
		#	h_temp=setHistStyle_(h_temp2,bins,shortname)
		#if CR=="SR": h_temp.Scale(20)
		#sel=h_temp.Integral()
		#fdict[CR+"_"+category].cd()
		#h_temp.Write()
		#print "this is old name",newname
		if CR=="SR" and (newname.split('_')[-1]=='QCD' or newname.split('_')[-1]=='DIBOSON' or newname.split('_')[-1]=='Top' or newname.split('_')[-1]=='STop' or newname.split('_')[-1]=='WJets' or newname.split('_')[-1]=='DYJets' or newname.split('_')[-1]=='ZJets' or newname.split('_')[-1]=='GJets'):
			newname=newname.split('_')[-1]
			print "this is new name",newname
		if CR=="SR" and newname.split('_')[-1]=='obs':
			newname='data_obs'
			#print "this is new name",newname

		#print "set this bins",bins
		#print "bins present in the histogram", h_temp2.GetSize()
		if 'met' in infile:
			newname_='met_'+newname
			h_temp=setHistStyle(h_temp2,bins,newname_)
			sel=h_temp.Integral()
			f.cd()
			h_temp.Write()
		elif 'Mass' in infile:
			newname_='Mbb_'+newname
			h_temp=setHistStyle_(h_temp2,bins,newname_)
			sel=h_temp.Integral()
			f.cd()
			h_temp.Write()
		else:
			sel=0
		
		#print "value from the second bin",h_temp.GetBinContent(1)

		

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

# ttDMFiles=[fold+"/ttDM/"+i for i in os.listdir(fold+"/ttDM/") if i.endswith('.root')]

#regions=['2e1b','2mu1b','2e2b','2mu2b','1e1b','1mu1b','1e2b','1mu2b','1mu1e1b','1mu1e2b']
regions=['2e2b','2mu2b','1e2b','1mu2b','1mu1e2b']

lumi=35900.


for sig_file in monoHFiles:
	#XsecFile=open("crosssectionZpBaryonic.txt",'r')
	fin=TFile(sig_file,"READ")
	#h_total=fin.Get('h_total_weight')
	h_total=fin.Get('h_total')
	tot=h_total.Integral()

	Mchi=''
	MZp=''

	for partname in sig_file.split('/')[-1].strip('MC25ns_LegacyMC_20170328.root').split('_'):
		#print "printing part", partname
		if partname.startswith('MChi'): Mchi=partname.split('-')[-1]
		if partname.startswith('MZp'): MZp=partname.split('-')[-1]

	print ""
	print "this file",sig_file.split('/')[-1]#+": "+Mchi+" "+MZp
	print "these are mass points", Mchi, MZp
	print "Total = "+str(tot)

	if 'ZpBaryonic' in sig_file:
		samp='MonoHbb_ZpBaryonic'
	else:
		print "Code is not reading file properly"
	# elif 'NLO' in infile:
	#     samp='bbNLO'
	# else:
	#     samp='bbLO'
	#
	# if "pseudo" in infile:
	#     samp+="_pseudo"
	# else:
	#     samp+="_scalar"

	# Store SR1 and SR2 in the signal_*b file
	# for sr,category in ['sr2','2b']:#[['sr1','1b'],['sr2','2b']]:
	# print "signal file",sig_file
	# h_temp2=fin.Get('h_met_'+sr+'_')
	#h_temp2=fin.Get('h_met_sr2_')
	#print "sr2 integral", h_temp2.Integral()
	# newname=samp+"_"+category+"_"+Mchi+"_"+MZp
	newname=samp+"_Mchi_"+Mchi+"_MZp_"+MZp
	isCS=False
	for hist in Hists:
		print "Hist: ",hist
		h_temp2=fin.Get(hist)
		if hist=='h_met_sr2_':
			print "enter in met hist" 
			newname_='met_'+newname
			h_temp=setHistStyle(h_temp2,bins,newname_)
		elif hist=='h_bb_Mass_sr2_':
			print "enter Mbb "
			newname_='Mbb_'+newname
			h_temp=setHistStyle_(h_temp2,bins,newname_)		
		sel=h_temp.Integral()
		#isCS=False
		XsecFile=open("crosssectionZpBaryonic.txt",'r')
		for line in XsecFile:
			#print "Line of text file",line
			mzp=line.split()[0]
			mchi=line.split()[1]
			CSZP=float(line.split()[2])
			if int(mzp)==int(MZp) and int(mchi)==int(Mchi) and int(Mchi)==1:
				print "MZP: ", mzp,"mchi: ", mchi,"CS: ",line.split()[2]
				isCS=True
				Xsec_MZp.append(CSZP)
				Eff_MZp.append(sel/tot)
				Mass_MZp.append(int(mzp))
				#print "Hist: ",hist
                                print "efficiency: ",sel/tot
				print "Int before scaling", h_temp.Integral()
				h_temp.Scale(lumi*CSZP/tot)
				print "Int after scaling", h_temp.Integral()
				print "ZpBaryonic: lumi,CS, tot   ",lumi,CSZP,tot 
			#fdict['signal_'+category].cd()
			#h_temp.Write()

				f.cd()
				h_temp.Write()
				break


	if not isCS:
			print "CS is not available for the mass points: ", MZp, Mchi

	#XsecFile.close()
	#fin.Close()


for inFile in HDMaFiles:
    fin=TFile(inFile,"READ")
    h_total=fin.Get('h_total_weight')
    tot=h_total.Integral()
    MH3='600'
    MH4=''
    MH2='600'

    MH4 = inFile.split('/')[-1].strip('.root').split('_')[-4]
    if 'MH4_100' in inFile.split('/')[-1]: continue

    xsec,MH4=getCross(inFile)
    xsec=float (xsec)

    print "2HDMa model",inFile
    print ("Total = "+str(tot))


    if '2HDMa' in inFile:
        samp='2HDMa_gg_tb_1p0_MH3_600'
    else:
        print ("Code is not reading file properly")

    for hist in Hists:	
		h_temp2=fin.Get(hist)
		print ("sr2 integral", h_temp2.Integral())
		# newname=samp+"_"+category+"_"+Mchi+"_"+MZp
		newname=samp+"_MH4_"+MH4+"_MH2_600"
		
		if hist=='h_met_sr2_': 
			newname_='met_'+newname
			h_temp=setHistStyle(h_temp2,bins,newname_)
		elif hist=='h_bb_Mass_sr2_':
			newname_='Mbb_'+newname
			h_temp=setHistStyle_(h_temp2,bins,newname_)

		sel=h_temp.Integral()
		h_temp.Scale(lumi*xsec/tot)

		#fdict['signal_'+category].cd()
		#h_temp.Write()

		f.cd()
		h_temp.Write()
		#if int(MH4)==150:
		#print "RequiredMass: ",MH4
		#print "Integral before scaling",sel
		  #  print "Integral after scaling",h_temp.Integral()
		#print "Tatal events",tot

    #if samp.startswith("2HDM"):
    #    h_temp=setHistStyle(h_temp2,bins,"MH3_600_MH4_"+MH4+"_MH2_600")
    #    h_temp.Scale(lumi*xsec/tot)

    #    fdict['SR_'+category].cd()
    #    h_temp.Write()
    #
    # if samp=="bbNLO_scalar" and Mchi=="Mchi-1" and Mphi=="Mphi-300":
    #     h_temp=setHistStyle(h_temp2,bins,"sig")
    #     h_temp.Scale(lumi/tot)
    #
    #     fdict['SR_'+category].cd()
    #     h_temp.Write()

    #print (": Count %.2f, Sel Eff. = %.8f"%(sel,sel/tot))

    # # Store all CR

    #for reg in regions:
    #    h_temp2=fin.Get('h_reg_'+reg+'_'+'hadrecoil_')
    #    if samp.startswith("2HDM"):
    #        pseudofile=fold+"/"+"reg_"+reg+"_hadrecoil.root"
    #        CR,category=getCRcat(pseudofile)
    #        h_temp=setHistStyle(h_temp2,bins,"MH3_600_MH4_"+MH4+"_MH2_600")
    #        h_temp.Scale(lumi*xsec/tot)
    #        if h_temp.Integral()==0.:
    #            for ibin in range(h_temp.GetSize()-1):
    #                h_temp.SetBinContent(ibin,6e-4)
    #        if h_temp.Integral()<0.:
    #            h_temp.Scale(6e-4/h_temp.Integral())
    #
    #        fdict[CR+'_'+category].cd()
    #        h_temp.Write()

        #if samp.startswith("bb"):
            #h_temp=setHistStyle(h_temp2,bins,samp[2:]+"_mphi_"+Mphi.split('-')[1]+"_mchi_"+Mchi.split('-')[1])
            #h_temp.Scale(lumi/tot)

            #for CR in CRnames:
                #fdict[CR+'_'+category].cd()
                #h_temp.Write()

        #if samp=="bbNLO_scalar" and Mchi=="Mchi-1" and Mphi=="Mphi-300":
            #h_temp=setHistStyle(h_temp2,bins,"sig")
            #h_temp.Scale(lumi/tot)

            #for CR in CRnames:
                #fdict[CR+'_'+category].cd()
                #h_temp.Write()



#for CR in CRnames:
#    for reg in ['1b','2b']:
#        fdict[CR+"_"+reg].Close()
f.Close()
