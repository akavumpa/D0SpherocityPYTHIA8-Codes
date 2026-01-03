const int n = 1000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, rapmultpoint5 = 0, FT0 = 0,
    etamultpoint8S0 = 0, tag[n] = {0};
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT[n] = {0}, mass[n] = {0},
       sp = 0;
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};
// This is self-normalised yield for jetty events prompt D0 meson

void SN_CRoff(TString CRcase = "off", TString MPIcase = "on") {

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
  theTree->SetBranchAddress("FT0", &FT0);
  theTree->SetBranchAddress("rapmultpoint5", &rapmultpoint5);
  theTree->SetBranchAddress("PID", PID);
  theTree->SetBranchAddress("pT", pT);
  theTree->SetBranchAddress("spherocity", &sp);
  theTree->SetBranchAddress("ntrack", &ntrack);
  theTree->SetBranchAddress("etamultpoint8S0", &etamultpoint8S0);

  const long long nevents = (long long)theTree->GetEntries();
  // int nevents = 10000000;
  // cout<<"Total number of events: "<<nevents<<endl;
  long long counter[7] = {0};
  long counter_MB = 0;
  TH1D *hjp[6];
  TH1D *hjnp[6];
  TH1D *hip[6];
  TH1D *hinp[6];
  TH1D *hintp[6];
  TH1D *hintnp[6];
  TH1D *h_MB_p[6];
  TH1D *h_MB_np[6];
  const Int_t Xbins = 7;

  double sphero1[7] = {0.483, 0.495, 0.51, 0.533, 0.572, 0.644, 0.722}; // CRoff
  double sphero2[7] = {0.756, 0.763, 0.772, 0.786, 0.808, 0.845, 0.879}; // CRoff
  double FT_1[7] = {4, 7, 10, 15, 22, 32, 58};
  double FT_2[7] = {7, 10, 15, 22, 32, 58, 200};

  const Char_t Pt[6][6] = {"1", "2", "3", "4", "5", "6"};
  double Pt_1[6] = {1.0, 2.0, 5.0};
  double Pt_2[6] = {2.0, 5.0, 24.0};
  Double_t FT0MClass[8] = {4, 7, 10, 15, 22, 32, 58, 200};
  Double_t FT0_MB[2] = {0, 200};
  double count_MB[6] = {0};

  for (int k = 0; k < 3; k++) {
    hjp[k] = new TH1D("", ";FT0M; Self Norm. Yield of D^{0}", Xbins, FT0MClass);
    hjnp[k] =
        new TH1D("", ";FT0M; Self Norm. Yield of D^{0}", Xbins, FT0MClass);
    hip[k] = new TH1D("", ";FT0M; Self Norm. Yield of D^{0}", Xbins, FT0MClass);
    hinp[k] =
        new TH1D("", ";FT0M; Self Norm. Yield of D^{0}", Xbins, FT0MClass);
    hintp[k] =
        new TH1D("", ";FT0M; Self Norm. Yield of D^{0}", Xbins, FT0MClass);
    hintnp[k] =
        new TH1D("", ";FT0M; Self Norm. Yield of D^{0}", Xbins, FT0MClass);

    h_MB_p[k] = new TH1D("", "", 1, FT0_MB);

    h_MB_np[k] = new TH1D("", "", 1, FT0_MB);
  }
  TH1D *hevcounter_j = new TH1D("", "", Xbins, FT0MClass);
  TH1D *hevcounter_i = new TH1D("", "", Xbins, FT0MClass);
  TH1D *hevcounter_int = new TH1D("", "", Xbins, FT0MClass);

  Int_t color[8] = {kRed, kGreen, kBlue, kOrange, kTeal, kYellow + 4};
  Int_t markerstyle[8] = {20, 21, 22, 23, 24, 25};
  Int_t markersize[8] = {1, 1, 1, 1, 1, 1};

  // const Char_t mult[6][8] = {"mult_1", "mult_2", "mult_3",
  //                            "mult_4", "mult_5", "mult_6" };
  for (int i = 0; i < 3; i++) {
    hjp[i]->SetMarkerColor(color[i]);
    hjp[i]->SetLineColor(color[i]);
    hjp[i]->SetMarkerStyle(markerstyle[i]);
    hjp[i]->SetMarkerSize(markersize[i]);
  }
  for (int i = 0; i < 3; i++) {
    hjnp[i]->SetMarkerColor(color[i]);
    hjnp[i]->SetLineColor(color[i]);
    hjnp[i]->SetMarkerStyle(markerstyle[i]);
    hjnp[i]->SetMarkerSize(markersize[i]);
  }
  for (int i = 0; i < 3; i++) {
    hip[i]->SetMarkerColor(color[i]);
    hip[i]->SetLineColor(color[i]);
    hip[i]->SetMarkerStyle(markerstyle[i]);
    hip[i]->SetMarkerSize(markersize[i]);
  }
  for (int i = 0; i < 3; i++) {
    hinp[i]->SetMarkerColor(color[i]);
    hinp[i]->SetLineColor(color[i]);
    hinp[i]->SetMarkerStyle(markerstyle[i]);
    hinp[i]->SetMarkerSize(markersize[i]);
  }
  TLorentzVector *vec = new TLorentzVector();

  for (long long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);
    // bool sphero= false;
    // if (etamultpoint8S0 >= 10) {sphero=true;}
    //  this condition is commented out and is added only where
    //   spherocity is needed because in denominator we need only MB and beacuse
    //   of it
    // we were getting very small value of yield
    //  if (sphero)

    int nFT0class = 999;
    for (int m = 0; m < Xbins; m++) {
      if (FT0 < FT_2[m] && FT0 >= FT_1[m]) {
        nFT0class = m;
      }
    }

    bool accepteventjetty = false;
    bool accepteventisotropic = false;
    bool accepteventintegrated = false;

    if (etamultpoint8S0 >= 10 && nFT0class != 999) {
      if ((sp < sphero1[nFT0class]) && (sp >= 0.0)) {
        accepteventjetty = true;
      }
      if ((sp > sphero2[nFT0class]) && (sp <= 1.0)) {
        accepteventisotropic = true;
      }
      if ((sp >= 0.0) && (sp <= 1.0)) {
        accepteventintegrated = true;
      }
    }
    if (accepteventjetty) {
      for (int j = 0; j < ntrack; j++) {
        vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);

        for (int k = 0; k < 3; k++) {
          if ((tag[j] == 1) && ((pT[j] > Pt_1[k]) && (pT[j] < Pt_2[k])) &&
              (abs(vec->Rapidity()) < 0.5)) {
            hjp[k]->Fill(FT0);
          }

          if ((tag[j] == 2) && ((pT[j] > Pt_1[k]) && (pT[j] < Pt_2[k])) &&
              (abs(vec->Rapidity()) < 0.5)) {
            hjnp[k]->Fill(FT0);
          }
        }
      }
      hevcounter_j->Fill(FT0);
    }

    if (accepteventisotropic) {
      for (int j = 0; j < ntrack; j++) {
        vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);

        for (int k = 0; k < 3; k++) {
          if ((tag[j] == 1) && ((pT[j] > Pt_1[k]) && (pT[j] < Pt_2[k])) &&
              (abs(vec->Rapidity()) < 0.5)) {
            hip[k]->Fill(FT0);
          }

          if ((tag[j] == 2) && ((pT[j] > Pt_1[k]) && (pT[j] < Pt_2[k])) &&
              (abs(vec->Rapidity()) < 0.5)) {
            hinp[k]->Fill(FT0);
          }
        }
      }
      hevcounter_i->Fill(FT0);
    }
    if (accepteventintegrated) {
      for (int j = 0; j < ntrack; j++) {
        vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);

        for (int k = 0; k < 3; k++) {
          if ((tag[j] == 1) && ((pT[j] > Pt_1[k]) && (pT[j] < Pt_2[k])) &&
              (abs(vec->Rapidity()) < 0.5)) {
            hintp[k]->Fill(FT0);
          }

          if ((tag[j] == 2) && ((pT[j] > Pt_1[k]) && (pT[j] < Pt_2[k])) &&
              (abs(vec->Rapidity()) < 0.5)) {
            hintnp[k]->Fill(FT0);
          }
        }
      }
      hevcounter_int->Fill(FT0);
    }

    // if ((sp >= 0.0)) {

    for (int d = 0; d < ntrack; d++) {
      vec->SetPxPyPzE(px[d], py[d], pz[d], energy[d]);

      for (int k = 0; k < 3; k++) {
        if ((tag[d] == 1) && ((pT[d] > Pt_1[k]) && (pT[d] < Pt_2[k])) &&
            (abs(vec->Rapidity()) < 0.5)) {
          h_MB_p[k]->Fill(FT0);
        }

        if ((tag[d] == 2) && ((pT[d] > Pt_1[k]) && (pT[d] < Pt_2[k])) &&
            (abs(vec->Rapidity()) < 0.5)) {
          h_MB_np[k]->Fill(FT0);
        }
      }
    }
    counter_MB++;

    if (i % 100000 == 0) {
      cout << std::setprecision(3) << "Processing :::: " << i * 100.0 / nevents
           << " % \r" << flush;
    }
  }
  // cout<< h_MB_ip[1]->Integral()<<endl;
  for (int q = 0; q < 3; q++) {
    hjp[q]->Scale(counter_MB / h_MB_p[q]->Integral());
    hjp[q]->Divide(hevcounter_j);
    hjnp[q]->Scale(counter_MB / h_MB_np[q]->Integral());
    hjnp[q]->Divide(hevcounter_j);
    hip[q]->Scale(counter_MB / h_MB_p[q]->Integral());
    hip[q]->Divide(hevcounter_i);
    hinp[q]->Scale(counter_MB / h_MB_np[q]->Integral());
    hinp[q]->Divide(hevcounter_i);
  }

  TFile *f1 = new TFile("D0SNyaxis_CR" + CRcase + "_.root",
                        "recreate"); //------- Name Change
  for (int r = 0; r < 3; r++) {
    hjp[r]->Write(Form("prompt_J_%s", Pt[r]));
    hjnp[r]->Write(Form("nonprompt_J_%s", Pt[r]));

    hip[r]->Write(Form("prompt_I_%s", Pt[r]));
    hinp[r]->Write(Form("nonprompt_I_%s", Pt[r]));
  }
  f1->Close();
}