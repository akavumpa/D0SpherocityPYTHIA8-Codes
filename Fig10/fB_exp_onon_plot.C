
void sethisto(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(510);
  r1__1->GetXaxis()->SetLabelOffset(0.005);
  r1__1->GetXaxis()->SetLabelSize(0.045);
  r1__1->GetXaxis()->SetTitleSize(0.05);
  r1__1->GetXaxis()->SetTickLength(0.03);
  r1__1->GetXaxis()->SetTitleOffset(0.97);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->CenterTitle(true);
  r1__1->GetYaxis()->SetNdivisions(507);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.005);
  r1__1->GetYaxis()->SetLabelSize(0.045);
  r1__1->GetYaxis()->SetTitleSize(0.06);
  r1__1->GetYaxis()->SetTickLength(0.02);
  r1__1->GetYaxis()->SetTitleOffset(0.99);
  r1__1->GetYaxis()->SetTitleFont(42);
  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);

  r1__1->Draw("");
}
void sethistodown(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->SetTitle("p_{T}[GeV/c]");
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(512);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.05);
  r1__1->GetXaxis()->SetTickLength(0.04);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetTitle("#frac{1}{2#piN_{eV}} #frac{d^{2}N}{dy dp_{T}}
  // [(GeV/c)^{-1}]");
  r1__1->GetYaxis()->SetNdivisions(507);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.07);
  r1__1->GetYaxis()->SetTitleSize(0.075);
  r1__1->GetYaxis()->SetTickLength(0.025);
  r1__1->GetYaxis()->SetTitleOffset(0.88);
  r1__1->GetYaxis()->SetTitleFont(42);
  r1__1->Draw("");
}
void setpad(TPad *c_1) {
  c_1->Draw();
  c_1->cd();
  //   c_1->Range(-0.427002,-0.01611993,4.141898,0.06259125);
  c_1->SetFillColor(0);
  c_1->SetBorderMode(0);
  c_1->SetBorderSize(1);
  c_1->SetTickx(1);
  c_1->SetTicky(1);
  c_1->SetLeftMargin(0.1296791);
  c_1->SetBottomMargin(0.13);
  c_1->SetTopMargin(0.04);
  c_1->SetRightMargin(0.03);
  c_1->SetFrameBorderMode(0);
  c_1->SetFrameLineWidth(1);
  c_1->SetFrameBorderMode(0);
}
void setlegendstyle(TLegend *leg1) {
  //   leg1->SetBorderSize(1);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(1);
  //   leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
}

void fB_exp_onon_plot() {

  TFile *file = new TFile("fB_MB_CRon_MPIon.root"); // PYTHIA
  // TFile *f1 = new TFile("D0_Rpp.root");

  TCanvas *c = new TCanvas("c", "", 116, 156, 750, 640);
  c->Range(-2.801391, -1.704977, 24.94513, 0.02075342);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  //  c->SetLogy();
  c->SetLeftMargin(0.122984);
  c->SetRightMargin(0.01604278);
  c->SetTopMargin(0.06818182);
  c->SetBottomMargin(0.123);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  // setpad(c);

  // Draw TPads

  TH2D *hframe1 = new TH2D("", ";p_{T} (GeV/#it{c});f_{non-prompt}", 100, 0.0,
                           24.5, 1000, 0.01, 0.20);
  sethisto(hframe1);
  TH1D *h1a;

  Double_t x[14] = {0.517, 1.3, 1.8, 2.27, 2.75, 3.26, 3.77,
                    4.52,  5.5, 6.5, 7.5,  10.0, 14.0, 20.0};
  Double_t y1[14] = {0.05,  0.051, 0.05,  0.056, 0.055, 0.06,  0.056,
                     0.065, 0.067, 0.071, 0.075, 0.088, 0.097, 0.13};
  Double_t y1er[14] = {0.0032, 0.0027,  0.0016, 0.0017,  0.00155,
                       0.0021, 0.00226, 0.002,  0.00344, 0.0046435,
                       0.0065, 0.0061,  0.0105, 0.0187};

  Double_t x1sys[14] = {0.2310, 0.2050, 0.2050, 0.2050, 0.2000, 0.2235, 0.2180,
                        0.2250, 0.2180, 0.2180, 0.2180, 0.2260, 0.2050, 0.2350};
  // Double_t xsys[14];
  Double_t y1sys[14] = {0.00917, 0.00720, 0.00535, 0.00565, 0.00551,
                        0.00628, 0.00610, 0.00765, 0.01210, 0.012715,
                        0.01340, 0.01570, 0.01720, 0.02300};
  // Double_t ysys[14];

  Double_t y2[14];
  Double_t x2er[14];
  Double_t y2er[14];

  TString partname1[1] = {"ratio_MB"};

  Int_t color[4] = {kGray + 2, kGreen + 1, kGreen + 1, kGreen + 2};
  Int_t markerstyle1[4] = {20, 24, 21, 25};
  //  Int_t markerstyle2[4] = {24, 25,27};
  Double_t markersize[4] = {1.8, 1.8, 1.8, 1.8};

  c->Draw();
  h1a = (TH1D *)file->Get(partname1[0]);
  // h1a->Draw("pesame");
  for (int j = 0; j < 14; j++) {
    x2er[j] = {h1a->GetBinWidth(j + 1) / 2};
    y2[j] = h1a->GetBinContent(j + 1);
    y2er[j] = {h1a->GetBinError(j + 1)};
  }
  TGraphErrors *gdatasyst = new TGraphErrors(14, x, y1, x1sys, y1sys);
  TGraphErrors *gdatastat = new TGraphErrors(14, x, y1, x2er, y1er);

  gdatasyst->SetFillStyle(0); // hollow boxes
  gdatasyst->SetFillColor(0);
  gdatasyst->SetLineWidth(2);
  gdatasyst->SetLineColor(kBlack);

  gdatastat->SetMarkerColor(kBlack);
  gdatastat->SetLineColor(kBlack);
  gdatastat->SetMarkerStyle(markerstyle1[0]);
  gdatastat->SetMarkerSize(markersize[0]);

  h1a->SetMarkerColor(kRed + 2);
  h1a->SetLineColor(kRed + 2);
  h1a->SetMarkerStyle(markerstyle1[0]);
  h1a->SetMarkerSize(markersize[0]);

  gdatasyst->Draw("E2same");
  gdatastat->Draw("PE1same");
  h1a->Draw("pesame");

  TLegend *pt = new TLegend(0.149, 0.6793035, 0.656417, 0.8257, NULL, "brNDC");

  pt->SetHeader("pp, #sqrt{s} = 13.6 TeV, |y|<0.5");
  pt->AddEntry((TObject *)0, "Minimum Bias", "");

  // pt->AddEntry()
  pt->SetTextSize(0.05);
  pt->SetFillColor(0);
  pt->SetNColumns(1);
  // pt->AddText("|y|<0.5");
  pt->SetBorderSize(0);
  pt->Draw("same");
  TLegend *legend =
      new TLegend(0.5688, 0.16717, 0.815508, 0.343297, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend);
  legend->AddEntry(gdatastat, "ALICE (INEL>0)", "lp");
  legend->AddEntry(h1a, "PYTHIA8", "lp");

  legend->SetTextSize(0.045);
  legend->SetNColumns(1);
  legend->SetBorderSize(0);
  legend->Draw("same");

  legend->Draw();

  // Update canvas to reflect changes
  // c->Update();
  c->SaveAs("fB_MBCRonMPIon.pdf");
}
