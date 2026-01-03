const int n = 1000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, FT0 = 0, tag[n] = {0},
    etamultpoint8S0 = 0, integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT = 0, mass[n] = {0}, sp = 0;
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};

void fMBvspT(TString CRcase = "on", TString MPIcase = "off") {

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
  auto pTsp = new TH2F("pTsp", "", 10, 0.0, 20.0, 10, 0.00000001, 0.01);
  pTsp->GetYaxis()->SetTitle("invariant yield");
  // pTsp->GetYaxis()->SetTitleOffset(1.3); pTsp->GetYaxis()->CenterTitle(true);
  pTsp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  // pTsp->GetXaxis()->CenterTitle(true);
  // c->SetLogy();
  c->Draw();

  TTree *theTree = (TTree *)f->Get("t");

  theTree->SetBranchAddress("ntrack",
                            &ntrack); // ntrack is the size of the tree (fill
                                      // only final chargedparticles)
  // theTree->SetBranchAddress("V0MMult", &V0MMult);
  // theTree->SetBranchAddress("PID", PID);
  theTree->SetBranchAddress("charge", charge);
  theTree->SetBranchAddress("px", px);
  theTree->SetBranchAddress("py", py);
  theTree->SetBranchAddress("pz", pz);
  theTree->SetBranchAddress("energy", energy);
  theTree->SetBranchAddress("tag", tag);
  // theTree->SetBranchAddress("ra",tag);
  theTree->SetBranchAddress("FT0", &FT0);
  theTree->SetBranchAddress("spherocity", &sp);
  theTree->SetBranchAddress("etamultpoint8S0", &etamultpoint8S0);

  const Int_t XBINS = 14;
  Double_t pTbins[XBINS + 1] = {0.0, 1.0, 1.5, 2.0, 2.5,  3.0,  3.5, 4.0,
                                5.0, 6.0, 7.0, 8.0, 12.0, 16.0, 24.0};
  // Double_t pTbins_clone[12] = {1.0, 2.0, 3.0,  4.0,  5.0,  6.0,
  //                        7.0, 8.0, 10.0, 12.0, 16.0, 24.0};

  TH1D *h_p = new TH1D("", "", XBINS, pTbins);
  TH1D *h_np = new TH1D("", "", XBINS, pTbins);

  Int_t color[8] = {kRed,  kGreen,      kBlue,    kOrange,
                    kTeal, kYellow + 4, kMagenta, kYellow};
  const Char_t mult[8][8] = {"mult_0", "mult_1", "mult_2", "mult_3",
                             "mult_4", "mult_5", "mult_6", "mult_7"};
  Int_t markerstyle[8] = {20, 21, 22, 23, 24, 25, 26, 27};
  Int_t markersize[8] = {1, 1, 1, 1, 1, 1, 1, 1};

  TLorentzVector *vec = new TLorentzVector();
  int counter = 0;

  const long long nevents = (long long)theTree->GetEntries();
  for (long long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);

    if (FT0 > 0) {
      for (int j = 0; j < ntrack; j++) {
        vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
        if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 1))
          h_p->Fill(vec->Pt());
        if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 2))
          h_np->Fill(vec->Pt());
        vec->Clear();
      }
      counter++; // track loop ends
    }
    // cout<<"spherocity"<<sp<<"\t "<<FT0<<endl;

    if (i % 100000 == 0) {
      cout << std::setprecision(3) << "Processing :::: " << i * 100.0 / nevents
           << " % \r" << flush;
    }
  }

  for (int bin = 1; bin <= XBINS; bin++) {
    h_p->SetBinContent(bin, h_p->GetBinContent(bin) / h_p->GetBinWidth(bin));
    h_np->SetBinContent(bin, h_np->GetBinContent(bin) / h_np->GetBinWidth(bin));
  }

  h_p->Scale(1.0 / (counter * 1.0)); // etty pro
  h_np->Scale(1.0 / (counter * 1.0));

  TH1D *h_r = (TH1D *)h_np->Clone();
  h_r->Divide(h_p);

  TFile *f1 = new TFile("fB_MB_CR"+CRcase+"_MPI"+MPIcase+".root",
                        "recreate"); //------- Name Change

  h_r->Write("ratio_MB");
  f1->Close();
}