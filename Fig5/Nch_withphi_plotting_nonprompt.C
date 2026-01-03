void SetStyle(Bool_t graypalette = kTRUE);

void sethisto(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->SetTitle("p_{T}[GeV/c]");
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(505);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.05);
  r1__1->GetXaxis()->SetTickLength(0.03);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetTitle("#frac{1}{2#piN_{eV}} #frac{d^{2}N}{dy dp_{T}}
  // [(GeV/c)^{-1}]");
  r1__1->GetYaxis()->SetNdivisions(510);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.05);
  r1__1->GetYaxis()->SetTitleSize(0.05);
  r1__1->GetYaxis()->SetTickLength(0.03);
  r1__1->GetYaxis()->SetTitleOffset(1.);
  r1__1->GetYaxis()->SetTitleFont(42);
  r1__1->GetZaxis()->SetLabelFont(42);
  r1__1->GetZaxis()->SetLabelSize(0.06);
  r1__1->GetZaxis()->SetTitleSize(0.06);
  r1__1->GetZaxis()->SetTitleOffset(1);
  r1__1->GetZaxis()->SetTitleFont(42);
  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);
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
  leg1->SetBorderSize(1);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(1);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
}

void Nch_withphi_plotting_nonprompt() {
  gStyle->SetOptStat(0);
  // gPad->SetTicks();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetPalette(kRainBow);
  TFile *f1 = new TFile("SN_pTD0lead_CRon_MPIon_plot.root");
  TFile *f2 = new TFile("SN_pTD0lead_CRon_MPIoff_plot.root");
  TCanvas *c = new TCanvas("c", "", 800, 600);
  setpad(c);

  // c->SetLogy();
  // c->Draw();
  TH1D *h1a[3];
  TH1D *h2a[3];
  TH1D *h1b[3];
  TH1D *h2b[3];
  TString partname1[3] = {"towardp_ptlead", "transp_ptlead", "awayp_ptlead"}; // MPI on    Prompt
  TString partname2[3] = {"towardp_ptlead", "transp_ptlead", "awayp_ptlead"}; // MPI off    Prompt

  TString partname3[3] = {"towardnp_ptlead", "transnp_ptlead", "awaynp_ptlead"};// MPI on   NonPrompt
  TString partname4[3] = {"towardnp_ptlead", "transnp_ptlead", "awaynp_ptlead"};// MPI off  NonPrompt

  // TString partID[3] = {"nonprompt_to", "nonprompt_trans", "nonprompt_away"};
  Int_t color[3] = {kRed + 2, kGreen + 2, kBlue + 2};
  Int_t markerstyle1[3] = {20, 21, 22};
  Int_t markerstyle2[3] = {24, 25, 26};
  Double_t markersize[3] = {1.5, 1.5, 1.5};
  Int_t linestyle[3] = {2, 7, 9};

  TLegend *legend;
  TLegend *legend1;

  TH2D *h2 = new TH2D("h2", "", 100, 0.1, 24.0, 100, 0.65, 3.5);
  sethisto(h2);
  h2->GetYaxis()->SetTitle("dN_{ch}/d#eta/#LTdN_{ch}/d#eta#GT(|#eta|<0.8)");
  h2->GetXaxis()->SetTitle("p_{T}^{D^{0}-lead} (GeV/#it{c})");

  h2->Draw();

  for (int i = 0; i < 3; i++) {
    // h[i] = (TH1D *)file->Get(Form("%s", partname[i]));
    h2a[i] = (TH1D *)f1->Get(partname3[i]);
    h2a[i]->SetMarkerColor(color[i]);
    h2a[i]->SetLineColor(color[i]);
    h2a[i]->SetMarkerStyle(markerstyle1[i]);
    h2a[i]->SetMarkerSize(markersize[i]);
    // h2a[i]->Draw("pesame");
  }

  for (int i = 0; i < 3; i++) {
    h2a[i]->Draw("pesame");
  }

  for (int j = 0; j < 3; j++) {
    // h[i] = (TH1D *)file->Get(Form("%s", partname[i]));
    h2b[j] = (TH1D *)f2->Get(partname4[j]);
    h2b[j]->SetMarkerColor(color[j]);
     h2b[j]->SetLineColor(color[j]);
    h2b[j]->SetMarkerStyle(markerstyle2[j]);
    h2b[j]->SetMarkerSize(markersize[j]);
    // h2b[j]->Draw("pesame");
  }

  for (int i = 0; i < 3; i++) {
    h2b[i]->Draw("pesame");
  }
  legend1 = new TLegend(0.236842, 0.556424, 0.542607, 0.690104, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend1);

  legend1->AddEntry(h2a[0], " ", "lp");
  legend1->AddEntry(h2b[0], " ", "lp");
  legend1->AddEntry(h2a[1], " ", "lp");
  legend1->AddEntry(h2b[1], " ", "lp");
  legend1->AddEntry(h2a[2], " ", "lp");
  legend1->AddEntry(h2b[2], " ", "lp");

  legend1->SetTextSize(0.05);
  legend1->SetNColumns(2);
  legend1->SetBorderSize(0);

  legend1->Draw();
  TLegend *legend2 =
      new TLegend(0.45614, 0.555556, 0.56391, 0.690972, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend2);

  legend2->AddEntry((TObject *)0, "Toward", "");

  legend2->AddEntry((TObject *)0, "Transverse", "");

  legend2->AddEntry((TObject *)0, "Away", "");

  legend2->SetTextSize(0.05);
  legend2->SetNColumns(1);
  legend2->SetBorderSize(0);

  legend2->Draw();
  legend = new TLegend(0.16792, 0.697917, 0.444862, 0.777778, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend);
  legend->AddEntry((TObject *)0, "MPI on", "");
  legend->AddEntry((TObject *)0, "MPI off", "");
  legend->SetTextSize(0.05);
  legend->SetNColumns(2);
  legend->SetBorderSize(0);

  legend->Draw();

  TLegend *pt =
      new TLegend(0.1817043, 0.7864583, 0.3258145, 0.8854167, NULL, "brNDC");
  setlegendstyle(pt);
  //    pt->SetFillColor(0);
  pt->SetTextSize(0.05);
  pt->AddEntry("", "Non-prompt D^{0}-lead", "");
  //    pt->SetBorderSize(0);
  pt->Draw("same");

  c->SaveAs("MPIoffon_diffphi_nonprompt.pdf");
}

void SetStyle(Bool_t graypalette) {
  // cout << "Setting style!" << endl;

  gStyle->Reset("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  if (graypalette)
    gStyle->SetPalette(8, 0);
  else
    gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.3);
  gStyle->SetPadBottomMargin(0.35);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetNdivisions(505, "y");
  gStyle->SetNdivisions(510, "x");

  gStyle->SetHistLineWidth(1);
  // gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  // gStyle->SetFuncColor(kBlack);
  gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.06, "xyz");
  gStyle->SetLabelOffset(0.01, "y");
  gStyle->SetLabelOffset(0.01, "x");
  gStyle->SetLabelColor(kBlack, "xyz");
  gStyle->SetTitleSize(0.06, "xyz");
  gStyle->SetTitleOffset(1.1, "y");
  gStyle->SetTitleOffset(1.1, "x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  gStyle->SetTickLength(0.04, "X");
  gStyle->SetTickLength(0.02, "Y");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
}