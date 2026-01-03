
const int n = 100000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, rapmultpoint5 = 0, a, FT0 = 0,
    integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT = 0, mass[n] = {0};
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};

void FV0_Slicing(TString CRcase = "off", TString MPIcase = "on") {

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
  gStyle->SetPalette(kRainBow);
  TCanvas *c = new TCanvas("c", "c", 750, 600);
  TH1D *h8 =
      new TH1D("rapmultpoint5sp", "This is the rapmultpoint5sp distribution",
               110, -0.5, 109.5);
  h8->SetLineColor(kRed);
  h8->SetMarkerColor(kRed);
  h8->SetMarkerSize(1);
  h8->SetMarkerStyle(20);
  h8->SetTitle("rapmultpoint5 Distribution; P(rapmultpoint5M)");
  h8->GetYaxis()->SetTitle("count");
  h8->GetXaxis()->SetTitle("rapmultpoint5");
  // c->SetLogy();
  c->Draw();

  TTree *theTree = (TTree *)f->Get("t");

  theTree->SetBranchAddress("ntrack",
                            &ntrack); // ntrack is the size of the tree (fill
                                      // only final chargedparticles)
  theTree->SetBranchAddress("PID", PID);
  theTree->SetBranchAddress("charge", charge);
  theTree->SetBranchAddress("px", px);
  theTree->SetBranchAddress("py", py);
  theTree->SetBranchAddress("pz", pz);
  theTree->SetBranchAddress("energy", energy);
  theTree->SetBranchAddress("rapmultpoint5", &rapmultpoint5);
  theTree->SetBranchAddress("FT0", &FT0);

  const Int_t nevents = (Int_t)theTree->GetEntries() / 100;
  // int nevents = 1000000;
  double a2[7] = {0.01, 0.05, 0.1, 0.2, 0.4, 0.6, 0.9};
  for (int i = 0; i < nevents; i++) {
    theTree->GetEntry(i);
    h8->Fill(FT0);
  }
  h8->Draw();
  a = h8->Integral(); // total number of entries in the histogram for V0M

  cout << h8->GetNbinsX() << endl;

  for (int k = 0; k < 7; k++) {
    // cout << "Checking for a2[" << k << "] = " << a2[k] << " and threshold = "
    // << (a2[k] * a) << endl;
    for (int j = 110; j >= 1; j--) {
      integral = h8->Integral(j, 110);
      // cout<<integral<<endl;
      if (integral >= (a2[k] * a)) {
        cout << a2[k] << "\t" << h8->GetBinCenter(j) << endl;
        break;
      }
      // if (integral >= (a2[k] * a)) {
      //     cout << "Condition met at bin " << j << ": a2[" << k << "] = " <<
      //     a2[k] << ", bin center = " << h8->GetBinCenter(j) << endl; break;
      //     // exit the loop once the condition is met
      // }
    }
  }
}