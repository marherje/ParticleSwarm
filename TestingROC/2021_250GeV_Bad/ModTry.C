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

void ModTry(){
//Get old file, old tree and set top branch address
  int n1 = 1000;
  Float_t mod1=n1 % 1000;
  if(mod1 == 0)cout<<"Mod1=0"<<endl;
  
  Float_t mod2=1001 % 1000;
  if(mod2 == 0)cout<<"Mod2=0"<<endl;
  
  Float_t mod3=1050 % 1000;
  if(mod3 == 0)cout<<"Mod3=0"<<endl;
  
  Float_t mod4=2000 % 1000;
  if(mod4 == 0)cout<<"Mod4=0"<<endl;
  
  Float_t mod5=3000 % 1000;
  if(mod5 == 0)cout<<"Mod5=0"<<endl;
  
}
