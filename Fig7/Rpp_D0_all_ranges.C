const int n = 10000;

int ntrack = 0, PID[n] = {0}, charge[n] = {0}, FT0 = 0, tag[n] = {0},
    etamultpoint8S0 = 0, integral;
double px[n] = {0}, py[n] = {0}, pz[n] = {0}, pT = 0, mass[n] = {0}, sp = 0;
double eta[n] = {0}, rap[n] = {0}, phi[n] = {0}, energy[n] = {0};
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

void Rpp_D0_all_ranges(TString CRcase = "on", TString MPIcase = "on") {

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
  TH1D *h_m_p[8];
  TH1D *h_m_np[8];

  const Int_t XBINS = 11;
  Double_t pTbins[XBINS + 1] = {0.15, 2.0, 3.0,  4.0,  5.0,  6.0,
                                7.0,  8.0, 10.0, 12.0, 16.0, 24.0};
  for (int k = 0; k < 8; k++) {
    h_pj[k] = new TH1D("", "", XBINS, pTbins);
    h_npj[k] = new TH1D("", "", XBINS, pTbins);
    h_pi[k] = new TH1D("", "", XBINS, pTbins);
    h_npi[k] = new TH1D("", "", XBINS, pTbins);
    h_m_p[k] = new TH1D("", "", XBINS, pTbins);
    h_m_np[k] = new TH1D("", "", XBINS, pTbins);
  }

  Int_t color[8] = {kRed,  kGreen,      kBlue,    kOrange,
                    kTeal, kYellow + 4, kMagenta, kYellow};
  const Char_t mult[8][8] = {"mult_0", "mult_1", "mult_2", "mult_3",
                             "mult_4", "mult_5", "mult_6", "mult_7"};
  Int_t markerstyle[8] = {20, 21, 22, 23, 24, 25, 26, 27};
  Int_t markersize[8] = {1, 1, 1, 1, 1, 1, 1, 1};
  double Jetty[7] = {
      0.68875, 0.61395, 0.55805, 0.53135,
      0.51455, 0.50265, 0.49125}; // min bias is not included here
  double Isotropic[7] = {0.86455, 0.83045, 0.80005, 0.78425,
                         0.77465, 0.76845, 0.76255};
  int sphero1[7] = {46, 26, 18, 13, 9, 7, 3};
  int sphero2[7] = {242, 46, 26, 18, 13, 9, 7};
  long counter1[8] = {0};
  long counter2[8] = {0};
  long counter3[8] = {0};
  long counter4[8] = {0};
  long counter5[8] = {0};
  long counter6[8] = {0};

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

  TLorentzVector *vec = new TLorentzVector();

  const long long nevents = (long long)theTree->GetEntries();
  cout << nevents << endl;
  //  int nevents = 1000000;
  // cout<<"Total number of events: "<<nevents<<endl;

  for (long long i = 0; i < nevents; i++) {
    theTree->GetEntry(i);
    if (etamultpoint8S0 < 10)
      continue;
    // if(V0MMult<50) continue;
    for (int m = 0; m < 7; m++) {
      if ((FT0 < sphero2[m]) && (FT0 >= sphero1[m])) {
        if ((sp < Jetty[m]) && (sp >= 0)) {
          for (int j = 0; j < ntrack; j++) {
            vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                (tag[j] == 1)) {
              h_pj[m]->Fill(vec->Pt());
              counter1[m]++;
            }

            //  if(abs(vec->Rapidity())<0.5 && vec->Pt()>0.15 && (tag[j]==1) &&
            //  (sp>0.855)) hD0p2->Fill(vec->Pt());
            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                (tag[j] == 2)) {
              h_npj[m]->Fill(vec->Pt());
              counter2[m]++;
              vec->Clear();
            }
          }
          // track loop ends
        }

        // cout<<"spherocity"<<sp<<"\t "<<FT0<<endl;

        if ((sp > Isotropic[m]) && (sp <= 1)) {

          //  cout<<"spherocity"<<sp<<"\t "<<FT0<<endl;
          for (int l = 0; l < ntrack; l++) {
            vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);

            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                (tag[l] == 1)) {
              h_pi[m]->Fill(vec->Pt());
              counter3[m]++;
            }

            if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                (tag[l] == 2)) {
              h_npi[m]->Fill(vec->Pt());
              counter4[m]++;
              vec->Clear();
            }
          } // track loop ends
        }

        if (sp >= 0) {
          {
            for (int l = 0; l < ntrack; l++) {
              vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[l] == 1)) {
                h_m_p[m]->Fill(vec->Pt());
                counter5[m]++;
              }

              if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 &&
                  (tag[l] == 2)) {
                h_m_np[m]->Fill(vec->Pt());
                counter6[m]++;
                vec->Clear();
              }
            }
          }
        }
      }
    }

    if (FT0 > 0) {
      if ((sp < 0.55755) && (sp >= 0)) {
        for (int j = 0; j < ntrack; j++) {
          vec->SetPxPyPzE(px[j], py[j], pz[j], energy[j]);
          if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 1)) {
            h_pj[7]->Fill(vec->Pt());
            counter1[7]++;
          }

          //  if(abs(vec->Rapidity())<0.5 && vec->Pt()>0.15 && (tag[j]==1)
          //  && (sp>0.855)) hD0p2->Fill(vec->Pt());
          if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[j] == 2)) {
            h_npj[7]->Fill(vec->Pt());
            counter2[7]++;
            vec->Clear();
          }
        } // track loop ends
        // cout<<"spherocity"<<sp<<"\t "<<FT0<<endl;
      }

      if ((sp > 0.80685) && (sp <= 1.0)) {
        for (int l = 0; l < ntrack; l++) {
          vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);

          if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[l] == 1)) {
            h_pi[7]->Fill(vec->Pt());
            counter3[7]++;
          }

          if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[l] == 2)) {
            h_npi[7]->Fill(vec->Pt());
            counter4[7]++;
            vec->Clear();

          } // track loop ends
        }
      }

      if (sp >= 0) {
        for (int l = 0; l < ntrack; l++) {
          vec->SetPxPyPzE(px[l], py[l], pz[l], energy[l]);

          if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[l] == 1)) {
            h_m_p[7]->Fill(vec->Pt());
            counter5[7]++;
          }

          if (abs(vec->Rapidity()) < 0.5 && vec->Pt() > 0.15 && (tag[l] == 2)) {
            h_m_np[7]->Fill(vec->Pt());
            counter6[7]++;
            vec->Clear();

          } // track loop ends
        }
      }
    }
  }

  cout << "counter1(0) HM jetty:" << counter1[0] << endl; // HM jetty
  cout << "counter1(1):" << counter1[1] << endl;
  cout << "counter1(2):" << counter1[2] << endl;
  cout << "counter1(3):" << counter1[3] << endl;
  cout << "counter1(4):" << counter1[4] << endl;
  cout << "counter1(5):" << counter1[5] << endl;
  cout << "counter1(6) LM Jetty:" << counter1[6] << endl; // LM Jetty
  cout << "counter1(7) Min Bias Jetty:" << counter1[7]
       << endl;                                               // Min Bias Jetty
  cout << "counter2(0) HM Isotropic:" << counter2[0] << endl; // HM Isotropic
  cout << "counter2(1):" << counter2[1] << endl;
  cout << "counter2(2):" << counter2[2] << endl;
  cout << "counter2(3):" << counter2[3] << endl;
  cout << "counter2(4):" << counter2[4] << endl;
  cout << "counter2(5):" << counter2[5] << endl;
  cout << "counter2(6) LM Isotropic:" << counter2[6] << endl; // LM Isotropic
  cout << "counter2(7) Min Bias Iso:" << counter2[7] << endl; // Min Bias Iso
  TH1D *h_jr[8];
  TH1D *h_ir[8];
  TH1D *h_intr[8];

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
      h_m_p[k]->SetBinContent(bin, h_m_p[k]->GetBinContent(bin) /
                                       h_m_p[k]->GetBinWidth(bin));
      h_m_np[k]->SetBinContent(bin, h_m_np[k]->GetBinContent(bin) /
                                        h_m_np[k]->GetBinWidth(bin));
    }
  }

  for (int q = 0; q < 8; q++) {
    h_pj[q]->Scale(1.0 / (counter1[q] * 1.0));  // jetty pro
    h_npj[q]->Scale(1.0 / (counter2[q] * 1.0)); // iso pro
    h_pi[q]->Scale(1.0 / (counter3[q] * 1.0));  // jetty nonpro
    h_npi[q]->Scale(1.0 / (counter4[q] * 1.0)); // iso nonpro
    h_m_p[q]->Scale(1.0 / (counter5[q] * 1.0));
    h_m_np[q]->Scale(1.0 / (counter6[q] * 1.0));
    // here delta y (rapidity) is 1, which is why division is done by 1 and 0.35
    // is the uniform bin width
  }

  TH1D *h_cpj[8];
  TH1D *h_cnpj[8];
  TH1D *h_cpi[8];
  TH1D *h_cnpi[8];
  // Error propagation in histogram(xvalue)

  for (int q = 0; q < 8; q++) {
    h_cpj[q] = (TH1D *)h_pj[q]->Clone();
    h_cpj[q]->Divide(h_m_p[q]);
    h_cnpj[q] = (TH1D *)h_npj[q]->Clone();
    h_cnpj[q]->Divide(h_m_np[q]);
    h_cpi[q] = (TH1D *)h_pi[q]->Clone();
    h_cpi[q]->Divide(h_m_p[q]);
    h_cnpi[q] = (TH1D *)h_npi[q]->Clone();
    h_cnpi[q]->Divide(h_m_np[q]);
  }

  TFile *f1 = new TFile("D0_Rpp.root",
                        "recreate"); //------- Name Change
  for (int r = 0; r < 8; r++) {
    h_cpj[r]->Write(Form("prompt_J_%s", mult[r]));
    h_cnpj[r]->Write(Form("nonprompt_J_%s", mult[r]));
    h_cpi[r]->Write(Form("prompt_I_%s", mult[r]));
    h_cnpi[r]->Write(Form("nonprompt_I_%s", mult[r]));
  }
  f1->Close();
}