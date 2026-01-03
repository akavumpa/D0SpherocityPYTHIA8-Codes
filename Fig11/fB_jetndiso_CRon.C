const int n = 1000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, FT0 = 0, tag[n] = {0},
    etamultpoint8S0 = 0, integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT = 0, mass[n] = {0}, sp = 0;
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};

void fB_jetndiso_CRon(TString CRcase = "on", TString MPIcase = "on") {

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
  TH1D *h_pj[8];
  TH1D *h_npj[8];
  TH1D *h_pi[8];
  TH1D *h_npi[8];
  TH1D *h_pint[8];
  TH1D *h_npint[8];

  const Int_t XBINS = 11;
  Double_t pTbins[12] = {1.0, 2.0, 3.0,  4.0,  5.0,  6.0,
                         7.0, 8.0, 10.0, 12.0, 16.0, 24.0};
  // Double_t pTbins_clone[12] = {1.0, 2.0, 3.0,  4.0,  5.0,  6.0,
  //                        7.0, 8.0, 10.0, 12.0, 16.0, 24.0};
  for (int k = 0; k < 8; k++) {
    h_pj[k] = new TH1D("", "", XBINS, pTbins);
    h_npj[k] = new TH1D("", "", XBINS, pTbins);
    h_pi[k] = new TH1D("", "", XBINS, pTbins);
    h_npi[k] = new TH1D("", "", XBINS, pTbins);
    h_pint[k] = new TH1D("", "", XBINS, pTbins);
    h_npint[k] = new TH1D("", "", XBINS, pTbins);
  }

  Int_t color[8] = {kRed,  kGreen,      kBlue,    kOrange,
                    kTeal, kYellow + 4, kMagenta, kYellow};
  const Char_t mult[8][8] = {"mult_0", "mult_1", "mult_2", "mult_3",
                             "mult_4", "mult_5", "mult_6", "mult_7"};
  Int_t markerstyle[8] = {20, 21, 22, 23, 24, 25, 26, 27};
  Int_t markersize[8] = {1, 1, 1, 1, 1, 1, 1, 1};
  double Jetty[7] = {
      0.68905, 0.61075, 0.55845, 0.531,
      0.514, 0.503, 0.491}; // min bias is not included here
  double Isotropic[7] = {0.86455, 0.830, 0.800, 0.784,
                         0.775, 0.768, 0.762};
  int sphero1[7] = {46, 26, 18, 13, 9, 7, 3};
  int sphero2[7] = {242, 46, 26, 18, 13, 9, 7};
  int counter1[8] = {0};
  int counter2[8] = {0};
  int counter3[8] = {0};

  for (int i = 0; i < 8; i++) {
    h_pj[i]->SetMarkerColor(color[i]);
    h_pj[i]->SetLineColor(color[i]);
    h_pj[i]->SetMarkerStyle(markerstyle[i]);
    h_pj[i]->SetMarkerSize(markersize[i]);
  }

  for (int i = 0; i < 8; i++) {
    h_npj[i]->SetMarkerColor(color[i]);
    h_npj[i]->SetLineColor(color[i]);
    h_npj[i]->SetMarkerStyle(markerstyle[i]);
    h_npj[i]->SetMarkerSize(markersize[i]);
  }

  for (int i = 0; i < 8; i++) {
    h_pi[i]->SetMarkerColor(color[i]);
    h_pi[i]->SetLineColor(color[i]);
    h_pi[i]->SetMarkerStyle(markerstyle[i]);
    h_pi[i]->SetMarkerSize(markersize[i]);
  }

  for (int i = 0; i < 8; i++) {
    h_npi[i]->SetMarkerColor(color[i]);
    h_npi[i]->SetLineColor(color[i]);
    h_npi[i]->SetMarkerStyle(markerstyle[i]);
    h_npi[i]->SetMarkerSize(markersize[i]);
  }
  for (int i = 0; i < 8; i++) {
    h_pint[i]->SetMarkerColor(color[i]);
    h_pint[i]->SetLineColor(color[i]);
    h_pint[i]->SetMarkerStyle(markerstyle[i]);
    h_pint[i]->SetMarkerSize(markersize[i]);
  }
  for (int i = 0; i < 8; i++) {
    h_npint[i]->SetMarkerColor(color[i]);
    h_npint[i]->SetLineColor(color[i]);
    h_npint[i]->SetMarkerStyle(markerstyle[i]);
    h_npint[i]->SetMarkerSize(markersize[i]);
  }

  TLorentzVector *vec = new TLorentzVector();

  const long nevents = (long)theTree->GetEntries() ;
  //  long nevents = 1000000;
  // cout<<"Total number of events: "<<nevents<<endl;

  for (long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);
    if (etamultpoint8S0 >= 10) {
      for (int m = 0; m < 7; m++) {
        if ((FT0 < sphero2[m]) && (FT0 >= sphero1[m])) {
          if ((sp < Jetty[m]) && (sp >= 0)) {
            for (int j = 0; j < ntrack; j++) {
              vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[j] == 1))
                h_pj[m]->Fill(vec->Pt());

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[j] == 2))
                h_npj[m]->Fill(vec->Pt());
              vec->Clear();
            }
            counter1[m]++; // track loop ends
          }

          // cout<<"spherocity"<<sp<<"\t "<<FT0<<endl;

          if ((sp > Isotropic[m]) && (sp <= 1.0)) {

            //  cout<<"spherocity"<<sp<<"\t "<<FT0<<endl;
            for (int l = 0; l < ntrack; l++) {
              vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[l] == 1))
                h_pi[m]->Fill(vec->Pt());

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[l] == 2))
                h_npi[m]->Fill(vec->Pt());
              vec->Clear();
            }
            counter2[m]++; // track loop ends
          }

          if ((sp >= 0.0) && (sp <= 1.0)) {
            for (int l = 0; l < ntrack; l++) {
              vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[l] == 1))
                h_pint[m]->Fill(vec->Pt());

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[l] == 2))
                h_npint[m]->Fill(vec->Pt());
              vec->Clear();
            }
            counter3[m]++;
          }
        }
      }

      if (FT0 >= 0) {

        if ((sp < 0.557) && (sp >= 0.0)) {
          for (int j = 0; j < ntrack; j++) {
            vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 1))
              h_pj[7]->Fill(vec->Pt());
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 2))
              h_npj[7]->Fill(vec->Pt());
            vec->Clear();
          } // track loop ends
          counter1[7]++;
        }

        if ((sp > 0.807) && (sp <= 1)) {
          for (int l = 0; l < ntrack; l++) {
            vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[l] == 1))
              h_pi[7]->Fill(vec->Pt());
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[l] == 2))
              h_npi[7]->Fill(vec->Pt());
            vec->Clear();
          } // track loop ends
          counter2[7]++;
        }

        if ((sp <= 1.0) && (sp >= 0.0)) {
          for (int j = 0; j < ntrack; j++) {
            vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 1))
              h_pint[7]->Fill(vec->Pt());

            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 2))
              h_npint[7]->Fill(vec->Pt());
            vec->Clear();
          } // track loop ends
          counter3[7]++;
        }
      }
    }
    if (i % 100000 == 0) {
      cout << std::setprecision(3) << "Processing :::: " << i * 100.0 / nevents
           << " % \r" << flush;
    }
  } // event loop ENDS!

  for (int k = 0; k < 8; k++) {

    for (int bin = 1; bin <= XBINS; bin++) {
      h_pj[k]->SetBinContent(bin, h_pj[k]->GetBinContent(bin) /
                                      h_pj[k]->GetBinWidth(bin));
      h_npj[k]->SetBinContent(bin, h_npj[k]->GetBinContent(bin) /
                                       h_npj[k]->GetBinWidth(bin));
      h_pi[k]->SetBinContent(bin, h_pi[k]->GetBinContent(bin) /
                                      h_pi[k]->GetBinWidth(bin));
      h_npi[k]->SetBinContent(bin, h_npi[k]->GetBinContent(bin) /
                                       h_npi[k]->GetBinWidth(bin));
      h_pint[k]->SetBinContent(bin, h_pint[k]->GetBinContent(bin) /
                                        h_pint[k]->GetBinWidth(bin));

      h_npint[k]->SetBinContent(bin, h_npint[k]->GetBinContent(bin) /
                                         h_npint[k]->GetBinWidth(bin));
    }
  }

  TH1D *h_jr[8];
  TH1D *h_ir[8];
  TH1D *h_intr[8];

  for (int q = 0; q < 8; q++) {
    h_pj[q]->Scale(1.0 / (counter1[q] * 1.0));  // jetty pro
    h_npj[q]->Scale(1.0 / (counter1[q] * 1.0)); // jetty nonpro

    h_pi[q]->Scale(1.0 / (counter2[q] * 1.0));  // iso pro
    h_npi[q]->Scale(1.0 / (counter2[q] * 1.0)); // iso nonpro

    h_pint[q]->Scale(1.0 / (counter3[q] * 1.0)); // iso pro
    h_npint[q]->Scale(1.0 / (counter3[q] * 1.0));
  }
  for (int q = 0; q < 8; q++) {
    // h_jr[q] = (TH1D *)h_npj[q]->Clone(Form("h_jr[%d]", q));
    // h_ir[q] = (TH1D *)h_npi[q]->Clone(Form("h_ir[%d]", q));
    // h_intr[q] = (TH1D *)h_npint[q]->Clone(Form("h_intr[%d]", q));
    h_jr[q] = (TH1D *)h_npj[q]->Clone();
    h_ir[q] = (TH1D *)h_npi[q]->Clone();
    h_intr[q] = (TH1D *)h_npint[q]->Clone();

    h_jr[q]->Divide(h_pj[q]);
    h_ir[q]->Divide(h_pi[q]);
    h_intr[q]->Divide(h_pint[q]);
  }
  TFile *f1 = new TFile("BfracD0.root",
                        "recreate"); //------- Name Change
  for (int r = 0; r < 8; r++) {
    h_jr[r]->Write(Form("ratio_J_%s", mult[r]));

    h_ir[r]->Write(Form("ratio_I_%s", mult[r]));

    h_intr[r]->Write(Form("ratio_int_%s", mult[r]));
  }
  f1->Close();
}