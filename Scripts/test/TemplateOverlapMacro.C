
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "TStyle.h"
#include "TString.h"
#include "TRegexp.h"

void Plot(){
time_t now = time(0);
tm *ltm = localtime(&now);
TString dirpathname;

 TString DirPreName = "/afs/cern.ch/work/d/dekumar/public/monoH/bbDMplots/CMSSW_8_0_26_patch1/src/limitplot/bbMET/bbMETplot/Scripts/test/";
 dirpathname = "11082018"; //.Form("%d%1.2d%d",ltm->tm_mday,1 + ltm->tm_mon,1900 + ltm->tm_year);
 
 system("mkdir -p  " + DirPreName+dirpathname +"/bbMETROOT");
 system("mkdir -p  " + DirPreName+dirpathname +"/bbMETPdf");
 system("mkdir -p  " + DirPreName+dirpathname +"/bbMETPng");
 
 
 ofstream mout;
 mout.open(DirPreName+dirpathname +"/HISTPATH"+dirpathname +"Integral.txt",std::ios::app);
 ofstream rout;
 rout.open(DirPreName+dirpathname +"/HISTPATH"+dirpathname +"Integral.html",std::ios::app);
 ofstream tableout;
 tableout.open(DirPreName+dirpathname +"/HISTPATH"+dirpathname +"IntegralWithError.txt",std::ios::app);                                                                  
 TString outputshapefilename = DirPreName+dirpathname +"/HISTPATH.root";
 TFile *fshape = new TFile(outputshapefilename,"RECREATE");

if(VARIABLEBINS){
ofstream metbinsout_1;
ofstream metbinsout_2;
ofstream metbinsout_3;

 system("mkdir -p  " + DirPreName+"METBIN_1");
 system("mkdir -p  " + DirPreName+"METBIN_2");
 system("mkdir -p  " + DirPreName+"METBIN_3");


 metbinsout_1.open(DirPreName+"METBIN_1/HISTPATH"+dirpathname +"Integral.txt",std::ios::app);
 metbinsout_2.open(DirPreName+"METBIN_2/HISTPATH"+dirpathname +"Integral.txt",std::ios::app);
 metbinsout_3.open(DirPreName+"METBIN_3/HISTPATH"+dirpathname +"Integral.txt",std::ios::app);
}

gROOT->ProcessLine(".L tdrstyle.C");
//setTDRStyle();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
gStyle->SetFrameLineWidth(3);
//gStyle->SetErrorX(0);
gStyle->SetLineWidth(1);

//Provide luminosity of total data
//cout << endl << "*************** WARNING: Assuming incomplete data: full luminosity is not used. ***************" << endl << endl; //Adjust the last factor in the next line according to available data.
float lumi = 35.545 * 1000; // 35.540082604 * 1000; // 3.1054555906 * 1000 ; ////11706.;// * 0.96838; // from the twiki https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis  //36.773
float luminosity = 35.5;// It will print on your plots too

std::vector<TString> filenameString;
//Change here Directories of the file


// histogram declaration for shape analysis
//TH1F*  monoHbbM600;
//TH1F*  monoHbbM800; 
//TH1F*  monoHbbM1000;
//TH1F*  monoHbbM1200;
//TH1F*  monoHbbM1400; 
//TH1F*  monoHbbM1700;
//TH1F*  monoHbbM2000;
//TH1F*  monoHbbM2500;
TH1F*  DIBOSON;
TH1F*  TT;
//TH1F*  TTJets;
TH1F*  WJets;
TH1F*  DYJets;
TH1F*  ZJets;
TH1F*  STop;
TH1F*  GJets;
TH1F*  QCD;
//TH1F*  data_obs;
TString filenamepath("/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/20180615_monoH_v2_uscms/bkg/"); 

// Diboson WW WZ ZZ 0 1 2
filenameString.push_back(filenamepath + "Output_crab_WW_TuneCUETP8M1_13TeV-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WZ_TuneCUETP8M1_13TeV-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZZ_TuneCUETP8M1_13TeV-pythia8_MC25ns_LegacyMC_20170328.root");


//ZJets High pt DYSample 3,4,5,6,7,8,9
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-100To200_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-200To400_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-400To600_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-600To800_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-800To1200_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_MC25ns_LegacyMC_20170328.root");


//DYJets High pt DYSample 10,11,12,13,14,15,16,17
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");

// WJets in Bins  18,18,19,20,21,22,23,24,25
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");

// Single Top 26,27,28,29 30
filenameString.push_back(filenamepath + "Output_crab_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-pythia8_TuneCUETP8M1_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-pythia8_TuneCUETP8M1_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_MC25ns_LegacyMC_20170328.root");

// Gamma + Jets 31,32,33,34,35
filenameString.push_back(filenamepath + "Output_crab_GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");
filenameString.push_back(filenamepath + "Output_crab_GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328.root");

// TTJets 36
filenameString.push_back(filenamepath + "Output_crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root");
//

// QCD 37,38,39,40,41,42,43,44,45 
filenameString.push_back(filenamepath + "Output_crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");  //dummy
filenameString.push_back(filenamepath + "Output_crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");  //dummy
filenameString.push_back(filenamepath + "Output_crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");  //dummy
filenameString.push_back(filenamepath + "Output_crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");  //dummy
filenameString.push_back(filenamepath + "Output_crab_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
filenameString.push_back(filenamepath + "Output_crab_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
filenameString.push_back(filenamepath + "Output_crab_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
filenameString.push_back(filenamepath + "Output_crab_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
filenameString.push_back(filenamepath + "Output_crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
//

// not used so far
TString filenamesigpath("/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/20180615_monoH_v2_uscms/signal/"); 
//bbMET Signal Sample 46 - 83
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-50_Mphi-400.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-50_Mphi-350.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-50_Mphi-300.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-450_Mphi-1000.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-350_Mphi-750.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-350_Mphi-1000.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-1_Mphi-750.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-1_Mphi-500.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-1_Mphi-400.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-1_Mphi-350.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-1_Mphi-300.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-10_Mphi-50.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-10_Mphi-10.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-10_Mphi-100.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-100_Mphi-500.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-100_Mphi-400.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-100_Mphi-350.root");
filenameString.push_back(filenamesigpath + "Output_scalar_NLO_Mchi-100_Mphi-300.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-50_Mphi-50.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-50_Mphi-500.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-50_Mphi-400.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-50_Mphi-350.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-50_Mphi-300.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-50_Mphi-200.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-450_Mphi-1000.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-1_Mphi-50.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-1_Mphi-500.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-1_Mphi-400.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-1_Mphi-350.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-1_Mphi-100.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-1_Mphi-1000.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-10_Mphi-50.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-10_Mphi-10.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-10_Mphi-100.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-100_Mphi-750.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-100_Mphi-500.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-100_Mphi-400.root");
filenameString.push_back(filenamesigpath + "Output_pseudo_NLO_Mchi-100_Mphi-350.root");

//

TString filenamedatapath("/afs/cern.ch/work/d/dekumar/public/monoH/BROutputs/20180615_monoH_v2_uscms/data/");
//Data File 84
filenameString.push_back(filenamedatapath + "data_combined_MET.root");


// dummy file
filenameString.push_back(filenamepath + "Output_crab_GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MC25ns_LegacyMC_20170328_copy.root");

//const int n_integral = (int)filenameString.size();

TString histnameString("HISTNAME");

TFile *fIn;
const int nfiles = (int) filenameString.size();
float Integral[nfiles] , Integral_Error[nfiles];

//kfactor * lo crossection
//check it once 

float Xsec[nfiles];

Xsec[0] = 118.7;                   // WW
Xsec[1] = 47.2;                    // WZ
Xsec[2] = 16.6;                    // ZZ

Xsec[3] = 1.23 * 280.35;           // Znunu HT 100-200
Xsec[4] = 1.23 * 77.67;            // Znunu HT 200-400
Xsec[5] = 1.23 * 10.73;            // Znunu HT 400-600
Xsec[6] = 1.23 * 2.559;            // Znunu HT 600-800
Xsec[7] = 1.23 * 1.1796;           // Znunu HT 800-1200
Xsec[8] = 1.23 * 0.28833;          // Znunu HT 1200-2500
Xsec[9] = 1.23 * 0.006945;         // Znunu HT 2500-inf

Xsec[10] = 1.23 * 169.9;           // DYJetsToLL HT 70-100
Xsec[11] = 1.23 * 147.4;           // DYJetsToLL HT 100-200
Xsec[12] = 1.23 * 40.99;           // DYJetsToLL HT 200-400
Xsec[13] = 1.23 * 5.678;           // DYJetsToLL HT 400-600
Xsec[14] = 1.23 * 1.367;           // DYJetsToLL HT 600-800
Xsec[15] = 1.23 * 0.6304;          // DYJetsToLL HT 800-1200
Xsec[16] = 1.23 * 0.1514;          // DYJetsToLL HT 1200-2500
Xsec[17] = 1.23 * 0.003565;        // DYJetsToLL HT 2500-inf

Xsec[18] = 1.459 * 1343;           // WJets HT 70-100     ***not available in twiki*** https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
Xsec[19] = 1.21 * 1345;            // WJets HT 100-200
Xsec[20] = 1.21 * 359.7;           // WJets HT 200-400
Xsec[21] = 1.21 * 48.91;           // WJets HT 400-600
Xsec[22] = 1.21 * 12.05;           // WJets HT 600-800
Xsec[23] = 1.21 * 5.501;           // WJets HT 800-1200
Xsec[24] = 1.21 * 1.329;           // WJets HT 1200-2500
Xsec[25] = 1.21 * 0.03216;         // WJets HT 2500-Inf

Xsec[26] =  44.07;                 // single top t-channel_top_4f_inclusiveDecays       ***not available in twiki***
Xsec[27] =  26.22;                 // single top t-channel_antitop_4f_inclusiveDecays   ***not available in twiki***
Xsec[28] =  3.36;                  // single top s-channel_4f_leptonDecays
Xsec[29] =  35.85;                 // single top tW_top_5f_inclusiveDecays
Xsec[30] =  35.85;                 // single top tW_antitop_5f_inclusiveDecays

Xsec[31] = 20790;                   // GJets_HT-40To100
Xsec[32] = 9238;                    // GJets_HT-100To200
Xsec[33] = 2305;                    // GJets_HT-200To400
Xsec[34] = 274.4;                   // GJets_HT-400To600
Xsec[35] = 93.46;                   // GJets_HT-600ToInf

Xsec[36] = 831.76;                  // ttbar     ***not available in twiki***

//float QCDSF=1.2166;

Xsec[37] = 0;    //246300000;              // QCD_HT50to100
Xsec[38] = 0;    //27990000;               // QCD_HT100to200
Xsec[39] = 0;    //1712000 * QCDSF;                // QCD_HT200to300
Xsec[40] = 0;    //347700 * QCDSF;                 // QCD_HT300to500
Xsec[41] = 32100 * QCDSF;                  // QCD_HT500to700
Xsec[42] = 6831 * QCDSF;                   // QCD_HT700to1000
Xsec[43] = 1207 * QCDSF;                   // QCD_HT1000to1500
Xsec[44] = 119.9 * QCDSF;                   // QCD_HT1500to2000
Xsec[45] = 25.24 * QCDSF;                   // QCD_HT2000toInf


//Xsec[38] = 93.46;                   // Dummy

double metbins[4]={200,350,500,1000};
TH1F* h_mc[nfiles] ;
float normalization[nfiles];
TH1F *h_data;
TH1F *h_temp;
TH1F *hnew;
TH1F *h_total;

//cout << to_string(nfiles) << endl;

for(int i =0; i<84; i++){
    if(VERBOSE) cout << "Reading file #" << to_string(i+1) << ": " << filenameString[i] << endl;
    fIn = new TFile(filenameString[i],"READ");

    //if(VARIABLEBINS){
    //h_temp = (TH1F*) fIn->Get(histnameString);

    //h_temp->Rebin(REBIN);
    //h_temp->Rebin(3,"hnew",metbins);
    //h_temp->Sumw2();
    //h_mc[i]= (TH1F*)hnew->Clone();
    //}else{
    h_mc[i] = (TH1F*) fIn->Get(histnameString);
    h_mc[i]->Rebin(REBIN);
    h_mc[i]->Sumw2();
    //}
    //h_total      = (TH1F*) fIn->Get("nEvents_weight");
     h_total      = (TH1F*) fIn->Get("h_total");
     
    //std::cout<<" normalization for = "<<i<<"  "<<filenameString[i]<<"   "<<h_mc[i]->Integral()
    //<<std::endl;

    if(h_total->Integral()>0) normalization[i]     = (lumi* Xsec[i])/(h_total->Integral()*BLINDFACTOR);
       else normalization[i]      = 0;
     //cout<<"normalization :" << normalization[i] << std::endl;

     Integral[i] = h_mc[i]->Integral();
     if(Integral[i]<=0) Integral_Error[i] = 0.0;
     if(Integral[i]>0) Integral_Error[i] = TMath::Sqrt(Integral[i]) * normalization[i];
     h_mc[i]->Scale(normalization[i]);
 }


fIn = new TFile(filenameString[84],"READ");
if(VARIABLEBINS){
h_temp =(TH1F*) fIn->Get(histnameString);
h_temp->Rebin(3,"hnew",metbins);
h_data= (TH1F*)hnew->Clone();
}else{
h_data = (TH1F*) fIn->Get(histnameString);
h_data->Rebin(REBIN);
h_data->Sumw2();
}


data_obs = (TH1F*) fIn->Get(histnameString);

DIBOSON   = (TH1F*)h_mc[0]->Clone();
DIBOSON->Add(h_mc[1]);
DIBOSON->Add(h_mc[2]);

ZJets     = (TH1F*)h_mc[3]->Clone();
for(int zjets1 = 4; zjets1 < 10; zjets1++){
ZJets->Add(h_mc[zjets1]);}

DYJets    = (TH1F*)h_mc[10]->Clone();
for(int DYjets = 11; DYjets < 18; DYjets++){
DYJets->Add(h_mc[DYjets]);}

WJets     = (TH1F*)h_mc[18]->Clone();
for(int wjets1 = 19; wjets1 < 26; wjets1++){
WJets->Add(h_mc[wjets1]);}

STop   = (TH1F*)h_mc[26]->Clone();
for(int ttjets = 27; ttjets < 31; ttjets++){
STop->Add(h_mc[ttjets]);}

GJets   = (TH1F*)h_mc[31]->Clone();
for(int gjets = 32; gjets < 36; gjets++){              
GJets->Add(h_mc[gjets]);}

TT        = (TH1F*)h_mc[36]->Clone();

QCD   = (TH1F*)h_mc[37]->Clone();
for(int qcd = 38; qcd < 46; qcd++){              
QCD->Add(h_mc[qcd]);}

float ZJetsCount    =   ZJets->Integral();
float DYJetsCount   =   DYJets->Integral();
float WJetsCount    =   WJets->Integral();
float STopCount     =   STop->Integral();
float GJetsCount    =   GJets->Integral();
float TTCount       =   TT->Integral();
float VVCount       =   DIBOSON->Integral();
float QCDCount      =   QCD->Integral();

TString DYLegend, WLegend, GLegend, ZLegend, STLegend, TTLegend, VVLegend, QCDLegend;

//if (ISCUTFLOW) {
if (1) {
    DYLegend    =   "Z(ll) + jets";
    WLegend     =   "W(l#nu) + jets";
    GLegend     =   "G jets";
    ZLegend     =   "Z(#nu#nu) + jets";
    STLegend    =   "Single t";
    TTLegend    =   "Top";
    VVLegend    =   "VV";
    QCDLegend   =   "QCD Multijet"; 
} else {
    DYLegend    =   "Z(ll) + jets: "+std::to_string(int(DYJetsCount));
    WLegend     =   "W(l#nu) + jets: "+std::to_string(int(WJetsCount));
    GLegend     =   "G jets: "+std::to_string(int(GJetsCount));
    ZLegend     =   "Z(#nu#nu) + jets: "+std::to_string(int(ZJetsCount));
    STLegend    =   "Single t: "+std::to_string(int(STopCount));
    TTLegend    =   "Top: "+std::to_string(int(TTCount));
    VVLegend    =   "VV: "+std::to_string(int(VVCount));
    QCDLegend   =   "QCD Multijet: "+std::to_string(int(QCDCount));
}

//NORATIOPLOT=0;

 //Legend
 TLegend *legend;
 
/* if(NORATIOPLOT){
    legend = new TLegend(0.57, 0.69, 0.94,0.90,NULL,"brNDC");
    legend->SetTextSize(0.020);
 }else{ */
 
 
float zj_i = ZJets->Integral();
float dyj_i = DYJets->Integral();
float wj_i = WJets->Integral();
float tt_i = TT->Integral();
float st_i = STop->Integral();
float gj_i = GJets->Integral();
float db_i = DIBOSON->Integral();
float qc_i = QCD->Integral();
float mcsum = zj_i+dyj_i+wj_i+tt_i+st_i+gj_i+db_i+qc_i;
 
legend = new TLegend(0.60, 0.70, 0.94,0.94,NULL,"brNDC"); 
legend->SetTextSize(0.020);

 legend->SetBorderSize(0);
 legend->SetLineColor(1);
 legend->SetLineStyle(1);
 legend->SetLineWidth(1);
 legend->SetFillColor(0);
 legend->SetFillStyle(0);
 legend->SetTextFont(42);
 legend->SetNColumns(2);
 
/* if (QCDSF==1) {
    legend->AddEntry(h_data,"Data","PEL");
 } 
 
 if (!NORATIOPLOT && QCDSF!=1) {
     legend->AddEntry(h_data,"Data","PEL");
     legend->AddEntry(DYJets,DYLegend,"f");
 } else {
     legend->AddEntry(ZJets,ZLegend,"f");
 }      */
 
 cout << "DY:" << dyj_i << endl;
 cout << "Total:" << mcsum << endl;
 
 float legendthres = 0.008;
 
 if (!NORATIOPLOT) legend->AddEntry(h_data,"Data","PEL");
 if (dyj_i/mcsum > legendthres) legend->AddEntry(DYJets,DYLegend,"f");
 if (zj_i/mcsum > legendthres) legend->AddEntry(ZJets,ZLegend,"f");
 if (wj_i/mcsum > legendthres) legend->AddEntry(WJets,WLegend,"f");
 if (tt_i/mcsum > legendthres) legend->AddEntry(TT,TTLegend,"f");
 if (st_i/mcsum > 0.) legend->AddEntry(STop,STLegend,"f");
 if (gj_i/mcsum > 0.) legend->AddEntry(GJets,GLegend,"f");
 if (db_i/mcsum > 0.) legend->AddEntry(DIBOSON,VVLegend,"f");
 if (qc_i/mcsum > 0.) legend->AddEntry(QCD,QCDLegend,"f");


//============== CANVAS DECLARATION ===================
TCanvas *c12 = new TCanvas("Hist", "Hist", 0,0,1000,1000);

//==================Stack==============================
THStack *hs = new THStack("hs"," ");

//Colors for Histos

DYJets->SetFillColor(kGreen+2);
//DYJets->SetLineColor(1);
DYJets->SetLineWidth(0);

ZJets->SetFillColor(kAzure+1);
//ZJets->SetLineColor(1);
ZJets->SetLineWidth(0);

DIBOSON->SetFillColor(kBlue+2);
//DIBOSON->SetLineColor(1);
DIBOSON->SetLineWidth(0);

//TT->SetFillColor(596);
TT->SetFillColor(kOrange-2);
//TT->SetLineColor(1);
TT->SetLineWidth(0);

WJets->SetFillColor(kViolet-3);
//WJets->SetLineColor(1);
WJets->SetLineWidth(0);

STop->SetFillColor(kOrange+1);
//STop->SetLineColor(1);
STop->SetLineWidth(0);

GJets->SetFillColor(kCyan-9);
//GJets->SetLineColor(1);
GJets->SetLineWidth(0);

QCD->SetFillColor(kGray+1);
//QCD->SetLineColor(1);
QCD->SetLineWidth(0);

//hadd all the histos acc to their contributions

//int order_ = 0;
//if ( zj_i > tt_i && zj_i > st_i && zj_i > wj_i && zj_i > dyj_i ) order_ = 0;
//if ( dyj_i > tt_i && dyj_i > wj_i && dyj_i > zj_i && dyj_i > st_i ) order_ = 1;
//if ( wj_i > tt_i && wj_i > zj_i && wj_i > dyj_i && wj_i > st_i ) order_ = 2;
//if ( tt_i > wj_i && tt_i > zj_i && tt_i > dyj_i && tt_i > st_i ) order_ = 3;
//if ( st_i > wj_i && st_i > zj_i && st_i > tt_i && st_i > dyj_i ) order_ = 4;


//hs->Add(DIBOSON,"hist");
//hs->Add(ZJets,"hist"); 
//hs->Add(GJets,"hist");

//if (order_==1) {
//hs->Add(WJets,"hist");
//hs->Add(TT,"hist");
//hs->Add(STop,"hist");
//hs->Add(DYJets,"hist");
//}

//if (order_==2) {
//hs->Add(DYJets,"hist");
//hs->Add(TT,"hist");
//hs->Add(STop,"hist");
//hs->Add(WJets,"hist");
//}

//if (order_==3) {
//hs->Add(WJets,"hist");
//hs->Add(DYJets,"hist");
//hs->Add(STop,"hist");
//hs->Add(TT,"hist");
//}

//if (order_==4) {
//hs->Add(WJets,"hist");
//hs->Add(DYJets,"hist");
//hs->Add(TT,"hist");
//hs->Add(STop,"hist");
//}



hs->Add(GJets,"hist");
hs->Add(DIBOSON,"hist");
hs->Add(QCD,"hist");
hs->Add(STop,"hist");
hs->Add(TT,"hist");
hs->Add(WJets,"hist");
hs->Add(ZJets,"hist"); 
hs->Add(DYJets,"hist");

h_data->SetMarkerColor(kBlack);
h_data->SetMarkerStyle(20);
//float maxi = h_data->GetMaximum();

 TH1F *Stackhist = (TH1F*)hs->GetStack()->Last(); 
 
hasNoEvents=false;
float maxi = Stackhist->GetMaximum();
cout << to_string(maxi) << endl;
if (Stackhist->GetEntries()==0){
    hasNoEvents=true;
    cout << "=============================" << endl << "No events found!" << endl << "=============================" << endl;
    fstream empfile ("Empty.txt", ios::app);
    empfile << "HISTNAME" <<endl;
    empfile.close();
}
 
 TH1F* h_err;
 h_err = (TH1F*) h_data->Clone("h_err");
 h_err = (TH1F*) h_mc[0]->Clone("h_err");
 h_err->Sumw2();
 h_err->Reset();
 //h_err->Add(h_mc[0]);
 for (int imc=1; imc<46; imc++) {
    h_err->Add(h_mc[imc]);
 }
 
// h_err->Add(h_mc[1]);
// h_err->Add(h_mc[2]);
// h_err->Add(h_mc[3]);
// h_err->Add(h_mc[4]);
// h_err->Add(h_mc[5]);
// h_err->Add(h_mc[6]);
// h_err->Add(h_mc[7]);
// h_err->Add(h_mc[8]);
// h_err->Add(h_mc[9]);
// h_err->Add(h_mc[10]);
// h_err->Add(h_mc[11]);
// h_err->Add(h_mc[12]);
// h_err->Add(h_mc[13]);
// h_err->Add(h_mc[14]);
// h_err->Add(h_mc[15]);
// h_err->Add(h_mc[16]);
// h_err->Add(h_mc[17]);
// h_err->Add(h_mc[18]);
// h_err->Add(h_mc[19]);
// h_err->Add(h_mc[20]);
// h_err->Add(h_mc[21]);
// h_err->Add(h_mc[22]);
// h_err->Add(h_mc[23]);
// h_err->Add(h_mc[24]);
// h_err->Add(h_mc[25]);
// h_err->Add(h_mc[26]);
// h_err->Add(h_mc[27]);
// h_err->Add(h_mc[28]);
// h_err->Add(h_mc[29]);
// h_err->Add(h_mc[30]);
Stackhist->SetLineWidth(2);


// for (int ibin=0; ibin<h_err->GetNbinsX();ibin++){
  // std::cout<<" stack err = "<<h_err->GetBinError(ibin)<<std::endl;
// }

//Setting canvas without log axis if it has zero entries
//int b1 = 1;
//for(int i =0; i<(int)filenameString.size()-1; i++){
//   if(ISLOG==1){
//      int en = h_mc[i]->GetEntries();
//      if (en<=0){
//         b1 = 0;
//      }
//   }
//  }
//if (b1 == 0){
//   c12->SetLogy(b1);}
//else{
c12->SetLogy(ISLOG);
   
// Upper canvas declaration
TPad *c1_2 = NULL;
 if(NORATIOPLOT){
    c1_2 = new TPad("c1_2","newpad",0,0.05,1,1);   //0.993);
    c1_2->SetRightMargin(0.04);
 }
  else{
    c1_2 = new TPad("c1_2","newpad",0,0.28,1,1);
    }
    
  c1_2->SetBottomMargin(0.03);
  c1_2->SetTopMargin(0.06);  
  c1_2->SetLogy(ISLOG);
  if(VARIABLEBINS){ c1_2->SetLogx(0);}
  c1_2->Draw();
  c1_2->cd();


hs->Draw();


std::cout<<" PREFITDIR "<<std::endl;
TH1F* h_prefit;
TFile* fprefit;
TString prefitfilename = "PREFITDIR/HISTPATH.root";
if(DRAWPREFIT){
fprefit = new TFile(prefitfilename,"READ");
h_prefit = (TH1F*) fprefit->Get("bkgSum");
std::cout<<" inside prefit loop "<<h_prefit->Integral()<<std::endl;
h_prefit->SetLineColor(kRed);
h_prefit->SetLineWidth(3);
h_prefit->SetFillColor(0);
//h_prefit->Draw("histsame");

//Stackhist->Draw("histsame");
//Stackhist->SetLineColor(kBlack);
//Stackhist->SetLineWidth(2);
//Stackhist->SetFillColor(0);

}

gStyle->SetHistTopMargin(0.);

  TH1F *Stackhist1 = (TH1F*)hs->GetStack()->Last(); 
  h_err->Draw("E2 SAME");
  h_err->Sumw2();
  h_err->SetFillColor(kGray+3);
  h_err->SetLineColor(kGray+3);
  h_err->SetMarkerSize(0);
  h_err->SetFillStyle(3013);

  h_data->SetLineColor(1);
 
//  if(!NORATIOPLOT){
//  h_data->Draw("same p e1");
//  } 
  if(!NORATIOPLOT)
  {
      h_data->Draw("same p e1");
      //if(ISLOG==1)    hs->SetMinimum(0.68);
  //    if(ISLOG==0)   hs->SetMinimum(0);
 //     if(ISLOG==0) hs->SetMaximum(maxi *1.4);
  }
 // else   {
 
      if(ISLOG==1)    hs->SetMinimum(0.68);
      if(ISLOG==0)   hs->SetMaximum(maxi*1.35);
      if(ISLOG==0)   hs->SetMinimum(0.0001);
      
      //if(!ISLOG)   hs->SetMaximum(maxi *1.70);
      //if(ISLOG)    hs->SetMaximum(maxi *5);
 // } 



//  cout <<"binofwidth = "<< binofwidth <<" binwidth_ = "<<binwidth_<<std::endl;

  double binofwidth = h_mc[0]->GetBinWidth(1);
  TString binwidth_;
  binwidth_.Form("%1.1f",binofwidth);
  
if (!hasNoEvents) {  
//hs->GetXaxis()->SetTickLength(0.07);
    hs->GetXaxis();
   hs->GetXaxis()->SetNdivisions(508);        
  if(NORATIOPLOT){
    /*hs->GetXaxis()->SetTitleSize(0.03);
    hs->GetXaxis()->SetTitleOffset(1.05);
    hs->GetXaxis()->SetTitleFont(42);
    hs->GetXaxis()->SetLabelFont(42);
    hs->GetXaxis()->SetLabelSize(.03);
    hs->GetYaxis()->SetTitle("Events");
    hs->GetYaxis()->SetTitleSize(0.12);
    hs->GetYaxis()->SetTitleOffset(1.5);
    hs->GetYaxis()->SetTitleFont(42);
    hs->GetYaxis()->SetLabelFont(42);
    hs->GetYaxis()->SetLabelSize(0.05);
    //hs->GetXaxis()->SetTitle("XAXISLABEL");*/
    
    hs->GetXaxis()->SetTitle("XAXISLABEL");
  //  hs->GetXaxis()->SetTitleSize(0.8);
 //   hs->GetXaxis()->SetTitleOffset(0.9);
    hs->GetXaxis()->SetTitleFont(42);
    hs->GetXaxis()->SetLabelFont(42);
    hs->GetXaxis()->SetLabelOffset(.01);
    hs->GetXaxis()->SetLabelSize(0.03); 
    hs->GetYaxis()->SetTitle("Events");
    hs->GetYaxis()->SetTitleSize(0.05); 
  //  hs->GetYaxis()->SetTitleOffset(1);
    hs->GetYaxis()->SetTitleFont(42);
    hs->GetYaxis()->SetLabelFont(42);
    hs->GetYaxis()->SetLabelSize(.03);
  }
  else{
    //hs->GetXaxis()->SetTitle("XAXISLABEL");
    hs->GetXaxis()->SetTitleSize(0.00);
    hs->GetXaxis()->SetTitleOffset(0.00);
    hs->GetXaxis()->SetTitleFont(42);
    hs->GetXaxis()->SetLabelFont(42);
    hs->GetXaxis()->SetLabelOffset(.01);
    hs->GetXaxis()->SetLabelSize(0.04); 
    hs->GetYaxis()->SetTitle("Events");
    hs->GetYaxis()->SetTitleSize(0.045); 
    hs->GetYaxis()->SetTitleOffset(1);
    hs->GetYaxis()->SetTitleFont(42);
    hs->GetYaxis()->SetLabelFont(42);
    hs->GetYaxis()->SetLabelSize(.03);
  }
  hs->GetXaxis()->SetRangeUser(XMIN,XMAX); 
  hs->GetXaxis()->SetNdivisions(508);        
  
 // if(VARIABLEBINS){ hs->GetXaxis()->SetNdivisions(310);}


  //legend->AddEntry(h_prefit,"Pre-fit","l");

//  legend->AddEntry(Stackhist,"Post-fit","l");
  //legend->AddEntry(ZJets,"Vh","f");
  legend->AddEntry(h_err,"Stat. Unc.","f");
    

 

 //Legend
 TLegend *legendsig;
 /*
 if(NORATIOPLOT){
 //legend = new TLegend(0.73, 0.62, 0.95,0.92,NULL,"brNDC");
    legendsig = new TLegend(0.58, 0.69, 0.92,0.94,NULL,"brNDC");
    legendsig->SetTextSize(0.020);
 }else{
    legendsig = new TLegend(0.57, 0.5, 0.94,0.65,NULL,"brNDC");
    legendsig->SetTextSize(0.030);
 } */
 
 legendsig = new TLegend(0.57, 0.5, 0.94,0.65,NULL,"brNDC");
    legendsig->SetTextSize(0.030);
 legendsig->SetBorderSize(0);
 legendsig->SetLineColor(1);
 legendsig->SetLineStyle(1);
 legendsig->SetLineWidth(1);
 legendsig->SetFillColor(0);
 legendsig->SetFillStyle(0);
 legendsig->SetTextFont(42);

 legend->Draw("same"); 
 legendsig->Draw("same");

//===========================Latex=================//

TH1F *h_MC_all = new TH1F(*((TH1F *)(hs->GetStack()->Last())));  // To get all MC event count

//TString latexCMSname= "CMS #it{#bf{Preliminary}}";//"CMS";// #it{#bf{Preliminary}}";
TString latexCMSname= "";
//TString latexPreCMSname= "#bf{CMS} #it{Preliminary}";

TString MC_count;
TString data_count;

if (ISCUTFLOW) {
    MC_count="Sel. MC="+std::to_string(int(h_MC_all->GetBinContent(h_MC_all->GetNbinsX())));
    data_count="; Sel. Data="+std::to_string(int(h_data->GetBinContent(h_data->GetNbinsX())));
}
else {
    MC_count="MC="+std::to_string(int(h_MC_all->Integral()));
    data_count="; Data="+std::to_string(int(h_data->Integral()));
}

TString hasQSF="";

if (QCDSF==1) {
    hasQSF="";
} else {
    hasQSF="; w/QCD-SF";
}

//TString latexPreCMSname="#bf{CMS} #it{Preliminary}: "+MC_count+data_count+hasQSF;
TString latexPreCMSname="#bf{CMS} #it{Preliminary}: "+MC_count+data_count;

TString latexnamemiddle;
latexnamemiddle.Form("%1.1f fb^{-1}",luminosity); 
TString latexnamepost = " (13 TeV)";
//TString latexname = latexnamepre+latexnamemiddle+latexnamepost;
TString latexname = latexnamemiddle+latexnamepost;
TString histolabel;
//histolabel = "bbMET";

histolabel = "HISTOLABEL";

//std::cout <<"HISTOLABEL"<<std::endl;

TLatex *t2a;
TLatex *t2b;
TLatex *t2c;
TLatex *t2d;

t2c = new TLatex(0.10,0.97,latexPreCMSname);
t2c->SetTextSize(0.045);

t2a = new TLatex(0.7,0.97,latexname);
t2a->SetTextSize(0.040);

/*if(NORATIOPLOT){
 t2b = new TLatex(0.22,0.85,latexCMSname);
 t2b->SetTextSize(0.036);

 t2d = new TLatex(0.15,0.79,histolabel);
 t2d->SetTextSize(0.036);

 }else{ */
 
 t2b = new TLatex(0.22,0.88,latexCMSname);
 t2b->SetTextSize(0.03); 

 t2d = new TLatex(0.46,0.9,histolabel);
 t2d->SetTextSize(0.045);

// }
 t2a->SetTextAlign(12);
 t2a->SetNDC(kTRUE);
 t2a->SetTextFont(42);

 t2b->SetTextAlign(12);
 t2b->SetNDC(kTRUE);
 t2b->SetTextFont(61);

 t2c->SetTextAlign(12);
 t2c->SetNDC(kTRUE);
 t2c->SetTextFont(42);

 t2d->SetTextAlign(12);
 t2d->SetNDC(kTRUE);
 t2d->SetTextFont(42);

  t2a->Draw("same");
  t2b->Draw("same");
  t2c->Draw("same");
  t2d->Draw("same");

//====
  

// Commenting out the signal for control region
//  h_mc[9]->Draw("hist same");
//  h_mc[10]->Draw("hist same");
//  h_mc[11]->Draw("hist same");

//*****************************************UNCOMMENT THIS PART AFTER ADDING XSECS***************
//  for (int imc=46;imc<84;imc++){
//    h_mc[imc]->Draw("hist same");
//  }
  
  
//  h_data->Draw("same p e1");
// for lower band stat and sys band



TH1F * ratiostaterr = (TH1F *) h_err->Clone("ratiostaterr");
ratiostaterr->Sumw2();
ratiostaterr->SetStats(0);
ratiostaterr->SetMinimum(0);
ratiostaterr->SetMarkerSize(0);
ratiostaterr->SetFillColor(kBlack);
ratiostaterr->SetFillStyle(3013);
 
for(Int_t i = 0; i < h_err->GetNbinsX()+2; i++) {
   ratiostaterr->SetBinContent(i, 1.0);

   if(h_err->GetBinContent(i) >1e-6 ) {  //< not empty
     double binerror = h_err->GetBinError(i)/h_err->GetBinContent(i);
     ratiostaterr->SetBinError(i, binerror);
//     cout << "bin:" <<i << "binerror:" <<h_err->GetBinContent(i)<< "errorband:" << binerror <<std::endl;
   }else {
     ratiostaterr->SetBinError(i, 999.);

   }

 }

TH1F * ratiosysterr = (TH1F *) ratiostaterr->Clone("ratiosysterr");
ratiosysterr->Sumw2();
ratiosysterr->SetMarkerSize(0);
//ratiosysterr->SetFillColor(kYellow-4);
// final plot
ratiosysterr->SetFillColor(kGray);
//ratiosysterr->SetFillStyle(3002);
ratiosysterr->SetFillStyle(1001);

for(Int_t i = 0; i < h_err->GetNbinsX()+2; i++) {
   if (h_err->GetBinContent(i) > 1e-6) {  //< not empty
   double binerror2 = (pow(h_err->GetBinError(i), 2) +
   pow(0.25 * WJets->GetBinContent(i), 2) +
//   pow(0.20 * WJets->GetBinContent(i), 2) +
   pow(0.25 * ZJets->GetBinContent(i), 2) +
   pow(0.20 * DYJets->GetBinContent(i), 2) +
   pow(0.25 * TT->GetBinContent(i), 2) +
   pow(0.20 * GJets->GetBinContent(i), 2) +
   pow(0.20 * QCD->GetBinContent(i), 2) +
   pow(0.25 * STop->GetBinContent(i), 2) +
   pow(0.20 * DIBOSON->GetBinContent(i), 2));
   double binerror = sqrt(binerror2);
   ratiosysterr->SetBinError(i, binerror / h_err->GetBinContent(i));
   }
}

TLegend * ratioleg = new TLegend(0.6, 0.88, 0.89, 0.98);
//ratioleg->SetFillColor(0);
ratioleg->SetLineColor(0);
ratioleg->SetShadowColor(0);
ratioleg->SetTextFont(42);
ratioleg->SetTextSize(0.09);
ratioleg->SetBorderSize(1);
ratioleg->SetNColumns(2);
//ratioleg->SetTextSize(0.07);
ratioleg->AddEntry(ratiosysterr, "stat + syst", "f");  //Pred. uncert. (stat + syst)
ratioleg->AddEntry(ratiostaterr, "stat", "f");  //Pred. uncert. (stat)


TLegend * ratioleg1 = new TLegend(0.35, 0.35, 0.94, 0.94);
ratioleg1->SetFillColor(0);
ratioleg1->SetLineColor(0);
ratioleg1->SetShadowColor(0);
ratioleg1->SetTextFont(42);
ratioleg1->SetTextSize(0.07);
ratioleg1->SetBorderSize(1);
ratioleg1->SetNColumns(2);
//ratioleg->SetTextSize(0.07);
//ratioleg1->AddEntry(ratiosysterr, "Pre-fit", "f");
//ratioleg1->AddEntry(ratiostaterr, "Postfit", "f");


//For DATA:
TH1F *DataMC;
TH1F *DataMCPre;

 // Lower Tpad Decalaration
 if(! NORATIOPLOT){
  c12->cd();
  DataMC    = (TH1F*) h_data->Clone();
  DataMCPre = (TH1F*) h_data->Clone();
  DataMC->Divide(Stackhist);
  
//  DataMCPre->Divide(h_prefit);
  DataMC->GetYaxis()->SetTitle("Data/Pred.");
  DataMC->GetYaxis()->SetTitleSize(0.1);
  DataMC->GetYaxis()->SetTitleOffset(0.42);
  DataMC->GetYaxis()->SetTitleFont(42);
  DataMC->GetYaxis()->SetLabelSize(0.08);
  DataMC->GetYaxis()->CenterTitle();
  DataMC->GetXaxis()->SetTitle("XAXISLABEL");
//DataMC->GetXaxis()->SetIndiceSize(0.1);
  DataMC->GetXaxis()->SetLabelSize(0.1);
  DataMC->GetXaxis()->SetTitleSize(0.1);
  DataMC->GetXaxis()->SetTitleOffset(1);
  DataMC->GetXaxis()->SetTitleFont(42);
  DataMC->GetXaxis()->SetTickLength(0.07);
  DataMC->GetXaxis()->SetLabelFont(42);
  DataMC->GetYaxis()->SetLabelFont(42);     
  
}

 TPad *c1_1 = new TPad("c1_1", "newpad",0,0.00,1,0.3);
 if (!NORATIOPLOT) c1_1->Draw();
 c1_1->cd();
 c1_1->Range(-7.862408,-629.6193,53.07125,486.5489);
 c1_1->SetFillColor(0);
 c1_1->SetTicky(1);
// c1_1->SetLeftMargin(0.1290323);
// c1_1->SetRightMargin(0.05040323);
 c1_1->SetLeftMargin(0.1);
 c1_1->SetRightMargin(0.1);
 c1_1->SetTopMargin(0.0);//0.0
 c1_1->SetBottomMargin(0.32);
 c1_1->SetFrameFillStyle(0);
 c1_1->SetFrameBorderMode(0);
 c1_1->SetFrameFillStyle(0);
 c1_1->SetFrameBorderMode(0);
 c1_1->SetLogy(0);
 

 
if(!NORATIOPLOT) {
    if(VARIABLEBINS){
        c1_1->SetLogx(0);
        DataMC->GetXaxis()->SetMoreLogLabels();
        DataMC->GetXaxis()->SetNoExponent();
        DataMC->GetXaxis()->SetNdivisions(508);
    }     
    DataMC->GetXaxis()->SetRangeUser(XMIN,XMAX);
    DataMC->SetMarkerSize(0.7);
    DataMC->SetMarkerStyle(20);
    DataMC->SetMarkerColor(1);
    DataMCPre->SetMarkerSize(0.7);
    DataMCPre->SetMarkerStyle(20);
    DataMCPre->SetMarkerColor(kRed);
    DataMCPre->SetLineColor(kRed);


    DataMC->Draw("P e1");
    //DataMCPre->Draw("P e1 same");
    ratiosysterr->Draw("e2 same");
    ratiostaterr->Draw("e2 same");
    DataMC->Draw("P e1 same");
    //DataMCPre->Draw("P e1 same");

    DataMC->Draw("P e1 same");
    DataMC->SetMinimum(-0.2);
    DataMC->SetMaximum(2.2);
    DataMC->GetXaxis()->SetNdivisions(508);
    DataMC->GetYaxis()->SetNdivisions(505);
    TLine* line0= new TLine(XMIN,1,XMAX,1);
    line0->SetLineStyle(2);
        line0->Draw("same");
        c1_1->SetGridy();
    ratioleg->Draw("same");
}


/*
TLegend * ratioleg2 = new TLegend(0.35, 0.45, 0.94, 0.55);
ratioleg2->SetFillColor(0);
ratioleg2->SetLineColor(0);
ratioleg2->SetShadowColor(0);
ratioleg2->SetTextFont(42);
ratioleg2->SetTextSize(0.09);
ratioleg2->SetBorderSize(1);
ratioleg2->SetNColumns(2);
//ratioleg->SetTextSize(0.07);
//ratioleg2->AddEntry(DataMCPre, "Pre-fit", "PEL");                                                                                    
//ratioleg2->AddEntry(DataMC, "Post-fit", "PEL");
ratioleg2->Draw("same");                                                                                                                                                              
*/

 

if(TEXTINFILE){ 
   
//=======================================================================
  //Calculating the contribution of each background in particular range
 // As Data DY(ee) diboson TTjets WWJets
 TAxis *xaxis = h_mc[0]->GetXaxis();
 Int_t binxmin = xaxis->FindBin(XMIN);
 Int_t binxmax = xaxis->FindBin(XMAX);
      
float dyjets = h_mc[3]->Integral()+h_mc[4]->Integral()+h_mc[5]->Integral()+h_mc[6]->Integral()+h_mc[7]->Integral()+h_mc[8]->Integral()+h_mc[9]->Integral()+h_mc[10]->Integral() ; 
float dyjets_error = TMath::Sqrt( pow(Integral_Error[3],2) + pow(Integral_Error[4],2) + pow(Integral_Error[5],2) + pow(Integral_Error[6],2) + pow(Integral_Error[7],2) + pow(Integral_Error[8],2)+ pow(Integral_Error[9],2)+ pow(Integral_Error[10],2));

float diboson_ = h_mc[0]->Integral() + h_mc[1]->Integral() + h_mc[2]->Integral();
float diboson_error = TMath::Sqrt(pow(Integral_Error[0],2) + pow(Integral_Error[1],2) + pow(Integral_Error[2],2));

float st_ = h_mc[19]->Integral() + h_mc[20]->Integral()+h_mc[21]->Integral()+h_mc[22]->Integral()+h_mc[22]->Integral() ;
float st_error = TMath::Sqrt(pow(Integral_Error[20],2) + pow(Integral_Error[21],2) + pow(Integral_Error[22],2) +pow(Integral_Error[22],2) +pow(Integral_Error[19],2) ) ;

float wjets = h_mc[11]->Integral() +h_mc[12]->Integral()+h_mc[13]->Integral()+h_mc[14]->Integral()+h_mc[15]->Integral()+h_mc[16]->Integral()+h_mc[17]->Integral()+h_mc[18]->Integral() ;
float wjets_error = TMath::Sqrt( pow(Integral_Error[11],2) + pow(Integral_Error[12],2) +pow(Integral_Error[13],2) +pow(Integral_Error[14],2) +pow(Integral_Error[15],2) +pow(Integral_Error[16],2) +pow(Integral_Error[17],2) +pow(Integral_Error[18],2));

float zjets = h_mc[3]->Integral()+h_mc[4]->Integral()+h_mc[5]->Integral()+h_mc[6]->Integral()+h_mc[7]->Integral()+h_mc[8]->Integral()+h_mc[9]->Integral()+h_mc[10]->Integral() ;
float zjets_error = TMath::Sqrt(pow(Integral_Error[3],2) + pow( Integral_Error[4],2) + pow(Integral_Error[5],2) + pow(Integral_Error[6],2) + pow(Integral_Error[7],2) + pow(Integral_Error[8],2)+ pow(Integral_Error[9],2)+ pow(Integral_Error[10],2));


  mout << "HISTPATH"            <<  " a b"<<std::endl; 
  mout << " DATA "    << h_data->Integral()  <<" 0"<< std::endl; 
  mout << " DIBOSON "   << diboson_                  <<" "<<diboson_error << std::endl;
  mout << " SingleT "      << st_ <<" "<<st_error <<  std::endl; 
  mout << " WJETS "    << wjets<< " "<<wjets_error<<std::endl;
  mout << " ZJETS "      << zjets <<" "<<zjets_error<< std::endl;
  mout << " DYJETS "   <<dyjets <<" "<<dyjets_error <<std::endl;  
 /* mout << " M600 "    << h_mc[7]->Integral() <<" "<<Integral_Error[7]<< std::endl;
  mout << " M800 "    << h_mc[8]->Integral() <<" "<<Integral_Error[8]<< std::endl;
  mout << " M1000 "    << h_mc[9]->Integral() <<" "<<Integral_Error[9]<< std::endl;
  mout << " M1200 "    << h_mc[10]->Integral() <<" "<<Integral_Error[10]<< std::endl;
  mout << " M1400 "   << h_mc[11]->Integral() <<" "<<Integral_Error[11]<< std::endl;
  mout << " M1700 "   << h_mc[12]->Integral() <<" "<<Integral_Error[12]<< std::endl;
  mout << " M2000 "   << h_mc[13]->Integral() <<" "<<Integral_Error[13]<< std::endl;
  mout << " M2500 "   << h_mc[14]->Integral() <<" "<<Integral_Error[14]<< std::endl;

*/
//  mout << "Total Bkg " <<diboson_+st_+wjets+zjets+dyjets <<" "<< diboson_error+st_error+wjets_error+zjets_error+dyjets_error <<std::endl;
  mout << "========= ======================== =====================" <<std::endl;
//=========================================================================
/*
if(VARIABLEBINS){
//  metbinsout_2.precision(3);
//metbinsout_2 << " DATA "        << h_data->GetBinContent(2)   <<" 0"<< std::endl; 
  metbinsout_2 << " DIBOSON "     << DIBOSON->GetBinContent(2)  <<" "<<DIBOSON->GetBinError(2)<< std::endl;
  metbinsout_2 << " SingleT "     << STop->GetBinContent(2)       <<" "<<STop->GetBinError(2)     <<  std::endl; 
  metbinsout_2 << " WJETS "       << WJets->GetBinContent(2)    <<" "<<WJets->GetBinError(2)  <<std::endl;
  metbinsout_2 << " ZJETS "       << ZJets->GetBinContent(2)       <<" "<<ZJets->GetBinError(2)     << std::endl;
  metbinsout_2 << " DYJETS "      <<DYJets->GetBinContent(2)    <<" "<<DYJets->GetBinError(2) <<std::endl;  
  metbinsout_2 << " M600 "    << h_mc[7]->GetBinContent(2)  <<" "<<h_mc[7]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M800 "    << h_mc[8]->GetBinContent(2)  <<" "<<h_mc[8]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M1000 "   << h_mc[9]->GetBinContent(2)  <<" "<<h_mc[9]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M1200 "   << h_mc[10]->GetBinContent(2) <<" "<<h_mc[10]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M1400 "   << h_mc[11]->GetBinContent(2) <<" "<<h_mc[11]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M1700 "   << h_mc[12]->GetBinContent(2) <<" "<<h_mc[12]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M2000 "   << h_mc[13]->GetBinContent(2) <<" "<<h_mc[13]->GetBinError(2)<< std::endl;
  metbinsout_2 << " M2500 "   << h_mc[14]->GetBinContent(2) <<" "<<h_mc[14]->GetBinError(2)<< std::endl;

  mout << "========= ======================== =====================" <<std::endl;
}

if(VARIABLEBINS){
  //metbinsout_3.precision(3);
//  metbinsout_3 << " DATA "    << h_data->GetBinContent(3)   <<" 0"<< std::endl; 
  metbinsout_3 << " DIBOSON " << DIBOSON->GetBinContent(3)  <<" "<<DIBOSON->GetBinError(3)<< std::endl;
  metbinsout_3 << " SingleT "      << STop->GetBinContent(3)       <<" "<<STop->GetBinError(3)     <<  std::endl; 
  metbinsout_3 << " WJETS "   << WJets->GetBinContent(3)    <<" "<<WJets->GetBinError(3)  <<std::endl;
  metbinsout_3 << " ZJETS "      << ZJets->GetBinContent(3)       <<" "<<ZJets->GetBinError(3)     << std::endl;
  metbinsout_3 << " DYJETS "  <<DYJets->GetBinContent(3)    <<" "<<DYJets->GetBinError(3) <<std::endl;  
  metbinsout_3 << " M600 "    << h_mc[7]->GetBinContent(3)  <<" "<<h_mc[7]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M800 "    << h_mc[8]->GetBinContent(3)  <<" "<<h_mc[8]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M1000 "   << h_mc[9]->GetBinContent(3)  <<" "<<h_mc[9]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M1200 "   << h_mc[10]->GetBinContent(3) <<" "<<h_mc[10]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M1400 "   << h_mc[11]->GetBinContent(3) <<" "<<h_mc[11]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M1700 "   << h_mc[12]->GetBinContent(3) <<" "<<h_mc[12]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M2000 "   << h_mc[13]->GetBinContent(3) <<" "<<h_mc[13]->GetBinError(3)<< std::endl;
  metbinsout_3 << " M2500 "   << h_mc[14]->GetBinContent(3) <<" "<<h_mc[14]->GetBinError(3)<< std::endl;

  mout << "========= ======================== =====================" <<std::endl;
}

if(VARIABLEBINS){
 // metbinsout_1.precision(3);
//  metbinsout_1 << " DATA "    << h_data->GetBinContent(1)   <<" 0"<< std::endl; 
  metbinsout_1 << " DIBOSON " << DIBOSON->GetBinContent(1)  <<" "<<DIBOSON->GetBinError(1)<< std::endl;
  metbinsout_1 << " SingleT "      << STop->GetBinContent(1)       <<" "<<STop->GetBinError(1)     <<  std::endl; 
  metbinsout_1 << " WJETS "   << WJets->GetBinContent(1)    <<" "<<WJets->GetBinError(1)  <<std::endl;
  metbinsout_1 << " ZJETS "      << ZJets->GetBinContent(1)       <<" "<<ZJets->GetBinError(1)     << std::endl;
  metbinsout_1 << " DYJETS "  <<DYJets->GetBinContent(1)    <<" "<<DYJets->GetBinError(1) <<std::endl;  
  metbinsout_1 << " M600 "    << h_mc[7]->GetBinContent(1)  <<" "<<h_mc[7]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M800 "    << h_mc[8]->GetBinContent(1)  <<" "<<h_mc[8]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M1000 "   << h_mc[9]->GetBinContent(1)  <<" "<<h_mc[9]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M1200 "   << h_mc[10]->GetBinContent(1) <<" "<<h_mc[10]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M1400 "   << h_mc[11]->GetBinContent(1) <<" "<<h_mc[11]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M1700 "   << h_mc[12]->GetBinContent(1) <<" "<<h_mc[12]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M2000 "   << h_mc[13]->GetBinContent(1) <<" "<<h_mc[13]->GetBinError(1)<< std::endl;
  metbinsout_1 << " M2500 "   << h_mc[14]->GetBinContent(1) <<" "<<h_mc[14]->GetBinError(1)<< std::endl;
 
 mout << "========= ======================== =====================" <<std::endl;
}
*/



// --------------------- table output --------------------
  tableout.precision(3);
  tableout << " Z \\rightarrow \\nu \\nu+Jets & "<< dyjets <<" \\pm "<<dyjets_error <<"\\\\"<<std::endl;
  tableout << " Z \\rightarrow ll + Jets & "<< zjets <<" \\pm "<<zjets_error <<"\\\\"<<std::endl;
  tableout << " st  & "<< st_ <<" \\pm "<<st_error <<"\\\\"<< std::endl; 
  tableout << " W+Jets & "  <<wjets <<" \\pm "<<wjets_error <<"\\\\"<< std::endl;
  tableout << " WW/WZ/ZZ & " << diboson_ <<" \\pm "<<diboson_error  <<"\\\\"<< std::endl;
/*  tableout << " M600  & "    << h_mc[7]->Integral() <<" \\pm "<<Integral_Error[7]<<"\\\\"<< std::endl;
  tableout << " M800  & "    << h_mc[8]->Integral() <<" \\pm "<<Integral_Error[8]<<"\\\\"<< std::endl;
  tableout << " M1000 &  "    << h_mc[9]->Integral() <<" \\pm "<<Integral_Error[9]<<"\\\\"<< std::endl;
  tableout << " M1200 &  "    << h_mc[10]->Integral() <<" \\pm "<<Integral_Error[10]<<"\\\\"<< std::endl;
  tableout << " M1400 &  "   << h_mc[11]->Integral() <<" \\pm "<<Integral_Error[11]<<"\\\\"<< std::endl;
  tableout << " M1700 &  "   << h_mc[12]->Integral() <<" \\pm "<<Integral_Error[12]<<"\\\\"<< std::endl;
  tableout << " M2000 &  "   << h_mc[13]->Integral() <<" \\pm "<<Integral_Error[13]<<"\\\\"<< std::endl;
  tableout << " M2500 &  "   << h_mc[14]->Integral() <<" \\pm "<<Integral_Error[14]<<"\\\\"<< std::endl;*/
  tableout << " DATA  & "    << h_data->Integral()  << std::endl; 


float a = wjets;
float b = st_;
//float c = h_data->Integral() - (diboson_ + zh + dyjets);

tableout << "a "<<a<<" "<<" b "<<b<<" "<<" c "<<"c"<<std::endl;
tableout << a <<"  "<< b <<"  " << diboson_ <<"  " << zjets <<"  "<< dyjets<<std::endl;
tableout<<" total_bkg "<<a + b + diboson_ + zjets + dyjets<<std::endl;
tableout<< " "<<std::endl;
}
// c1_1->Draw();
 c12->Draw();
 
if(ISLOG==0){
 c12->SaveAs(DirPreName+dirpathname +"/bbMETPdf/HISTPATH.pdf");
 c12->SaveAs(DirPreName+dirpathname +"/bbMETPng/HISTPATH.png");
// cout << "Saved." << endl;
// c12->SaveAs(DirPreName+dirpathname +"/bbMETROOT/HISTPATH.root");                                                                         
 rout<<"<hr/>"<<std::endl;
 rout<<"<table class=\"\"> <tr><td><img src=\""<<"DYPng/HISTPATH.png\" height=\"400\" width=\"400\"></td>   </tr> </table>"<<std::endl;

}
 
if(ISLOG==1){
 c12->SaveAs(DirPreName+dirpathname +"/bbMETPdf/HISTPATH_log.pdf");
 c12->SaveAs(DirPreName+dirpathname +"/bbMETPng/HISTPATH_log.png");
 cout << "Saved." << endl;
// c12->SaveAs(DirPreName+dirpathname +"/bbMETROOT/HISTPATH_log.root");                                                                        
}

fshape->cd();
//Save root files for datacards
Stackhist->SetNameTitle("bkgSum","bkgSum");
Stackhist->Write();

/*
monoHbbM600->SetNameTitle("monoHbbM600","monoHbbM600"); 
monoHbbM600->Write();
monoHbbM800->SetNameTitle("monoHbbM800","monoHbbM800");
monoHbbM800->Write(); 
monoHbbM1000->SetNameTitle("monoHbbM1000","monoHbbM1000");
monoHbbM1000->Write();
monoHbbM1200->SetNameTitle("monoHbbM1200","monoHbbM1200");
monoHbbM1200->Write();
monoHbbM1400->SetNameTitle("monoHbbM1400","monoHbbM1400");
monoHbbM1400->Write(); 
monoHbbM1700->SetNameTitle("monoHbbM1700","monoHbbM1700");
monoHbbM1700->Write();
monoHbbM2000->SetNameTitle("monoHbbM2000","monoHbbM2000");
monoHbbM2000->Write();
monoHbbM2500->SetNameTitle("monoHbbM2500","monoHbbM2500");
monoHbbM2500->Write();
*/
DIBOSON->SetNameTitle("DIBOSON","DIBOSON");
DIBOSON->Write();
ZJets->SetNameTitle("ZJets","ZJets");
ZJets->Write();
GJets->SetNameTitle("GJets","GJets");
GJets->Write();
QCD->SetNameTitle("QCD","QCD");
QCD->Write();
STop->SetNameTitle("STop","STop");
STop->Write();
TT->SetNameTitle("TT","TT");
TT->Write();
WJets->SetNameTitle("WJets","WJets");
WJets->Write();
DYJets->SetNameTitle("DYJets","DYJets");
DYJets->Write(); 
data_obs->SetNameTitle("data_obs","data_obs");
data_obs->Write();
fshape->Write();
fshape->Close();

if (VARIABLEBINS)
{
system("cp "+outputshapefilename+" "+DirPreName+"METBIN_1");
system("cp "+outputshapefilename+" "+DirPreName+"METBIN_2");
system("cp "+outputshapefilename+" "+DirPreName+"METBIN_3");
}
}
}
