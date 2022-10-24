#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"

void SelectCategoryA(){
//Get old file, old tree and set top branch address
  TString nameoldfile_L="mergedfile_eL_pR.root";
  TFile *oldfile_L = new TFile(nameoldfile_L);
  TTree *oldtree_L = (TTree*)oldfile_L->Get("Stats");
  Int_t nentries_L = (Int_t)oldtree_L->GetEntries();

  TString nameoldfile_R="mergedfile_eR_pL.root";
  TFile *oldfile_R = new TFile(nameoldfile_R);
  TTree *oldtree_R = (TTree*)oldfile_R->Get("Stats");
  Int_t nentries_R = (Int_t)oldtree_R->GetEntries();
  
  Int_t jet_nvtx_L;
  oldtree_L->SetBranchAddress("jet_nvtx",&jet_nvtx_L);
  
  Int_t jet_nvtx_R;
  oldtree_R->SetBranchAddress("jet_nvtx",&jet_nvtx_R);

  //Create a new file + a clone of old tree in new file
  TString newfilename_L="catA_eL_pR.root";
  cout<<"Preparing eL_pR TTree"<<endl;
  cout<<"...takes some time"<<endl;
  TFile *newfile_L = new TFile(newfilename_L,"recreate");
  TTree *newtree_L = oldtree_L->CloneTree();
  newtree_L->Reset();
  cout<<"Filling eL_pR TTree"<<endl;
  //i<nentries_L
  for (Int_t i=0;i<nentries_L; i++) {
    oldtree_L->GetEntry(i);
    if(i % 1000 == 0){
      Float_t current=i;
      Float_t total=nentries_L;
      Float_t percentage=(current/total)*100;
      cout<<"eL_pR %: "<<percentage<<endl;
    }
    //fill catA:
    if (jet_nvtx_L == 0){newtree_L->Fill();}
  }

  TString newfilename_R="catA_eR_pL.root";
  cout<<"Preparing eR_pL TTree"<<endl;
  cout<<"...takes some time"<<endl;
  TFile *newfile_R = new TFile(newfilename_R,"recreate");
  TTree *newtree_R = oldtree_R->CloneTree();
  newtree_R->Reset();
  cout<<"Filling eR_pL TTree"<<endl;
  //i<nentries_L        
  for (Int_t i=0;i<nentries_R; i++) {
    oldtree_R->GetEntry(i);
    if(i % 1000 == 0){
      Float_t current=i;
      Float_t total=nentries_R;
      Float_t percentage=(current/total)*100;
      cout<<"eR_pL %: "<<percentage<<endl;
    }
    //fill catA:                                        
    if (jet_nvtx_R == 0){newtree_R->Fill();}
  }

  //newtree_L->Print();
  newtree_L->AutoSave();
  delete oldfile_L;
  delete newfile_L;

  //newtree_R->Print();                                                                                                                
  newtree_R->AutoSave();
  delete oldfile_R;
  delete newfile_R;
}
