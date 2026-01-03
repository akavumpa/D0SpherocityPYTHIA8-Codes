
void sethisto1(TH2D *r1__1) {
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

void sethisto2(TH2D *r1__1) {
  r1__1->SetStats(0);
  r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(505);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.13);
  r1__1->GetXaxis()->SetTitleSize(0.14);
  r1__1->GetXaxis()->SetTickLength(0.07);
  r1__1->GetXaxis()->SetTitleOffset(0.);
  r1__1->GetXaxis()->SetTitleFont(42);

  r1__1->GetYaxis()->CenterTitle(true);
  r1__1->GetYaxis()->SetNdivisions(505);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.13);
  r1__1->GetYaxis()->SetTitleSize(0.14);
  r1__1->GetYaxis()->SetTickLength(0.03);
  r1__1->GetYaxis()->SetTitleOffset(0.5);
  r1__1->GetYaxis()->SetTitleFont(42);
  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);

  r1__1->Draw("");
}

void setpad(TPad *c_1) {
  //   c_1->Draw();
  //   c_1->cd();
  c_1->SetFillColor(0);
  c_1->SetBorderMode(0);
  //   c_1->SetBorderSize(1);
  c_1->SetTickx(1);
  c_1->SetTicky(1);
  //   c_1->SetLeftMargin(0.14);
  // c_1->SetBottomMargin(0.13);
  //   c_1->SetTopMargin(0.04);
  //   c_1->SetRightMargin(0.03);

  c_1->SetFrameBorderMode(0);
  //   c_1->SetFrameLineWidth(2);
}

void setlegendstyle(TLegend *leg1) {
  //   leg1->SetBorderSize(1);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(1);
  //   leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
}

void fBCRoffHM() {

  TFile *file = new TFile("BfracD0_CRoff.root");
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
  // c->SetLogy();

  // Draw TPads

  TH2D *hframe1 = new TH2D("", ";p_{T} (GeV/c);f_{non-prompt}", 100, 0.5, 24.5,
                           100, 0.0, 0.35);

  sethisto1(hframe1);

  c->Draw();

  hframe1->Draw();

  TH1F *h1a[6];
  TH1F *h1b[3];
  TH1F *h2a[5];
  TH1F *h2b[3];

  TString partname1[6] = {"ratio_J_mult_7",   "ratio_I_mult_7",
                          "ratio_int_mult_7", "ratio_J_mult_0",
                          "ratio_I_mult_0",   "ratio_int_mult_0"};

  Int_t color[6] = {kGreen + 1, kMagenta, kBlue, kGreen + 1, kMagenta, kBlue};
  Int_t markerstyle1[6] = {20, 21, 22, 20, 21, 22};
  //  Int_t markerstyle2[6] = {26, 25,27};
  Double_t markersize[6] = {1.7, 1.7, 1.7, 1.7, 1.7, 1.7};

  for (int i = 0; i < 6; i++) {
    h1a[i] = (TH1F *)file->Get(partname1[i]);
    h1a[i]->SetMarkerColor(color[i]);
    h1a[i]->SetLineColor(color[i]);
    h1a[i]->SetMarkerStyle(markerstyle1[i]);
    h1a[i]->SetMarkerSize(markersize[i]);
  }

  for (int j = 3; j < 6; j++) {

    h1a[j]->Draw("pesame");
  }

  TLegend *legend2 =
      new TLegend(0.135, 0.7646, 0.409091, 0.88474, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend2);
  legend2->AddEntry((TObject *)0, "CR off", "");
  legend2->SetTextSize(0.05);
  legend2->SetNColumns(1);
  legend2->SetBorderSize(0);
  legend2->Draw();
  // Update canvas to reflect changes
  // c->Update();

  c->SaveAs("pTsratio_HM_CRoff.pdf");
}
