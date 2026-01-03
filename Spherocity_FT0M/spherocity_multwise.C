const int n = 1000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, etamultone = 0, tag[n] = {0},
    etamultpoint8S0 = 0, etamultpoint8 = 0, FT0 = 0, integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT = 0, mass[n] = {0}, sp = 0;
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};
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
void spherocity_multwise(TString CRcase = "off", TString MPIcase = "on") {

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
                    CRcase + "-MPI-" + MPIcase + "/ppoffon.root");
  } else {
    std::cerr << "Error: Can not run with both CR and MPI cases off" << endl;
    return;
  }
  gStyle->SetPalette(kRainBow);

  TCanvas *c = new TCanvas("c", "c", 750, 600);
  auto sph = new TH2F("pTsp", "", 1000, 0.0, 1.0, 10, 0, 5.0);
  sph->GetYaxis()->SetTitle("events");
  // pTsp->GetYaxis()->SetTitleOffset(1.3); pTsp->GetYaxis()->CenterTitle(true);
  sph->GetXaxis()->SetTitle("Spherocity");
  // pTsp->GetXaxis()->CenterTitle(true);
  // c->SetLogy();
  // c->Draw();

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
  theTree->SetBranchAddress("spherocity", &sp);
  theTree->SetBranchAddress("etamultone", &etamultone);
  theTree->SetBranchAddress("etamultpoint8S0", &etamultpoint8S0);
  theTree->SetBranchAddress("etamultpoint8", &etamultpoint8);
  theTree->SetBranchAddress("FT0", &FT0);

  // const Int_t XBINS = ;
  Double_t FTbins[8] = {4, 7, 10, 15, 22, 32, 58, 200};

  TH1D *hD01 = new TH1D("h1", "1st range", 1000, 0.0, 1.0);
  hD01->SetLineColor(kRed + 2);
  hD01->SetMarkerSize(2);

  TH1D *hD02 = new TH1D("", "", 1000, 0.0, 1.0);
  hD02->SetLineColor(kGreen + 2);
  hD02->SetMarkerSize(2);

  TH1D *hD03 = new TH1D("h3", "3rd range", 1000, 0.0, 1.0);
  hD03->SetLineColor(kYellow + 2);
  hD03->SetMarkerSize(2);

  TH1D *hD04 = new TH1D("h4", "4th range", 1000, 0.0, 1.0);
  hD04->SetLineColor(kPink + 2);
  hD04->SetMarkerSize(2);

  TH1D *hD05 = new TH1D("h5", "5th range", 1000, 0.0, 1.0);
  hD05->SetLineColor(kCyan + 2);
  hD05->SetMarkerSize(2);

  TH1D *hD06 = new TH1D("h6", "6th range", 1000, 0.0, 1.0);
  hD06->SetLineColor(kRed);
  hD06->SetMarkerSize(2);

  TH1D *hD07 = new TH1D("h7", "7th range", 1000, 0.0, 1.0);
  hD07->SetLineColor(kGreen);
  hD07->SetMarkerSize(2);

  TH1D *hD08 = new TH1D("h8", "min bias", 1000, 0.0, 1.0);
  hD08->SetLineColor(kBlack);
  hD08->SetMarkerSize(2);

  TLorentzVector *vec = new TLorentzVector();

  const long nevents = (long)theTree->GetEntries() / 10;
  // int nevents = 100000000;
  // cout<<"Total number of events: "<<nevents<<endl;

  for (long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);
    bool sphero = false;
    if (etamultpoint8S0 >= 10) {
      sphero = true;
    }

    // cout<<etamultpoint8S0<<"\t "<<etamultpoint8<<" \t"<<sp<<endl;
    //  if (sp>=0.0)
    //    break;
    if (sphero)

    {
      if (FT0 > 58) {
        // counter1 = etamultpoint8 + counter1;
        hD01->Fill(sp);
        // counter1_MB++;
      }
      if ((58 >= FT0) && (FT0 > 32)) {
        hD02->Fill(sp);
        // // counter2 = etamultpoint8 + counter2;
        // counter2_MB++;
      }
      if ((32 >= FT0) && (FT0 > 22)) {
        hD03->Fill(sp);
        // // counter3 = etamultpoint8 + counter3;
        // counter3_MB++;
      }
      if ((22 >= FT0) && (FT0 > 15)) {
        hD04->Fill(sp);
        // // counter4 = etamultpoint8 + counter4;
        // counter4_MB++;
      }
      if ((15 >= FT0) && (FT0 > 10)) {
        hD05->Fill(sp);
        // // counter5 = etamultpoint8 + counter5;
        // counter5_MB++;
      }
      if ((10 >= FT0) && (FT0 > 7)) {
        hD06->Fill(sp);
        // // counter6 = etamultpoint8 + counter6;
        // counter6_MB++;
      }
      if ((7 >= FT0) && (FT0 > 4)) {
        hD07->Fill(sp);
        // // counter7 = etamultpoint8 + counter7;
        // counter7_MB++;
      }
      if ((FT0 >= 0)) {
        hD08->Fill(sp);
        // counter8++;
      }
    }
  }

  int a0 = hD01->Integral();
  cout << a0 << endl;

  int flag0 = 0, flag1 = 0;

  for (int j = 1; j <= hD01->GetNbinsX(); j++) {
    integral = hD01->Integral(1, j);
    if (integral >= 0.2 * a0 && flag0 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD01->GetBinCenter(j)
           << endl;
      flag0 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a0 && flag1 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD01->GetBinCenter(j)
           << endl;
      flag1 = 1;
    }
  }
  int a1 = hD02->Integral();

  int flag2 = 0, flag3 = 0;

  for (int k = 1; k <= hD02->GetNbinsX(); k++)

  {
    integral = hD02->Integral(1, k);
    if (integral >= 0.2 * a1 && flag2 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD02->GetBinCenter(k)
           << endl;
      flag2 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a1 && flag3 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD02->GetBinCenter(k)
           << endl;
      flag3 = 1;
    }
  }
  int a2 = hD03->Integral();

  int flag4 = 0, flag5 = 0;

  for (int l = 1; l <= hD03->GetNbinsX(); l++)

  {
    integral = hD03->Integral(1, l);
    if (integral >= 0.2 * a2 && flag4 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD03->GetBinCenter(l)
           << endl;
      flag4 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a2 && flag5 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD03->GetBinCenter(l)
           << endl;
      flag5 = 1;
    }
  }
  int a3 = hD04->Integral();

  int flag6 = 0, flag7 = 0;

  for (int m = 1; m <= hD04->GetNbinsX(); m++) {
    integral = hD04->Integral(1, m);
    if (integral >= 0.2 * a3 && flag6 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD04->GetBinCenter(m)
           << endl;
      flag6 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a3 && flag7 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD04->GetBinCenter(m)
           << endl;
      flag7 = 1;
    }
  }
  int a4 = hD05->Integral();

  int flag8 = 0, flag9 = 0;

  for (int o = 1; o <= hD05->GetNbinsX(); o++)

  {
    integral = hD05->Integral(1, o);
    if (integral >= 0.2 * a4 && flag8 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD05->GetBinCenter(o)
           << endl;
      flag8 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a4 && flag9 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD05->GetBinCenter(o)
           << endl;
      flag9 = 1;
    }
  }
  int a5 = hD06->Integral();

  int flag10 = 0, flag11 = 0;

  for (int p = 1; p <= hD06->GetNbinsX(); p++)

  {
    integral = hD06->Integral(1, p);
    if (integral >= 0.2 * a5 && flag10 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD06->GetBinCenter(p)
           << endl;
      flag10 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a5 && flag11 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD06->GetBinCenter(p)
           << endl;
      flag11 = 1;
    }
  }
  int a6 = hD07->Integral();

  int flag12 = 0, flag13 = 0;

  for (int q = 1; q <= hD07->GetNbinsX(); q++)

  {
    integral = hD07->Integral(1, q);
    if (integral >= 0.2 * a6 && flag12 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD07->GetBinCenter(q)
           << endl;
      flag12 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a6 && flag13 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD07->GetBinCenter(q)
           << endl;
      flag13 = 1;
    }
  }
  int a7 = hD08->Integral();

  int flag14 = 0, flag15 = 0;

  for (int r = 1; r <= hD08->GetNbinsX(); r++)

  {
    integral = hD08->Integral(1, r);
    if (integral >= 0.2 * a7 && flag14 == 0) {
      cout << " 0.2 perc = " << integral << "\t" << hD08->GetBinCenter(r)
           << endl;
      flag14 = 1;
    }
    // cout<<"aa"<<endl;
    if (integral >= 0.8 * a7 && flag15 == 0) {
      cout << " 0.8 perc = " << integral << "\t" << hD08->GetBinCenter(r)
           << endl;
      flag15 = 1;
    }
  }

  // cout<<"Highest Mult Jetty Counts ::::
  // "<<hD01->Integral(0,hD01->FindBin(0.17975))<<endl; cout<<"Highest Mult
  // Isotropic Counts ::::
  // "<<hD01->Integral(hD01->FindBin(0.54875),hD01->GetNbinsX())<<endl;
}
