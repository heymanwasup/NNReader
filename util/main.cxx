#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <TH1D.h>
#include <iostream>
#include <TMVA/ROCCalc.h>
#include <string>
#include <vector>
#include <TH1F.h>
#include "NNReader/NNReader.h"

using namespace std;
using namespace TMVA;

int main()
{

  TFile * file = TFile::Open("/afs/cern.ch/user/c/chenc/public/forChangqiao/splited_traintest_mva24.root");
  string model = "/afs/cern.ch/work/c/chenc/ML/Keras_ML/data/nn_test_scale_2jE.json";

  NNReader reader;
  reader.BookModel(model);

  TTree * sig_tree = (TTree*) file -> Get("test_sig");
  TTree * bkg_tree = (TTree*) file -> Get("test_bkg");

  map<string, float> T ;
  vector<string> branches = {"MET","HT","dPhiMETdijet","pTB1","pTB2","mBB","dRBB","dEtaBB","EventWeight"};

  for(auto br : branches){
    T[br] = 0.;
    sig_tree->SetBranchAddress(br.c_str(),&T[br]);
    bkg_tree->SetBranchAddress(br.c_str(),&T[br]);
    reader.AddVariable(br, T[br]);
  }

  TFile * out = new TFile("./test_roc.root","recreate");
  TH1D * sig = new TH1D("sig","sig",20000,-0.1,1.1);
  TH1D * bkg = new TH1D("bkg","bkg",20000,-0.1,1.1);

  int N;

  N = sig_tree -> GetEntries();
  for (int n=0;n<N;n++){
    double score = reader.Evaluate();
    sig_tree -> GetEntry(n);
    cout << "score = "<<score<<endl;

    sig -> Fill(score,T["EventWeight"]);
  }
  
  N = bkg_tree -> GetEntries();
  for (int n=0;n<N;n++){
    bkg_tree -> GetEntry(n);
    double score = reader.Evaluate();
    bkg -> Fill(score,T["EventWeight"]);
  }

  TMVA::ROCCalc *  roccalc = new TMVA::ROCCalc(sig,bkg);
  TH1D * roc = roccalc->GetROC();

  out->cd();
  roc->Write();

  sig->Write();
  bkg->Write();

  return 0;
}
