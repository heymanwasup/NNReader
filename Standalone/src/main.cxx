#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH1D.h>
#include <TMVA/ROCCalc.h>

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "NNReader.h"

using namespace std;
using namespace TMVA;

void FillHist(TTree * tree, map<string,float> & T, TH1D * hist, NNReader & reader)
{
  sleep(3);
  int N;
  N = tree -> GetEntries();
  for (int n=0;n<N;n++){
    if(n%5000==0){ 
      cout <<"   processed "<< n << " events" << endl;
    }
    tree -> GetEntry(n);
    double score = reader.Evaluate();
    hist -> Fill(score,T["EventWeight"]);
  }
}

int main(int argc, char * argv[])
{
  //parse options
  string runtag;
  string cate; 
  string cut;
  if(argc==3) {
    runtag = string(argv[1]);

    int category = atoi(argv[2]);
    int parity   = category%2;
    int nJ       = 2 + (category>>1)%2;

    map<int,string> trans = {{0,"E"},{1,"O"}};
    cate = to_string(nJ) + "j" + trans[parity];      

    map<int,string> cut_j = {{2,"(nJ>1.5)&&(nJ<2.5)"},{3,"(nJ>2.5)&&(nJ<3.5)"}};
    map<int,string> cut_p = {
      {0,"(EventNumberMod2>-0.5)&&(EventNumberMod2<0.5)"},
      {1,"(EventNumberMod2>0.5)&&(EventNumberMod2<1.5)"},
    };
    cut = cut_j[nJ] + "&&" + cut_p[parity];
    cout << "Working on the "<< cate << " category" <<endl;

  } else {
    cout <<"Usage: main <runtag> <category>"<<endl;
    cout <<" 0  <=  category  <  4"<<endl;
    cout <<"    parity(Even or Odd) = category%2"<<endl;
    cout <<"    num of jets = 2+(category>>1)%2"<<endl;
    return 1;
  }

  TFile * file = TFile::Open("/afs/cern.ch/user/c/chenc/public/forChangqiao/splited_traintest_mva24.root");
  string s_out = "./out_" + runtag + "_" + cate + ".root";
  TFile * out = new TFile(s_out.c_str(),"recreate");

  TTree * sig_tree = ((TTree*) file -> Get("test_sig")) -> CopyTree( cut.c_str());
  TTree * bkg_tree = ((TTree*) file -> Get("test_bkg")) -> CopyTree( cut.c_str());

  NNReader reader;
  
  string model = "./data/nn_" + runtag + "_" + cate + ".json";

  cout << "Loading the model:\n\t" << model << endl; 
  reader.BookModel(model);
  //book variables
  map<string, float> T ;
  vector<string> branches = {"MET","HT","dPhiMETdijet","pTB1","pTB2","mBB","dRBB","dEtaBB","pTJ3","mBBJ","EventWeight"};
  for(auto br : branches){
    T[br] = 0.;
    sig_tree->SetBranchAddress(br.c_str(),&T[br]);
    bkg_tree->SetBranchAddress(br.c_str(),&T[br]);
    reader.AddVariable(br, T[br]);
  }

  //fill <sig, bkg, roc> hists
  out -> cd();
  TH1D * sig = new TH1D("sig","sig",20000,-0.1,1.1);
  TH1D * bkg = new TH1D("bkg","bkg",20000,-0.1,1.1);

  cout <<" Processing signal..."<<endl;
  FillHist(sig_tree,T,sig,reader);
 
  cout <<" Processing background..."<<endl;
  FillHist(bkg_tree,T,bkg,reader);

  TMVA::ROCCalc *  roccalc = new TMVA::ROCCalc(sig,bkg);
  TH1D * roc = roccalc->GetROC();
  cout << "ROC AUC = "<< roc -> Integral() <<endl;

  out->cd();

  roc->Write();
  sig->Write();
  bkg->Write();

  delete sig_tree;
  delete bkg_tree;

  out->ls();


  out->Close();
  return 0;
}
