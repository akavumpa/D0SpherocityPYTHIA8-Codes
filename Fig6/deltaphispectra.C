const int n = 10000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, no_mpi = 0, nspecies = 0,
    tag[n] = {0}, rapmultpoint5 = 0, toward[4] = {0}, toward_p = 0,
    toward_np = 0, transverse[4] = {0}, transverse_p = 0, transverse_np = 0,
    away[4] = {0}, away_p = 0, away_np = 0;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT[n] = {0}, mass[n] = {0},
       pt_hat(0);
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0},
       pTlead[4] = {0}, sp(0), pTD0plead(0), pTD0nplead(0), philead[4] = {0};
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

void deltaphispectra(TString CRcase = "on", TString MPIcase = "off") {
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
  theTree->SetBranchAddress("philead", philead);

  const Int_t XBINS = 20;
  // Double_t deltaphibins[13] = {-3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0,
  //                              0.5,  1.0,  1.5,  2.0,  2.5,  3.0};
  const float pi = TMath::Pi();
  TH1D *h1 = new TH1D(
      "", "Prompt-phi vs charged-phi; #Delta#phi (rad); 1/N_{pairs} dN/d#phi",
      25, -0.5 * pi, 1.5 * pi);
  h1->SetLineColor(kRed);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(24);
  h1->SetMarkerSize(2);

  TH1D *h2 = new TH1D(
      "",
      "NonPrompt-phi vs charged-phi; #Delta#phi (rad); 1/N_{pairs} dN/d#phi",
      25, -0.5 * pi, 1.5 * pi);
  h2->SetLineColor(kBlue);
  h2->SetMarkerColor(kBlue);
  h2->SetMarkerStyle(25);
  h2->SetMarkerSize(2);

  TLorentzVector *vec = new TLorentzVector();

  const long nevents = (long)theTree->GetEntries();
  // int nevents = 10000000;

  int counter = 0;
  for (long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);

    bool isD0 = false;
    bool isNch = false;
    float high_pt_D = 0.0;
    float rap = 0.0;

    if (pTlead[1] > 0.15 && pTlead[3] > 0.15) {
      double deltaphi = philead[1] - philead[3];

      while (deltaphi < -0.5 * TMath::Pi()) {
        deltaphi += 2 * TMath::Pi();
      }

      while (deltaphi > 1.5 * TMath::Pi()) {
        deltaphi -= 2 * TMath::Pi();
      }
      h1->Fill(deltaphi);
    }

    if (pTlead[2] > 0.15 && pTlead[3] > 0.15) {
      double deltaphi = philead[2] - philead[3];

      while (deltaphi < -0.5 * TMath::Pi()) {
        deltaphi += 2 * TMath::Pi();
      }

      while (deltaphi > 1.5 * TMath::Pi()) {
        deltaphi -= 2 * TMath::Pi();
      }
      h2->Fill(deltaphi);
    }
    if (i % 100000 == 0)
      print_progress_bar(i, nevents);
    // cout<<rapmultpoint5<<endl;
  }
  // print_progress_bar(nevents, nevents);

  h1->Scale(1.0 / (h1->Integral(0, -1) * h1->GetBinWidth(1)));
  h2->Scale(1.0 / (h2->Integral(0, -1) * h2->GetBinWidth(1)));

  TFile *f1 =
      new TFile("deltaphispectra_plot_CR" + CRcase + "_MPI" + MPIcase + ".root",
                "recreate"); //------- Name Change

  h1->Write("Delphi-dist-prompt");
  h2->Write("Delphi-dist-nonprompt");

  f1->Close();
}