#include <iostream>
const int n = 10000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, no_mpi = 0, nspecies = 0,
    tag[n] = {0}, rapmultpoint5 = 0, toward[4] = {0}, toward_p = 0,
    toward_np = 0, transverse[4] = {0}, transverse_p = 0, transverse_np = 0,
    away[4] = {0}, away_p = 0, away_np = 0;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT[n] = {0}, mass[n] = {0},
       pt_hat(0);
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0},
       pTlead[4] = {0}, sp(0), pTD0plead(0), pTD0nplead(0);
// const int nevents = 100000000;
void print_progress_bar(long current, long total, std::string done = "=",
                        std::string remain = ".") {
  // ANSI color codes for green, yellow, red
  const char *GREEN = "\033[1;32m";
  const char *YELLOW = "\033[1;33m";
  const char *RED = "\033[1;31m";
  const char *RESET = "\033[0m";
  const char *BLUE = "\033[1;34m";
  const int bar_width = 50;
  float progress = float(current) / total;
  int pos = bar_width * progress;

  std::cout << "\r" << BLUE << "[";
  for (int i = 0; i < bar_width; ++i) {
    if (i < pos)
      std::cout << GREEN << done;
    else if (i == pos)
      std::cout << ">";
    else
      std::cout << RED << remain;
  }
  std::cout << BLUE << "] " << YELLOW << int(progress * 100) << "% " << RESET
            << "(" << current << "/" << total << ")" << std::flush;
}

void proftograph(TProfile *pf, TGraphErrors *gr, Double_t scalex = 1.0,
                 Double_t scaley = 1.0) {
  for (int i = 0; i < pf->GetNbinsX(); i++) {
    gr->SetPoint(i, pf->GetBinCenter(i + 1) / scalex,
                 pf->GetBinContent(i + 1) / scaley);
    gr->SetPointError(
        i, 0 * pf->GetBinWidth(i + 1) / scalex,
        pf->GetBinError(i + 1) /
            scaley); // zero is multiplied in order to get zero error in x-axis
  }
}

void S0vspTlead(TString CRcase = "on", TString MPIcase = "on") {

  TFile *f;
  if (CRcase == "on" && MPIcase == "on") {
    f = TFile::Open("/mnt/5F1B0F4D3322F79F/Purnima/D0spherocity_work1/"
                    "D0promptndn0nprompt/rootfiles/CR-" +
                    CRcase + "-MPI-" + MPIcase + "/pp-on-on.root");
  } else if (CRcase == "on" && MPIcase == "off") {
    f = TFile::Open("/mnt/5F1B0F4D3322F79F/Purnima/D0spherocity_work1/"
                    "D0promptndn0nprompt/rootfiles/CR-" +
                    CRcase + "-MPI-" + MPIcase + "/pp-on-off.root");
  } else if (CRcase == "off" && MPIcase == "on") {
    f = TFile::Open("/mnt/5F1B0F4D3322F79F/Purnima/D0spherocity_work1/"
                    "D0promptndn0nprompt/rootfiles/CR-" +
                    CRcase + "-MPI-" + MPIcase + "/pp-off-on.root");
  } else {
    std::cerr << "Error: Can not run with both CR and MPI cases off" << endl;
    return;
  }

  TTree *theTree = (TTree *)f->Get("t");

  theTree->SetBranchAddress("ntrack", &ntrack);
  theTree->SetBranchAddress("nspecies", &nspecies);
  theTree->SetBranchAddress("charge", charge);
  theTree->SetBranchAddress("px", px);
  theTree->SetBranchAddress("py", py);
  theTree->SetBranchAddress("pz", pz);
  theTree->SetBranchAddress("energy", energy);
  theTree->SetBranchAddress("tag", tag);
  theTree->SetBranchAddress("pt_hat", &pt_hat);
  theTree->SetBranchAddress("no_mpi", &no_mpi);
  theTree->SetBranchAddress("pTlead", pTlead);
  theTree->SetBranchAddress("pT", pT);
  theTree->SetBranchAddress("rapmultpoint5", &rapmultpoint5);
  theTree->SetBranchAddress("toward", toward);
  theTree->SetBranchAddress("transverse", transverse);
  theTree->SetBranchAddress("away", away);
  theTree->SetBranchAddress("toward", toward);
  theTree->SetBranchAddress("transverse", transverse);
  theTree->SetBranchAddress("away", away);
  theTree->SetBranchAddress("spherocity", &sp);
  const Int_t XBINS = 11;

  Double_t pThat[XBINS + 1] = {2.0, 3.0,  4.0,  5.0,  6.0,  7.0,
                               8.0, 10.0, 12.0, 16.0, 24.0, 100};

  Double_t pTbins[XBINS + 1] = {1.0, 2.0, 3.0,  4.0,  5.0,  6.0,
                                7.0, 8.0, 10.0, 12.0, 16.0, 24.0};

  TProfile *hsphp = new TProfile("", "", XBINS, pTbins, "");
  hsphp->SetLineColor(kRed + 2);
  hsphp->SetMarkerSize(2);
  TProfile *hsphnp = new TProfile("", "", XBINS, pTbins, "");
  hsphnp->SetLineColor(kRed + 2);
  hsphnp->SetMarkerSize(2);
  int prompt = 0;
  int non_pro = 0;
  int inclusive = 0;

  TLorentzVector *vec = new TLorentzVector();

  const long nevents = (long)theTree->GetEntries();
  // const int nevents = 100000;

  // long counter(0);
  for (long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);

    bool promptD0 = false;
    bool nonpromptD0 = false;
    bool ncharge = false;

    //  for (int j=0; j<nspecies;j++)

    if (pTlead[1] > 0.15)

    {
      promptD0 = true;
      pTD0plead = pTlead[1];
      toward_p = toward[1];
      transverse_p = transverse[1];
      away_p = away[1];
    }

    // if (promptD0) {cout<<pTD0plead<<endl;}
    if (pTlead[2] > 0.15) {
      nonpromptD0 = true;
      pTD0nplead = pTlead[2];
      toward_np = toward[2];
      transverse_np = transverse[2];
      away_np = away[2];
    }
    // pTlead Vs pThat
    if (promptD0) {
      hsphp->Fill(pTD0plead, sp);
      // pTlead Vs Nmpi
    }
    if (nonpromptD0) {

      hsphnp->Fill(pTD0nplead, sp);
    }
    //     std::cout << typeid(pTD0plead).name() << std::endl;
    // std::cout << typeid(pThat).name() << std::endl;

    if (i % 100000 == 0)
      print_progress_bar(i, nevents);
    // cout<<rapmultpoint5<<endl;
  }
  print_progress_bar(nevents, nevents);

  // cout << "Avg Nmpi D0 prompt: "<<hD0MPIp->GetMean(1) << endl;
  // cout << prompt << endl;
  // cout << non_pro << endl;

  TFile *f1 =
      new TFile("AvgS0_pTD0lead_CR" + CRcase + "_MPI" + MPIcase + "_plot.root",
                "recreate"); //------- Name Change

  hsphp->Write("Spherop");
  hsphnp->Write("Spheronp");

  f1->Close();
}
