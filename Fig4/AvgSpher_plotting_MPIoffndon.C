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

void AvgSpher_plotting_MPIoffndon() {
  gStyle->SetOptStat(0);
  // gPad->SetTicks();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetPalette(kRainBow);
  TFile *f1 = new TFile("AvgS0_pTD0lead_CRon_MPIon_plot.root");
  TFile *f2 = new TFile("AvgS0_pTD0lead_CRon_MPIoff_plot.root");
  TCanvas *c = new TCanvas("c", "c", 750, 600);
  setpad(c);
  // c->SetLogy();
  c->Draw();
  TLegend *legend;
  TLegend *legend1;

  TH2D *h2 = new TH2D("h2", "", 100, 0, 24.0, 100, 0.0, 1.0);
  sethisto(h2);
  h2->GetYaxis()->SetTitle("#LTS_{0}#GT");
  h2->GetXaxis()->SetTitle("p_{T}^{D^{0}-lead} (GeV/#it{c})");

  TH1D *h[4];
  // const Char_t partname[9][8] = {"Ds", "Dp", "DZero","lambc", "Jsi"};

  TString partname[4] = {"Spherop", "Spheronp", "Spherop", "Spheronp"};

  // TString partID1[5]= {"D_{s}", "D^{#pm}", "D^{0}", "#Lambda_{c}", "J/#psi"};
  Int_t color[4] = {kAzure + 2, kMagenta + 1, kAzure + 2, kMagenta + 2};
  Int_t markerstyle[4] = {20, 21, 24, 25};
  Double_t markersize[4] = {1.8, 1.8, 1.8, 1.8};

  h2->Draw();
  h[0] = (TH1D *)f1->Get(partname[0]);
  h[1] = (TH1D *)f1->Get(partname[1]);
  h[2] = (TH1D *)f2->Get(partname[2]);
  h[3] = (TH1D *)f2->Get(partname[3]);
  for (int i = 0; i < 4; i++) {
    // h[i] = (TH1D *)file->Get(Form("%s", partname[i]));

    h[i]->SetMarkerColor(color[i]);
    h[i]->SetLineColor(color[i]);
    h[i]->SetMarkerStyle(markerstyle[i]);
    h[i]->SetMarkerSize(markersize[i]);
    h[i]->Draw("pesame");
  }
  legend1 = new TLegend(0.196524, 0.269097, 0.426471, 0.348958, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend1);

  legend1->AddEntry((TObject *)0, "MPI on", "");
  legend1->AddEntry((TObject *)0, "MPI off", "");
  legend1->AddEntry((TObject *)0, "", "");
  legend1->AddEntry((TObject *)0, "", "");
  legend1->SetTextSize(0.04);
  legend1->SetNColumns(2);
  legend1->SetBorderSize(0);

  legend1->Draw();

  legend = new TLegend(0.256684, 0.201389, 0.93984, 0.300347, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend);

  legend->AddEntry(h[0], " ", "lp");
  legend->AddEntry(h[2], " ", "lp");
  legend->AddEntry((TObject *)0, "Prompt", "");

  legend->AddEntry(h[1], " ", "lp");
  legend->AddEntry(h[3], " ", "lp");
  legend->AddEntry((TObject *)0, "Non-prompt", "");

  legend->SetTextSize(0.04);
  legend->SetNColumns(3);
  legend->SetBorderSize(0);

  legend->Draw();

  TLegend *pt =
      new TLegend(0.209893, 0.8020833, 0.3529412, 0.9010417, NULL, "brNDC");
  setlegendstyle(pt);
  //    pt->SetFillColor(0);

  pt->AddEntry("", "pp, #sqrt{s} = 13.6 TeV, PYTHIA8", "");
  //    pt->AddEntry("","Minimum Bias","");
  //    pt->SetBorderSize(0);
  pt->SetTextSize(0.045);
  pt->Draw("same");

  c->SaveAs("D0MPIonoffavgsphero.pdf");
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