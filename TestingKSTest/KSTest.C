#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

#include "TGraph.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TMath.h"

#include "TStopwatch.h"
#include "TMVA/IMethod.h"
#include "TMVA/MethodBase.h"
//include "TMVA/MethodBDT.h"                                                                                                
#include "TMVA/ResultsClassification.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Reader.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TVirtualFitter.h"

#include "TMVA/DataSet.h"
#include "TMVA/ResultsMulticlass.h"
#include "TMatrixT.h"

void KSTest(){

  TFile* outputfile=TFile::Open("TMVAMulticlass.root");
  //outputfile.cd("dataloader");
  TTree* TestTree=(TTree*) outputfile->Get("dataloader/TestTree");
  
  Int_t test_entries=TestTree->GetEntries();
  cout<<"Test TTree entries: "<<test_entries<<endl;

  

  TH1F* test_B_histo=new TH1F("test_B_histo","test_B_histo",100,0,1);
  TH1F* test_C_histo=new TH1F("test_C_histo","test_C_histo",100,0,1);
  TH1F* test_O_histo=new TH1F("test_O_histo","test_O_histo",100,0,1);
  
  for(int i=0;i<test_entries;i++){
    TestTree->GetEntry(i);
    Float_t value_B=TestTree->GetBranch("myMVA")->GetLeaf("jet_B")->GetValue(0);       
    Float_t value_C=TestTree->GetBranch("myMVA")->GetLeaf("jet_C")->GetValue(0);
    Float_t value_O=TestTree->GetBranch("myMVA")->GetLeaf("jet_O")->GetValue(0);
    test_B_histo->Fill(value_B);
    test_C_histo->Fill(value_C);
    test_O_histo->Fill(value_O);
    

  }

  
  TTree* TrainTree=(TTree*) outputfile->Get("dataloader/TrainTree");

  Int_t train_entries=TrainTree->GetEntries();
  cout<<"Train TTree entries: "<<train_entries<<endl;

  TH1F* train_B_histo=new TH1F("train_B_histo","train_B_histo",100,0,1);
  TH1F* train_C_histo=new TH1F("train_C_histo","train_C_histo",100,0,1);
  TH1F* train_O_histo=new TH1F("train_O_histo","train_O_histo",100,0,1);



  for(int i=0;i<train_entries;i++){
    TrainTree->GetEntry(i);

    Float_t value_B=TrainTree->GetBranch("myMVA")->GetLeaf("jet_B")->GetValue(0);
    Float_t value_C=TrainTree->GetBranch("myMVA")->GetLeaf("jet_C")->GetValue(0);
    Float_t value_O=TrainTree->GetBranch("myMVA")->GetLeaf("jet_O")->GetValue(0);
    train_B_histo->Fill(value_B);
    train_C_histo->Fill(value_C);
    train_O_histo->Fill(value_O);
  }

  for(int i=0;i<100;i++){
    Int_t bincontent_B=test_B_histo->GetBinContent(i);
    Float_t error_B=pow(bincontent_B,0.5);
    test_B_histo->SetBinError(i,error_B);
    
    Int_t bincontent_C=test_C_histo->GetBinContent(i);
    Float_t error_C=pow(bincontent_C,0.5);
    test_C_histo->SetBinError(i,error_C);

    Int_t bincontent_O=test_O_histo->GetBinContent(i);
    Float_t error_O=pow(bincontent_O,0.5);
    test_O_histo->SetBinError(i,error_O);
    
}

  
  TCanvas* canvas = new TCanvas("canvas","canvas",1000,300);
  canvas->Divide(3);
  canvas->cd(1);
  test_B_histo->Draw();
  train_B_histo->SetLineColor(2);
  train_B_histo->Draw("same");

  canvas->cd(2);
  test_C_histo->Draw();
  train_C_histo->SetLineColor(2);
  train_C_histo->Draw("same");

  canvas->cd(3);
  test_O_histo->Draw();
  train_O_histo->SetLineColor(2);
  train_O_histo->Draw("same");

  canvas->SaveAs("KS-Test.png");

  Float_t ks_b=test_B_histo->KolmogorovTest(train_B_histo);
  Float_t ks_c=test_C_histo->KolmogorovTest(train_C_histo);
  Float_t ks_o=test_O_histo->KolmogorovTest(train_O_histo);
  
  Float_t KS_BC=TMath::Min(ks_b, ks_c);
  Float_t KS_BO=TMath::Min(ks_b, ks_o);
  
  Float_t KS=TMath::Min(KS_BC, KS_BO);

  cout<<"KS for b: "<<ks_b<<endl;
  cout<<"KS for c: "<<ks_c<<endl;
  cout<<"KS for uds: "<<ks_o<<endl;
  cout<<"KS: "<<KS<<endl;
  
  return KS;

}
