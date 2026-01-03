const int n = 10000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, no_mpi = 0, toward_D0 = 0,
    transverse_D0 = 0, away_D0 = 0, FT0 = 0, tag[n] = {0}, etamultpoint8S0 = 0,
    etamultpoint8 = 0;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT[n] = {0}, sp = 0,
       mass[n] = {0};
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};
// const int nevents = 100000000;

void MeanpTD0vsSNch(TString CRcase = "on", TString MPIcase = "on") {

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

  TCanvas *c = new TCanvas("c", "c", 750, 600);
  auto pTsp = new TH2F("pTsp", "", 10, 0.0, 24.0, 10, 1.0, 30.0);
  pTsp->GetYaxis()->SetTitle("#LTN_{ch}#GT");
  // pTsp->GetYaxis()->SetTitleOffset(1.3); pTsp->GetYaxis()->CenterTitle(true);
  pTsp->GetXaxis()->SetTitle("p_{T}^{D^{0}-lead} (GeV/c)");
  // pTsp->GetXaxis()->CenterTitle(true);
  // c->SetLogy();
  c->Draw();

  TTree *theTree = (TTree *)f->Get("t");

  theTree->SetBranchAddress(
      "ntrack", &ntrack); // ntrack is the size of the tree (fill only final
                          // chargedparticles)
                          //  theTree->SetBranchAddress("V0MMult", &V0MMult);
  // theTree->SetBranchAddress("PID", PID);
  theTree->SetBranchAddress("charge", charge);
  theTree->SetBranchAddress("px", px);
  theTree->SetBranchAddress("py", py);
  theTree->SetBranchAddress("pz", pz);
  theTree->SetBranchAddress("energy", energy);
  theTree->SetBranchAddress("tag", tag);
  // theTree->SetBranchAddress("no_mpi", &no_mpi);
  theTree->SetBranchAddress("pT", pT);
  theTree->SetBranchAddress("FT0", &FT0);
  theTree->SetBranchAddress("spherocity", &sp);
  theTree->SetBranchAddress("etamultpoint8S0", &etamultpoint8S0);
  theTree->SetBranchAddress("etamultpoint8", &etamultpoint8);

  const Int_t XBINS = 7;
  Double_t mult_bins[XBINS + 1] = {3, 7, 9, 13, 18, 26, 46, 200};
  Double_t Jetty[XBINS] = {
      0.49125, 0.50265, 0.51455, 0.53135,
      0.55805, 0.61395, 0.68875}; // min bias is not included here
  Double_t Isotropic[XBINS] = {0.76255, 0.76845, 0.77465, 0.78425,
                               0.80005, 0.83045, 0.86455};
  int FT_1[XBINS] = {3, 7, 9, 13, 18, 26, 46};
  int FT_2[XBINS] = {7, 9, 13, 18, 26, 46, 200};
  // double pt = 0;
  // int counter = 0;

  TProfile *hD0jp = new TProfile("h1", "pTsp_prompt_J", 7, mult_bins, "");
  hD0jp->SetLineColor(kRed + 2);
  hD0jp->SetMarkerSize(2);

  TProfile *hD0jnp = new TProfile("h2", "pTsp_nonprompt_J", 7, mult_bins, "");
  hD0jnp->SetLineColor(kGreen + 2);
  hD0jnp->SetMarkerSize(2);

  TProfile *hD0ip = new TProfile("h3", "pTsp_prompt_I", 7, mult_bins, "");
  hD0ip->SetLineColor(kBlue);
  hD0ip->SetMarkerSize(2);

  TProfile *hD0inp = new TProfile("h4", "pTsp_nonprompt_I", 7, mult_bins, "");
  hD0inp->SetLineColor(kCyan);
  hD0inp->SetMarkerSize(2);

  TLorentzVector *vec = new TLorentzVector();

  const long long nevents = (long long)theTree->GetEntries();

  // cout<<"Total number of events: "<<nevents<<endl;
  // const int nevents = 100000000;

  for (long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);

    int nFT0class = 999;
    for (int m = 0; m < XBINS; m++) {
      if (FT0 < FT_2[m] && FT0 >= FT_1[m]) {
        nFT0class = m;
      }
    }

    bool accepteventjetty = false;
    bool accepteventisotropic = false;
    bool accepteventintegrated = false;

    if (etamultpoint8S0 >= 10 && nFT0class != 999) {
      if ((sp < Jetty[nFT0class]) && (sp >= 0.0)) {
        accepteventjetty = true;
      }
      if ((sp > Isotropic[nFT0class]) && (sp <= 1.0)) {
        accepteventisotropic = true;
      }
      if ((sp >= 0.0) && (sp <= 1.0)) {
        accepteventintegrated = true;
      }
    }

    if (accepteventjetty) {
      for (int j = 0; j < ntrack; j++) {
        vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);

        if (abs(vec->Rapidity()) < 0.5 && (vec->Pt() > 0.15) &&
            ((tag[j] == 1))) {
          hD0jp->Fill(FT0, pT[j]);
        }
        if (abs(vec->Rapidity()) < 0.5 && (vec->Pt() > 0.15) && (tag[j] == 2)) {
          hD0jnp->Fill(FT0, pT[j]);
        }
      }
    }
    if (accepteventisotropic) {
      for (int j = 0; j < ntrack; j++) {
        vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);

        if (abs(vec->Rapidity()) < 0.5 && (vec->Pt() > 0.15) &&
            ((tag[j] == 1))) {
          hD0ip->Fill(FT0, pT[j]);
        }
        if (abs(vec->Rapidity()) < 0.5 && (vec->Pt() > 0.15) && (tag[j] == 2)) {
          hD0inp->Fill(FT0, pT[j]);
        }
      }
    }
    if (i % 100000 == 0) {
      cout << std::setprecision(3) << "Processing :::: " << i * 100.0 / nevents
           << " % \r" << flush;
    }
  }
  // double avg = pt / counter;
  // cout << avg << endl;

  pTsp->Draw();
  hD0ip->Draw("pesame");
  hD0inp->Draw("pesame");
  hD0jp->Draw("pesame");
  hD0jnp->Draw("pesame");

  TFile *f1 = new TFile("MeanpT_Yaxis.root", "recreate"); //------- Name Change
  {
    hD0jp->Write("prompt_jetty");
    hD0jnp->Write("nonprompt_jetty");
    hD0ip->Write("prompt_isotropic");
    hD0inp->Write("nonprompt_isotropic");
  }
  f1->Close();
}
