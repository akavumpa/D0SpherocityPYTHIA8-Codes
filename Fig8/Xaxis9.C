const int n = 1000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, etamultone = 0, tag[n] = {0},
    etamultpoint8S0 = 0, etamultpoint8 = 0, FT0 = 0, integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT = 0, mass[n] = {0}, sp = 0;
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};
void proftograph(TProfile *pf, TGraphErrors *gr, Double_t scalex = 1.0,
                 Double_t scaley = 1.0)
{
  for (int i = 0; i < pf->GetNbinsX(); i++)
  {
    gr->SetPoint(i, pf->GetBinCenter(i + 1) / scalex,
                 pf->GetBinContent(i + 1) / scaley);
    gr->SetPointError(i, 0 * pf->GetBinWidth(i + 1) / scalex,
                      pf->GetBinError(i + 1) / scaley); // zero is multiplied in order to get zero error in x-axis
  }
}

void Xaxis9(TString CRcase = "on", TString MPIcase = "on")
{
  gStyle->SetPalette(kRainBow);

  TFile *f;
  if (CRcase == "on" && MPIcase == "on") {
    f = TFile::Open(
        "/mnt/5F1B0F4D3322F79F/Purnima/D0spherocity_work1/"
        "D0promptndn0nprompt/rootfiles/CR-on-MPI-on/pp-on-on.root");
  } else if (CRcase == "on" && MPIcase == "off") {
    f = TFile::Open(
        "/mnt/5F1B0F4D3322F79F/Purnima/D0spherocity_work1/D0promptndn0nprompt/"
        "rootfiles/pp13TeV_4Cdefault_MPIoff_CRon_1759596671.root");
  } else if (CRcase == "off" && MPIcase == "on") {
    f = TFile::Open(
        "/mnt/5F1B0F4D3322F79F/Purnima/D0spherocity_work1/D0promptndn0nprompt/"
        "rootfiles/CR-off-MPI-on/pp-off-on.root");
  } else {
    std::cerr << "Error: Can not run with both CR and MPI cases off" << endl;
    return;
  }

  TCanvas *c = new TCanvas("c", "c", 750, 600);
  auto sph = new TH2D("pTsp", "", 1000, 0.0, 1.0, 10, 0, 5.0);
  sph->GetYaxis()->SetTitle("dNchdeta of 0.8 class");
  sph->GetXaxis()->SetTitle("FT0");

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
  theTree->SetBranchAddress("spherocity", &sp);
  theTree->SetBranchAddress("etamultone", &etamultone);
  theTree->SetBranchAddress("etamultpoint8S0", &etamultpoint8S0);
  theTree->SetBranchAddress("etamultpoint8", &etamultpoint8);
  theTree->SetBranchAddress("FT0", &FT0);

  // const Int_t XBINS = ;
  Double_t FTbins[8] = {4, 7, 10, 15, 22, 32, 58, 200};

  TProfile *hD01 = new TProfile("h1", "1st range", 7, FTbins);
  hD01->SetLineColor(kRed + 2);
  hD01->SetMarkerSize(2);

  TProfile *hMB = new TProfile("", "", 1, 0, 200);
  hMB->SetLineColor(kGreen + 2);
  hMB->SetMarkerSize(2);

  TLorentzVector *vec = new TLorentzVector();

  const long nevents = (long)theTree->GetEntries() / 10;
  // int nevents = 100000000;
  // cout<<"Total number of events: "<<nevents<<endl;

  for (long i = 0; i < nevents; i++)
  {
    theTree->GetEntry(i);

    hD01->Fill(FT0, etamultpoint8 / 1.6);
    hMB->Fill(FT0, etamultpoint8 / 1.6);
  }

  for (int i = 1; i <= hD01->GetNbinsX(); i++)
  {
    cout << "Class = " << hD01->GetNbinsX() + 1 - i << "\t FT0M = " << hD01->GetBinCenter(i) << "\t <dNchmid0p8/deta> = " << hD01->GetBinContent(i) << " +/- " << hD01->GetBinError(i) << endl;
  }

  cout << "{" << hD01->GetBinContent(7) << "," << hD01->GetBinContent(6) << "," << hD01->GetBinContent(5) << "," << hD01->GetBinContent(4) << "," << hD01->GetBinContent(3) << "," << hD01->GetBinContent(2) << "," << hD01->GetBinContent(1) << "}" << endl;
  cout << "{" << hD01->GetBinError(7) << "," << hD01->GetBinError(6) << "," << hD01->GetBinError(5) << "," << hD01->GetBinError(4) << "," << hD01->GetBinError(3) << "," << hD01->GetBinError(2) << "," << hD01->GetBinError(1) << "}" << endl;

  cout << "=============================================================" << endl;

  // cout << "Min Bias <dNch/deta> = " << hMB->GetMean() <<  " +/- " << hMB->GetMeanError() << endl;
  cout << "Min Bias <dNch/deta>|0.8 for FT0 --> " << hMB->GetBinCenter(1) << "\t = " << hMB->GetBinContent(1) << " +/- " << hMB->GetBinError(1) << endl;

  TFile *f1 =
      new TFile("Xaxis89_FT0_0p8dNchdeta_OffOn.root", "recreate"); //------- Name Change

  hD01->Write("profile_FT0_0p8dNchdeta");
  hMB->Write("profile_MB_0p8dNchdeta");

  f1->Close();
}
