#include <iostream>
const int n = 10000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, no_mpi = 0, tag[n] = {0},
    nspecies = 0, rapmultpoint5 = 0, FT0 = 0, etamultpoint8S0 = 0,
    etamultpoint8 = 0, mult_bins[n] = {0}, integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT[n] = {0}, mass[n] = {0},
       pt_hat(0);
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0}, pTD0lead(0),
       sp(0);
// const int nevents = 100000000;
void print_progress_bar(int current, int total, std::string done = "=",
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
        i, (pf->GetBinWidth(i + 1) / 2.0) / scalex,
        pf->GetBinError(i + 1) /
            scaley); // zero is multiplied in order to get zero error in x-axis
  }
}

void AvgD0NchVspThatandMPI(TString CRcase = "on", TString MPIcase = "on") {

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
  theTree->SetBranchAddress("pT", pT);
  theTree->SetBranchAddress("rapmultpoint5", &rapmultpoint5);
  theTree->SetBranchAddress("FT0", &FT0);
  theTree->SetBranchAddress("spherocity", &sp);
  theTree->SetBranchAddress("etamultpoint8S0", &etamultpoint8S0);
  theTree->SetBranchAddress("etamultpoint8", &etamultpoint8);

  const Int_t XBINS = 11;

  Double_t pTbins[XBINS + 1] = {2.0, 3.0,  4.0,  5.0,  6.0,  7.0,
                                8.0, 10.0, 12.0, 16.0, 24.0, 100};

  int FT_1_on[7] = {3, 7, 9, 13, 18, 26, 46};
  int FT_2_on[7] = {7, 9, 13, 18, 26, 46, 150};

 
  int FT_1_off[7] = {4, 7, 10, 15, 22, 32, 58};
  int FT_2_off[7] = {7, 10, 15, 22, 32, 58, 200};

  const int *FT_1 = nullptr;
  const int *FT_2 = nullptr;

  // Choose which one to use
  if (CRcase == "on") {
   
    FT_1 = FT_1_on;
    FT_2 = FT_2_on;
  } else if (CRcase == "off") {
    
    FT_1 = FT_1_off;
    FT_2 = FT_2_off;
  } else {
    std::cerr << "Invalid CRcase value!" << std::endl;
    return;
  }

  // Now create the TProfile using selected bin array

 
  TProfile *hD0p = new TProfile("", "pThat vs prompt", XBINS, pTbins, "");
  hD0p->SetLineColor(kRed + 2);
  hD0p->SetMarkerSize(2);
  TProfile *hD0np = new TProfile("", "pThat vs nonprompt", XBINS, pTbins, "");
  hD0np->SetLineColor(kRed + 2);
  hD0np->SetMarkerSize(2);

  TProfile *hD0 = new TProfile("", "pThat vs D0inclusive", XBINS, pTbins, "");
  hD0->SetLineColor(kRed + 2);
  hD0->SetMarkerSize(2);
  TProfile *hNch = new TProfile("", "pThat vs Charged", XBINS, pTbins, "");
  hNch->SetLineColor(kRed + 2);
  hNch->SetMarkerSize(2);

  TProfile *hD0MPIp = new TProfile("", "Nmpi vs prompt", 12, 1, 49, "");
  hD0MPIp->SetLineColor(kRed + 2);
  hD0MPIp->SetMarkerSize(2);
  TProfile *hD0MPInp = new TProfile("", "Nmpi vs nonprompt", 12, 1, 49, "");
  hD0MPInp->SetLineColor(kRed + 2);
  hD0MPInp->SetMarkerSize(2);

  TProfile *hD0MPI = new TProfile("", "Nmpi vs D0inclusive", 12, 1, 49, "");
  hD0MPI->SetLineColor(kRed + 2);
  hD0MPI->SetMarkerSize(2);
  TProfile *hNchMPI = new TProfile("", "Nmpi vs Charged", 12, 1, 49, "");
  hNchMPI->SetLineColor(kRed + 2);
  hNchMPI->SetMarkerSize(2);

  int prompt = 0;
  int non_pro = 0;
  int inclusive = 0;
 
  TLorentzVector *vec = new TLorentzVector();

  const long nevents = (long)theTree->GetEntries();
  // const int nevents = 100000;

  // long counter(0);

  for (long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);
    int counterp = 0;
    int counternp = 0;
    int counter = 0;
   
    double avg_pt_prompt(0);
    double avg_pt_nonprompt(0);
    int nFT0class = 999;

    for (int m = 0; m < 7; m++) {
      if (FT0 < FT_2[m] && FT0 >= FT_1[m]) {
        nFT0class = 6 - m;
      }
    }

    for (int j = 0; j < ntrack; j++) {
      vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
      if ((abs(vec->Rapidity()) < 0.5) && vec->Pt() > 0.15) {
        counter++;
      }
      if ((abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15) && (tag[j] == 1)) {

        counterp++;
      }

      if ((abs(vec->Rapidity()) < 0.5) && vec->Pt() > 0.15 && (tag[j] == 2)) {

        counternp++;
      }
    }

   
    

    inclusive = inclusive + counter;
    prompt = prompt + counterp;
    non_pro = non_pro + counternp;

   
    hNch->Fill(pt_hat, rapmultpoint5);
    hD0p->Fill(pt_hat, counterp);
    hD0np->Fill(pt_hat, counternp);
    hD0->Fill(pt_hat, counter);

    // CRon case
    // hNchMPI->Fill(no_mpi, rapmultpoint5);
    // hD0MPInp->Fill(no_mpi, counternp);
    // hD0MPIp->Fill(no_mpi, counterp);
    // CR off case
    hNchMPI->Fill(no_mpi, rapmultpoint5);
    hD0MPInp->Fill(no_mpi, counternp);
    hD0MPIp->Fill(no_mpi, counterp);

    // if (i % 100000 == 0)
    //   print_progress_bar(i, nevents);
    // cout<<rapmultpoint5<<endl;
  }
  print_progress_bar(nevents, nevents);

 
  hD0p->Scale(1.0 / hD0p->GetMean(2));
  hD0np->Scale(1.0 / hD0np->GetMean(2));
  // hD0->Scale(1.0 / hD0->GetMean(2));
  hNch->Scale(1.0 / hNch->GetMean(2));

  hD0MPIp->Scale(1.0 / hD0MPIp->GetMean(2));
  hD0MPInp->Scale(1.0 / hD0MPInp->GetMean(2));
  // hD0MPI->Scale(1.0 / hD0MPI->GetMean(2));
  hNchMPI->Scale(1.0 / hNchMPI->GetMean(2));

 


  TGraphErrors *grMPIvsD0 = new TGraphErrors();
  TGraphErrors *grMPIvsD0p = new TGraphErrors();
  TGraphErrors *grMPIvsD0np = new TGraphErrors();
  TGraphErrors *grMPIvsNch = new TGraphErrors();
  

  proftograph(hD0MPIp, grMPIvsD0p, hD0MPIp->GetMean(1), 1);
  proftograph(hD0MPInp, grMPIvsD0np, hD0MPInp->GetMean(1), 1);
  proftograph(hD0MPI, grMPIvsD0, hD0MPI->GetMean(1), 1);
  proftograph(hNchMPI, grMPIvsNch, hNchMPI->GetMean(1), 1);
 
  // cout << hD0MPIp->GetBinWidth(5) << endl;

  cout << "X-axis avg prompt  " << hD0MPIp->GetMean(1) << endl;
  cout << "X-axis avg non-prompt : " << hD0MPInp->GetMean(1) << endl;

  // TFile *f1 =
  //     new TFile("AvgD0VspthatCR" + CRcase + "_" + MPIcase + "_plot.root",
  //               "recreate"); //------- Name Change

  // hD0p->Write("pThat-D0p");
  // hD0np->Write("pThat-D0np");
  // hNch->Write("pThat-Nch");
  // grMPIvsD0p->Write("grMPIvsD0p");
  // grMPIvsD0np->Write("grMPIvsD0np");
  // grMPIvsNch->Write("grMPIvsNch");
 

  // f1->Close();
}
